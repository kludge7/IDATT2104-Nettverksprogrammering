//
// Created by Andreas Kluge Svendsrud on 10/01/2024.
//

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>

using namespace std;

mutex primeNumbersMutex;
vector<int> primeNumbers;
int lower = 0;
int upper = 10000;
int amountThreads = 5;

/**
 * Method that finds all the primes between a lowerBound and upperBound.
 * These numbers are then added to the global vector primeNumbers.
*/
void findPrimes(int lowerBound, int upperBound) {
    for (int number = lowerBound; number < upperBound; number++) {
        bool isPrime = true;

        if (number > 1) {
            for (int i = 2; i <= number / 2; i++) {
                if (number % i == 0) {
                    isPrime = false;
                    break;
                }
            }

            if (isPrime) {
                lock_guard<std::mutex> lock(primeNumbersMutex);
                primeNumbers.push_back(number);
            }
        }
    }
}

int main() {
    vector<thread> threads;

    int range = (upper - lower) / amountThreads;

    for (int i = 0; i < amountThreads; i++) {
        int threadLower = lower + i * range;
        int threadUpper = (i == amountThreads - 1) ? upper : threadLower + range;
        threads.emplace_back(&findPrimes, threadLower, threadUpper);
    }

    for (auto &thread : threads) {
        thread.join();
    }

    cout << "lol" << endl;

    sort(primeNumbers.begin(), primeNumbers.end());

    for(int primeNumber : primeNumbers) {
        cout << primeNumber << endl;
    }


    return 0;
}