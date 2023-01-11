#include <random>
#include <time.h>

using namespace std;

long long randomNumber(long long low, long long high) {
	random_device device;
	mt19937 rng(device());
	uniform_int_distribution<long long> distribution(low, high);
	return distribution(rng);
}