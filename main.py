primes = [2, 3, 5, 7, 11, 13]
base = 3
iterator = 0

def get_base_prime(num, base):
    res = 1
    i = 0
    while num > 0:
        res *= pow(primes[i], num % base)
        num = num // base
        i += 1
    return res    

def base_loop(layer, base_prime, temp_arr, num_base_p):
    if layer == -1: 
        return

    global iterator
    global base
    next_iterator = iterator + pow(base, layer + 1) - 1
    i = 0
    while True:
        base_loop(layer - 1, base_prime, temp_arr[:], num_base_p)
        if i + 1 == base:
            break
        base_prime *= primes[layer]
        iterator += 1
        temp_arr[layer] += 1
        num_base_p += pow(10, layer)
        if base_prime == iterator:
            print(f"{temp_arr}, {num_base_p}, {base}, {base_prime}")
        elif base_prime > iterator:
            iterator = next_iterator
            break
        i += 1


def print_base_primes(layers):
    temp_arr = [0] * layers
    base_loop(layers - 1, 1, temp_arr, 0)

def scan_base_range(largest_base, layers):
    global base
    global iterator
    base = 3
    print("Number base p, equivalent base, base 10")
    while base <= largest_base:
        print_base_primes(layers)
        base += 1
        iterator = 0

def main():
    digits = 5

    scan_base_range(10000000, digits)

if __name__ == "__main__":
    main()
