#include <math.h>
#include <stdio.h>

int main() {
    int prime[500];
    int count = 2;
    prime[0] = 2;
    prime[1] = 3;
    for (int i = 5; i <= 1000; i += 2) {
        for (int j = count - 1; ; j -= 1) {
            if (i % prime[j] == 0) {
                break;
            } else if(j == 0) {
                prime[count] = i;
                count++;

                break;
            }
        }


    }
    for (int i = 0; i < count; i++) {
        printf("%d\n", prime[i]);
    }
    return 0;
}