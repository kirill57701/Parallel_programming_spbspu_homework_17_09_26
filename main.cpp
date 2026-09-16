#include <iostream>
#include <chrono>

class Clicker {
public:
  Clicker() : start_(std::chrono::high_resolution_clock::now()) {}

  double millisec() const {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;

    auto t = high_resolution_clock::now();
    return duration_cast<duration<double, std::milli>>(t - start_).count();
  }

private:
  std::chrono::high_resolution_clock::time_point start_;
};

int main() {
  std::cout << "std::cout";
}
