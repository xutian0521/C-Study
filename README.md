# C++Study

#### vscode C++ 快发环境搭建
1. vscode 插件：`C/C++` , `C/C++ Clang Command Adapter`, `Code Runner` C++ 编译插件，相当于帮你执行了g++ xxx.cpp -o xxx
2. 安装gcc/g++编译器： [windows 下 gcc/g++ 的安装](https://blog.csdn.net/qq_38080117/article/details/78022390)

#### vc6.0 迁移高版本编译器 问题
1. argument of type "const char *" is incompatible with parameter of type "LPCWSTR"
``` cpp
#include <tchar.h>

const char *__format="Hello";
LPCWSTR str3 = _T("Hello");
```
>`const char *` 和`char *` 等类型其实就是 `LPCWSTR` 这是开发工具在字符串强类型检查的 编码方式不同和兼容性问题，忽略开发工具报错，也是可以编译成功的
2. vc6.0 可以用void main函数，高版本必须int main函数。
3. FindWindow 等需要中文字符串参数的 函数, 需要用gb2312 编码保存，才能正常使用，否则无法找到中文标题的窗口