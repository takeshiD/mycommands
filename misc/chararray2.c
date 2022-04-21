#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Cmd Cmd;
struct Cmd {
    char **argv;
    int argc;
    int capa;
    Cmd *next;
};

bool is_ident_char(char c){
    switch(c){
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
#define SIZE_ARGV 8

Cmd *newCmd(){
    Cmd *cmd = malloc(sizeof(Cmd));
    if(cmd == NULL){
        perror("memory alloccation failed");
        exit(EXIT_FAILURE);
    }
    cmd->argv = malloc(sizeof(char*)*SIZE_ARGV);
    cmd->argc = 0;
    cmd->capa = SIZE_ARGV;
    cmd->next = NULL;
    return cmd;
}

void freeCmd(Cmd *cmdhead){
    Cmd *tmp = cmdhead->next;
    if(tmp != NULL){
        freeCmd(tmp);
    }
    free(cmdhead->argv);
    free(cmdhead);
}

void printCmd(Cmd *cmd){
    fprintf(stdout, "[");
    for(int i=0; i < cmd->argc; i++){
        fprintf(stdout, "\"%s\"", cmd->argv[i]);
        if(i<cmd->argc-1){
            fprintf(stdout, ", ");
        }
    }
    fprintf(stdout, "]");
    if(cmd->next != NULL){
        fprintf(stdout, " -> ");
        printCmd(cmd->next);
    }
    else{
        fprintf(stdout, "\n");
    }
}

bool isidentify(char c){
    switch(c){
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

Cmd *parse_command_line(char *cur){
    /*
     * In : "    ls    -la | head -n 5 | wc"
     * Out: ["ls -la"]->["head"]->["wc"]->[NULL]
     */
    Cmd *cmdhead = newCmd();
    while(*cur){
        while(*cur && isspace(*cur)){
            *cur = '\0';
            cur++;
        }
        if(*cur && isidentify(*cur)){
            break;
        }
        if(*cur && !isspace(*cur) && (isalnum(*cur) || *cur == '-')){
            if(cmdhead->capa <= cmdhead->argc){
                cmdhead->capa *= 2;
                cmdhead->argv = realloc(cmdhead->argv, cmdhead->capa);
            }
            cmdhead->argv[cmdhead->argc] = cur;
            cmdhead->argc++;
        }
        while(*cur && !isspace(*cur) && (isalnum(*cur) || *cur == '-')){
            cur++;
        }
    }
    if(cmdhead->capa <= cmdhead->argc){
        cmdhead->capa += 1;
        cmdhead->argv = realloc(cmdhead->argv, cmdhead->capa);
    }
    cmdhead->argv[cmdhead->argc] = NULL;
    if(*cur == '|' || *cur == '>'){
        if(cmdhead == NULL || cmdhead->argc == 0){
            fprintf(stderr, "parse error\n");
            exit(EXIT_FAILURE);
        }
        cmdhead->next = parse_command_line(cur+1);
        if(cmdhead->next == NULL || cmdhead->next->argc == 0){
            fprintf(stderr, "parse error\n");
            exit(EXIT_FAILURE);
        }
        *cur = '\0';
    }
    return cmdhead;
}

void test_printCmd(){
    Cmd *cmdhead = newCmd();
    cmdhead->argv[0] = "ls";
    cmdhead->argv[1] = "-la";
    cmdhead->argc = 2;
}

int main(int argc, char *argv[]){
    char p[] = "   ls   -la | head -n 5| wc";
    Cmd *cmd = parse_command_line(p);
    printCmd(cmd);
    exit(EXIT_SUCCESS);
}
