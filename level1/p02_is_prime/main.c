#include <math.h>
#include <stdio.h>

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    int limit = sqrt(number);
    if (number >= 2) {
        for (int i = limit; i < number; i++) {
            if (number % i == 0) {
                printf("%d is not prime\n", i);
                return 0;
            }
            else if (i == number - 1) {
                printf("%d is prime\n", number);
            }
        }
    } else {
        printf("%d <=1 \n", number);
    }
    return 0;


}