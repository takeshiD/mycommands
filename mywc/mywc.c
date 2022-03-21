#include <stdio.h>
#include <stdlib.h>

void _wc(FILE *f){
    int lines = 0;
    int words = 0;
    int c;
    while((c = fgetc(f)) != EOF){
        if(c == '\n') lines++;
        else words++;
    }
    fprintf(stdout, "%d %d\n", lines, words);
}

int main(int argc, char **argv){
    if(argc < 2){
        fprintf(stderr, "[Error]dont specified file\n");
        exit(1);
    }
    FILE *f;
    for(int i=1; i<argc; i++){
        f = fopen(argv[i], "r");
        if(!f){
            perror(argv[i]);
            exit(1);
        }
        _wc(f);
        fclose(f);
    }
    return 0;
}
