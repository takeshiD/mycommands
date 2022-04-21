#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    pid_t pid;
    if(argc != 3){
        fprintf(stderr, "Usage %s <command> <arg>\n", argv[0]);
        exit(1);
    }
    printf("%d, %s\n", argc, argv[2]);
    pid = fork();
    if(pid < 0){
        fprintf(stderr, "fork(2) failed\n");
        exit(1);
    }
    if(pid == 0){   // 子プロセス
        sleep(5);
        printf("I'm child process\n");
        sleep(3);
        execl(argv[1], argv[1], argv[2], NULL);
        printf("oh child is failed\n");
        perror(argv[1]);
        exit(99);
    }else{          // 親プロセス
        int status;
        printf("I'm parent process. wait child\n");
        waitpid(pid, &status, 0);
        printf("child (PID=%d) finished: ", pid);
        if(WIFEXITED(status)){
            printf("exit status=%d\n", WEXITSTATUS(status));
        }
        else if(WIFSIGNALED(status)){
            printf("signal, sig=%d\n", WTERMSIG(status));
        }else{
            printf("abnormal exit\n");
        }
        exit(0);
    }
}
