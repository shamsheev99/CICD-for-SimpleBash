#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NMAX 100
#define BASH_GREP "test/test_grep.sh"
#define S21_GREP_OUT "test/test_s21_grep.txt"
#define GREP_OUT "test/test_grep.txt"

void *gen_foo() {
  FILE *p1 = fopen(BASH_GREP, "w");
  char flags[8][3] = {"-i", "-v", "-c", "-l", "-n", "-h", "-s", "-o"};
  char files[3][11] = {"test/1.txt", "test/2.txt", "test/3.txt"};
  char patterns[11][10] = {"cat", "grep", "aa",   "zx",  "hi",  "spec",
                           "bdf", "face", "FACE", "afk", "asdd"};

  srand(time(NULL));
  for (int i = 0; i < 11; i++) {
    int n = rand() % 3;
    fprintf(p1, "echo \"/-/-/-/-/-/-/-grep %s %s-/-/-/-/-/-/-/-\" >> %s\n",
            patterns[i], files[n], GREP_OUT);
    fprintf(p1, "grep %s %s >> %s\n", patterns[i], files[n], GREP_OUT);
    fprintf(p1, "echo \"/-/-/-/-/-/-/-grep %s %s-/-/-/-/-/-/-/-\" >> %s\n",
            patterns[i], files[n], S21_GREP_OUT);
    fprintf(p1, "grep/s21_grep %s %s >> %s\n", patterns[i], files[n],
            S21_GREP_OUT);
  }
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 11; i++) {
      int n = rand() % 3;
      fprintf(p1, "echo \"/-/-/-/-/-/-/-grep %s %s %s-/-/-/-/-/-/-/-\" >>%s\n",
              flags[j], patterns[i], files[n], GREP_OUT);
      fprintf(p1, "grep %s %s %s >> %s\n", flags[j], patterns[i], files[n],
              GREP_OUT);
      fprintf(p1, "echo \"/-/-/-/-/-/-/-grep %s %s %s-/-/-/-/-/-/-/-\" >>%s\n",
              flags[j], patterns[i], files[n], S21_GREP_OUT);
      fprintf(p1, "grep/s21_grep %s %s %s >> %s\n", flags[j], patterns[i],
              files[n], S21_GREP_OUT);
    }
  }
  for (int z = 0; z < 8; z++) {
    for (int j = 0; j < 8; j++) {
      for (int i = 0; i < 11; i++) {
        int n = rand() % 3;
        int k = rand() % 3;
        fprintf(
            p1,
            "echo \"/-/-/-/-/-/-/-grep %s %s %s %s %s-/-/-/-/-/-/-/-\" >>%s\n",
            flags[j], flags[z], patterns[i], files[n], files[k], GREP_OUT);
        fprintf(p1, "grep  %s %s %s %s %s >> %s\n", flags[j], flags[z],
                patterns[i], files[n], files[k], GREP_OUT);
        fprintf(
            p1,
            "echo \"/-/-/-/-/-/-/-grep %s %s %s %s %s-/-/-/-/-/-/-/-\" >>%s\n",
            flags[j], flags[z], patterns[i], files[n], files[k], S21_GREP_OUT);
        fprintf(p1, "grep/s21_grep %s %s %s %s %s >> %s\n", flags[j], flags[z],
                patterns[i], files[n], files[k], S21_GREP_OUT);
      }
    }
  }
  for (int i = 0; i < 11; i++) {
    int n = rand() % 3;
    int k = rand() % 3;
    fprintf(p1, "echo \"/-/-/-/-/-/-/-grep %s %s %s %s-/-/-/-/-/-/-/-\" >>%s\n",
            "-e", patterns[i], files[n], files[k], GREP_OUT);
    fprintf(p1, "grep %s %s %s %s >> %s\n", "-e", patterns[i], files[n],
            files[k], GREP_OUT);
    fprintf(p1, "echo \"/-/-/-/-/-/-/-grep %s %s %s %s-/-/-/-/-/-/-/-\" >>%s\n",
            "-e", patterns[i], files[n], files[k], S21_GREP_OUT);
    fprintf(p1, "grep/s21_grep %s %s %s %s >> %s\n", "-e", patterns[i],
            files[n], files[k], S21_GREP_OUT);
    fprintf(p1, "echo \"/-/-/-/-/-/-/-grep %s%s %s %s-/-/-/-/-/-/-/-\" >>%s\n",
            "-e", patterns[i], files[n], files[k], GREP_OUT);
    fprintf(p1, "grep %s%s %s %s >> %s\n", "-e", patterns[i], files[n],
            files[k], GREP_OUT);
    fprintf(p1, "echo \"/-/-/-/-/-/-/-grep %s%s %s %s-/-/-/-/-/-/-/-\" >>%s\n",
            "-e", patterns[i], files[n], files[k], S21_GREP_OUT);
    fprintf(p1, "grep/s21_grep %s%s %s %s >> %s\n", "-e", patterns[i], files[n],
            files[k], S21_GREP_OUT);
  }
  for (int i = 0; i < 11; i++) {
    int n = rand() % 3;
    int k = rand() % 3;
    char search_file[] = "test/grep_search.txt";
    fprintf(p1, "echo \"/-/-/-/-/-/-/-grep %s %s %s %s-/-/-/-/-/-/-/-\" >>%s\n",
            "-f", search_file, files[n], files[k], GREP_OUT);
    fprintf(p1, "grep %s %s %s %s >> %s\n", "-f", search_file, files[n],
            files[k], GREP_OUT);
    fprintf(p1, "echo \"/-/-/-/-/-/-/-grep %s %s %s %s-/-/-/-/-/-/-/-\" >>%s\n",
            "-f", search_file, files[n], files[k], S21_GREP_OUT);
    fprintf(p1, "grep/s21_grep %s %s %s %s >> %s\n", "-f", search_file,
            files[n], files[k], S21_GREP_OUT);
    fprintf(p1, "echo \"/-/-/-/-/-/-/-grep %s%s %s %s-/-/-/-/-/-/-/-\" >>%s\n",
            "-f", search_file, files[n], files[k], GREP_OUT);
    fprintf(p1, "grep %s%s %s %s >> %s\n", "-f", search_file, files[n],
            files[k], GREP_OUT);
    fprintf(p1, "echo \"/-/-/-/-/-/-/-grep %s%s %s %s-/-/-/-/-/-/-/-\" >>%s\n",
            "-f", search_file, files[n], files[k], S21_GREP_OUT);
    fprintf(p1, "grep/s21_grep %s%s %s %s >> %s\n", "-f", search_file,
            files[n], files[k], S21_GREP_OUT);
  }
}

int main() {
  gen_foo();
  return 0;
}