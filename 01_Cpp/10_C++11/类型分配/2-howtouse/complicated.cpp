
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

class TypeId
{
public:
    template <typename T>
    static TypeId of()
    {
        static const char id_{};
        return TypeId(&id_);
    }
    operator size_t() const { return reinterpret_cast<size_t>(id_); }

    inline const char* name() {
        return reinterpret_cast<const char*>(reinterpret_cast<size_t>(id_));
    }

    inline bool operator==(const TypeId &rhs) {
        return static_cast<size_t>(reinterpret_cast<size_t>(id_)) == static_cast<size_t>(rhs);
    }
    
    inline bool operator!=(const TypeId &rhs) {
        return static_cast<size_t>(reinterpret_cast<size_t>(id_)) != static_cast<size_t>(rhs);
    }
    
private:
    typedef const void* Id;

    explicit TypeId(Id id) : id_(id) {}

    Id id_;
};

enum class State {
    Pending,
    Fulfilled,
};

class Core
{
protected:
    Core(State state, TypeId id) : _state(state), _id(id) {}
    virtual ~Core(){}
    
    TypeId _id;
    State  _state;
public:
    virtual bool isVoid() const = 0;
    virtual void* memory() = 0;
    
    template<typename T, typename... Args>
    void construct(Args&&... args) {
        if (isVoid()) {
            throw std::runtime_error("can not construct a void type");
        }
        if (_id != TypeId::of<T>()) {
            throw std::runtime_error("type is not match");
        }
        
        void *mem = memory();
        new (mem) T(std::forward<Args>(args)...);
        _state = State::Fulfilled;
    }
};

template <typename T>
class Storage : public Core
{
    typename std::aligned_storage<sizeof(T), alignof(T)>::type object;
public:
    Storage() : Core(State::Pending, TypeId::of<T>()) {}
    virtual ~Storage() {}
    
    virtual bool isVoid() const override { return false; }
    virtual void* memory() override { return &object; }
    
    T& value() {
        if (_state != State::Fulfilled) {
            throw std::runtime_error("attempted to take the value of a not fulfilled value");
        }
        return *reinterpret_cast<T*>(&object);
    }
};

template <>
class Storage<void> : public Core
{
public:
    Storage() : Core(State::Pending, TypeId::of<void>()) {}
    virtual ~Storage() {}
    
    virtual bool isVoid() const override { return true; }
    void *memory() { return nullptr; }
};

class Apple
{
public:
    Apple(int i, std::string c) : index(i), color(c) {}
    ~Apple(){}
public:
    int index;
    std::string color;
};

int main()
{

    Storage<Apple> storeApple;
    storeApple.construct<Apple>(1, "red");

    storeApple.value().color = "Green";
    
    std::cout << "index=" << storeApple.value().index << std::endl; 
    std::cout << "color=" << storeApple.value().color << std::endl; 

    return 0;
}