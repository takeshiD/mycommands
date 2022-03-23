#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

#define DEFAULT_N_LINES 10

static struct option longopts[] = {
    {"lines", required_argument, NULL, 'n'},
    {"help", no_argument, NULL, 'h'},
    {0,0,0,0},
};

void do_tail(FILE *f, int nlines){
    int c;
    fseek(f, 0, SEEK_END);
    while(nlines >= 0){
        c = fgetc(f);
        if(c == '\n' || c == EOF){
            nlines--;
        }
        fseek(f, -2, SEEK_CUR);
        if(ftell(f) <= 0){
            fseek(f, 0, SEEK_SET);
            break;
        }
    }
    fseek(f, 2, SEEK_CUR);
    while((c = fgetc(f)) != EOF){
        fputc(c, stdout);
    }
}

int main(int argc, char **argv){
    int opt;
    int nlines = DEFAULT_N_LINES;
    while((opt = getopt_long(argc, argv, "hn:", longopts, NULL)) != -1){
        switch(opt){
            case 'n':
                nlines = atol(optarg);
                break;
            case 'h':
                fprintf(stdout, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
                exit(0);
            case '?':
                fprintf(stdout, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
                exit(1);
        }
    }
    if(optind == argc){
        // do_tail(stdin, nlines);
        fprintf(stderr, "file specified");
        exit(1);
    }else{
        for(int i=optind; i<argc; i++){
            FILE *f;
            f = fopen(argv[i], "r");
            if(!f){
                perror(argv[i]);
                exit(1);
            }
            do_tail(f, nlines);
            fclose(f);
        }
    }
    exit(0);
}

