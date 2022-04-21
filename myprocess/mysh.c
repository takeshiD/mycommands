#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
1. プロンプトで入力を待つ
2. 入力, Enter, 実行
3. 入力文字列を解析
4. execvpに入れる形に整形する
5. 親: fork -> waitpid
6. 子: execvp
7. 実行後プロンプトに戻る
8. エラーが出たらsterrに出力してプロンプトに戻る
*/ 

#define BUFSIZE 1024
#define ARGSIZE 64

const char *PROMPT = "(mysh)$ ";

typedef struct Command Command;
struct Command{
    int argc;
    char *argv[ARGSIZE];
};

typedef enum Status Status;
enum Status{
    SUCCESS,
    EXIT,
};

Command *new_command(){
    Command *cmd = malloc(sizeof(Command));
    cmd->argc = 0;
    for(int i=0; i<ARGSIZE; i++){
        cmd->argv[i] = malloc(sizeof(char)*ARGSIZE);
    }
    return cmd;
}

void print_command(Command *cmd){
    printf("argc: %d\n", cmd->argc);
    for(int i=0; i<cmd->argc; i++){
        printf("argv[%d]: %s\n", i, cmd->argv[i]);
    }
}

Command *parse(char *buf){
    /* e.g: ls -la ~/ -> ["ls", "-la", "~/"] */
    Command *cmd = new_command();
    char *cur = buf;
    while(isspace(*cur)){
        cur++;
    }
    while(*cur){
        if(isspace(*cur)){
            cmd->argc++;
            cur++;
            continue;
        }
        if(*cur){
            strncat(cmd->argv[cmd->argc], cur, 1);
            cur++;
            continue;
        }
    }
    cmd->argv[cmd->argc] = NULL;
    return cmd;
}

void exec_command(Command *cmd){
    if(0<cmd->argc && strcmp(cmd->argv[0], "exit")==0){
        exit(EXIT_SUCCESS);
    }
    pid_t pid;
    pid = fork();
    if(pid < 0){
        fprintf(stderr, "fork(2) failed\n");
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
        execvp(cmd->argv[0], cmd->argv);
        perror("command execute filaed\n");
        exit(EXIT_FAILURE);
    }
    else if(pid > 0){
        int status;
        waitpid(pid, &status, 0);
        if(WIFEXITED(status)){
            // nop
        }
        else if(WIFSIGNALED(status)){
            fprintf(stderr, "Stop Signaled\n");
        }
        else{
            fprintf(stderr, "Abnormal exit\n");
        }
    }
}
int main(int argc, char **argv){
    char buf[BUFSIZE];
    while(true){
        fprintf(stdout, "%s", PROMPT);
        if(fgets(buf, BUFSIZE, stdin) == NULL){
            fprintf(stderr, "failed\n");
            continue;
        }
        Command *cmd = parse(buf);
        //print_command(cmd);
        exec_command(cmd);
    }
    exit(EXIT_SUCCESS);
}

