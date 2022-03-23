#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>

struct option longopts[] = {
    {"show-tabs", no_argument, NULL, 'T'},
    {"numbers", no_argument, NULL, 'n'},
    {"help", no_argument, NULL, 'h'},
    {0, 0, 0, 0},
};

int _cat(FILE *f, int line, bool numbers, bool tabs){
    int c;
    while((c=fgetc(f)) != EOF){
        if(c == '\t' && tabs){
            fputc('\\',stdout);
            fputc('t', stdout);
            continue;
        }
        if(c == '\n'){
            if(tabs){
                fputc('$', stdout);
            }
            fputc('\n', stdout);
            if(numbers){
                fprintf(stdout, "%*d ", 5, line);
                line++;
            }
            continue;
        }
        if(fputc(c, stdout) == EOF){
            return line;
        }
    }
    return line;
}

int main(int argc, char **argv){
    bool numbers = false;
    bool tabs = false;
    int opt;
    while((opt = getopt_long(argc, argv, "nt", longopts, NULL)) != -1){
        switch(opt){
            case 'n':
                numbers = true;
                break;
            case 'T':
                tabs = true;
                break;
            case 'h':
                fprintf(stdout, "Usage: %s [-n] [-T] [FILE ...]\n", argv[0]);
                exit(0);
            case '?':
                fprintf(stderr, "Usage: %s [-n] [-T] [FILE ...]\n", argv[0]);
                exit(1);
        }
    }
    int line = 1;
    if(argc == optind){
        _cat(stdin, line, numbers, tabs);
    }
    else{
        FILE *f;
        for(int i=1; i<argc; i++){
            f = fopen(argv[i], "r");
            if(!f){
                perror(argv[i]);
                exit(1);
            }
            line = _cat(f, line, numbers, tabs);
            fclose(f);
        }
    }
}
