
### std::aligned_storage

定义
```c++
    template<size_t Len, size_t Align = /* default alignment */>
        struct aligned_storage;
```
std::aligned_storage 提供了平凡标准布局类型适于作为任何大小至多为 Len 且对齐要求为 Align 的因数的对象的未初始化存储。

[示例程序](t/01_aligned_storage.cpp)

下面会进行一些实现。

示例的公共类定义如下:
```c++
    class Apple
    {
    public:
        Apple(int i, std::string c) : index(i), color(c) { std::cout << "called construction" << std::endl; }
        ~Apple(){ std::cout << "called destruction" << std::endl; }
    public:
        int index;
        std::string color;
    };
```

  
### 简单的实现

实现示例
```c++
    template<typename T>
    class Storage
    {
        typename std::aligned_storage<sizeof(T), alignof(T)>::type object;
    public:
        Storage() {}
        ~Storage() {
            reinterpret_cast<T*>(&object)->~T();
        }
        template<typename... Args>
        void construct(Args&&... args) {
            new (&object) T(std::forward<Args>(args)...);
        }
        T& value() {
            return *reinterpret_cast<T*>(&object);
        }
    };
```

不能将 construct 函数实现转移到构造函数中去，像下面的这种做法是无法编译通过的:
```c++
    template<typename... Args>
    Storage(Args&&... args) {
        new (&object) T(std::forward<Args>(args)...);
    }
```
因为构造函数在未返回之前，对象还未构造完成，这时对对象内成员的访问非法的。

使用示例如下:
```c++
    Storage<Apple> storeApple;
    storeApple.construct(1, "red");
    
    storeApple.value().color = "Green";
    
    std::cout << "index=" << storeApple.value().index << std::endl; 
    std::cout << "color=" << storeApple.value().color << std::endl; 
```

[示例程序]:(t/02_easy.cpp)


### 特性化实现

虽然已经将 Storage 定义为一个模板类，可以存储不同的类型。但是如果希望 Storage 更功能、更特性一些，那么就可以抽象出来一层界面，如下:
```c++
    class Feature
    {
    protected:
        Feature() {}
        virtual ~Feature(){}
    public:
        virtual void* memory() = 0;
        
        template<typename T, typename... Args>
        void construct(Args&&... args) {
            void *mem = memory();
            new (mem) T(std::forward<Args>(args)...);
        }
    };

    template <typename T>
    class Storage : public Feature
    {
        typename std::aligned_storage<sizeof(T), alignof(T)>::type object;
    public:
        Storage() : Feature() {}
        virtual ~Storage() {}
    public:
        virtual void* memory() override { return &object; }

        T& value() {
            return *reinterpret_cast<T*>(&object);
        }
    };
```

Feature 是一个顶层抽象类，用于定义功能。construct 作为一个通用适用接口，也定义在这里。在 Feature 声明某项特性，在派生类中实现，这样就可以实现功能特性多样的 Storage 了。

使用示例如下:
```c++
    Storage<Apple> storeApple;
    storeApple.construct<Apple>(1, "red");
    
    storeApple.value().color = "Green";
    
    std::cout << "index=" << storeApple.value().index << std::endl;
    std::cout << "color=" << storeApple.value().color << std::endl; 
```

[示例程序]:(t/02_feature.cpp)


### 较不推荐的实现

如果 Storage 中没有定义新成员变量，那么也可以在派生类的构造函数中直接调用 construct 函数:
```c++
    // class Feature 定义不变
    template <typename T, typename... Args>
    class Storage : public Feature
    {
        typename std::aligned_storage<sizeof(T), alignof(T)>::type object;
    public:
        Storage(Args&&... args) : Feature() {
            this->template construct<T>(std::forward<Args>(args)...);
        }
        virtual ~Storage() {}
    public:
        virtual void* memory() override { return &object; }

        T& value() {
            return *reinterpret_cast<T*>(&object);
        }
    };
```

使用示例如下:
```c++
    Storage<Apple, int, std::string> storeApple(1, "red");
    Apple apple = storeApple.value();
    
    storeApple.value().color = "Green";
    
    std::cout << "index=" << storeApple.value().index << std::endl;
    std::cout << "color=" << storeApple.value().color << std::endl; 
```
因为不需要显式调用 construct 函数，所以可以将其定义为 protected 访问控制。

这种方法不方便扩展，不建议使用。

[示例程序](t/02_deprecated.cpp)


### 更复杂的实现

加入了一些编译时类型判断的特性。

[示例程序](t/02_complicated.cpp)
