
#include <stdio.h>
#include <math.h>

bool is_prime(int n)
{
    bool is = true;
    int i = 2;
    
    while (i <= sqrt(n)) {
        if (n % i == 0) {
            is = false;
            break;
        }
        i++;
    }

    return is;
}

int main()
{
    printf("%d\n", is_prime(12000));
    printf("%d\n", is_prime(12011));

    return 0;
}