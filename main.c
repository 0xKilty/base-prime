#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int* sieve_of_eratosthenes(int limit, int *primes_count) {
    bool *is_prime = malloc((limit + 1) * sizeof(bool));
    if (is_prime == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i <= limit; i++) {
        is_prime[i] = true;
    }

    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= limit; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }

    *primes_count = 0;
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i])
            (*primes_count)++;
    }

    int *primes = malloc((*primes_count) * sizeof(int));
    if (primes == NULL) {
        perror("Failed to allocate memory");
        free(is_prime);
        exit(EXIT_FAILURE);
    }

    int primes_index = 0;
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i])
            primes[primes_index++] = i;
    }

    free(is_prime);

    return primes;
}

int get_base_prime(int num, int* primes) {
    int res = 1;
    div_t int_div;
    int i = 0;
    while (num > 0) {
        int_div = div(num, 10);
        res *= pow(primes[i], int_div.rem);
        num = int_div.quot;
        i++;
    }
    return res;
}

int main() {
    int limit = 200;
    int primes_count;

    int *primes = sieve_of_eratosthenes(limit, &primes_count);

    int base_prime = get_base_prime(831704, primes);
    printf("%d\n", base_prime);

    free(primes);

    return 0;
}
