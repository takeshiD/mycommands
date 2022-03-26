#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <regex.h>

#define ARRAY_SIZE(arr) (sizeof(arr))/sizeof((arr)[0])

//static const char *const str = "1) John Driverhacker;\n2) John Doe;\n3) John Foo;\n";
static const char *const str = "aabbccddee";
static const char *const re = "(aa)(b(bc)(c))(dd)";

int main(void){
    static const char *s = str;
    regex_t regex;
    regmatch_t pmatch[4];
    regoff_t off, len;
    if(regcomp(&regex, re, REG_EXTENDED)){
        exit(EXIT_FAILURE);
    }
    printf("String = \"%s\"\n", str);
    printf("Matches:\n");
    for(int i=0;; i++){
        if(regexec(&regex, s, ARRAY_SIZE(pmatch), pmatch, 0)) break;
        printf("-----------------\n");
        printf("array_size: %ld\n", ARRAY_SIZE(pmatch));
        printf("Original String:\n%s\n", str);
        printf("Now String:\n%s\n", s);
        printf("s-str:%jd\n", s-str);
        printf("rm_so[0]: %d\n", pmatch[0].rm_so);
        printf("rm_eo[0]: %d\n", pmatch[0].rm_eo);
        printf("rm_so[1]: %d\n", pmatch[1].rm_so);
        printf("rm_eo[1]: %d\n", pmatch[1].rm_eo);
        printf("rm_so[2]: %d\n", pmatch[2].rm_so);
        printf("rm_eo[2]: %d\n", pmatch[2].rm_eo);
        printf("rm_so[3]: %d\n", pmatch[3].rm_so);
        printf("rm_eo[3]: %d\n", pmatch[3].rm_eo);


        off = pmatch[0].rm_so + (s-str);
        len = pmatch[0].rm_eo - pmatch[0].rm_so;
        printf("#%d:\n", i);
        printf("offset=%jd; length=%jd\n", (intmax_t)off, (intmax_t)len);
        printf("substring=\"%.*s\"\n", len, s+pmatch[0].rm_so);
        s += pmatch[0].rm_eo;
    }
    exit(EXIT_SUCCESS);
}
