primes = [2, 3, 5, 7, 11]
base = 10
iterator = 0

def get_base_prime(num, base):
    res = 1
    i = 0
    while num > 0:
        res *= pow(primes[i], num % base)
        num = num // base
        i += 1
    return res

def base_loop(layer, base_prime):
    if layer == -1: 
        return

    global iterator
    for _ in range(base):
        base_loop(layer - 1, base_prime)
        base_prime *= primes[layer]
        iterator += 1
        print(iterator, base_prime, get_base_prime(iterator, base))
        

def print_base_primes(layer):
    base_loop(layer - 1, 1)

def main():
    digits = 2

    print_base_primes(digits)

if __name__ == "__main__":
    main()