
#include <stdio.h>
#include "../prog1lib/lib/base.h"
#include <math.h>


typedef struct statistics_s {

    // todo

    double avg_age;
    double std_age;
    double avg_time_mouse;
    double avg_time_touch;
    double avg_time_keyboard;
} Statistics;

Statistics make_statistics() {

    // todo

    Statistics s = { 0.0, 0.0, 0.0, 0.0, 0.0};
    return s;
}

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

void print_statistics(Statistics s) {

    // todo

    printf("Average age: %.2f years\n", s.avg_age);
    printf("Standard age deviation: %.2f years\n", s.std_age);
    printf("Average time of mouse: %.2f s\n", s.avg_time_mouse);
    printf("Average time of touchscreen: %.2f s\n", s.avg_time_touch);
    printf("Average time of keyboard: %.2f s\n", s.avg_time_keyboard);
}

Statistics compute_statistics(String table) {

    // todo

 Statistics stats = make_statistics();

    int n = s_length(table);
    int i = 0;

    while (i < n && s_get(table, i) != '\n') i++;
    if (i < n) i++; 

    int count_people = 0;
    double sum_age = 0.0;
    double sum_age_square = 0.0;
    double sum_mouse = 0.0, sum_touch = 0.0, sum_keyboard = 0.0;
    int count_mouse = 0, count_touch = 0, count_keyboard = 0;

    while (i < n) {
        int line_start = i;
        while (i < n && s_get(table, i) != '\n') i++;
        int line_end = i;

        String line = s_sub(table, line_start, line_end);

        int tab1 = 0;
        while (tab1 < s_length(line) && s_get(line, tab1) != '\t') tab1++;
        String s_age = s_sub(line, 0, tab1);
        tab1++;

        int tab2 = tab1;
        while (tab2 < s_length(line) && s_get(line, tab2) != '\t') tab2++;
        String s_device = s_sub(line, tab1, tab2);
        tab2++;

        String s_time = s_sub(line, tab2, s_length(line));

        int age = i_of_s(s_age);
        char device = s_get(s_device, 0);
        double time = d_of_s(s_time);

        sum_age += age;
        sum_age_square += age * age;
        count_people++;

        if (device == 'm') {
            sum_mouse += time;
            count_mouse++;
        } else if (device == 't') {
            sum_touch += time;
            count_touch++;
        } else if (device == 'k') {
            sum_keyboard += time;
            count_keyboard++;
        }

        if (i < n && s_get(table, i) == '\n') i++;

        free(line);
        free(s_age);
        free(s_device);
        free(s_time);
    }

    if (count_people > 0) stats.avg_age = sum_age / count_people;
    if (count_people > 0) stats.std_age = sqrt((sum_age_square / count_people) - (stats.avg_age * stats.avg_age));
    if (count_mouse > 0) stats.avg_time_mouse = sum_mouse / count_mouse;
    if (count_touch > 0) stats.avg_time_touch = sum_touch / count_touch;
    if (count_keyboard > 0) stats.avg_time_keyboard = sum_keyboard / count_keyboard;

    return stats;
}

int main(void) {
    String table = s_read_file("measurements.txt");
    Statistics statistics = compute_statistics(table);
    print_statistics(statistics);
    return 0;
    
        /* 
            Erwartete Ausgabe:
            Age (Mean):                     37.33 years
            Age (Std. Dev.):                11.14 years
            Mean Time (Mouse):              16.00 s
            Mean Time (Touchscreen):        12.86 s
            Mean Time (Keyboard):           22.40 s
        */
}