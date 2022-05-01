# Structural-Programming

## Array

### 特征

- 存储相同类型的元素
- 存储空间连续

### 一维数组

- 类型定义 `T a[]`
- 函数接口 `void f(T a[], int n)` 数组大小需要当作参数传递，不能使用 `sizeof` (数组类型变量参与表达式就退化成指针类型)

### 多维数组

- 定义: `T a[][]`
- 存储组织 : 不管是一维还是多维，在内存中都表现为一片连续的空间，如 `int a[2][2]` 在内存中排列顺序为：`a[0][0],a[0][1],a[1][0],a[1][1]` 
- 参数传递 : 缺省第一维 `void f(T a[][m], int n)`
- 升降维处理 : 多维当作一维使用/一维当作多维使用，与指针有关。

## Struct

### struct

- 赋值 ： 同类型才可以赋值
- 内存分布：成员按声明顺序从高地址向低地址排列， 考虑对齐
- 参数传递 : 传递指针或者引用 (方便施加副作用/节省空间) `void f(T* s), void g(T& s)`

## Union

### union

- 存储分布：所有成员共享存储空间，占的大小和对齐以最大的成员为准
- 使用场景 : 对同一个位串做不同解释、实现某种多态行为

## Pointer

### 管理地址信息

- 管理数据 : 指向各种类型变量的指针
- 调用代码 : 函数指针

### 指针定义

- 格式`<base type> * <pointer variable>` : `T * p;`

- 使用 typedef 来定义一个指针类型 : `typedef int* Pointer; Pointer p, q;`, p,q 都是指针类型变量
- 赋值 : `int* p = 0x8048900; int * q = (int*)0x8048900`

### 操作符

- 取地址 `&`: `&x` 取出变量 x 的地址
- 间接引用 `*`: `*x` 简介引用指针变量 x 指向的内存空间，`*x = 1` 将 x 指向的变量赋值为 1 (假设 x 是指向整数类型的指针)

### 初始化

指针变量要初始化，如果没有合适的初始值要置为 `nullptr`, 防止访问到不该访问的内存。 

### 指针运算

- 赋值 : 同类型赋值
- 加减运算(与整型变量) : 基类型不变，改变的值为 `sizeof(base type) * 整型数值 `， `int* p; p ++;` p 的值改变了 4

- 同类型指针相加减 : 结果是整型，数值是偏移量 (指针值差/`sizeof(base type)`)
- 比较运算 : 只有 `!= , ==`

### 输出

```c++
int x = 1;
int * p = &x;
cout << p << endl; // p 的值 (x 的地址)
cout << *p << endl; //p 指向的整数的值
//特例 : 字符串
char* s = "abcd";
cout << s << endl; // 指针指向的字符串
cout << *s << endl;// 指向的字符，即 a
cout << (int*)s << endl;//地址值
```

### void*

只管理地址信息，不知道这块内存存的是什么

- 指针类型的公共接口 : 

  ```c++
  void *p;
  int x;
  double y;
  p = &x;
  p = &y;
  ```

- 要做任何操作必须强制类型转换

  ```C++
  *p = 1; //error
  
  *((double*) p) = 1;//OK
  *((int*) p) = 1;//OK
  //example : memset(void*, unsigned)
  void memset(void* p, unsigned n){
      char* q = (char*)p;
      for(unsigned i = 0; i < n; i ++){
          *q = 0;
          q ++;
      }
  }
  ```

  