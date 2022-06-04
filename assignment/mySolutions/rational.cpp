#include <cctype>
#include <cstring>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

int gcd(int a, int b){
    if(!b){
        return a;
    }
    
    return gcd(b, a%b);
}

template <typename T>
class Rational {
 public:
  Rational(const T &n, const T &d);
  Rational(const Rational<T> &rhs);

  T numerator() const;
  T denominator() const;

  Rational<T> operator+(const Rational<T> &rhs) const;
  Rational<T> operator-(const Rational<T> &rhs) const;
  Rational<T> operator*(const Rational<T> &rhs) const;
  Rational<T> operator/(const Rational<T> &rhs) const;

  Rational<T> &operator=(const Rational<T> &rhs);

  friend std::ostream &operator<<(std::ostream &out, const Rational<T> &r){
      int g = gcd((int)r.n, (int)r.d);
    int m = (int)r.n / g;
    int e = (int)r.d / g;
    if(e > 1)
        out << m << "/" << e;
    else out << m;
    
    return out;
  }

  // TODO: your code
  private:
  T n;
  T d;
};

template <typename T>
Rational<T>::Rational(const T &n, const T &d){
    if(d == 0)throw std::logic_error("denominator must be != 0");
    this->n = n;
    this->d = d;
}

template <typename T>
Rational<T>::Rational(const Rational<T> &rhs){
    this->n = rhs.numerator();
    this->d = rhs.denominator();
}

template <typename T>
T Rational<T>::numerator() const {
    return this->n;
}

template <typename T>
T Rational<T>::denominator() const {
    return this->d;
}

template <typename T>
Rational<T> Rational<T>::operator+(const Rational<T> &rhs) const {
    int n1 = (int)n;
    int n2 = (int)rhs.numerator();
    int d1 = (int)d;
    int d2 = (int)rhs.denominator();
    int n3 = n1 * d2 + n2 * d1;
    int d3 = d1 * d2;
    
    return Rational<T>((T)n3, (T)d3);
}

template <typename T>
Rational<T> Rational<T>::operator-(const Rational<T> &rhs) const {
    int n1 = (int)n;
    int n2 = (int)rhs.numerator();
    int d1 = (int)d;
    int d2 = (int)rhs.denominator();
    int n3 = n1 * d2 - n2 * d1;
    int d3 = d1 * d2;
    
    return Rational<T>((T)n3, (T)d3);
}

template <typename T>
Rational<T> Rational<T>::operator*(const Rational<T> &rhs) const {
    int n1 = (int)n;
    int n2 = (int)rhs.numerator();
    int d1 = (int)d;
    int d2 = (int)rhs.denominator();
    int n3 = n1*n2, d3 = d1*d2;
    return Rational<T>((T)n3, (T)d3);
}

template <typename T>
Rational<T> Rational<T>::operator/(const Rational<T> &rhs) const {
    int n1 = (int)n;
    int n2 = (int)rhs.numerator();
    int d1 = (int)d;
    int d2 = (int)rhs.denominator();
    int n3 = n1 * d2;
    int d3 = d1 * n2;
    return Rational<T>((T)n3, (T)d3);
}

template <typename T>
Rational<T> &Rational<T>::operator=(const Rational<T>& rhs){
    n = rhs.numerator();
    d = rhs.denominator();
    
    return *this;
}






Rational<int> operator""_r(const char *str, size_t len);

Rational<int> operator""_r(const char* str, size_t len){
    std::string n;
    std::string d;
    int index = 0;
    while(index < len && str[index] != '/'){
        n.push_back(str[index]);
        index ++;
    };
    index ++;
    while(index < len){
        d.push_back(str[index]);
        index ++;
    };
    int n_ = std::stoi(n);
    int d_ = std::stoi(d);
    
    return Rational<int>(n_, d_);
}

void test_1() {
  Rational<int> r(3, 4);
  std::cout << r << std::endl;
}

void test_2() {
  bool exception_thrown = false;
  bool expected_message = false;
  try {
    Rational<int> r = Rational<int>(1, 0);
  } catch (std::logic_error &exn) {
    exception_thrown = true;
    if (!strncmp(exn.what(), "denominator must be != 0", 24)) {
      expected_message = true;
    }
  } catch (...) {
  }
  if (exception_thrown) {
    std::cout << "std::logic_error thrown!" << std::endl;
    if (expected_message) {
      std::cout << "the message is as expected." << std::endl;
    }
  } else {
    std::cout << "Oops!" << std::endl;
  }
}

void test_3() {
  Rational<int> r(3, 4);
  std::cout << r.numerator() << ' ' << r.denominator() << std::endl;
}

void test_4() {
  Rational<int> lhs(1, 6), rhs(1, 3);
  std::cout << (lhs + rhs) << std::endl;
}

void test_5() {
  Rational<int> lhs(1, 2), rhs(1, 6);
  std::cout << (lhs - rhs) << std::endl;
}

void test_6() {
  Rational<int> lhs(2, 4), rhs(4, 6);
  std::cout << (lhs * rhs) << std::endl;
}

void test_7() {
  Rational<int> lhs(2, 4), rhs(4, 6);
  std::cout << (lhs / rhs) << std::endl;
}

void test_8() {
  Rational<int> r(3, 4);
  std::cout << r << std::endl;
  Rational<int> rhs(101, 203);
  r = rhs;
  std::cout << r << ' ' << rhs << std::endl;
}

void test_9() {
  auto r = "3/4"_r;
  std::cout << r << std::endl;
}

void test_10() { std::cout << Rational<int>(4, 2) << std::endl; }

void test_11() {
  std::cout << (Rational<int>(1, 2) - Rational<int>(2, 4)) << std::endl;
}

void test_12() { std::cout << Rational<int>(3, 6) << std::endl; }

int main() {
  std::unordered_map<std::string, std::function<void()>> test_cases_by_name = {
      {"test_1", test_1},   {"test_2", test_2},   {"test_3", test_3},
      {"test_4", test_4},   {"test_5", test_5},   {"test_6", test_6},
      {"test_7", test_7},   {"test_8", test_8},   {"test_9", test_9},
      {"test_10", test_10}, {"test_11", test_11}, {"test_12", test_12},
  };
  std::string tname;
  std::cin >> tname;
  auto it = test_cases_by_name.find(tname);
  if (it == test_cases_by_name.end()) {
    std::cout << "输入只能是 test_<N>，其中 <N> 可取整数 1 到 12." << std::endl;
    return 1;
  }
  (it->second)();
}