#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

unsigned long long fib(int n) {
    if (n == 1) {
        return 0;
    }

    unsigned long long prev = 0, cur = 1;
    for (int i = 2; i <= n; ++i) {
        unsigned long long nxt = prev + cur;
        if (nxt < prev) {
            printf("Overflow!\n");
            exit(1);
        }
        prev = cur;
        cur = nxt;
    }
    return cur;
}


unsigned long long fact(int n) {
    unsigned long long ans = 1;
    for (int i = 1; i <= n; ++i) {
        unsigned long long prev = ans;
        ans *= i;
        if (ans < prev) {
            printf("Overflow!\n");
            exit(1);
        }
    }
    return ans;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Excepted one argument!");
        exit(1);
    }

    int n = atoi(argv[1]);
    pid_t pid = fork();
    if (pid == 0) {
        unsigned long long ans = fact(n);
        printf("Factorial: %llu\n", ans);
    } else {
        unsigned long long ans = fib(n);
        printf("Fibonaci: %llu\n", ans);
        wait(NULL);
    }
    return 0;
}
