#include <stdio.h>

int main(){
    int v = 0;
    for(int i=0; i<10;i ++){
        for(int j=0; j<10; j++){
            v = 10*i + j;
            printf("\033[%dm%03d\033[0m ", v, v);
        }
        printf("\n");
    }
    return 0;
}
