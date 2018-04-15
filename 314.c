#include <sys/types.h>                                                                                                                                                 
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    pid_t  pid;
    int n;
    scanf("%d",&n);
    pid = fork();
    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed\n");
        return 1;  // exit(1);
    }
    else if (pid == 0) { /* child process */
        while(n>1){
            if(n%2==0) n/=2;
            else if(n%2==1) n=3*n+1;
            printf("%d ",n);
        }
    }
    else { /* parent process */
          /* parent will wait for the child to complete */
        wait(NULL);
        printf ("Tesk Complete\n");
    }
    return 0;

}
