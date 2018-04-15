#include <stdlib.h>                                         
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int main(){
    int fd1[2];
    int fd2[2];
    pid_t pid;
    char message[100];
    char buffer[100];
    fgets(message, 100, stdin);
    int len = strlen(message);
	// create a pipe
    if(pipe(fd1) == -1) {
        fprintf(stderr,"Pipe failed");
        return 1;
    }
    
    if(pipe(fd2) == -1) {
        fprintf(stderr, "Pipe failed");
        return 2;
    }


	pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Fork failed");
        return 3;
    }
    if(pid > 0) {  // parent process
        close(fd1[0]);
        close(fd2[1]);
        printf("parent sending message\n");
        write(fd1[1], message, len+1);
		char ans[100];
		wait(NULL);
	    read(fd2[0], ans, 100);
        printf("%s\n", ans);
        close(fd1[1]);
        close(fd2[0]);
    } else {  // child process
        close(fd1[1]);
        close(fd2[0]);
        read(fd1[0], buffer, 100);
        char* result;
        int i=0;
        for(; i<len; i++){
            if (islower(buffer[i]))
				buffer[i] = toupper(buffer[i]);
			else
				buffer[i] = tolower(buffer[i]);
        }
	
        write(fd2[1], buffer, len+1);  
        close(fd1[0]);
        close(fd2[1]);
    }

    return 0;
}                                                         

