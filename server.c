#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <math.h>

void FixCpy(char* dest , char* sors);
void numToChar(char* string , int num);

void handler(int dummy)
{
  signal(1, handler);
  int pid;
  pid = fork();  
if (pid == 0) /* son */ 
{	
 
   char const *const clientInput = "FromClient.txt";
    FILE *file = fopen(clientInput, "r");
    if (!file){
        printf("Error opening: %s", clientInput);
        exit(0);
    }

    char Pid[50] = {"0"};
    int intPid;
    int x;
    int op; //operator
    int y;
     char line[500];
    fgets(line, sizeof(line), file);
    FixCpy(Pid, line);
    intPid = atoi(line);
    printf("%s\n", Pid);
    fgets(line, sizeof(line), file);
    printf("%d\n", atoi(line));
    x = atoi(line);
    fgets(line, sizeof(line), file);
    printf("%d\n", atoi(line));
    op = atoi(line);
    fgets(line, sizeof(line), file);
    printf("%d\n", atoi(line));
    y = atoi(line);
    fclose(file);

    char PidFilePath[50]= {"ToClient"};
    strcat(PidFilePath,Pid);
    strcat(PidFilePath,".txt");
    printf("%s\n", PidFilePath);

char const *const serverOutPut = PidFilePath;
    FILE *file1 = fopen(serverOutPut, "w");
    if (!file1){
        printf("Error opening: %s", serverOutPut);
        exit(0);
    }

    int res;
    switch (op)
    {
     case 1:
     res = x+y;
      break;

     case 2:
     res = x-y;
     break;

     case 3:
     res = x*y;
     break;

     case 4:
     if(y){
       res = x/y;
     }else{
       fprintf(file1,"Cant divide by 0");
       fclose(file1);
       kill(intPid,1);
       exit(-1);
     }
     break;

    
    default:
      break;
    }

  fprintf(file1,"%d",res);
  fgets(line, sizeof(line), file);
  printf("\nthe res: %d\n", res);
  fclose(file1);
  
  kill(intPid,1);
  exit(0);
} 
}

int main(int argc, char *argv[])
{
     int test;
    signal(1, handler);
    printf("server pid: %d  press '1' to continue",getpid());
    scanf("%d", &test);

    sleep(15);

    return 0;
}

void FixCpy(char* dest , char* sors){
    if(sors){
        int i = 0;
        while(sors[i]!='\n'){
            dest[i]=sors[i];
            i++;
        }
    }
}

void numToChar(char* string , int num){

  char temp[50] = {"0"};
  int i = 0;
  while((num/10)>0){
     temp[i]=(num%10)+'0';
        num=num/10;
        i++;
    }
    temp[i]=(num%10)+'0';

    int j=0;
  for(;i>=0;i--,j++){
    string[j]=temp[i];
  }
}