#include <cstdint>
#include <functional>
#include <iostream>
#include <unordered_map>

template <uintmax_t N>
struct Fib {
  static constexpr uintmax_t value = Fib<N - 1>::value + Fib<N - 2>::value;
};

template<>
struct Fib<0> {
    static constexpr uintmax_t value = 0;
};

template<>
struct Fib<1> {
    static constexpr uintmax_t value = 1;
};

void test_1() { std::cout << Fib<0>::value << std::endl; }

void test_2() { std::cout << Fib<1>::value << std::endl; }

void test_3() { std::cout << Fib<2>::value << std::endl; }

void test_4() { std::cout << Fib<5>::value << std::endl; }

void test_5() { std::cout << Fib<20>::value << std::endl; }

int main() {
  std::unordered_map<std::string, std::function<void()>> test_cases_by_name = {
      {"test_1", test_1}, {"test_2", test_2}, {"test_3", test_3},
      {"test_4", test_4}, {"test_5", test_5},
  };
  std::string tname;
  std::cin >> tname;
  auto it = test_cases_by_name.find(tname);
  if (it == test_cases_by_name.end()) {
    std::cout << "输入只能是 test_<N>，其中 <N> 可取整数 1 到 5." << std::endl;
    return 1;
  }
  (it->second)();
}