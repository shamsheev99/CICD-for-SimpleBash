#include <stdio.h>
#include <string.h>

#define NMAX 1000
#define CAT_TXT "test/test_cat.txt"
#define GREP_TXT "test/test_grep.txt"
#define S21CAT_TXT "test/test_s21_cat.txt"
#define S21GREP_TXT "test/test_s21_grep.txt"

int zero_cycle(char *buff)
{
  int i = 0;
  while (i < NMAX)
  {
    *(buff + i) = '\0';
    i++;
  }
  return 0;
}

int compare_foo(int flag)
{
  FILE *p1 = NULL;
  FILE *p2 = NULL;
  if (flag == 1)
  {
    p1 = fopen(CAT_TXT, "r");
    p2 = fopen(S21CAT_TXT, "r");
  }
  else if (flag == -1)
  {
    p1 = fopen(GREP_TXT, "r");
    p2 = fopen(S21GREP_TXT, "r");
  }
  else
    printf("ERROR\n");
  if (flag != 0)
  {
    char *estr1 = NULL;
    char *estr2 = NULL;
    char buff1[NMAX];
    char buff2[NMAX];
    char buff_err[NMAX];
    int cnt_err = 0;
    int num_str = 1;
    int length = 0;
    zero_cycle(buff1);
    zero_cycle(buff2);
    if (p1 != NULL || p2 != NULL)
    {
      while (1)
      {
        estr1 = fgets(buff1, NMAX, p1);
        estr2 = fgets(buff2, NMAX, p2);
        if (estr1 == NULL || estr2 == NULL || buff1 == "\n" || buff2 == "\n")
        {
          break;
        }
        else
        {
          if (strcmp(buff1, buff2) != 0)
          {
            if (cnt_err < 1)
            {
              //printf("test files %s %s\n", CAT_TXT, S21CAT_TXT);
              // printf("Error string:\n");
              // printf("default util: %s\n", buff1);
              // printf("s21_util: %s\n", buff2);
            }
            cnt_err++;
          }
          num_str++;
        }
      }
    }
    if (cnt_err != 0)
    {
      printf("ERROR\n");
      printf("first err %d\n", num_str);
    }
    else
    {
      printf("OK!!!\n");
      printf("first err %d\n", num_str);
    }
    fclose(p1);
    fclose(p2);
  }
  return 0;
}

int main(int argc, char *argv[])
{
  int flag = 0;
  if (strcmp(argv[argc - 1], "cat") == 0)
    flag = 1;
  else if (strcmp(argv[argc - 1], "grep") == 0)
    flag = -1;
  compare_foo(flag);
  return 0;
}