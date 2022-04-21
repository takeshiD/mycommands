#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/***** misc *****/
static void *xmalloc(size_t size){
    void *p;
    p = calloc(1, size);
    if(p == NULL){
        exit(EXIT_FAILURE);
    }
    return p;
}

static void *xrealloc(void *ptr, size_t size){
    void *p;
    if(ptr == NULL){
        return xmalloc(size);
    }
    p = realloc(ptr, size);
    if(p == NULL){
        exit(EXIT_FAILURE);
    }
    return p;
}

bool isidentify(char p){
    switch(p){
        case '|':
            return true;
        case '>':
            return true;
        case '<':
            return true;
        default:
            return false;
    }
}

bool isvalidchar(char p){
    return !isidentify(p) && !isspace(p) && 32<=p && p<=126;
}

/***** Command *****/
#define SIZE_ARG 8

typedef struct Cmd Cmd;
struct Cmd {
    char **argv;
    int argc;
    int capa;
    Cmd *next;
};

Cmd *make_cmd(){
    Cmd *cmd = xmalloc(sizeof(Cmd));
    cmd->argv = xmalloc(sizeof(char*)*SIZE_ARG);
    cmd->argc = 0;
    cmd->capa = SIZE_ARG;
    return cmd;
}

void free_cmd(Cmd *cmd){
    if(cmd->next != NULL){
        free_cmd(cmd->next);
    }
    free(cmd->argv);
    free(cmd);
}

void print_cmd(Cmd *cmd){
    fprintf(stdout, "[");
    for(int i=0; i < cmd->argc; i++){
        fprintf(stdout, "\"%s\"", cmd->argv[i]);
        if(i < cmd->argc-1){
            fprintf(stdout, ",");
        }
    }
    fprintf(stdout, "]");
    if(cmd->next != NULL){
        fprintf(stdout, " -> ");
        print_cmd(cmd->next);
    }
    else{
        fprintf(stdout, "\n");
    }
}

Cmd *parse(char *p){
    Cmd *cmd = make_cmd();
    while(*p){
        while(*p && isspace(*p)){
            *p = '\0';
            p++;
        }
        if(*p && isidentify(*p)){
            break;
        }
        if(*p && isvalidchar(*p)){
            if(cmd->capa <= cmd->argc){
                cmd->capa *= 2;
                cmd->argv = xrealloc(cmd->argv, cmd->capa);
            }
            cmd->argv[cmd->argc] = p;
            cmd->argc++;
        }
        while(*p && isvalidchar(*p)){
            p++;
        }
    }
    if(cmd->capa <= cmd->argc){
        cmd->capa++;
        cmd->argv = xrealloc(cmd->argv, cmd->capa);
    }
    cmd->argv[cmd->argc] = NULL;
    if(*p == '|' || *p == '>'){
        cmd->next = parse(p+1);
        if(cmd->next == NULL || cmd->argc==0){
            fprintf(stderr, "Parse Error\n");
            exit(EXIT_FAILURE);
        }
    }
    return cmd;
}

/***** prompt and execute  *****/
#define PROMPT "$ "
#define SIZE_BUFFER 1024

void exec_command(Cmd *cmd){
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

void prompt(){
    char buf[SIZE_BUFFER];
    for(;;){
        fprintf(stdout, "%s", PROMPT);
        fflush(stdout);
        if(fgets(buf, SIZE_BUFFER, stdin)){
            Cmd *cmd = parse(buf);
            if(cmd == NULL){
                fprintf(stderr, "syntax error\n");
                exit(EXIT_FAILURE);
            }
            exec_command(cmd);
            free_cmd(cmd);
        }
    }
}

int main(int argc, char *argv[]){
    prompt();
    exit(EXIT_SUCCESS);
}
