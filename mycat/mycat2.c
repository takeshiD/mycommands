#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    FILE *f;
    int c;
    if(argc < 2){
        f = stdin;
        while(1){
            c = fgetc(f);
            if(c == EOF) break;
            if(putchar(c) < 0) exit(1);
        }
        fclose(f);
    }else{
        for(int i=1; i<argc; i++){
            f = fopen(argv[i], "r");
            if(!f){
                perror(argv[i]);
                exit(1);
            }
            while(1){
                c = fgetc(f);
                if(c == EOF) break;
                if(putchar(c) < 0) exit(1);
            }
            fclose(f);
        }
    }
    return 0;
}
