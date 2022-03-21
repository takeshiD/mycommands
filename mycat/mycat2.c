#include <stdio.h>
#include <stdlib.h>

void _cat(FILE *f){
    if(!f){
        perror("FILE is null");
        exit(1);
    }
    int c;
    while((c=fgetc(f)) != EOF){
        if(fputc(c, stdout) == EOF) exit(1);
    }
}

int main(int argc, char **argv){
    if(argc < 2){
        _cat(stdin);
    }
    else{
        FILE *f;
        for(int i=1; i<argc; i++){
            f = fopen(argv[i], "r");
            _cat(f);
            fclose(f);
        }
    }
}
