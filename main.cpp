#include <iostream>
#include <chrono>
#include <vector>
#include <future>
#include <string>

namespace {

class Clicker
{
public:
  Clicker():
    start_(std::chrono::high_resolution_clock::now())
  {}

  double millisec() const
  {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;

    const auto t = high_resolution_clock::now();
    return duration_cast< duration< double, std::milli > >(t - start_).count();
  }

private:
  std::chrono::high_resolution_clock::time_point start_;
};

using data_t = std::vector< unsigned long long >;
using value_t = data_t::value_type;

value_t threads_summer(const data_t &d, const int l, const int r)
{
  value_t s = 0;
  for (int i = l; i < r; ++i) {
    s += d[i];
  }
  return s;
}

}

int main(int argc, char **argv)
{
  const int thrs = std::stoi(argv[1]);
  constexpr size_t size{ 1'000'000'000 };
  double init{ 0 };
  double total{ 0 };
  value_t sum{ 0 };
  {
    const Clicker cl;
    const data_t values(size, 1);
    init = cl.millisec();
    std::vector< std::future< value_t > > fut;
    fut.reserve(thrs);
    const int potok_s = size / thrs;
    const int ost = size % thrs;
    int beg = 0;
    for (size_t i = 0; i < static_cast< size_t >(thrs); ++i) {
      int end = beg + potok_s;
      end += (i < static_cast< size_t >(ost) ? 1 : 0);
      fut.push_back(std::async(threads_summer, std::cref(values), beg, end));
      beg = end;
    }
    for (std::vector< std::future< value_t > >::iterator i = fut.begin(); i != fut.end(); ++i) {
      sum += i->get();
    }
    total = cl.millisec();
  }
  std::cout << total << '\n';
  std::cout << sum << '\n';
}
