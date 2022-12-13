#include <stdio.h>
#include <string.h>

typedef struct type_flags {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int count_flags;
  int count_files;
  char buff_sym;
} type_flags;

int zero_struct(type_flags *flags) {
  flags->b = 0;
  flags->e = 0;
  flags->n = 0;
  flags->s = 0;
  flags->t = 0;
  flags->v = 0;
  flags->count_flags = 0;
  flags->count_files = 0;
  flags->buff_sym = ' ';
  return 0;
}

FILE *init_file(char *path) {
  FILE *testFile = NULL;
  if ((testFile = fopen(path, "r")) == NULL) {
    fprintf(stderr, "s21_cat: %s: No such file or directory\n", path);
  }
  return testFile;
}

int proc_file(char *path, type_flags *flags, int line_break, int num_file) {
  FILE *file_p;
  file_p = init_file(path);
  if (file_p != NULL) {
    char symbol = ' ';
    char buff_symbol = '\n';
    int cnt_empt_str = 0;
    int print_flag = 1;
    int numb_str = 0;
    int n_flag = 1;
    int b_flag = 1;
    while (1) {
      symbol = fgetc(file_p);
      if (symbol == EOF) {
        flags->buff_sym = buff_symbol;
        break;
      }
      if (flags->s == 1) {
        if (symbol == '\n' && buff_symbol == '\n') {
          print_flag = 0;
          cnt_empt_str++;
        } else if (symbol != '\n') {
          cnt_empt_str = 0;
          print_flag = 1;
        }
      }
      // CHECK FLAG N
      if (buff_symbol == '\n')
        n_flag = 1;
      else
        n_flag = 0;
      if (flags->b == 1 && buff_symbol == '\n' && symbol != '\n')
        b_flag = 1;
      else
        b_flag = 0;
      if (line_break != 1 && numb_str == 0 && num_file != 1 && flags->buff_sym != '\n') {
        n_flag = 0;
        b_flag = 0;
      }
      if (n_flag == 1) {
        if (flags->n == 1 && print_flag == 1) {
          printf("%6d\t", line_break++);
        }
      }
      // CHECK FLAG B
      if (b_flag != 0) {
        printf("%6d\t", line_break++);
      }
      // CHECK FLAG S
      if (flags->s == 1) {
        if (print_flag == 0 && cnt_empt_str == 1) {
          if (flags->n == 1)
            printf("%6d\t", line_break++);
          if (flags->e != 0)
            printf("$\n");
          else
            printf("\n");
        }
      }
      if (print_flag == 1 && symbol != EOF) {
        // CHECK FLAG E
        if (flags->e == 1 && symbol == '\n')
          printf("$");

        // CHECK FLAG T
        if ((flags->t == 1 && symbol > 0 && symbol < 32 && symbol != '\n') ||
            (flags->v && symbol != 9 && symbol > 0 && symbol < 32 &&
             symbol != '\n')) {
          printf("^");
          symbol += 64;
        }
        if (cnt_empt_str > 1)
          printf("\n");
        printf("%c", symbol);
      }
      buff_symbol = symbol;
      numb_str++;
    }
    fclose(file_p);
  }
  return line_break;
}

int switch_foo(char flag, type_flags *flags) {
  switch (flag) {
  case 'b':
    flags->b = 1;
    flags->n = 0;
    break;
  case 'e':
    flags->e = 1;
    flags->v = 1;
    break;
  case 'n':
    ((flags->b == 0) ? (flags->n = 1) : (flags->n = 0));
    break;
  case 's':
    flags->s = 1;
    break;
  case 'T':
  case 't':
    flags->t = 1;
    break;
  case 'v':
    flags->t = 1;
    flags->v = 1;
    break;
  default:
    break;
  }
  return 0;
}

int parse_flags(int argc, char *argv[], type_flags *flags) {
  char flag_index[] = "benstTv";
  char nonblank[] = "number-nonblank";
  char number[] = "number";
  char squeeze[] = "squeeze-blank";
  int i = 1;
  int cnt_options = 0;
  int legal_opt = 0;
  zero_struct(flags);
  while (i < argc) {
    if (argv[i][0] == '-') {
      cnt_options++;
      int j = 1;
      if (argv[i][1] == '-') {
        if (strcmp(nonblank, (argv[i] + 2)) == 0)
          switch_foo('b', flags);
        else if (strcmp(number, (argv[i] + 2)) == 0)
          switch_foo('n', flags);
        else if (strcmp(squeeze, (argv[i] + 2)) == 0)
          switch_foo('s', flags);
        else
          legal_opt = 0;
      } else {
        while (argv[i][j] != '\0') {
          int k = 6;
          while (k >= 0) {
            if (argv[i][j] == flag_index[k]) {
              switch_foo(argv[i][j], flags);
              flags->count_flags++;
              legal_opt = 1;
            }
            k--;
          }
          if (legal_opt == 0) {
            fprintf(stderr, "cat: illegal option -- %c\n", argv[i][j]);
            fprintf(stderr, "usage: cat [-benst] [file ...]\n");
            cnt_options = -1;
            break;
          }
          j++;
        }
      }
    }
    i++;
  }
  return cnt_options;
}

int main(int argc, char *argv[]) {
  type_flags flags;
  int cnt_options = cnt_options = parse_flags(argc, argv, &flags);
  if (cnt_options != -1) {
    int k = 1 + cnt_options;
    int z = argc;
    int i = k;
    int lines = 1;
    int num_file = 1;
    while (i < z) {
#ifdef __APPLE__
      proc_file(argv[i], &flags, lines, num_file++);
#else
      lines = proc_file(argv[i], &flags, lines, num_file++);
#endif
      flags.count_files++;
      i++;
    }
  }

  return 0;
}
