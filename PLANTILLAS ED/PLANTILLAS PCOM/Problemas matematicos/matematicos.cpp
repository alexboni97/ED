#include<iostream>
#include<bitset>
#include<vector>
#include<cassert>
using namespace std;

// Numeros grandes
string suma(string a, string b) {
    string r;
    if (a.length() < b.length()) a.swap(b);
    b = string(a.length() - b.length(), '0') + b;
    unsigned int i = a.length(), carry = 0;
    while(i--) {
        carry += a[i] + b[i] - 2 * '0';
        r.push_back('0' + carry % 10);
        carry /= 10;
    }
    if (carry)
    r.push_back(carry + '0');
    reverse(r.begin(), r.end());
    return r;
}

// Numeros primos
void factoriza(unsigned int i) {
    assert(i >= 2); // O comprobaciones especiales
    unsigned int p = 2;
    while(p*p <= i) { // ¡Mucho mejor que sqrt!
        while(!(i % p)) {
            cout << p << ' ';
            i /= p;
        }
        ++p;
    }
    if (i != 1) // Podria quedarnos un unico primo
        cout << i << ' ';
    cout << '\n';
}

#define MAX_PRIME 5
using uint = unsigned int;

// Criba de Eratostenes
bitset<MAX_PRIME+1> bs; // #include <bitset>
    vector<uint> primes; // unsigned int
void sieve() {
    bs.set(); // De momento, todos son primos
    bs[0] = bs[1] = 0; // El 0 y el 1 no lo son.
    for (uint i = 2; i <= MAX_PRIME; ++i) {
        if (bs[i]) {
            // El actual es primo. Tiramos sus m´ultiplos
            for (uint j = i*i; j <= MAX_PRIME; j += i)
            bs[j] = 0; // i*i en el for ¡Cuidado con el rango!
            primes.push_back(i);
        } // if es primo
    } // for
} // sieve

bool isPrime(unsigned long long n) {
    if (n <= MAX_PRIME) 
        return bs[n];
    for (unsigned int i = 0; primes[i]*primes[i] <= n; ++i) {
        if (!(n % primes[i]))
            return false;
    }
    return true;
}