#include "../exercise.h"

// READ: 派生类 <https://zh.cppreference.com/w/cpp/language/derived_class>

static int i = 0;

struct X {
    int x;

    X(int x_) : x(x_) {
        std::cout << ++i << ". " << "X(" << x << ')' << std::endl;
    }
    X(X const &other) : x(other.x) {
        std::cout << ++i << ". " << "X(X const &) : x(" << x << ')' << std::endl;
    }
    ~X() {
        std::cout << ++i << ". " << "~X(" << x << ')' << std::endl;
    }
};
struct A {
    int a;

    A(int a_) : a(a_) {
        std::cout << ++i << ". " << "A(" << a << ')' << std::endl;
    }
    A(A const &other) : a(other.a) {
        std::cout << ++i << ". " << "A(A const &) : a(" << a << ')' << std::endl;
    }
    ~A() {
        std::cout << ++i << ". " << "~A(" << a << ')' << std::endl;
    }
};
struct B : public A {
    X x;

    B(int b) : A(1), x(b) {
        std::cout << ++i << ". " << "B(" << a << ", X(" << x.x << "))" << std::endl;
    }
    B(B const &other) : A(other.a), x(other.x) {
        std::cout << ++i << ". " << "B(B const &) : A(" << a << "), x(X(" << x.x << "))" << std::endl;
    }
    ~B() {
        std::cout << ++i << ". " << "~B(" << a << ", X(" << x.x << "))" << std::endl;
    }
};

int main(int argc, char **argv) {
    X x = X(1);
    A a = A(2);
    B b = B(3);

    // TODO: 补全三个类型的大小
    static_assert(sizeof(X) == 4, "There is an int in X");
    static_assert(sizeof(A) == 4, "There is an int in A");
    static_assert(sizeof(B) == 8, "B is an A with an X");

    i = 0;
    std::cout << std::endl
              << "-------------------------" << std::endl
              << std::endl;

    // 这是不可能的，A 无法提供 B 增加的成员变量的值
    // B ba = A(4);

    // 这也是不可能的，因为 A 是 B 的一部分，就好像不可以把套娃的外层放进内层里。
    A ab = B(5);// 然而这个代码可以编译和运行！
    // THINK: 观察打印出的信息，推测把大象放进冰箱分几步？
    // THINK: 这样的代码是“安全”的吗？
    // NOTICE: 真实场景中不太可能出现这样的代码

    i = 0;
    std::cout << std::endl
              << "-------------------------" << std::endl
              << std::endl;

    return 0;
}

// ANSWER0:
// 一、打开冰箱门
// ```bash
// 1. A(1)
// 2. X(5)
// 3. B(1, X(5))
// ```
// - 创建完整的派生类对象B(5)
// - 先调用基类A的构造函数
// - 再初始化成员变量X
// - 最后执行B自己的构造函数体
// 二、把大象放进冰箱
// ```bash
// 4. A（A const &） : a(1)
// ```
// - 执行对象切片操作
// - 通过A的拷贝构造函数，将B对象中的基类部分复制到新的A对象中
// - 这一步只保留了B对象中的"大象鼻子"（基类部分），而丢弃了"大象身体"（派生类特有部分）
// 三、关闭冰箱门
// ```bash
// 5. ~B(1, X(5))
// 6. ~X(5)
// 7. ~A(1)
// ```
// - 临时B对象被销毁
// - 先调用B的析构函数
// - 然后销毁成员变量X
// - 最后调用基类A的析构函数
//
// ANSWER1:
// 这种代码是不安全的，此处即触发了对象切片操作，因为 B 是 A 的一部分，所以可以把 B 赋值给 A，但是 A 没有
// B 的成员变量，所以派生类中特有的部分（x）会被“切片”掉。所以会调用 A(A const &) : a(1) 构造函数。总结
// 下来：
// 1. 语法合法但不推荐：C++允许派生类对象赋值给基类对象，但这种做法违背面向对象设计原则。
// 2. 核心问题：会发生"对象切片"，派生类特有的成员变量和行为被丢弃，只保留基类部分。
// 3. 安全性评估：
//    - 简单类（无动态资源）基本不会崩溃
//    - 多态场景下极其危险（虚函数调用失效）
//    -代码维护性差，易出错
// 4. 推荐替代：使用指针、引用或智能指针（如 A* ab = new B(5)），可保留多态行为，避免切片问题。
