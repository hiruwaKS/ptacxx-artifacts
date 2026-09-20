# d260917-suite

## Purpose

- 使用大量语言特性，用于测试指针分析器
- 自带编译方式

## Data Generation

- overview
    - 语言版本
        - 见附录 A
        - 命名方式，标准+category+具体（+序号）.c/.cpp
        - `category.csv`
    - STL 版本
        - libstdc++ (by GCC)
        - libc++ (by LLVM)
    - 在 C11 与 C++20 这两个标准下已废弃的特性不再测试
    - 这里标准只是对使用最显著的语言特性分类，不是说程序必须要写成这个标准下的模样
- 素材来源
    - SVF Test-Suite
        - 断言简化：去掉 SVF Test-Suite 自己的 assert
        - 删改注释：去掉 SVF Test-Suite 自己的注释，加上文件来源引用（<svf-test-suite>/...）
        - 运行：用一个简单的编译器运行它，修补修补，确保rc=0
        - 流程：断言简化、删改注释、运行、命名
        - 主要素材
            - ba、ests、cs_、ests、fs_、ests、path_、ests、objtype_、ests、failed_、ests、complex_tests
            - TODO：mta 是多线程的，暂时不测试
        - 其他文件夹随机抽样 100 个样本（除了real-world和多线程）
            - 最后剔除 17 个不好编译的
- 再手动编写，文件命名
    - 统计所有 count <= 5 的
    - 不引入不测试的特殊特性，如 conversion
    - 使用至少2个指针，2个二级指针，6次指针解引用use，函数数目+控制流复杂度（圈复杂性）不低于10（简单估计，不用定量算）
    - 写完后，编译检查
- 分类
    - c
    - cpp，细分 stl impl sensitive 和 stl impl insensitive
- 编译方式
    - `python3 compile.py <LLVM_PATH> --libcxx <LIBCXX_PREFIX> [-j N] [--recompile FILE]`
    - cpp/sensitive： `clang++ -x c++ <src> -std=c++20 -emit-llvm -S -g -O0 [-nostdinc++ -isystem <LIBCXX_PREFIX>/include/c++/v1] -o <out>`
    - c： `clang++ -x c <src> -std=<c89|c99|c11> -emit-llvm -S -g -O0 -o <out>`（标准按文件名前缀）
        - src： `source/{c,cpp,cpp-std-impl-sensitive}`
        - out： `blob/<ver>/{c,cpp,stl-libstdcxx,stl-libcxx}`，输出 `<源文件名>.ll`
        - sensitive 两种 STL
    - 具体配置
        - LLVM
            - 14.0.6
            - 21.1.0
        - libc++
            - 14.0.0（`_LIBCPP_VERSION 14000`），头目录 `<LIBCXX14_INCLUDE>`（经 `--libcxx` 提供）
            - `llvm14` 与 `llvm21` 的 `stl-libcxx` 都用它
        - libstdc++
            - GCC 13.3.0（Ubuntu 13.3.0-6ubuntu2~24.04）
- 编译到目标文件运行验证
- 生成 `caseId.csv`

## Data Result

- 7 个c/cpp标准，56个 categories （每个>=5），共 751 个源文件
- ll 文件数目（llvm14 与 llvm21 相同）
    - c：328
    - cpp：247
    - stl-libstdcxx：176
    - stl-libcxx：172（libcxx14 编译 std20 预期失败 4 个）
    - 合计：923
- loc、时间分布： `distributions.png`

## Usage

- 用于后续插桩 `d260917-pts`

## Other

- Related Work
    - SVF与PhASAR：PTABen 是 PhASAR 内置的评测工具（`tools/ptaben`），用 SVF 的 Test-Suite 来评测 PhASAR 的别名分析。SVF 的 [Test-Suite](git@github.com:SVF-tools/Test-Suite.git) 是一套约 400 个手写 C/C++ 程序的微基准集，被编译成 LLVM bitcode 后作为 PTABen 的输入，真值取自测试用例中的 `aliascheck` 断言。
        - 缺点：测试用例是手动编写的，规模和覆盖范围有限，无法自动生成或扩展
        - 优点：基准固定 commit，使评测结果可复现、便于不同分析之间比较
- TODO
    - 多线程指针分析 mta
    - real-world programs
    - 复杂图结构（如 SCC）合成程序
    - 见附录A TODO

## Appendix A: Features in ISO C and C++ for Pointer-Analysis testing

- ISO C
    - C89/C90：
        - 基本取地址解引用
        - 空指针
        - 指针求差和偏移
        - struct初始化列表
        - struct整体赋值
        - union初始化列表
        - union整体赋值
        - 各种成员访问
        - void*
        - 函数指针
        - stdlib.h（下面的要分点）
            - 分配：malloc、calloc、realloc
            - free
            - qsort
        - string.h（下面的要分点）
            - memory：memcpy、memmove、memset、memcmp
            - string：strcpy、strcat、strchr、strstr
        - goto
        - 可变参数（stdarg.h）
        - conversion：自动类型提升、类型转换
    - C99
        - C95 没有相关特性，略
        - 变长数组
        - 指定初始化器
        - Compound Literals
        - Flexible Array Member
    - C11
        - aligned_alloc
        - 匿名结构体/联合体
    - TODO
        - POSIX
            - strdup
        - restrict （C99）
        - const 、volatile
        - register、 内联汇编
        - setjmp.h
        - 可能无法分析
        - c多线程支持（C11）
- C++
    - C++98
        - this指针
        - 构造函数
        - 析构函数
        - 虚函数
        - 拷贝构造函数
        - new
        - delete（对应的 operator、[]）
        - 异常 try、catch、throw
        - static_cast
        - dynamic_cast
        - const_cast
        - reinterpret_cast
        - STL（下面的要分点）
            - 线性容器：vector、list、deque
            - 其他容器：set、multiset、map、multimap、stack、queue、priority_queue
            - 迭代器
            - sort
            - copy
            - functional
            - 异常：exception、stdexcept
        - StrictAliasing  （C++98 标准 3.10/15）（下面的要分点）
            - 分析器能否区分静态类型和动态类型（运行时this的实际类型），而不是只看指针的声明类型？
            - 子对象与指针调整
            - char* 处理
    - C++11
        - C++03 没有相关特性，略
        - 移动语义
        - 高级指针：unique_ptr、shared_ptr、std::weak_ptr
        - Lambda 表达式
        - std::initializer_list
        - STL其他容器：std::array、std::forward_list、std::unordered_map、unordered_set
        - emplace
    - C++17
        - C++14 没有相关特性，略
        - memory：new 和 delete 的 std::align_val_t、uninitialized_default_construct、uninitialized_value_construct、uninitialized_copy、uninitialized_move、uninitialized_fill、destroy_at、destroy_n
        - 词汇类型：std::optional、std::variant、std::any、std::string_view
    - C++20
        - EBO：[[no_unique_address]] 与空基类优化（EBO）
        - memory：ranges::、make_shared_for_overwrite
    - TODO：
        - c++多线程支持（C++11）
        - std::launder （C++17）
