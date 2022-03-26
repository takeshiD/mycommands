#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <regex.h>
#include <getopt.h>
#include <stdbool.h>
#include <string.h>

const char *usage = "Usage: mygrep [OPTION]... PATTERN [FILE ...]\n"
"-h, --help\t show this usage\n"
"-c, --color\t enhance matched pattern\n"
"-v, --inverse-match\t show non-matched lines\n"
"-i, --ignore\t ignore upper and lower case\n";

struct option long_options[] = {
    {"help",  no_argument,          NULL, 'h'},
    {"color", required_argument,    NULL, 'c'},
    {"ignore",no_argument,          NULL, 'i'},
    {"invert-match", no_argument,   NULL, 'v'},
    {0,0,0,0}
};

typedef enum COLOR COLOR;
enum COLOR{
    RED,
    GREEN,
    YELLOW,
    BLUE,
    NOT_IMPLEMENTED,
};


#define ARRAY_SIZE(arr) (sizeof((arr))/sizeof((arr)[0]))

char *color_start = "\x1b[31m";
const char *color_end   = "\x1b[39m";

COLOR set_color(const char *color){
    printf("color: %s\n", color);
    if(strcmp(color,"red")==0 || strcmp(color,"r")==0) return RED;
    else if(strcmp(color,"green")==0  || strcmp(color,"g")==0) return GREEN;
    else if(strcmp(color,"yellow")==0 || strcmp(color,"y")==0) return YELLOW;
    else if(strcmp(color,"blue")==0   || strcmp(color,"b")==0) return BLUE;
    else return NOT_IMPLEMENTED;
}

static void do_grep(regex_t *pat, FILE *src, bool inverse){
    char buf[4096];
    regmatch_t pmatch[1];
    regoff_t off, len;
    while(fgets(buf, sizeof(buf), src)){
        const char *cur = buf;
        if(inverse){
            if(regexec(pat, cur, ARRAY_SIZE(pmatch), pmatch, 0) != 0){
                printf("%s", cur);
            }
        }
        else{
            for(int i=0; cur!=NULL; i++){
                if(regexec(pat, cur, ARRAY_SIZE(pmatch), pmatch, 0) == 0){
                    off = pmatch[0].rm_so;
                    len = pmatch[0].rm_eo - pmatch[0].rm_so;
                    printf("%.*s", off, cur);
                    printf("%s", color_start);
                    printf("%.*s", len, cur + off);
                    printf("%s", color_end);
                    cur += pmatch[0].rm_eo;
                }else{
                    printf("%s", cur);
                    break;
                }
            }
        }
    }
}

int main(int argc, char **argv){
    int opt, index;
    int regopt = REG_EXTENDED | REG_NEWLINE;
    bool inverse = false;
    COLOR color = RED;
    while((opt = getopt_long(argc, argv, "hivc:", long_options, &index)) != -1){
        switch(opt){
            case 'h':
                fprintf(stdout, "%s\n", usage);
                exit(0);
            case 'i':
                regopt |= REG_ICASE;
                break;
            case 'v':
                inverse = true;
                break;
            case 'c':
                color = set_color(optarg);
                switch(color){
                    case RED:
                        color_start = "\x1b[31m";
                        break;
                    case GREEN:
                        color_start = "\x1b[32m";
                        break;
                    case YELLOW:
                        color_start = "\x1b[33m";
                        break;
                    case BLUE:
                        color_start = "\x1b[34m";
                        break;
                    default:
                        fprintf(stderr, "Error! specified color is not implemented!\n");
                        exit(1);
                }
                break;
            case '?':
                fprintf(stderr, "%s\n", usage);
                exit(1);
        }
    }
    regex_t pat;
    if(argc==optind){
        fputs("no pattern\n", stderr);
        exit(1);
    }
    int err = regcomp(&pat, argv[optind], regopt);
    if(err != 0){
        char buf[1024];
        regerror(err, &pat, buf, sizeof(buf));
        puts(buf);
        exit(1);
    }
    if(argc-optind==1){
        do_grep(&pat, stdin, inverse);
    }
    else{
        for(int i = optind+1; i<argc; i++){
            FILE *f;
            f = fopen(argv[i], "r");
            if(!f){
                perror(argv[i]);
                exit(1);
            }
            do_grep(&pat, f, inverse);
            fclose(f);
        }
    }
    regfree(&pat);
    exit(0);
}
