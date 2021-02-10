
## 容器与 emplace_back

所有的标准容器(array 除外)都增加了类似的方法: emplace, emplace_hint, emplace_front, emplace_after 和 emplace_back 。

以 emplace_back 为例，它能够就地通过参数构造对象，不需要拷贝或者移动内存，相比 push_back 能更好地避免内存的拷贝与移动，使容器插入元素的性能得到进一步提升。

基本用法
```c++  
    struct A
    {
        int x;
        double y;
        A(int a, double b): x(a), y(b) {}
    };
    
    // main
    std::vector<A> v;
    v.emplace_back(1, 2);
    std::cout << v.size() << std::endl;
  ```

## 比较 push_back 和 emplace_back 的性能
```c++
    struct Complicated
    {
        int year;
        double country;
        std::string name;
        
        Complicated(int a, double b, std::string c) : year(a), country(b), name(c)
        {
            std::cout << "is constructed" << std::endl;
        }
        
        Complicated(const Complicated& other)
            : year(other.year), country(other.country), name(std::move(other.name))
        {
            std::cout << "is moved" << std::endl;
        }
    };
    
    // main
    std::map<int, Complicated> m;
    int anInt = 4;
    double aDouble = 5.0;
    std::string aString = "C++";
    std::cout << "-- insert --" << std::endl;
    m.insert(std::make_pair(4, Complicated(anInt, aDouble, aString)));
    
    std::cout << "-- emplace --" << std::endl;
    // should be easier for the optimizer
    m.emplace(4, Complicated(anInt, aDouble, aString));
    
    std::cout << "-- emplace_back --" << std::endl;
    std::vector<Complicated> v;
    v.emplace_back(anInt, aDouble, aString);
    
    std::cout << "-- push_back --" << std::endl;
    v.push_back(Complicated(anInt, aDouble, aString));
```
添加编译选项 `-fno-elide-constructors` 后，输出结果如下:
```c++
    -- insert --
    is constructed
    is moved
    is moved
    is moved
    -- emplace --
    is constructed
    is moved
    -- emplace_back --
    is constructed
    -- push_back --
    is constructed
    is moved
    is moved
```
