#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#define DEFAULT_N_LINES 10;

static struct option longopts[] = {
    {"lines", required_argument, NULL, 'n'},
    {"help", no_argument, NULL, 'h'},
    {0, 0, 0, 0}
};

void do_head(FILE *f, int nlines){
    int c;
    while(nlines > 0){
        c = fgetc(f);
        if(c == '\n'){
            nlines--;
        }
        if(c == EOF){
            nlines = 0;
            exit(0);
        }
        fputc(c, stdout);
    }
}

int main(int argc, char **argv){
    int opt;
    int nlines = DEFAULT_N_LINES;
    while((opt = getopt_long(argc, argv, "n", longopts, NULL)) != -1){
        switch(opt){
            case 'n':
                nlines = atol(optarg);
                break;
            case 'h':
                fprintf(stdout, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
                exit(0);
            case '?':
                fprintf(stderr, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
                exit(1);
        }
    }
    if(optind == argc){
        do_head(stdin, nlines);
    }else{
        for(int i=optind; i<argc; i++){
            FILE *f;
            f = fopen(argv[i], "r");
            if(!f){
                perror(argv[i]);
                exit(1);
            }
            do_head(f, nlines);
            fclose(f);
        }
    }
    exit(0);
}
