#include "../exercise.h"
#include <cmath>

// READ: 函数模板 <https://zh.cppreference.com/w/cpp/language/function_template>
// TODO: 将这个函数模板化
// int plus(int a, int b) {
//     return a + b;
// }
template<typename T> T plus(T a, T b) {
    return a + b;
}

const double EPSILON = 1e-9;

int main(int argc, char **argv) {
    ASSERT(plus(1, 2) == 3, "Plus two int");
    ASSERT(plus(1u, 2u) == 3u, "Plus two unsigned int");

    // THINK: 浮点数何时可以判断 ==？何时必须判断差值？
    ASSERT(plus(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(plus(1.25, 2.5) == 3.75, "Plus two double");
    // TODO: 修改判断条件使测试通过
    ASSERT(fabs(plus(0.1, 0.2) - 0.3) < EPSILON, "How to make this pass?");

    return 0;
}

// ANSWER:
// 当浮点数是通过运算产生，并且可能包含精度误差时，总是需要判断差值。这是因为大多数十进制小数（如
// 0.1）在二进制中无法精确表示，任何涉及到他们的计算都会引入微小的的舍入误差，这些误差在多次计算后
// 会累积，导致 == 比较失败。仅当浮点数是已知精确的字面量或特殊情况下的精确计算结果时，才可以使用
// == 比较。但为了避免潜在的错误，最佳实践是始终使用差值比较来判断浮点数的相等性。
