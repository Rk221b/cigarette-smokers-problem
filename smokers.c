#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#define SHMKEY1 70
#define SHMKEY2 75
#define SHMKEY3 80
#define SHMKEY4 85
#define SHMKEY5 90

int shmid,*sindex,*smoker[3],*agent;

void main()
{
int i;

shmid=shmget(SHMKEY1,sizeof(int),0600|IPC_CREAT);
smoker[0]=(int *) shmat(shmid,0,0);

shmid=shmget(SHMKEY2,sizeof(int),0600|IPC_CREAT);
smoker[1]=(int *) shmat(shmid,0,0);

shmid=shmget(SHMKEY3,sizeof(int),0600|IPC_CREAT);
smoker[2]=(int *) shmat(shmid,0,0);

shmid=shmget(SHMKEY4,sizeof(int),0600|IPC_CREAT);
agent=(int *) shmat(shmid,0,0);

shmid=shmget(SHMKEY5,sizeof(int),0600|IPC_CREAT);
sindex=(int *) shmat(shmid,0,0);

*sindex=1;
*agent=1;

 for(i=0;i<3;i++)
 {
 *smoker[i]=0;
 }


  if(fork()==0)
  {
    while(1)
     {
      if(*smoker[*sindex]==1)
       {
        (*smoker[*sindex])--;

         switch(*sindex)
          {
          case 0:
          printf("I AM FIRST SMOKER HAVING PAPER:\n");
          printf("GOT MATCHBOX AND TOBACCO FROM AGENT \n");
          printf("I AM SMOKING NOW :\n");
          sleep(3);
          break;

          case 1:

            printf("I AM SECOND SMOKER HAVING MATCHBOX:\n");
          printf("GOT PAPER AND TOBACCO FROM AGENT \n");
          printf("I AM SMOKING NOW :\n");
          sleep(3);
          break;

          case 2:

          printf("I AM THIRD SMOKER HAVING TOBACCO:\n");
          printf("GOT MATCHBOX AND PAPER FROM AGENT \n");
          printf("I AM SMOKING NOW :\n");
          sleep(3);
          break;

          }
          *sindex=(*sindex+1)%3;
          (*agent)++;


       }


     }



  }
  else
  {

   while(1)
    {
    if(*agent==1)
     {
     (*agent)--;
     printf("I AM AGENT :\n");


       switch(*sindex)
        {

        case 0:
        printf("I AM SUPPLYING MATCHBOX AND TOBACCO TO 1st SMOKER : \n");
        sleep(3);
        break;

        case 1:
        printf("I AM SUPPLYING PAPER AND TOBACCO TO 2st SMOKER : \n");
        sleep(3);
        break;

        case 2:
        printf("I AM SUPPLYING MATCHBOX AND PAPER TO 3st SMOKER : \n");
        sleep(3);
        break;



        }
        (*smoker[*sindex])++;


     }


    }



  }

}
