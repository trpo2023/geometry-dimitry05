#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_1 "Error reading from file\n"
#define ERROR_2 "Enter the object\n"
#define ERROR_3 "Expected '('\n"
#define ERROR_4 "Object data is expected to be entered\n"
#define ERROR_5 "Enter the data\n"
#define ERROR_6 "Introduced '%s' expected 'circle', 'triangle' or 'polygon'\n"
#define ERROR_7 "Expected '<double>'\n"
#define ERROR_8 "Too many variables were passed\n"
#define ERROR_9 "Expected ','\n"
#define ERROR_10 "Expected ')'\n"
#define ERROR_11 "Unexpected token\n"
#define ERROR_12 "The radius cannot be negative\n"

int check_object(char* str, char* str_O, int* o)
{
    int i = 0, n = strlen(str), k = 0, m = 0;
    char c = str[i];

    while (c != '(' && i != n) {
        c = str[i];
        if (c != ' ' && c != '(') {
            if (k == 1) {
                puts(str);
                str_O[m] = '\0';
                printf(ERROR_6, str_O);
                return -1;
            }
            str_O[m] = str[i];
            m++;
        }
        if (m != 0 && c == ' ')
            k = 1;

        i++;
    }
    if (c == '(' && i == n)
        return 4;
    if (i == 0)
        return 2;
    if (i == n)
        return 3;
    str_O[m] = '\0';
    *o = i;
    for (i = 0; i < m + 1; i++) {
        int c = str_O[i];
        c = tolower(c);
        str_O[i] = c;
    }
    if (strcmp(str_O, "circle") == 0)
        return 101;
    if (strcmp(str_O, "triangle") == 0)
        return 102;
    if (strcmp(str_O, "polygon") == 0)
        return 103;
    puts(str);
    printf(ERROR_6, str_O);
    return -1;
}

int check_circle(char* str, int k, char* str_D)
{
    int v = 0, m = 0, l = 0, g, n = strlen(str);
    char c = str[k], q = ',', w = ')', h;
    for (int j = 0; j < 2; j++) {
        if (j == 0) {
            h = q;
            g = 2;
        }
        if (j == 1) {
            v = 0;
            h = w;
            g = 1;
            k++;
            l = 0;
            c = str[k];
        }
        while (c != h && k != n) {
            if (isdigit(c) != 0 && v < g) {
                str_D[m] = str[k];
                m++;
            }
            if (isdigit(c) != 0 && v == g) {
                puts(str);
                for (int i = 0; i < k; i++) {
                    printf(" ");
                }
                printf("^\n");
                printf(ERROR_8);
                return -1;
            }
            if (isdigit(c) == 0 && v < g) {
                if (c == '-') {
                }
                if (c == '.') {
                    if (l > 0) {
                        puts(str);
                        for (int i = 0; i < k; i++) {
                            printf(" ");
                        }
                        printf("^\n");
                        printf(ERROR_7);
                        return -1;
                    }
                    if (l == 0 && isdigit(str[k - 1]) != 0) {
                        str_D[m] = str[k];
                        m++;
                        l++;
                    }
                    if (l == 0 && isdigit(str[k - 1]) == 0) {
                        puts(str);
                        for (int i = 0; i < k; i++) {
                            printf(" ");
                        }
                        printf("^\n");
                        printf(ERROR_7);
                        return -1;
                    }
                }
                if (c == ' ') {
                    l = 0;
                    if (str[k - 1] != ' ' && str[k - 1] != '('
                        && str[k - 1] != ',')
                        v++;
                }
            }
            if (isdigit(c) == 0 && c != ' ' && c != '.') {
                if (c == '-' && isdigit(str[k + 1]) != 0 && g == 2) {
                    str_D[m] = str[k];
                    m++;
                } else {
                    if (g == 1 && c == '-' && isdigit(str[k + 1]) != 0) {
                        puts(str);
                        for (int i = 0; i < k; i++) {
                            printf(" ");
                        }
                        printf("^\n");
                        printf(ERROR_12);
                        return -1;
                    }
                    if (isdigit(str[k - 1]) != 0 || isdigit(str[k + 1]) != 0
                        || v < g) {
                        puts(str);
                        for (int i = 0; i < k; i++) {
                            printf(" ");
                        }
                        printf("^\n");
                        printf(ERROR_7);
                        return -1;
                    }
                    if (v == g) {
                        puts(str);
                        for (int i = 0; i < k; i++) {
                            printf(" ");
                        }
                        printf("^\n");
                        if (g == 2)
                            printf(ERROR_9);
                        if (g == 1)
                            printf(ERROR_10);
                        return -1;
                    }
                }
            }
            k++;
            c = str[k];
        }
    }
    k++;
    if (k < n - 1) {
        while (k != n + 1) {
            c = str[k];
            if (isgraph(c)) {
                puts(str);
                for (int i = 0; i < k; i++) {
                    printf(" ");
                }
                printf("^\n");
                printf(ERROR_11);
                return -1;
            }
            k++;
        }
    }
    return 0;
}

int check_triangle(char* str, int k, char* str_D)
{
    return 0;
}

int check_polygon(char* str, int k, char* str_D)
{
    return 0;
}

int check(char* str)
{
    char* str_O = malloc(100 * sizeof(char));
    int k;
    int n = check_object(str, str_O, &k);
    free(str_O);
    char* str_D = malloc(100 * sizeof(char));
    if (n == 101) {
        n = check_circle(str, k, str_D);
    }
    if (n == 102) {
        n = check_triangle(str, k, str_D);
    }
    if (n == 103) {
        n = check_polygon(str, k, str_D);
    }
    return n;
}

int check_and_output(FILE* file)
{
    int n = 1000, v = 0;
    char *str1, *str = malloc(n * sizeof(char));
    while (1) {
        str1 = fgets(str, n, file);
        if (str1 == NULL) {
            if (feof(file) != 0) {
                if (v == 0) {
                    printf(ERROR_5);
                    return -1;
                }
                return 0;
            } else {
                printf("\n");
                printf(ERROR_1);
                return -1;
            }
        }
        int err = check(str);
        int n = strlen(str);
        if (str[n - 1] == '\n')
            str[n - 1] = '\0';
        if (err == 2) {
            puts(str);
            printf("^\n");
            printf(ERROR_2);
            return -1;
        }
        if (err == 3) {
            puts(str);
            char c = ' ';
            for (int i = 0; i < strlen(str); i++)
                printf("%c", c);
            printf("^\n");
            printf(ERROR_3);
            return -1;
        }
        if (err == 4) {
            puts(str);
            char c = ' ';
            for (int i = 0; i < strlen(str); i++)
                printf("%c", c);
            printf("^\n");
            printf(ERROR_4);
            return -1;
        }
        if (err == -1)
            return -1;
        puts(str);
        v++;
    }
    free(str);
}

int main()
{
    FILE* file = fopen("geometry_test", "r");
    int Error = check_and_output(file);

    if (Error == 0)
        return 0;
    if (Error == -1)
        return -1;
}
