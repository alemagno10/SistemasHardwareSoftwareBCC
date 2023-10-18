// gcc -o ex1 example1.c

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int sum = 0;
    if(argc > 2){
        for(int i = 1; i<argc; i++){
            int num = atoi(argv[i]); 
            if(num == 0 && argv[i][0] != '0'){
                sum += 0;
            } else {
                sum += num;
            }
        }
    } else {
        printf("erro\n");
    }
    printf("soma dos args: %d\n", sum);
}
