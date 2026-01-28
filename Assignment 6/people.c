/*
Compile: make people
Run: ./people
make people && ./people
*/

#include "../prog1lib/lib/base.h"

// Represents statistics of a people table.
struct Statistics {
	int mean_year;
	int number_males;
	int number_females;
	int number_diverse;
	double mean_height_males; // in m
	double mean_height_females; // in m
	double mean_height_diverse; // in m
	double mean_length_of_names;
};

typedef struct Statistics Statistics;


//Returns substring of s from character i to character j
String s_sub(String s, int i, int j) {
    require_not_null(s);
    int n = strlen(s);
    if (i < 0) i = 0;
    if (j > n) j = n;
    if (i >= j || i >= n || j <= 0) {
        char *a = xmalloc(1 * sizeof(char));
        a[0] = '\0';
        return a;
    }
    // assert i < j && i < n && j > 0
    n = j - i;
    char *a = xmalloc((n + 1) * sizeof(char));
    memcpy(a, s + i, n * sizeof(char));
    a[n] = '\0';
    return a;
}


Statistics make_statistics(void) {
	Statistics ps = { 0, 0, 0, 0, 0.0, 0.0, 0.0 };
	return ps;
}

void print_statistics(Statistics s) {
	printf("mean year: %d\n", s.mean_year);
	printf("number males: %d\n", s.number_males);
	printf("number females: %d\n", s.number_females);
	printf("number diverse: %d\n", s.number_diverse);
	printf("mean height males: %.2f m\n", s.mean_height_males);
	printf("mean height females: %.2f m\n", s.mean_height_females);
	printf("mean height diverse: %.2f m\n", s.mean_height_diverse);
	printf("mean length of names: %3.2f characters\n", s.mean_length_of_names);

}

Statistics compute_statistics(String table) {
    Statistics ps = make_statistics();

    int n = s_length(table);
    int i = 0;
	
    // Skip header line
    while (i < n && s_get(table, i) != '\n') i++;
    if (i < n) i++; // skip newline

    int people = 0;
    int sum_year = 0;
    double sum_height_m = 0.0, sum_height_f = 0.0, sum_height_d = 0.0;
    int count_m = 0, count_f = 0, count_d = 0;
    double sumOfNames = 0.0;

    while (i < n) {
        int line_start = i;
        while (i < n && s_get(table, i) != '\n') i++;
        int line_end = i;

        String line = s_sub(table, line_start, line_end); 
        
        int tab1 = 0;
        while (tab1 < s_length(line) && s_get(line, tab1) != '\t') tab1++;
        String s_year = s_sub(line, 0, tab1);
        tab1++; 

        int tab2 = tab1;
        while (tab2 < s_length(line) && s_get(line, tab2) != '\t') tab2++;
        String s_sex = s_sub(line, tab1, tab2);
        tab2++;

        int tab3 = tab2;
        while (tab3 < s_length(line) && s_get(line, tab3) != '\t') tab3++;
        String s_height = s_sub(line, tab2, tab3);
        tab3++;

        String s_name = s_sub(line, tab3, s_length(line));

        int year = i_of_s(s_year);
        char sex = s_get(s_sex, 0);
        double height = d_of_s(s_height);
        double nameLength = (double)s_length(s_name);

        sum_year += year;
        sumOfNames += nameLength;
        people++;

        if (sex == 'm') {
            count_m++;
            sum_height_m += height;
        } else if (sex == 'f') {
            count_f++;
            sum_height_f += height;
        } else if (sex == 'd') {
            count_d++;
            sum_height_d += height;
        }

        if (i < n && s_get(table, i) == '\n') i++;

        free(line);
        free(s_year);
        free(s_sex);
        free(s_height);
        free(s_name);
    }

    if (people > 0) ps.mean_year = ((sum_year) / people); else  ps.mean_year = 0;
	ps.number_males = count_m;
    ps.number_females = count_f;
    ps.number_diverse = count_d;
    if (count_m > 0) ps.mean_height_males = sum_height_m / count_m; else ps.mean_height_males = 0.0;
    if (count_f > 0) ps.mean_height_females = sum_height_f / count_f; else ps.mean_height_females = 0.0;
    if (count_d > 0) ps.mean_height_diverse = sum_height_d / count_d; else ps.mean_height_diverse = 0.0;
    if (people > 0) ps.mean_length_of_names = sumOfNames / people; else ps.mean_length_of_names = 0.0;

    return ps;
}


int main(void) {
	String table = s_read_file("people.txt");
	Statistics s = compute_statistics(table);
	print_statistics(s);
	
	/*
	Erwartete Ausgabe:
	
	mean year: 1974
	number males: 445
	number females: 455
	number diverse: 100
	mean height males: 1.79 m
	mean height females: 1.64 m
	mean height diverse: 1.71 m
	mean length of names: 11.88 characters
	*/
	
	return 0;
}
