//现代C++的起点

关键字constexpr，常量表达式修饰符
关键字explicit，关闭自动转换特性
关键字final，限制某个类不能被继承，或某个虚函数不能被重写
关键字override，表示重写基类虚函数，提高代码可读性
关键字auto，自动类型推导
关键字decltype，表达式类型推导
关键字using，为模板起别名
关键字nullptr表示指针空值
关键字char16_t
关键字char32_t
关键字static_assert静态断言
关键字=default启用默认函数
关键字=delete禁用默认函数

关键字组合enum class，强类型枚举
关键字组合long long，64位整型

关键字export，弃用留名

语法，原始字面量
语法，统一初始化列表
语法，基于范围的for循环
语法，lambda表达式
语法，函数后置返回类型
语法，类内成员初始化
语法，右值引用
语法，嵌套模板的...<...<>>
语法，模板默认参数
语法，委托构造函数
语法，继承构造函数

STL容器initializer_list初始化列表
STL容器array静态数组
STL容器forward_list单向链表
STL容器unordered_xxxx哈希表
STL容器成员函数cbegin()、cend()、crbegin()、crend()，将元素视为const
STL容器成员函数emplace()原地构造插入
STL functional，通用函数包装器，类型擦除，彻底改变了回调、事件和函数式编程的方式，革命性的抽象

11.可调用对象包装器、绑定器
14.转移和完美转发
15.共享智能指针
16.独占智能指针
17.弱引用智能指针


21.异常方面修改
数值类型和字符串之间的转换to_string函数


//C++14——对C++11的改进
auto可以推导函数返回类型（之前作占位符）从而不再需要后置返回类型
constexpr限制放松
二进制字面量和数值字面量分隔符