我希望通过这个项目加强自己对以下技能的应用:
+ C++ 编程语言与面向对象设计方法
+ socket网络编程
+ mysql数据库
+ redis

### 更早些时候
+ 使用string()初始化一个字符串类，用以实现一个常量字符串的拼接，比如 string()+"ABC"+"D"

### 2020-07-19 星期日
+ 函数传入参数还是尽量使用string吧，const char* 不太好拓展，可以使用string.data()转换成char*s
+ set<class A> 的insert方法传入参数是一个引用，也就是说要注意变量的生命周期
+ 为了使用set需要重载类的<和==方法，<必须是const的