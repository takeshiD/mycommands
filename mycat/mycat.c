#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 2048

static void die(const char *s){
    perror(s);
    exit(1);
}

static void do_cat(const int fd, const char *path){
    unsigned char buf[BUFFER_SIZE];
    ssize_t n;
    for(;;){
        n = read(fd, buf, sizeof buf);
        if(n<0) die(path);
        if(n==0) break;
        ssize_t status = write(STDOUT_FILENO, buf, n);
        if(status < 0) die(path);
    }
}

int main(int argc, char **argv){
    if(argc < 2){
        do_cat(STDIN_FILENO, "STDIN");
    }else{
        int fd;
        for(int i=1; i<argc; i++){
            fd = open(argv[i], O_RDONLY);
            if(fd<0) die(argv[i]);
            do_cat(fd, argv[i]);
            if(close(fd)<0) die(argv[i]);
        }
    }
}
