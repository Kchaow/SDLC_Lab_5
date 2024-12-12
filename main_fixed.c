#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void    checkArg(const char *a)
{
  while (*a)
    {
      if (   (*a == ';')
          || (*a == '&')
          || (*a == '|')
          || (*a == ',')
          || (*a == '$')
          || (*a == '(')
          || (*a == ')')
          || (*a == '{')
          || (*a == '}')
          || (*a == '`')
          || (*a == '>')
          || (*a == '<') ) {
        puts("Forbidden !!!");
        exit(2);
      }
        a++;
    }
}

int     main()
{
  int bufferSize = 16;
  int maxCopyAndCatSize = 100;
  char  *arg = malloc(0x20);
  char  *cmd = malloc(0x400);
  setreuid(geteuid(), geteuid());

  strncpy(cmd, "/bin/ls -l ", maxCopyAncCatSize);

  printf("Enter directory you want to display : ");

  fgets(arg, bufferSize, stdin);
  checkArg(arg);

  strncat(cmd, arg, maxCopyAncCatSize);
  system(cmd);

  return 0;
}