#include <iostream>

class MyComplex {
public:
    MyComplex(int real, int imag) : real(real), imag(imag) {}
    int real;
    int imag;
    MyComplex operator+(const MyComplex& other) const {
        // TODO: implement this
        MyComplex temp{0, 0};
        temp.real = this->real + other.real;
        temp.imag = this->imag + other.imag;
        return temp;
    }
    friend std::ostream& operator<<(std::ostream& os, const MyComplex& mc);
};

std::ostream& operator<<(std::ostream& os, const MyComplex& mc) {
    // TODO: implement this
    os << "(" << mc.real << "," << mc.imag << ")";
    
    return os;
}


template <typename Ty1, typename Ty2>
auto GenericAdder(Ty1 a, Ty2 b) {
    return a + b;
}
// sample
template <>
auto GenericAdder(int a, std::string b) {
    return std::to_string(a) + b;
}
//TODO: write GenericAdder for string+int
template<>
auto GenericAdder(std::string a, int b){
    return a + std::to_string(b);
}
//TODO: write GenericAdder for int+MyComplex
template <>
auto GenericAdder(int a, MyComplex b){
    MyComplex ret{a, 0};
    
    return ret + b;
}
//TODO: write GenericAdder for (Ty1*)+(Ty2*)
template <typename T1, typename T2>
auto GenericAdder(T1* a, T2* b){
    return (*a) + (*b);
}

template <typename T1, typename T2>
auto GenericAdder(T1** a, T2** b){
    return (**a) + (**b);
}


void test1() {
    std::cout << GenericAdder(1, 2) << "\n";
    std::cout << GenericAdder(1.0, 2.0) << "\n";
    std::cout << GenericAdder(1, std::string("1")) << "\n";
}

void test2() {
    std::cout << GenericAdder(1, MyComplex(1, 3)) << "\n";
    std::cout << GenericAdder(MyComplex(1, 3), MyComplex(1, 3)) << "\n";
}

void test3() {
    MyComplex a{1, 3};
    MyComplex b{2, 6};
    std::cout << GenericAdder(&a, &b) << "\n";
}

void test4() {
  MyComplex a{1, 3};
  MyComplex b{2, 6};
  MyComplex *pa = &a;
  MyComplex *pb = &b;
  std::cout << GenericAdder(&pa, &pb) << "\n";
}

#define TEST(x) std::cout << "test" << #x << "\n"; test##x();

int main(){
  TEST(1);
  TEST(2);
  TEST(3);
  TEST(4);
  return 0;
}