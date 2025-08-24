#include "../exercise.h"

// READ: `static` 关键字 <https://zh.cppreference.com/w/cpp/language/storage_duration>
// THINK: 这个函数的两个 `static` 各自的作用是什么？
static int func(int param) {
    static int static_ = param;
    // std::cout << "static_ = " << static_ << std::endl;
    return static_++;
}

int main(int argc, char **argv) {
    // TODO: 将下列 `?` 替换为正确的数字
    // ASSERT(func(5) == ?, "static variable value incorrect");
    // ASSERT(func(4) == ?, "static variable value incorrect");
    // ASSERT(func(3) == ?, "static variable value incorrect");
    // ASSERT(func(2) == ?, "static variable value incorrect");
    // ASSERT(func(1) == ?, "static variable value incorrect");
    ASSERT(func(5) == 5, "static variable value incorrect");
    ASSERT(func(4) == 6, "static variable value incorrect");
    ASSERT(func(3) == 7, "static variable value incorrect");
    ASSERT(func(2) == 8, "static variable value incorrect");
    ASSERT(func(1) == 9, "static variable value incorrect");
    return 0;
}

// ANWSER:
// 1. static before function -> Change linkage duration of the function to internal linkage.
// 2. static before variable ->
//    a. In function block: Change storage duration of the variable to static storage duration -- meaning only intialized once and keep last revoked value.
//    b. In file / namespace scope: Change linkage duration of the variable to internal linkage(same as function).