#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Returns gcd of a and b
long long gcd(long long a, long long b) {
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

// Function for modular exponentiation
unsigned long long expo(unsigned long long base, unsigned long long exponent, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;

    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % mod;

        exponent = exponent >> 1;
        base = (base * base) % mod;
    }

    return result;
}

int main() {
    long long i, num, n, count;

    // Public keys
    long long P = 4294967291;
    printf("The value of P: %lld\n\n", P);
    long long G = 2;
    printf("The value of G: %lld\n\n\n", G);

    // Alice Part
    printf("Enter the range for Alice:\n");
    scanf("%lld", &n);

    printf("\n\nThe prime numbers in between the range 1 to %lld:", n);

    for (num = 1; num <= n; num++) {
        count = 0;
        for (i = 2; i <= num / 2; i++) {
            if (num % i == 0) {
                count++;
                break;
            }
        }

        if (count == 0 && num != 1)
            printf("%lld ", num);
    }

    long long pa, qa, na, ea, Ka, da;
    long long phia;

    printf("\n\nEnter prime numbers (32 bits) for Alice:\n");
    scanf("%lld %lld", &pa, &qa);

    na = pa * qa;
    printf("\nna = %lld\n", na);

    phia = (pa - 1) * (qa - 1);
    printf("\nphi of a(%lld) = %lld\n", na, phia);

    for (ea = 2; ea < phia; ea++) {
        if (gcd(ea, phia) == 1) {
            printf("value of ea: %lld\n", ea);
            break;
        }
    }

    // Bob Part
    printf("\nEnter the range for Bob:\n");
    scanf("%lld", &n);

    printf("\nThe prime numbers in between the range 1 to %lld:", n);

    for (num = 1; num <= n; num++) {
        count = 0;
        for (i = 2; i <= num / 2; i++) {
            if (num % i == 0) {
                count++;
                break;
            }
        }

        if (count == 0 && num != 1)
            printf("%lld ", num);
    }

    long long pb, qb, nb, eb, db, Kb;
    long long phib;

    printf("\n\nEnter prime numbers (32 bits) for Bob:\n");
    scanf("%lld %lld", &pb, &qb);

    nb = pb * qb;
    printf("\nnb = %lld\n", nb);

    phib = (pb - 1) * (qb - 1);
    printf("\nphi of b(%lld) = %lld\n", nb, phib);

    for (eb = 2; eb < phib; eb++) {
        if (gcd(eb, phib) == 1) {
            printf("value of eb: %lld\n", eb);
            break;
        }
    }

    // Key Exchange
    int A, B;
    printf("\nEnter a Random Number for Alice:\n");
    scanf("%d", &A);

    unsigned long long ga = expo(G, A, P);
    printf("\nThe value of g^a is (KA): %llu\n", ga);

    printf("\nEnter a Random Number for Bob:\n");
    scanf("%d", &B);

    unsigned long long gb = expo(G, B, P);
    printf("\nThe value of g^b is (KB): %llu\n", gb);

    // Verification
    unsigned long long Sa = expo(gb, ea, na);
    unsigned long long verifyA = expo(Sa, ea, na);

    if (verifyA == (ga % na)) {
        printf("Sa verified\n");
    }

    unsigned long long Sb = expo(ga, eb, nb);
    unsigned long long verifyB = expo(Sb, eb, nb);

    if (verifyB == (gb % nb)) {
        printf("Sb verified\n");
    }

    return 0;
}