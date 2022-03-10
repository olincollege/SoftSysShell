#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    char *string = "echo hello < foo.txt";
    char sep = '<';
    char *first = malloc(100);
    char *second = malloc(100);
    

    char *ret = strchr(string, sep);
    *ret++ = '\0';
  
    strcpy(first, string);
    printf("first: %s\n", first);
    // strcpy(second, ret);
    // printf("second: %s\n", second);
    return 0;
}
