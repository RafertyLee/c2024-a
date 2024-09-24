#include <stdio.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
unsigned long long get_current_time_in_microseconds() {
    LARGE_INTEGER frequency, currentTime;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&currentTime);


    return (currentTime.QuadPart * 1000000) / frequency.QuadPart;
}


#else
#include <sys/time.h>]
long long get_current_time_in_microseconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000LL) + tv.tv_usec;
}
#endif

int main() {
    unsigned long long start_time = get_current_time_in_microseconds();

    int prime[500];
    for (int i = 0; i < 500; i++) {
        prime[i] = 0;
    }
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
    clock_t end = clock ();
    for (int i = 0; i < count; i++) {
        if (prime[i] == 0) {
            break;
        }
        printf("%d\n", prime[i]);
    }
    unsigned long long end_time = get_current_time_in_microseconds();
    printf("time = %lld us",end_time-start_time);
    return 0;
}
