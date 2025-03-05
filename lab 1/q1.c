#include<stdio.h>

int main(){
    int a;
    float b;
    char c;
    printf("enter int : ");
    scanf("%d", &a);
    printf("a : %d\n", a);
    
    printf("enter float : ");
    scanf("%f", &b);
    printf("b : %f\n", b);
    
    printf("enter char : ");
    scanf(" %c", &c); 
    printf("c : %c\n", c);
    
    return 0;
}