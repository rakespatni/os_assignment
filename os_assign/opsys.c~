#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <time.h>   
#include <stdlib.h>
#define buffrsize 128

main()
{
clock_t start_thread, end_thread, total_thread;	
int pipe1[2],pipe2[2];
int i,j,k;
ssize_t numRead = -1;
const char* firstmsg = "PIPE ASSIGNMENT";
const unsigned int clen = strlen(firstmsg) + 1;
const char secondmsg[20];
char buffr[buffrsize];
pipe(pipe1);
if (pipe(pipe1) == -1)
    {
        printf("\n ERROR:OPENING PIPE A->B!\n");
        exit(1);
    	
    }
    	
	pipe(pipe2);
if (pipe(pipe2) == -1)
    {
        printf("\n ERROR: OPENING PIPE B->A!\n");
        exit(1);
    }
	
	printf("\n PIPE HAS OPENED SUCCESSFULLY\n");
	start_thread = clock();
	
switch (fork())
    {
        case -1:
         printf("\n ERROR : FORKING CHILD A!\n");
         exit(1);
	
	case 0:
         printf("\nCHILD A GETTING EXECUTED\n");
         sleep(1);
            		
          
         if (close(pipe1[0]) == -1)
          {
           printf("\n ERROR: CLOSING READING END OF PIPE 1.\n");
           _exit(1);
          }
           
          if (close(pipe2[1]) == -1)
           {
            printf("\n ERROR: CLOSING WRITING END OF PIPE 2.\n");
            _exit(1);
           }

           
           if (write(pipe1[1], firstmsg, clen) != clen)
           {
             printf("\n ERROR:WRITING TO PIPE 1.\n");
             _exit(1);
           }
           if (close(pipe1[1]) == -1)
           {
              printf("\n ERROR: CLOSING WRITING END OF PIPE 1.\n");
              _exit(1);
           }

            
            numRead = read(pipe2[0], buffr, 15);
            if (numRead == -1)
           {
            printf("\n ERROR :READING FROM PIPE 2.\n");
            _exit(1);
           }
            i=atoi(buffr);
	    if(i+1==clen)
	      printf("\n NO ERROR:EXECUTION CONTINUES\n ");
	    else
	      printf("ERROR");
            if (close(pipe2[0]) == -1)
            {
            printf("\nERROR :CLOSING READING END OF PIPE 2.\n");
            _exit(1);
	    }
	           

            	printf("\nMESSAGE RECEIVED BY CHILD A IS THE SIZE OF THE MSG IT SENT TO B =");
                printf(" %s\n", buffr);
            	printf("\nNOW CHILD A EXITS\n");
            	         		
            	_exit(0);

        	default:
                break;
}

	
	// child B
    	switch (fork())
    	{
        	case -1:
            		printf("\nERROR:FORKING CHILD B\n");
            		exit(1);
        	case 0:
            		printf("\nCHILD B IS GETTING EXECUTED\n");
            		
            		sleep(1);
            		
            		
                        if (close(pipe2[0]) == -1)
            		{
                		printf("\nERROR in closing reading end of pipe 2.\n");
                		_exit(1);
            		}
            		
            		if (close(pipe1[1]) == -1)
            		{
                		printf("\nERROR in closing writing end of pipe 1.\n");
                		_exit(1);
            		}


            		if (read(pipe1[0], buffr, clen) == -1)
            		{
                		printf("\nERROR in reading from pipe 1.\n");
                		_exit(EXIT_FAILURE);
            		}

            		if (close(pipe1[0]) == -1)
            		{
                		printf("\nERROR in closing reading end of pipe 1.\n");
                		_exit(EXIT_FAILURE);
            		}
			j=strlen(buffr);
			sprintf(secondmsg,"%d",j);
            		
            		if (write(pipe2[1], secondmsg,15) != 15)
            		{
                		printf("\nERROR in writing to the pipe.\n");
                		_exit(EXIT_FAILURE);
            		}

            		if (close(pipe2[1]) == -1)
            		{
                		printf("\nERROR in closing writing end of pipe 2.\n");
                		_exit(EXIT_FAILURE);
            		}

            		printf("\nMESSAGE RECEIVED BY CHILD B: %s\n", buffr);
            		
            		
            		
            		printf("\nCHILD B EXITS\n");
            		
            		
            		
            		_exit(EXIT_SUCCESS);

        	default:
            		break;
    	}
	
	printf("\nPIPES CLOSED BY PARENT\n");
	
	sleep(1);
     	
    	if (close(pipe1[0]) == -1)
    	{
        	printf("\nERROR in closing reading end of the pipe.\n");
        	exit(EXIT_FAILURE);
    	}

    	if (close(pipe2[1]) == -1)
    	{
        	printf("\nERROR in closing writing end of the pipe.\n");
        	exit(EXIT_FAILURE);
    	}

    	if (close(pipe2[0]) == -1)
    	{
        	printf("\n ERROR in closing reading end of the pipe.\n");
        	exit(EXIT_FAILURE);
    	}

    	if (close(pipe1[1]) == -1)
    	{
        	printf("\n ERROR in closing writing end of the pipe.\n");
        	exit(EXIT_FAILURE);
    	}

    	printf("\n PARENT WAITS FOR COMPLETION OF CHILD\n");
    	if (wait(NULL) == -1)
    	{
        	printf("\n WAIT ERROR\n");
        	exit(EXIT_FAILURE);
    	}
    	if (wait(NULL) == -1)
    	{
        	printf("\n WAIT ERROR\n");
        	exit(EXIT_FAILURE);
    	}
	
    	printf("\n EXITING PARENT\n");
    	end_thread = clock();
	printf("\n END THREAD : %ld \n ",end_thread);
	total_thread = (double)(end_thread - start_thread) / CLOCKS_PER_SEC;
	printf ("CPU TIME : %lf\n", total_thread );
	
	if(total_thread>0.0000001)
		kill(getpid(),SIGABRT);
	
	
	exit(EXIT_SUCCESS);
}
