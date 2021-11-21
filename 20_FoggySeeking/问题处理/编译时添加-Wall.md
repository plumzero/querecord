
## 运行出现异常
- 如下列程序
  ```c++
    class Stu
    {
    public:
        Stu(int i, int a) : index(i), age(a) {}
        ~Stu(){}
        
        int index;
        int age;
    };

    struct GreatEqualThanAge
    {
        bool operator()(const Stu& s) { s.age >= age; }
        GreatEqualThanAge(int a) : age(a) {}
    private:
        int age;
    };
    
    std::vector<Stu> Students;
    Students.emplace_back(1, 19);
    
    auto bl = std::all_of(Students.begin(), Students.end(), GreatEqualThanAge(18));
    std::cout << std::boolalpha << bl << std::endl;
  ```
  `-g -O0` 时编译通过，但运行结果却不是 true。
- 添加 -Wall 选项再次编译，有警告:
  ```shell
    warning: no return statement in function returning non-void [-Wreturn-type]
         bool operator()(const Stu& s) { s.age >= age; }
  ```
