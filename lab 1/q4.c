#include <stdio.h>

int main() {
    int arr[10];  
    int sum = 0;  
    float average; 


    printf("Enter 10 integers:\n");
    for (int i = 0; i < 10; i++) {
        printf("Enter integer %d: ", i + 1);
        scanf("%d", &arr[i]);
    }


    for (int i = 0; i < 10; i++) {
        sum += arr[i]; 
    }


    average = sum / 10.0;

    printf("The average is: %.2f\n", average);

    return 0;
}
