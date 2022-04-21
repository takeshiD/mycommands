#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

const int BUFSIZE = 64;
const int SIZE = 32;
int main(int argc, char **argv){
    char *buf;
    buf = (char*)malloc(sizeof(char)*BUFSIZE);
    fprintf(stdout, "> ");
    if(fgets(buf, BUFSIZE, stdin) == NULL){
        perror("failed\n");
        exit(EXIT_FAILURE);
    }
    printf("receive: %s\n", buf);
    char *cur = buf;
    char chars[SIZE][SIZE];
    int i = 0;
    while(*cur){
        if(isspace(*cur)){
            fprintf(stdout, "\\0");
            cur++;
            i++;
            continue;
        }
        if(*cur == '\n'){
            fprintf(stdout, "\\n");
            cur++;
            continue;
        }
        putchar(*cur);
        strncat(chars[i], cur, 1);
        cur++;
    }
    putchar('\n');
    printf("[");
    for(int j=0; j<i; j++){
        printf("\"%s\",", chars[j]);
    }
    printf("]");
    putchar('\n');
    free(buf);
    exit(EXIT_SUCCESS);
}
