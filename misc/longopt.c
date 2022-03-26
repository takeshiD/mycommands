#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>

int main(int argc, char **argv){
    struct option longopts[] = {
        {"help", no_argument, NULL, 'h'},
        {"add", required_argument, NULL, 'a'},
        {"bad", no_argument, NULL, 'b'},
        {"chance", no_argument, NULL, 'c'},
        {0,0,0,0},
    };
    int opt, index;
    while((opt = getopt_long(argc, argv, "hbca:", longopts, &index)) != -1){
        printf("---------------------------\n");
        printf("opt    : %c\n", opt);
        printf("optarg : %s\n", optarg);
        printf("optind : %d\n", optind);
        printf("arv[%d]: %s\n", optind-1, argv[optind-1]);
        printf("index  : %d\n", index);
        printf("---------------------------\n");
    }
    printf("optind:%d, argc:%d\n", optind, argc);
    if(argc == optind){
        fprintf(stderr, "not pattern\n");
        exit(1);
    }
    for(int i=optind; i<argc; i++){
        printf("arg[%d] : %s\n", i, argv[i]);
    }
    return 0;
}
