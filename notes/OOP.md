# OOP

## Concept

- Program = A collection of Objects
- Object = Data + Operation
- Class

## Typical structure of OOP program

```cpp
//.h file: declaration
/**
*class definition, variable declaration, function declaration, inline function
**/
//a.h
class A {
    private:
    	int x;
    	int y;
    	int z;
    public:
    	//normal functions
    	void f();
    	void g();
    	//inline functions
    	void h(){
            cout << "request inline" << endl;
        }
};
```

```cpp
//.cpp file : implementation
//a.cpp
void A::f(){
    cout << "f implemented" << endl;
}

void A::g(){
    cout << "g implemented" << endl;
}
```

## constructor

- 负责对象的初始化
- 与类同名，无返回类型
- 自动调用，不能直接调用
- 可重载
- 编译器会自动提供一个默认无参数构造器，这里面做了什么？开辟空间，对象初始化
- 可以设成 private，接管对象的创建权，例子：单例模式

- 调用：自动调用

```cpp
//demo
class A {
    public:
    	A(){}
    	A(int i){}
    	A(char* p){}
};

int main(){
    A a1; //调用 A()
    A a2 = A();//调用 A(), 但是不能写成 A a2();
    A a3 = A(1);//调用 A(int i)
    A a4 = 1;//调用 A(int i)
    A a5("abcd");//调用 A(char*p)
    A a[4] = {"1", A(), 2, "abcd"};
    
    return 0;
}
```

## 成员初始化表

- 作为构造函数的补充
- 按照成员声明顺序执行
- 先于构造函数体执行

demo

```cpp
class A {
  public:
    int x;
    int y;
    char* p;
    //初始化顺序是 x = 1, y = 2, p = "abcd";
    A():x(1), p("abcd"), y(2){
        
    }
};
```

使用建议：

- 尽量使用初始化表代替直接赋值：效率高
- const 成员，reference成员，对象成员必须初始化
- 如果成员变量太多可以不遵守上述规则
  - 破坏了可读性

## 析构函数

- 语法: `~<class name>(){//...}`
- 对象消亡时自动调用
- public:
  - 可以声明成 private 接管资源的释放

## copy constructor

- 用同一类型的对象进行初始化
- 自动调用
- 默认拷贝构造函数：
  - 对逐个成员进行初始化
  - 对于对象成员，该定义是递归的

```cpp
//demo
public:
	A(const A& a){
        //...
    }
```

## move constructor

```cpp
string generate()
{    ......
     return string("test");
}

string S=generate();
string::string (String &&s):p(s.p)
{s.p=nullptr; }
```

## 动态对象

- 在 heap 创建的
- 用 new 创建，delete 释放
- new 会调用构造函数，delete 会调用析构函数

## const 成员变量

- 最好在成员初始化表进行初始化（但是直接在定义的地方初始化好像并不会报错）

## const 成员函数

- const 成员函数里面不能改变成员变量
- 机制是传入的 this 指针是 `const A* const this`

```cpp
//Demo
class A {
    public:
    	int x;
    	int y;
    	void f() const;
};
//violation
void A::f(){
    x = 1;//error
    cout << x << endl;//ok
}
```

## 静态成员变量

- 语法

```cpp
//demo
class A {
    public:
    	static int shared;
};

int A::shared = 1;
```

## 静态成员函数

- 语法

```cpp
class A {
    public:
    	static int shared;
    	static void f();
}

//调用
A::f();
```

- 通过类名调用
- 静态成员函数里面只能访问静态成员，以及调用静态成员函数，因为普通成员函数和成员变量需要依赖某一个对象实例才能存在，而静态成员函数是整个类的实例共享的。
- 遵守类的访问控制

## 友元

- 类外部不能访问 private 成员
- 需要通过 public 方法来访问
- 但是有时候需要频繁这么做，多次调用函数会降低效率

### 分类

- 友元类

  - 如果一个类 B 把 类 A 声明为 friend class，那么类 A 就可以访问 B 的私有和保护成员

  - ```cpp
    //demo
    class B {
      private:
        int private_int;
       friend class A;
    };
    
    class A {
        public:
        	void f(B b);
    };
    
    void A::f(B b){
        cout << b.private_int << endl;//ok
    };
    ```

    

- 友元成员函数：如果 一个类 B 把 A 的一个成员函数 f 声明为友元函数，那么只有这个函数里面能访问 B 的私有成员

```cpp
class B {
  private:
	int private_int;
   friend void A::f(B b);
};

class A {
    public:
    	void f(B b){
            cout << b.private_int << endl;//ok
        }
    	void g(B b){
            cout << b.private_int << endl;//error
        }
};
```

- 友元函数: 如果类 B 把一个函数声明为友元函数，那么这个函数可以访问类 B 的私有和保护成员

### 作用

- 提高灵活性
- 数据保护和数据存取的一个折中方案

## 继承

- 基于目标代码的复用
- 把事物分类
- 增量开发

### 单继承

- 语法：

```cpp
class A : public B {
    
};
//A public 继承 B
//继承方式还有 private 和 protected
```

- 派生类对象的初始化：
  - 由基类和派生类对象共同完成
- 构造函数执行顺序：
  - 基类构造函数
  - 成员对象构造函数
  - 派生类构造函数
- 析构函数执行次序
  - 与构造函数相反

- 基类构造函数的调用
  - 默认调用午餐构造，如果要调用重载的构造函数要在初始化表里面指出

## 虚函数

- 类型相容，赋值相容
- 当 B 是 A 的派生类的时候，b 赋值给 a 是可以的，但是 b 会丢掉派生类的属性，身份发生变化。
- 但是用指针的话身份不发生变化

```cpp
//比如如下情况, B 是 A 的派生类
A* p = new B;
```

- 前期绑定
  - 根据静态类型
  - 效率高，灵活性差
  - 编译时刻确定
- 后期绑定
  - 运行时刻确定
  - 根据对象实际类型
  - 效率低，灵活性高
- 注重效率
  - 默认前期绑定
  - 如果要后期绑定需要显式指出 `virtual`

### 语法

```cpp
virtual void f();
```

### 一些原则

- 成员函数才可以定义为虚函数
- 静态成员函数不能定义为虚函数
- 构造函数不能定义为虚函数
- 析构函数往往需要是虚函数

### 后期绑定的实现

```cpp
class A
{     int x,y;
public:
     virtual f();
    virtual g();
    h();
};
class B: public A
{      int z;
public:
       f();
      h();
};
A a; B b;
A *p; 

```



![](https://img2022.cnblogs.com/blog/2302323/202205/2302323-20220511155540701-1499405777.png)

通过虚函数表来实现

构造函数返回之后虚函数才能正常调用

### override，final 关键字

用 final 来指明这个函数不想被覆盖了，用 override 来指明这个函数是覆盖了基类的一个虚函数，编译器会检查有没有对应的虚函数在基类

### 纯虚函数

在生命后面加 = 0

往往只给出声明，无实现

### 抽象类

包含至少一个纯虚函数，不能创建对象，为子类提供一个框架



