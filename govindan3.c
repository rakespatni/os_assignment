#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;
char var[20];

void* child1(void *p) 
{
	
	int k=0;
	pthread_mutex_lock(&m1);
	printf("\nENTER U MESSAGE:");
	gets(var);
	k=strlen(var);
 	printf("\nUR MESSAGE HAS BEEN SENT BY CHILD 1\n");
        pthread_mutex_unlock(&m1);
        pthread_mutex_lock(&m2);
        printf("\n MESSAGE HAS BEEN RECEIVED BY CHILD 1\n");
        if(atoi(var)==k)
        	printf("\nPROG WORKING WELL:NO OF CHARATERS SENT AND RECEIVED ARE SAME: %d\n",k);
        else
        {
           	printf("\nNO OF CHARATERS SENT BY CHILD1: %d",k);
           	printf("\nNO OF CHARACTERS RECEIVED BY CHILD 2 : %d",atoi(var));
           	printf("\nNo of characters sent != No of characters received!!! \n");
        }
        pthread_mutex_unlock(&m2);
 	exit(0);
}

void* child2(void *p)
{
  pthread_mutex_lock(&m2);
  pthread_mutex_lock(&m1);
  printf("\nMESSAGE RECEIVED BY CHILD 2\n");
  sprintf(var,"%d",(int)strlen(var));
  printf("\nMESSAGE SENT BY CHILD 2\n");
  pthread_mutex_unlock(&m1);
  pthread_mutex_unlock(&m2);
}

int main() 
{
	pthread_t p1, p2;
	int ir1 = pthread_create(&p1, NULL, child1, NULL);
	wait(1);	
	int ir2 = pthread_create(&p2, NULL, child2, NULL);
	while(1){}
}

