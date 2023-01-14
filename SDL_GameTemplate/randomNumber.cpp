#include <random>
#include <time.h>

using namespace std;

long long randomNumber(long long low, long long high) {
    static bool seeded = false;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = true;
    }
    return (rand() % (high - low + 1)) + low;
}