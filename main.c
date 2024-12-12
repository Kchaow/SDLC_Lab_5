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
  char  *arg = malloc(0x20);
  //C и C++ не возвращают автоматически неиспользуемую память. Разработчик должен освободить память, затребованную для его приложения, которая больше не нужна. 
  //В отличие от стека, который автоматически выделяет локальные переменные при вызове функции и освобождает их при возврате функции, куча не предлагает автоматического 
  //управления памятью. Разработчик должен убедиться, что освобождает память, которую он выделяет динамически в куче.
  char  *cmd = malloc(0x400);
  //Функции из семейства setuid, включая setuid и setgid, используются для изменения идентификатора вызывающего процесса. 
  //Они используются для изменения привилегий для последующих действий, которые должны быть выполнены. Если вызов этих функций возвращает ошибку, 
  //которая не проверяется и не обрабатывается должным образом, последующие части программы будут выполнены с неожиданными привилегиями. Это, в свою очередь, 
  //приводит к неожиданному поведению программы и представляет серьезную угрозу безопасности.
  setreuid(geteuid(), geteuid());

  //Использование функции strcpy считается небезопасным, так как она не отслеживает размер своего буфера и ведет к уязвимости buffer overflow
  strcpy(cmd, "/bin/ls -l ");

  printf("Enter directory you want to display : ");

  //Использование функции gets считается небезопасным, так как она не отслеживает размер своего буфера и ведет к уязвимости buffer overflow
  gets(arg);
  checkArg(arg);

  //Функция strcat так же не отслеживает размер своего буфера и ведет к уязвимости buffer overflow
  strcat(cmd, arg);
  system(cmd);

  return 0;
}