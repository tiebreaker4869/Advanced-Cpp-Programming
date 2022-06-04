#include <iostream>
#include <vector>

using namespace std;

class MyBitVector {
private:
    // TODO: Add your private member variables here
    int currentSize;
    vector<char> data;
public:
    explicit MyBitVector(int size) {
        currentSize = size;
        for(int i = 0; i < currentSize; i ++){
            data.push_back('0');
        }
    }

    explicit MyBitVector(const string &s) {
        currentSize = s.size();
        for(int i = 0; i < currentSize; i ++){
            data.push_back(s[i]);
        }
    }

    void set(int index) {
        data[index] = '1';
    }

    void clear(int index) {
        data[index] = '0';
    }

    bool get(int index) {
        
        return data[index] - '0';
    }

    void print() {
        for(int i = 0; i < currentSize; i ++)cout << data[i];
        cout << endl;
    }

    // TODO: operator overloads to generate new bitvectors from existing ones
    MyBitVector operator&(MyBitVector &other) {
        MyBitVector ret(currentSize);
        for(int i = 0; i < currentSize; i ++){
            bool one = get(i) & other.get(i);
            if(one)ret.set(i);
        }
        
        return ret;
    }

    MyBitVector operator|(MyBitVector &other) {
        MyBitVector ret(currentSize);
        for(int i = 0; i < currentSize; i ++){
            bool one = get(i) | other.get(i);
            if(one)ret.set(i);
        }
        
        return ret;
    }

    MyBitVector operator^(MyBitVector &other) {
        MyBitVector ret(currentSize);
        for(int i = 0; i < currentSize; i ++){
            bool one = get(i) ^ other.get(i);
            if(one)ret.set(i);
        }
        
        return ret;
    }

    MyBitVector operator~() {
         MyBitVector ret(currentSize);
         for(int i = 0; i < currentSize; i ++){
             bool one = !get(i);
             if(one)ret.set(i);
         }
         
         return ret;
    }

    // TODO: operator overloads to modify existing bitvectors in place
    MyBitVector &operator&=(MyBitVector &other) {
        for(int i = 0; i < currentSize; i ++){
            bool one = get(i) & other.get(i);
            if(one)data[i] = '1';
            else data[i] = '0';
        }
        
        return *this;
    }

    MyBitVector &operator|=(MyBitVector &other) {
        for(int i = 0; i < currentSize; i ++){
            bool one = get(i) | other.get(i);
            if(one)data[i] = '1';
            else data[i] = '0';
        }
        
        return *this;
    }

    MyBitVector &operator^=(MyBitVector &other) {
        for(int i = 0; i < currentSize; i ++){
            bool one = get(i) ^ other.get(i);
            if(one)data[i] = '1';
            else data[i] = '0';
        }
        
        return *this;
    }

};

void test1() {
    MyBitVector bv1("01010100");
    MyBitVector bv2("11101111");
    MyBitVector bv3 = bv1 & bv2;
    bv1 &= bv2;
    bv1.print();
    bv2.print();
    bv3.print();
}

void test2() {
    MyBitVector bv1("00001000");
    MyBitVector bv2("11010011");
    MyBitVector bv3 = bv1 | bv2;
    bv1 |= bv2;
    bv1.print();
    bv2.print();
    bv3.print();
}

void test3() {
    MyBitVector bv1("00010010");
    MyBitVector bv2("10111001");
    MyBitVector bv3 = bv1 ^ bv2;
    bv1 ^= bv2;
    bv1.print();
    bv2.print();
    bv3.print();
}

void test4() {
    MyBitVector bv1("00100100");
    MyBitVector bv2 = ~bv1;
    bv1 = ~bv1;
    bv1.print();
    bv2.print();
}

void test5() {
    MyBitVector bv1("00000001");
    bv1.set(2);
    bv1.print();
}

#define TEST(x) std::cout << "test" << #x << "\n"; test##x();

int main() {
    TEST(1);
    TEST(2);
    TEST(3);
    TEST(4);
    TEST(5);
    return 0;
}