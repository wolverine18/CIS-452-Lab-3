#include <stdio.h>
#include <stdlib.h>

int main () {
	int fd[2];
	pid_t pid;
	srand(time(NULL));

	if(pipe(fd) < 0){
		perror("Error setting up the pipe");
		exit(1);
	}

	if((pid = fork()) < 0){
		perror("Error forking");
		exit(1);
	}
	//child process
	else if(!pid){
		//randomly generate a number from 1 to 5
		exit(0);
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
