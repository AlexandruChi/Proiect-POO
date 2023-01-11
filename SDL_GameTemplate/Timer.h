#pragma once
#include <chrono>

class Timer {
public:
	Timer(double duration, bool initial_call = false);
	bool run(bool reset = false);
	void reset();
	void duration(double duration);

private:
	double duration_;
	std::chrono::time_point<std::chrono::high_resolution_clock> start_;
	bool initial_call_;
};