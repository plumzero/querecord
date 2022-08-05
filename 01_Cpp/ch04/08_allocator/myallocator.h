#include <stddef.h>

template<typename _Tp>
class myallocator
{
public:
    typedef size_t     size_type;
    typedef ptrdiff_t  difference_type;
    typedef _Tp*       pointer;
    typedef const _Tp* const_pointer;
    typedef _Tp&       reference;
    typedef const _Tp& const_reference;
    typedef _Tp        value_type;

    template<typename _Tp1>
    struct rebind
    { typedef myallocator<_Tp1> other; };


    myallocator() throw() { }

    myallocator(const myallocator&) throw() { }

    template<typename _Tp1>
    myallocator(const myallocator<_Tp1>&) throw() { }

    ~myallocator() throw() { }

    pointer
    allocate(size_type __n, const void* = 0)
    {
        return static_cast<_Tp*>(::operator new(__n * sizeof(_Tp)));
    }

    void
    deallocate(pointer __p, size_type)
    {
        if (nullptr != __p)
            ::operator delete(__p);
    }

    void 
    construct(pointer __p, const _Tp& __val)
    { ::new((void *)__p) _Tp(__val); }  // 在地址 __p 处构造 _Tp，并将 _Tp 赋值为 __val

    void 
    destroy(pointer __p) { __p->~_Tp(); }

    size_type
    max_size() const noexcept
    { return size_t(-1) / sizeof(_Tp); }

    pointer
    address(reference __x) const noexcept
    {
        return reinterpret_cast<_Tp*>
            (&const_cast<char&>(reinterpret_cast<const volatile char&>(__x)));
    }

    const_pointer
    address(const_reference __x) const noexcept
    {
        return reinterpret_cast<_Tp*>
            (&const_cast<char&>(reinterpret_cast<const volatile char&>(__x)));
    }

    // Inherit everything else.
};