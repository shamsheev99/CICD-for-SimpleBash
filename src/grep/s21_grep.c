#include <pcre.h>
#include <stdio.h>
#include <string.h>

#define NMIN_STR 1000
#define NMAX_STR 10000

typedef struct type_flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int count_flags;
  int count_files;
  char search_str[NMIN_STR];
  char pattern_path[NMIN_STR];
} type_flags;

char *zero_cycle(char str[NMIN_STR]) {
  int i = 0;
  while (i < NMIN_STR) {
    str[i] = '\0';
    i++;
  }
  return str;
}

int zero_struct(type_flags *flags) {
  flags->e = 0;
  flags->i = 0;
  flags->v = 0;
  flags->c = 0;
  flags->l = 0;
  flags->n = 0;
  flags->h = 0;
  flags->s = 0;
  flags->f = 0;
  flags->o = 0;
  flags->count_flags = 0;
  flags->count_files = 0;
  zero_cycle(flags->search_str);
  zero_cycle(flags->pattern_path);
  return 0;
}

int search_str(char *estr, type_flags *flags, char *file_name, int num_str);

FILE *init_file(char *path, type_flags *flags) {
  FILE *file_check = NULL;
  if ((file_check = fopen(path, "r")) == NULL && !flags->s) {
    fprintf(stderr, "s21_grep: %s: No such file or directory\n", path);
  }
  return file_check;
}

int print_path(type_flags *flags, char *path) {
  if (flags->count_files > 1 && flags->h == 0) {
    printf("%s:", path);
  }
  return 0;
}

char *proc_file(char *path, type_flags *flags) {
  FILE *file_p;
  int match = 0;
  int num_str = 1;
  char sym[NMIN_STR] = {0};
  zero_cycle(sym);
  file_p = init_file(path, flags);
  if (file_p != NULL) {
    char *estr;
    while (1) {
      estr = fgets(sym, NMIN_STR, file_p);
      int i = 0;
      while (sym[i] != '\0') {
        i++;
      }
      if (sym[i - 1] != '\n') {
        sym[i] = '\n';
        sym[i + 1] = '\0';
      }
      if (estr == NULL) {
#ifdef __APPLE__
        if (flags->c == 1) {
          if (flags->count_files > 1) {
            print_path(flags, path);
          }
          if (flags->c == 1 && flags->l == 1 && match != 0)
            printf("%d\n", 1);
          else
            printf("%d\n", match);
        }
#else
        if (flags->c == 1 && flags->l != 1) {
          if (flags->count_files > 1) {
            print_path(flags, path);
          }
          printf("%d\n", match);
        }
#endif
        if (flags->l == 1 && match != 0) {
          printf("%s", path);
          printf("\n");
        }
        break;
      } else {
        int n = search_str(sym, flags, path, num_str);
        match += n;
      }
      num_str++;
    }
    fclose(file_p);
  }
  return 0;
}

int switch_foo(char flag, type_flags *flags) {
  switch (flag) {
    case 'e':
      flags->e = 1;
      break;
    case 'i':
      flags->i = 1;
      break;
    case 'v':
      flags->v = 1;
      break;
    case 'c':
      flags->c = 1;
      flags->n = 0;
      break;
    case 'l':
      flags->l = 1;
#ifdef __APPLE__
#else
      flags->c = 0;
#endif
      break;
    case 'n':
      flags->n = 1;
      break;
    case 'h':
      flags->h = 1;
      break;
    case 's':
      flags->s = 1;
      break;
    case 'f':
      flags->f = 1;
      break;
    case 'o':
      flags->o = 1;
    default:
      break;
  }
  return 0;
}

int parse_flags(int argc, char *argv[], type_flags *flags) {
  char flag_index[] = "eivclnhsfo";
  int i = 1;
  int cnt_options = 0;
  int legal_opt = 0;
  int flag_arg_e = 0;
  int flag_arg_f = 0;
  zero_struct(flags);
  while (i < argc) {
    if (cnt_options == -1) break;
    if (argv[i][0] == '-') {
      cnt_options++;
      int j = 1;
      while (argv[i][j] != '\0') {
        int k = 9;
        while (k >= 0) {
          if (argv[i][j] == flag_index[k]) {
            switch_foo(argv[i][j], flags);
            flags->count_flags++;
            legal_opt = 1;
            // READ -e ARG
            if (argv[i][j] == 'e' && argv[i][j - 1] == '-') {
              if (flag_arg_e >= 1) strncat(flags->search_str, "|", 2);
              if (argv[i][j + 1] != '\0') {
                strncat(flags->search_str, &argv[i][j + 1], strlen(&argv[i][j + 1]));
                flag_arg_e++;
                i++;
              } else {
                strncat(flags->search_str, &argv[i + 1][0], strlen(&argv[i + 1][0]));
                cnt_options++;
                flag_arg_e++;
              }
            }
            // READ -f ARG
            if (argv[i][j] == 'f' && argv[i][j - 1] == '-') {
              if (flag_arg_f >= 1) strncat(flags->pattern_path, "|", 2);
              if (argv[i][j + 1] != '\0') {
                strncat(flags->pattern_path, &argv[i][j + 1], strlen(&argv[i][j + 1]));
                flag_arg_f++;
                i++;
              } else {
                strncat(flags->pattern_path, &argv[i + 1][0], strlen(&argv[i + 1][0]));
                cnt_options++;
                flag_arg_f++;
              }
            }
          }
          k--;
        }
        if (legal_opt == 0) {
          fprintf(stderr, "s21_grep: illegal option -- %c\n", argv[i][j]);
          fprintf(stderr,
                  "usage: s21_grep [-ivclnhso] [-e pattern] [-f file] [file "
                  "...]\n");
          cnt_options = -1;
          break;
        }
        j++;
      }
    } else if (strlen(flags->search_str) == 0 && flags->f == 0) {
      strncpy(flags->search_str, argv[i], strlen(argv[i]));
      cnt_options++;
    }
    i++;
  }
  return cnt_options;
}

