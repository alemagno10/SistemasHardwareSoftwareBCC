#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    long num = (long)atoi(argv[1]);
    int resultado;
    if(num < 0) resultado = -1;
    else if(num % 2 == 0) resultado = 1;
    else resultado = 0;
    printf("%d\n", resultado);
    return resultado;
}