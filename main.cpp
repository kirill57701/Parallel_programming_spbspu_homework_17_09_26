#include <iostream>
#include <chrono>
#include <vector>
#include <future>

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

using data_t = std::vector< unsigned long long >;
using value_t = data_t::value_type;

value_t threads_summer(const data_t& d, int l, int r) {
  value_t s = 0;
  for (int i = l; i < r; ++i)
  {
    s += d[i];
  }
  return s;
}

int main(int argc, char** argv) {
  int thrs = std::stoi(argv[1]);
  constexpr size_t size{1'000'000'000};
  double init{0}, total{0};
  value_t sum{0};
  {
    mtt::Clicker cl;
    data_t values(size, 1);
    init = cl.millisec();
    std::vector<std::future<value_t>> fut;
    fut.reserve(thrs);
    int potok_s = size/thrs;
    int ost = size % thrs;
    int beg = 0;
    for (size_t i = 0; i < values.size(); ++i) {
    sum += values[i];
  }
  total = cl.millisec();
  }
}
