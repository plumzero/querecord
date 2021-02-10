
#include <iostream>
#include <string>
#include <vector>

/**
 * 定义自己的进程内类型检测类。
 * 仅适用于静态编译时检查。
 */
class TypeId
{
public:
    template <typename T>
    static TypeId of()
    {
        static const char id_{};
        return TypeId(&id_);
    }
    /** 思想: 一个进程内只有一份，所以地址与类型可以认为一一对应 */
    operator size_t() const { return reinterpret_cast<size_t>(id_); }
    
	/** 定义相应的成员函数 */
    inline const char* name() {	/** 将地址作为类型的名字。unprintable, convert it */
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

class VBase
{
protected:
	VBase(TypeId id) : tid(id) {}
	virtual ~VBase(){}
	
	TypeId tid;
public:
	virtual bool isVoid() const = 0;
	
	
};

template <typename T>
class VDerived : public VBase
{
public:
	VDerived() : VBase(TypeId::of<T>()) {}
	virtual ~VDerived() {}
	
	virtual bool isVoid() const override { return false; }
};

template <>
class VDerived<void> : public VBase
{
public:
	VDerived() : VBase(TypeId::of<void>()) {}
	virtual ~VDerived() {}
	
	virtual bool isVoid() const override { return true; }
};

int main()
{
    {
        /** [1] 基本测试 */
		std::cout << "基本测试:" << std::endl;
        if (TypeId::of<void>() == TypeId::of<void>()) {
            std::cout << "the same type" << std::endl;
        } else {
            std::cout << "not the same type" << std::endl;
        }
        
        if (TypeId::of<void>() != TypeId::of<int>()) {
            std::cout << "not the same type" << std::endl;
        } else {
            std::cout << "the same type" << std::endl;
        }
        
        std::cout << TypeId::of<void>().name() << std::endl;
    }
	
	{
		/** [2] 应用测试 */
		std::cout << "应用测试:" << std::endl;
		
	}
    

    return 0;
}