#include <stdio.h>
#include <stdlib.h>

char cha[3] = {'A','B','C'};

void hanoi(int end,int O ,int M ,int D) {
    if (end == 1) {
        printf("%c -> %c\n",cha[O],cha[D]);
    }else {
        hanoi(end-1,O,D,M);
        printf("%c -> %c\n",cha[O],cha[D]);
        hanoi(end-1,M,O,D);
    }
}

int main() {
    int temp = rand()%2; //doge
    hanoi(64,0,temp,3-temp);
    return 0;
}