#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    fprintf(stderr, "*");
    sleep(1);
    fprintf(stderr, "\033[5G");
    sleep(1);
    fprintf(stderr, "\033[K");
    return 0;
}

