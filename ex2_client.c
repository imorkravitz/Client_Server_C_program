#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>

void numToChar(char *string, int num);
int checkIfFileExist(const char *filename);
//----------------------------------------//

void handler(int dummy){
  signal(1, handler);
  char Pid[50] = {"0"};
  numToChar(Pid, getpid());
  char PidFilePath[50] = {"to_client_"};
  strcat(PidFilePath, Pid);
  strcat(PidFilePath, ".txt");
  printf("%s\n", PidFilePath);

  char const *const serverOutPut = PidFilePath;
  FILE *file = fopen(serverOutPut, "r");
  if (!file){
    printf("ERROR_FROM_EX2\n");
    exit(0);
  }
  char line[500];
  fgets(line, sizeof(line), file);
  printf("The resulte is:  %s\n", line);
}

int main(int argc, char *argv[]){
  if (argc != 5)
  {
    printf("there are no mach argoments");
    exit(0);
  }

  char PidFilePath[50] = {"to_srv.txt"};
  printf("%s\n", PidFilePath);

  char const *const input = PidFilePath;
  int count = 0;
  int check = 0;
  srand(time(NULL));
  do
  {
    check = checkIfFileExist(input);
    int r = rand() % 6;
    sleep(r);
    count++;

  } while (count < 10 && check);
  FILE *file;
  if (!check)
  {
    file = fopen(input, "w");
    if (!file)
    {
      printf("ERROR_FROM_EX2\n");
      return -1;
    }
  }else{
    printf("\nThe server was closed because no service rquest was recived for the las 60 second\n");
    return 0;
  }

  int Server_Pid = atoi(argv[1]);
  int x = atoi(argv[2]);
  int op = atoi(argv[3]); // operator
  int y = atoi(argv[4]);
  int Pid = getpid();

  printf("\nServer pid: %d\n", Server_Pid);
  printf("\nClient pid: %d\n", getpid());
  printf("\n%d\n", x);
  printf("\n%d\n", op);
  printf("\n%d\n", y);

  while (op < 1 || op > 4){
    printf("enter Operator : 1 = '+',2 = '-',3 = '*', 4 = '/' \n");
    scanf("%d", &op);
  }

  fprintf(file, "%d\n", Pid);
  fprintf(file, "%d\n", x);
  fprintf(file, "%d\n", op);
  fprintf(file, "%d\n", y);

  fclose(file);
  if(kill(Server_Pid, 1)){
    printf("The server is busy... mabye try later");
    remove(PidFilePath);
  }
  signal(1, handler);
  sleep(10);

  return 0;
}

void numToChar(char *string, int num){

  char temp[50] = {"0"};
  int i = 0;
  while ((num / 10) > 0)
  {
    temp[i] = (num % 10) + '0';
    num = num / 10;
    i++;
  }
  temp[i] = (num % 10) + '0';

  int j = 0;
  for (; i >= 0; i--, j++)
  {
    string[j] = temp[i];
  }
}

int checkIfFileExist(const char *filename){
  FILE *file;
  file = fopen(filename, "r");
  if (file)
  {
    fclose(file);
    return 1;
  }
  return 0;
}