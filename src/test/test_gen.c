#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BASH "test/test_cat.sh"
#define S21_CAT_OUT "test/test_s21_cat.txt"
#define CAT_OUT "test/test_cat.txt"

void *gen_foo()
{
    FILE *p1 = fopen(BASH, "w");
    // FILE *p2 = fopen(GREP, "w");
    char flags[5][3] = {"-e",
                        "-b",
                        "-n",
                        "-s",
                        "-t"};
    char files[3][11] = {"test/1.txt",
                         "test/2.txt",
                         "test/3.txt"};
    srand(time(NULL));
    for (int i = 0; i < 5; i++)
    {
        int n = rand() % 3;
        fprintf(p1, "echo \"/-/-/-/-/-/-/-cat %s %s-/-/-/-/-/-/-/-\" >> %s\n", flags[i], files[n], CAT_OUT);
        fprintf(p1, "cat %s %s >> %s\n", flags[i], files[n], CAT_OUT);
        fprintf(p1, "echo \"/-/-/-/-/-/-/-cat %s %s-/-/-/-/-/-/-/-\" >> %s\n", flags[i], files[n], S21_CAT_OUT);
        fprintf(p1, "cat/s21_cat %s %s >> %s\n", flags[i], files[n], S21_CAT_OUT);
    }
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 5; i++)
        {
            int n = rand() % 3;
            int k = rand() % 3;
            fprintf(p1, "echo \"/-/-/-/-/-/-/-cat %s %s %s %s-/-/-/-/-/-/-/-\" >> %s\n",
                    flags[i], flags[j], files[n], files[k], CAT_OUT);
            fprintf(p1, "cat %s %s %s %s >> %s\n", flags[i],
                    flags[j], files[n], files[k], CAT_OUT);
            fprintf(p1, "echo \"/-/-/-/-/-/-/-cat %s %s %s %s-/-/-/-/-/-/-/-\" >> %s\n",
                    flags[i], flags[j], files[n], files[k], S21_CAT_OUT);
            fprintf(p1, "cat/s21_cat %s %s %s %s >> %s\n", flags[i],
                    flags[j], files[n], files[k], S21_CAT_OUT);
        }
    }
    for (int z = 0; z < 5; z++)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < 5; i++)
            {
                int n = rand() % 3;
                int k = rand() % 3;
                int m = rand() % 3;
                fprintf(p1, "echo \"/-/-/-/-/-/-/-cat %s %s %s %s %s %s-/-/-/-/-/-/-/-\" >> %s\n",
                        flags[i], flags[j], flags[z], files[n], files[k], files[m], CAT_OUT);
                fprintf(p1, "cat %s %s %s %s %s %s >> %s\n", flags[i],
                        flags[j], flags[z], files[n], files[k], files[m], CAT_OUT);
                fprintf(p1, "echo \"/-/-/-/-/-/-/-cat %s %s %s %s %s %s-/-/-/-/-/-/-/-\" >> %s\n",
                        flags[i], flags[j], flags[z], files[n], files[k], files[m], S21_CAT_OUT);
                fprintf(p1, "cat/s21_cat %s %s %s %s %s %s >> %s\n", flags[i],
                        flags[j], flags[z], files[n], files[k], files[m], S21_CAT_OUT);
            }
        }
    }
    fprintf(p1, "echo \"/-/-/-/cat -b -e -n -s -t test/1.txt test/2.txt test/3.txt\" >> %s\n", CAT_OUT);
    fprintf(p1, "cat -b -e -n -s -t test/1.txt test/2.txt test/3.txt >> %s\n", CAT_OUT);
    fprintf(p1, "echo \"/-/-/-/cat -b -e -n -s -t test/1.txt test/2.txt test/3.txt\" >> %s\n", S21_CAT_OUT);
    fprintf(p1, "cat/s21_cat -b -e -n -s -t test/1.txt test/2.txt test/3.txt >> %s\n", S21_CAT_OUT);
#ifdef __APPLE__
#else
    fprintf(p1, "echo \"/-/-/-/cat --number-nonblank test/1.txt\" >> %s\n", CAT_OUT);
    fprintf(p1, "cat --number-nonblank test/1.txt >> %s\n", CAT_OUT);
    fprintf(p1, "echo \"/-/-/-/cat --number-nonblank test/1.txt\" >> %s\n", S21_CAT_OUT);
    fprintf(p1, "cat/s21_cat --number-nonblank test/1.txt >> %s\n", S21_CAT_OUT);

    fprintf(p1, "echo \"/-/-/-/cat --number test/1.txt\" >> %s\n", CAT_OUT);
    fprintf(p1, "cat --number test/1.txt >> %s\n", CAT_OUT);
    fprintf(p1, "echo \"/-/-/-/cat --number test/1.txt\" >> %s\n", S21_CAT_OUT);
    fprintf(p1, "cat/s21_cat --number test/1.txt >> %s\n", S21_CAT_OUT);

    fprintf(p1, "echo \"/-/-/-/cat --squeeze-blank test/1.txt\" >> %s\n", CAT_OUT);
    fprintf(p1, "cat --squeeze-blank test/1.txt >> %s\n", CAT_OUT);
    fprintf(p1, "echo \"/-/-/-/cat --squeeze-blank test/1.txt\" >> %s\n", S21_CAT_OUT);
    fprintf(p1, "cat/s21_cat --squeeze-blank test/1.txt >> %s\n", S21_CAT_OUT);
#endif
    fclose(p1);
}

int main()
{
    gen_foo();
    return 0;
}