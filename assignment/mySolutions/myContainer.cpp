#include <iostream>

class MyContainer {
public:
    MyContainer(int size) : _size(size) {
        // TODO
        std::cout << "constructor" << std::endl;
        _count ++;
        _data = new int[_size];
    }

    ~MyContainer() {
        // TODO
        std::cout << "release..." << std::endl;
        _count --;
        delete[] _data;
    }

    MyContainer(const MyContainer &Other) {
        // TODO
        std::cout << "copy" << std::endl;
        _count ++;
        int* p = Other.data();
        int size = Other.size();
        delete[] _data;
        _data = new int[size];
        for(int i = 0; i < size; i ++){
            _data[i] = p[i];
        }
    }

    MyContainer &operator=(const MyContainer &Other) {
        // TODO
        if(_data == Other.data())return *this;
        int* p = Other.data();
        int size = Other.size();
        delete[] _data;
        _data = new int[size];
        for(int i = 0; i < size; i ++)_data[i] = p[i];
        return *this;
    }

    int size() const {
        return _size;
    }

    int* data() const {
        return _data;
    }

    static int count() {
        return _count;
    }

    static int _count;

private:
    // C++11 引入的 initializer_list
    int *_data{nullptr};
    int _size{0};
};

int MyContainer::_count = 0;

void test1(){
    MyContainer m(5);
    std::cout << m.count() << std::endl;

    MyContainer m2(m);
    std::cout << m2.count() << std::endl;

    MyContainer m3 = m2;
    std::cout << m3.count() << std::endl;
}

void test2(){
    MyContainer m1(5);
    std::cout << m1.count() << std::endl;

    MyContainer m2 = m1;
    std::cout << m2.count() << std::endl;
    std::cout << (m2.data() == m1.data()) << std::endl;
}

void test3(){
    MyContainer m1(3);
    std::cout << m1.count() << std::endl;

    MyContainer m2 = m1;
    std::cout << m2.count() << std::endl;
    std::cout << (m2.data() == m1.data()) << std::endl;

    m1 = m2;
    std::cout << m1.count() << std::endl;
    std::cout << (m2.data() == m1.data()) << std::endl;

    m2 = m1;
    std::cout << m2.count() << std::endl;
    std::cout << (m2.data() == m1.data()) << std::endl;

    int * prev_ptr = m1.data();
    m1 = m1;
    std::cout << m1.count() << std::endl;
    std::cout << (m1.data() == prev_ptr) << std::endl;

}

void test4(){
    MyContainer m1(3);
    std::cout << m1.count() << std::endl;

    {
        MyContainer m2 = m1;
        std::cout << m2.count() << std::endl;
        std::cout << (m2.data() == m1.data()) << std::endl;

        m1 = m2;
        std::cout << m1.count() << std::endl;
        std::cout << (m2.data() == m1.data()) << std::endl;

        m2 = m1;
        std::cout << m2.count() << std::endl;
        std::cout << (m2.data() == m1.data()) << std::endl;

    }

    std::cout << m1.count() << std::endl;
}

MyContainer get(){
  MyContainer m {1};
  return m;
}

void additionalTest(){
    MyContainer m = get();
}

int main(){
    test1();
    test2();
    test3();
    test4();
    additionalTest();
    return 0;
}