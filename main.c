#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define BASE_P_SIZE 8

int* primes;
int primes_count;
int base;
int iterator = 0;

int *sieve_of_eratosthenes(int limit, int *primes_count) {
    bool *is_prime = malloc((limit + 1) * sizeof(bool));
    if (is_prime == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i <= limit; i++)
        is_prime[i] = true;

    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= limit; i++) {
        if (!is_prime[i])
            continue;
        for (int j = i * i; j <= limit; j += i)
            is_prime[j] = false;
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

int power(int base, int exponent) {
    int result = 1;
    while (exponent > 0) {
        if (exponent & 1)
            result *= base;
        base *= base;
        exponent >>= 1;
    }
    return result;
}


int base10_to_base_n(int num, int base) {
    int remainders[100];
    int length = 0;

    div_t int_div;
    while (num > 0) {
        int_div = div(num, base);
        remainders[length++] = int_div.rem;
        num = int_div.quot;
    }

    int result = 0;
    for (int i = length - 1; i >= 0; i--)
        result += remainders[i] * power(10, i);

    return result;
}


long long get_base_prime(int num, int base) {
    long long res = 1;
    div_t int_div;
    for (int i = 0; num > 0; i++) {
        int_div = div(num, base);
        res *= power(primes[i], int_div.rem);
        num = int_div.quot;
    }
    return res;
}

void initalize_primes(int limit) {
    primes = sieve_of_eratosthenes(limit, &primes_count);
}

void free_primes() {
    free(primes);
    primes = NULL;
}

void initalize_base(int base_) {
    base = base_;
}

void print_arr(int* arr) {
    for (int i = 0; i < BASE_P_SIZE; i++) {
        printf("%d, ", arr[i]);
    }
}

void print_bitwise_p_bin(long bitwise_p) {
    int numBits = sizeof(long) * 8;
    
    for (int i = numBits - 1; i >= 0; i--) {
        if (bitwise_p & (1UL << i)) {
            printf("1");
        } else {
            printf("0");
        }
        if (i % 8 == 0 && i != 0) {
            printf(" ");
        }
    }
    printf(", ");
}

void print_bitwise_p(long bitwise_p) {
    int num_bytes = sizeof(long);
    char flag = 0;
    for (int i = num_bytes - 1; i >= 0; i--) {
        unsigned char byte = (bitwise_p >> (i * 8)) & 0xFF;
        if (!flag && byte != 0)
            flag = 1;
        if (flag) {
            if (byte <= 9) {
                printf("%c", byte + 48);
            }
            else {
                printf("%c", byte + 55);
            }
        }
    }
    printf(", ");
}

void base_loop(int layer, long base_prime, long bitwise_p) {
    if (layer == -1)
        return;

    int next_iterator = iterator + power(base, layer + 1) - 1;
    int i = 0;
    while (true) {
        base_loop(layer - 1, base_prime, bitwise_p);
        if (i++ == base)
            break;

        base_prime *= primes[layer];
        iterator++;
        bitwise_p += 1 << (layer * 8);
        if (base_prime == iterator) {
            print_bitwise_p(bitwise_p);
            printf("%d, %ld\n", base, base_prime);
        } else if (base_prime > iterator) {
            iterator = next_iterator;
            break;
        }
    }
}

void print_base_primes(int layers) {
    base_loop(layers - 1, 1, 0);
}

void scan_base_range(int largest_base, int layers) {
    base = 3;
    printf("Number base p, equivalent base, base 10\n");
    while (base <= largest_base) {
        print_base_primes(layers);
        base++;
        iterator = 0;
    }
}

int main() {
    int limit = 10000;
    initalize_primes(limit);
    initalize_base(10);
    
    int digits = 8;
    int largest_base = 100000000;
    scan_base_range(largest_base, digits);

    free_primes();

    return 0;
}
