#include "Timer.h"

Timer::Timer(double duration, bool initial_call) : duration_(duration), initial_call_(initial_call) {}

bool Timer::run(bool reset) {
    if (reset || initial_call_) {
        start_ = std::chrono::high_resolution_clock::now();
        initial_call_ = false;
        return true;
    }
    auto end = std::chrono::high_resolution_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start_).count();
    if (elapsed >= duration_) {
        start_ = std::chrono::high_resolution_clock::now();
        return true;
    }
    return false;
}

void Timer::reset() {
    start_ = std::chrono::high_resolution_clock::now();
}

void Timer::duration(double duration) {
    duration_ = duration;
}