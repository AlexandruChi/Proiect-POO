#include <cmath>
#include <utility>

using namespace std;

unsigned long long calculateDistance(pair<long long, long long> A, pair<long long, long long> B) {
    return (unsigned long long)sqrt(pow(B.first - A.first, 2) + pow(B.second - A.second, 2));
}
