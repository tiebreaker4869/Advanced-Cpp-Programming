#include <iostream>
#include <string>

class Content {
public:
    explicit Content(int id) : id(id) {
        std::cout << "create " << std::to_string(id) << std::endl;
    }

    ~Content() {
        std::cout << "destroy " << std::to_string(id) << std::endl;
    }
    
    void add_ref_count(){
        _ref_count ++;
    }
    
    void decrease_ref_count(){
        _ref_count --;
    }
    
    static void free_content(Content* p){
        delete p;
    }
    
    int get_ref_count(){
        return _ref_count;
    }

private:
    int id{-1};
    char data[1024]{};
    int _ref_count{0};
};

class SharedContainer {
public:
    //TODO
    explicit SharedContainer(int mem_id){
        _data = new Content(mem_id);
        _data->add_ref_count();
    }
    //TODO
    ~SharedContainer(){
        _data->decrease_ref_count();
        int count = _data->get_ref_count();
        if(count == 0)Content::free_content(_data);
        _data = nullptr;
    }
    //TODO
    SharedContainer(const SharedContainer &other){
       _data = other.get_data();
       _data->add_ref_count();
    }
    
    Content* get_data() const{return _data;}

    //TODO
    SharedContainer& operator=(const SharedContainer &other){
        Content* other_data = other.get_data();
        if(other_data == _data)return *this;
        if(_data == nullptr){
            _data = other_data;
        }else {
            _data->decrease_ref_count();
            int count = _data->get_ref_count();
            if(count == 0)Content::free_content(_data);
            _data = other_data;
        }
        _data->add_ref_count();
        return *this;
    }
    //TODO
    int get_count() const{
        return _data->get_ref_count();
    }

    SharedContainer(const SharedContainer &&) = delete;
    SharedContainer &operator=(const SharedContainer &&) = delete;

private:
    Content *_data{nullptr};
    //TODO: design your own reference counting mechanism
};

void test1(){
    SharedContainer m1(1);
    SharedContainer m2 = m1;
    SharedContainer m3(m2);
    std::cout << m1.get_count() << std::endl;
    std::cout << m2.get_count() << std::endl;
    std::cout << m3.get_count() << std::endl;
}

void test2(){
    SharedContainer m1(1);
    SharedContainer m2 = m1;
    m1 = m1;
    {
        SharedContainer m3 = m1;
        std::cout << m1.get_count() << std::endl;
    }
    std::cout << m1.get_count() << std::endl;
    std::cout << m2.get_count() << std::endl;
}

void test3(){
    SharedContainer m1(1);
    SharedContainer m2(2);
    m1 = m2;
    std::cout << m1.get_count() << std::endl;
    std::cout << m2.get_count() << std::endl;
    {
        SharedContainer m3(3);
        m1 = m3;
        std::cout << m1.get_count() << std::endl;
        std::cout << m2.get_count() << std::endl;
        std::cout << m3.get_count() << std::endl;
    }
    std::cout << m1.get_count() << std::endl;
    std::cout << m2.get_count() << std::endl;

}

int main(){
    test1();
    test2();
    test3();
    return 0;
}