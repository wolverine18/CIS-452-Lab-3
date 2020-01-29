#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void sigusr1Handler(int sigNum){
	printf("\treceived a SIGUSR1 signal\n");
}

void sigusr2Handler(int sigNum){
	printf("\treceived a SIGUSR2 signal\n");
}

void sigintHandler(int sigNum){
	printf("\t^C received.\n");
	printf("That's it, I'm shutting you down...");
}

int main () {
	pid_t pid;

	if((pid = fork()) < 0){
		perror("Error forking");
		exit(1);
	}
	//child process
	else if(!pid){
		//randomly generate a number from 1 to 5
		int sleepTime = 0;
		srand(time(NULL));
		//gets parent pid
		pid_t ppid = getppid();
		
		while(1){
			sleepTime = rand() % 5 + 1;
			sleep(sleepTime);
			
			if(sleepTime % 2 == 0){
				//send SIGUSR1 signal
				kill(SIGUSR1, ppid);
			}else{
				//send SIGUSR2 signal
				kill(SIGUSR2, ppid);
			}
		}
	}

	//parent process
	printf("spawned child PID# %d\n", pid);

	//install signal handlers
	while(1){
		signal(SIGUSR1, sigusr1Handler);
		signal(SIGUSR2, sigusr2Handler);
		signal(SIGINT, sigintHandler);
		printf("waiting...");
		pause();
	}
	return 0;
}
