#include <stdio.h>                                                                                                                                                     
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
int main(){
    const int SIZE = 4096;
    const char *name = "OS";
    char *buffer;

    int shm_fd;     // shared memory file descriptor
    void *ptr;  // pointer to shared memory object
    int n;
    scanf("%d",&n);
    shm_fd = shm_open(name, O_CREAT |O_RDWR, 0666);
    ftruncate(shm_fd,SIZE);

    pid_t  pid;

    pid = fork(); /* fork another process */
    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed\n");
        return 1;  // exit(1);
    }
    else if (pid == 0) { /* child process */
            ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
            while(n>1){
                if(n%2==0) n/=2;
                else n=3*n+1;
                sprintf(buffer,"%d, ",n);
                sprintf(ptr,"%s",buffer);
                ptr += strlen(buffer);
            }
    }
    else { /* parent process */
          /* parent will wait for the child to complete */
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	wait(NULL);
        printf("%s\n", (char *) ptr);
        shm_unlink(name);
        printf ("Complete\n");
        return 0;
    }   



