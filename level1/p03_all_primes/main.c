#include <math.h>
#include <stdio.h>

int main() {
    int prime[500];
    int count = 1;
    prime[0] = 3;
    for (int i = 5; i <= 1000; i += 2) {
        for (int j = count - 1; ; j -= 1) {
            if (i % prime[j] == 0) {
                break;
            } else if(j == 0) {
                printf("%d\n", i);
                prime[count] = i;
                count++;

                break;
            }
        }


    }
    return 0;
}