/*
    Compile: make alignment
    Run: ./alignment
    make alignment && ./alignment
*/


#include <stdio.h>
#include "../prog1lib/lib/base.h"
#include <math.h>


// Exits the program if the failure condition is true. Reports the line number
// and the reason for the failure.
#define panic_if_exit(condition, ...) \
if (condition) {\
    fprintf(stderr, "%s:%d, %s: ", __FILE__, __LINE__, __func__);\
    fprintf(stderr, __VA_ARGS__);\
    fprintf(stderr, "\n");\
    exit(EXIT_FAILURE);\
}

// Str is shallow abstraction over C strings and C char arrays. Str allows keeping
// track of a starting point in memory, a length, and a capacity (0 <= length <=
// capacity). The explicit length allows dealing with parts of ('\0'-terminated) C
// strings.

// A Str points to some part of a C string, i.e., it does not have to end
// with '\0'. Instead, it has an explicit length and a buffer capacity.
typedef struct Str Str;
struct Str {
    char* s;
    int len;
    int cap;
};

// Creates a Str that points to a char array (e.g., a part of a C string).
Str make_str(char* s, int len) {
    require_not_null(s);
    require("length not negative", len >= 0);
    return (Str) {s, len, len};
}


// Dynamically allocates a buffer with a capacity of cap bytes.
Str new_str(int cap) {
    require("capacity not negative", cap >= 0);
    return (Str) {xmalloc(cap), 0, cap};
}

// Appends t to str. Fails if the result would not fit into str.
void append_str(Str* str, Str t) {
    require_not_null(str);
    int n = str->len + t.len;
    panic_if_exit(n > str->cap, "overflow");
    memcpy(str->s + str->len, t.s, t.len);
    str->len = n;
}

// Appends c to str. Fails if the result would not fit into str.
void append_char(Str* str, char c) {
    require_not_null(str);
    panic_if_exit(str->len >= str->cap, "overflow");
    str->s[str->len] = c;
    str->len++;
}


// Prints str.
void print_str(Str str) {
    printf("%.*s", str.len, str.s);
}

// Checks if str is equal to C-string t.
bool cstring_equal(Str str, char* t) {
    return strncmp(str.s, t, str.len) == 0 && t[str.len] == '\0';
}

// Reads the contents of a file into a Str. Exits if an error occurs.
Str read_file(char* name) {
    require_not_null(name);
    FILE *f = fopen(name, "rb"); 
    panic_if_exit(f == NULL, "cannot open %s", name);
    fseek (f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);
    char *s = xmalloc(size + 1);
    long size_read = fread(s, 1, size, f);
    panic_if_exit(feof(f) != 0 || size_read != size, "cannot read %s to end.\n", name); 
    s[size_read] = '\0';
    fclose(f);
    return make_str(s, size_read);
}

// Returns true if the end of the string is reached.
bool eos(char* s) {
    require_not_null(s);
    return *s == '\0';
}

// Forwards s to the first non-whitespace character.
char* skip_spaces(char* s) {
    require_not_null(s);
    while (isspace(*s)) s++;
    return s;
}

// Forwards s to the first character after the word.
char* skip_word(char* s) {
    require_not_null(s);
    while (!eos(s) && !isspace(*s)) s++;
    return s;
}

// Returns the number of words in s.
int count_words(char* s) {
    require_not_null(s);
    int n = 0;
    while (true) {
        s = skip_spaces(s);
        if (eos(s)) return n;
        // assert: s on first character of word
        n++;
        s = skip_word(s);
        // assert: s on first character after word (or at end of string)
        if (eos(s)) return n; 
    }
}

// Splits text into an array of words. Parameter words points to a Str-array of the
// given length. Returns the number of words that were actually set (depends on the
// number of words in text).
int split_words(/*in*/Str text, /*out*/Str* words, int words_length) {
    require_not_null(words);
    require("not negative", words_length >= 0);
    // TODO: b)

    char* p = text.s;
    int count = 0;

    while (count < words_length) {
        p = skip_spaces(p);

        if (eos(p)) break;

        char* word_start = p;

        p = skip_word(p);

        int word_len = (int)(p - word_start);
        words[count] = make_str(word_start, word_len);

        count++;
    }

    return count;
}


// Formats the words array (which contains words_length words), as space-separated,
// left-aligned text with linebreaks at the given width. The first word of a line
// will always be output, even if it is longer than width. Words are not split.
// There is always a single space (or a line break) between adjacent words. There
// are no spaces at the end of a line.
void words_align_left(/*out*/Str* dst, /*in*/Str* words, int words_length, int width) {
    require_not_null(dst);
    require_not_null(words);
    require("not negative", words_length >= 0);
    require("not negative", width >= 0);
    // TODO: c)
    if (words_length == 0) return;

    int current_line_width = 0;

    for (int i = 0; i < words_length; i++) {
        Str word = words[i];

        if (i > 0) {
            if (current_line_width + 1 + word.len <= width) {
                append_char(dst, ' ');
                current_line_width += 1;
            } else {
                append_char(dst, '\n');
                current_line_width = 0;
            }
        }

        append_str(dst, word);
        current_line_width += word.len;
    }
}

void print_bar(int width) {
    for (int i = 0; i < width; i++) putchar('-');
    putchar('\n');
}

void test(void) {
    Str text = read_file("mytext.txt");
    printsln(text.s);
    int n = count_words(text.s);
    printf("%d words\n", n);
    assert("correct number of words", n == 69);

    Str words[n];
    int m = split_words(text, words, n);
    assert("correct number of words", n == m);
    for (int i = 0; i < m; i++) {
        Str word = words[i];
        printf("%.*s|", word.len, word.s);
    }
    putchar('\n');
    test_equal_b(cstring_equal(words[0], "Lorem"), true);
    test_equal_b(cstring_equal(words[1], "ipsum"), true);
    test_equal_b(cstring_equal(words[2], "dolor"), true);

    int width = 40;

    int total_len = 0;
    for (int i = 0; i < n; i++) {
        total_len += words[i].len;
    }

    Str formatted_text = new_str(total_len * 2);
    words_align_left(&formatted_text, words, n, width);
    print_bar(width);
    print_str(formatted_text);
    print_bar(width);

}

int main(void) {
    test();
    return 0;
}

/*

gcc alignment.c ../prog1lib/lib/base.c -o x
 
./x
 
*/