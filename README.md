我希望通过这个项目加强自己对以下技能的应用:
+ C++ 编程语言与面向对象设计方法
+ socket网络编程
+ sqlite3数据库
+ redis

### 更早些时候
+ 使用string()初始化一个字符串类，用以实现一个常量字符串的拼接，比如 string()+"ABC"+"D"

### 2020-07-19 星期日
+ 函数传入参数还是尽量使用string吧，const char* 不太好拓展，可以使用string.data()转换成char*s
+ set<class A> 的insert方法传入参数是一个引用，也就是说要注意变量的生命周期(但是insert的应该是拷贝的)
+ 为了使用set需要重载类的<和==方法，<必须是const的

### 2020-07-24 星期五
+ 还是用sqlite3吧，mysql的C++操作实在是太麻烦了~

### 2020-07-28 星期二
+ 对于sqlite3的C++api, 查询表内容主要有回调函数和sqlite3_get_table两种方式，但是回调这种方式似乎要回调多次，感觉不太合适

### 2020-07-30 星期四
+ 使用一个DBGetTable类管理获取的表格，在析构函数中释放资源

### 2020-09-05 星期六
+ sqlite3_get_table 被认为是过时的接口，也许我应该换一种方式!(回调)

### 2020-09-12 星期六
+ 注意从客户端发来的消息可能含有"\n\r"等后缀，会影响判断


### 2021-02-04 Thu
+ I add a new branch named "docker", which is made for docker. It's more simple than master branch
