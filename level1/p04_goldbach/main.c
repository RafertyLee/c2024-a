#include <stdio.h>
int prime[50];


void get_prime_number(void) {
    int count = 2;
    prime[0] = 2;
    prime[1] = 3;
    for (int i = 5; i <= 100; i += 2) {
        for (int j = count - 1; ; j -= 1) {
            if (i % prime[j] == 0) {
                break;
            } else if (j == 0) {
                prime[count] = i;
                count++;

                break;
            }
        }
    }
}

int main() {
    get_prime_number();
    for (int i = 4; i <= 100; i += 2) {

        for (int j = 0; j <= 49; j++) {
            for (int k = 0; k <= 49; k++) {
                if (i == prime[j] + prime[k]) {
                    printf("%d = %d + %d\n", i, prime[j], prime[k]);
                    goto next;
                }
            }
        }
        next:
    }
    return 0;
}
