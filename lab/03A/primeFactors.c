//

#include <stdio.h>

int factor(input){
    int retr = 0;
    int i = 2;
    while(i<input){
        if((input%i) == 0){
        	retr = i;
            return i;
        }
        i++;
    }
    return retr;
}


int main(void){
    int number;
    int pbuff;
    printf("Enter number: ");
    scanf("%d",&number);
    pbuff = number;
    //
    //printf("%d \n", factor(number));
    if(factor(number) == 0){
        printf("%d is prime \n", pbuff);
        return 0;
    }
    printf("The prime factorization of %d is: \n" , number);
    while(number > 1){
        if(factor(number) == 0) {
            printf("%d",number);
            break;
        }
        printf("%d * ",factor(number));
        number = number/factor(number);
    }
    printf(" = %d \n", pbuff);
    return 0;
}