int search_str(char *sym, type_flags *flags, char *file_name, int num_str) {
  int options = 0;
  int erroffset;
  int match = 0;
  const char *error;
  char pattern[NMAX_STR];
  char path[NMIN_STR];
  char str[NMIN_STR];
  char output_str[NMIN_STR];
  pcre *re;
  const unsigned char *tables = NULL;
  tables = pcre_maketables();
  zero_cycle(pattern);
  zero_cycle(str);
  zero_cycle(path);
  zero_cycle(output_str);
  // FLAG H
  if (flags->h != 1) {
    strncpy(path, file_name, strlen(file_name));
  }
  // FLAG I
  if (flags->i == 1) {
    char reg[] = "(?i)";
    strncpy(pattern, reg, strlen(reg));
    strncat(pattern, flags->search_str, strlen(flags->search_str));
  } else {
    strncpy(pattern, flags->search_str, strlen(flags->search_str));
  }
  snprintf(str, sizeof(str), sym);
  re = pcre_compile((char *)pattern, options, &error, &erroffset, NULL);
  if (re) {
    int count = 0;
    int k = 0;
    int flag_print_path = 0;
    do {
      int ovector[30];
      count = pcre_exec(re, NULL, (char *)str, strlen(str), k, 0, ovector, 30);
      k = ovector[1];
#ifdef __APPLE__
      if (flags->v == 1 && flags->o == 1) {
        flags->o = 0;
      }
#else
      if (flags->v == 1 && flags->o == 1) {
        count = 0;
        break;
      }
#endif
      if ((flags->v == 0 ? (count == 1) : (count == -1))) {
        if (flags->c == 0 && flags->l == 0) {
          if (flags->o == 1 && flags->v == 0) {
            zero_cycle(output_str);
            for (int i = 0; i < 2 * count; i += 2) {
              strncpy(output_str, (str + ovector[i]),
                      (ovector[i + 1] - (ovector[i])));
            }
            strncat(output_str, "\n", 2);
          } else {
            snprintf(output_str, NMIN_STR, str);
          }
          if (flag_print_path == 0) print_path(flags, path);
          flag_print_path++;
          if (flags->n == 1) {
            printf("%d:%s", num_str, output_str);
          } else {
            printf("%s", output_str);
          }
        }
        match++;
      }
      if (flags->o == 0) break;
    } while ((size_t)k < strlen(str));
  }
  pcre_free((void *)re);
  pcre_free((void *)tables);
  return match;
}

char *proc_flag_f(char *path, type_flags *flags) {  // PROCESSING FLAG F
  FILE *file_p;
  char sym[NMAX_STR];
  file_p = init_file(path, flags);
  int i = 0;
  if (file_p != NULL) {
    while (1) {
      sym[i] = fgetc(file_p);
      if (sym[i] == EOF) {
        break;
      } else if (sym[i] == '\n') {
        sym[i] = '|';
      }
      i++;
    }
    strncat(flags->search_str, sym, strlen(sym));
    fclose(file_p);
  }
  return 0;
}

int main(int argc, char *argv[]) {
  type_flags flags;
  char sym[] = "|";
  int cnt_options = parse_flags(argc, argv, &flags);
  if (cnt_options != -1) {
    int k = 1 + cnt_options;
    int z = argc;
    int i = k;
    char *save_ptr = NULL;
    flags.count_files = z - i;
    if (flags.f) {
      char *istr = strtok_r(flags.pattern_path, sym, &save_ptr);
      while (istr != NULL) {
        proc_flag_f(istr, &flags);
        istr = strtok_r(NULL, sym, &save_ptr);
      }
    }
    while (i < z) {
      proc_file(argv[i], &flags);
      i++;
    }
  }
  return 0;
}
