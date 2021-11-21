
## 说明
- 在一个类中定义了两个智能指针相关的成员变量
  ```c++
    class ServerManager
    {
        // ...
        public:
        std::unordered_map<SID_t, std::shared_ptr<ServerInfo>> m_servers;
        std::unordered_map<SID_t, std::shared_ptr<ConnectInfo>> m_connects;
        
        ServerManager() = default;
        ~ServerManager() = default;
    };
  ```
  在 main 函数中执行如下测试:
  ```c++
    ServerManager manager;
  ```
  之后不做任何操作返回，会出现 core dump。将 coredump 文件保存，调用 gdb 查看，打印栈如下:
  ```shell
    #0  0x000000000041af63 in __gnu_cxx::__exchange_and_add (__mem=0x1fc49, __val=-1)
        at /usr/include/c++/4.8.2/ext/atomicity.h:49
    #1  0x000000000041afc3 in __gnu_cxx::__exchange_and_add_dispatch (__mem=0x1fc49, __val=-1)
        at /usr/include/c++/4.8.2/ext/atomicity.h:82
    #2  0x000000000041ca57 in std::_Sp_counted_base<(__gnu_cxx::_Lock_policy)2>::_M_release (this=0x1fc41)
        at /usr/include/c++/4.8.2/bits/shared_ptr_base.h:141
    #3  0x000000000041ca07 in std::__shared_count<(__gnu_cxx::_Lock_policy)2>::~__shared_count (this=0x13de3c8, 
        __in_chrg=<optimized out>) at /usr/include/c++/4.8.2/bits/shared_ptr_base.h:546
    #4  0x000000000041c826 in std::__shared_ptr<TCW::ServerInfo, (__gnu_cxx::_Lock_policy)2>::~__shared_ptr (
        this=0x13de3c0, __in_chrg=<optimized out>) at /usr/include/c++/4.8.2/bits/shared_ptr_base.h:781
    #5  0x000000000041c840 in std::shared_ptr<TCW::ServerInfo>::~shared_ptr (this=0x13de3c0, 
        __in_chrg=<optimized out>) at /usr/include/c++/4.8.2/bits/shared_ptr.h:93
    #6  0x000000000041c85e in std::pair<unsigned long const, std::shared_ptr<TCW::ServerInfo> >::~pair (
        this=0x13de3b8, __in_chrg=<optimized out>) at /usr/include/c++/4.8.2/bits/stl_pair.h:96
    #7  0x000000000041c87c in std::__detail::_Hash_node<std::pair<unsigned long const, std::shared_ptr<TCW::ServerInfo> >, false>::~_Hash_node (this=0x13de3b0, __in_chrg=<optimized out>)
        at /usr/include/c++/4.8.2/bits/hashtable_policy.h:189
    #8  0x000000000041c89a in __gnu_cxx::new_allocator<std::__detail::_Hash_node<std::pair<unsigned long const, std::shared_ptr<TCW::ServerInfo> >, false> >::destroy<std::__detail::_Hash_node<std::pair<unsigned long const, std::shared_ptr<TCW::ServerInfo> >, false> > (this=0x7ffdfb7ff0a8, __p=0x13de3b0)
        at /usr/include/c++/4.8.2/ext/new_allocator.h:124
    #9  0x000000000041c41d in std::_Hashtable<unsigned long, std::pair<unsigned long const, std::shared_ptr<TCW::ServerInfo> >, std::allocator<std::pair<unsigned long const, std::shared_ptr<TCW::ServerInfo> > >, std::__detail::_Select1st, std::equal_to<unsigned long>, std::hash<unsigned long>, std::__detail::_Mod_range_hashing, std::__detail::_Default_ranged_hash, std::__detail::_Prime_rehash_policy, std::__detail::_Hashtable_traits<false, false, true> >::_M_deallocate_node (this=0x7ffdfb7ff098, __n=0x13de3b0) at /usr/include/c++/4.8.2/bits/hashtable.h:746
    #10 0x000000000041be91 in std::_Hashtable<unsigned long, std::pair<unsigned long const, std::shared_ptr<TCW::ServerInfo> >, std::allocator<std::pair<unsigned long const, std::shared_ptr<TCW::ServerInfo> > >, std::__detail::_Select1st, std::equal_to<unsigned long>, std::hash<unsigned long>, std::__detail::_Mod_range_hashing, std::__detail::_Default_ranged_hash, std::__detail::_Prime_rehash_policy, std::__detail::_Hashtable_traits<false, false, true> >::_M_deallocate_nodes (this=0x7ffdfb7ff098, __n=0x0) at /usr/include/c++/4.8.2/bits/hashtable.h:763
    #11 0x000000000041b90a in std::_Hashtable<unsigned long, std::pair<unsigned long const, std::shared_ptr<TCW::ServerInfo> >, std::allocator<std::pair<unsigned long const, std::shared_ptr<TCW::ServerInfo> > >, std::__detail::_Select1st, std::equal_to<unsigned long>, std::hash<unsigned long>, std::__detail::_Mod_range_hashing, std::__detail::_Default_ranged_hash, std::__detail::_Prime_rehash_policy, std::__detail::_Hashtable_traits<false, false, true> >::clear (this=0x7ffdfb7ff098) at /usr/include/c++/4.8.2/bits/hashtable.h:1641
    #12 0x000000000041b60c in std::_Hashtable<unsigned long, std::pair<unsigned long const, std::shared_ptr<TCW::ServerInfo> >, std::allocator<std::pair<unsigned long const, std::shared_ptr<TCW::ServerInfo> > >, std::__detail::_Select1st, std::equal_to<unsigned long>, std::hash<unsigned long>, std::__detail::_Mod_range_hashing, std::__detail::_Default_ranged_hash, std::__detail::_Prime_rehash_policy, std::__detail::_Hashtable_traits<false, false, true> >::~_Hashtable (this=0x7ffdfb7ff098, __in_chrg=<optimized out>) at /usr/include/c++/4.8.2/bits/hashtable.h:958
    #13 0x000000000041b21e in std::unordered_map<unsigned long, std::shared_ptr<TCW::ServerInfo>, std::hash<unsigned long>, std::equal_to<unsigned long>, std::allocator<std::pair<unsigned long const, std::shared_ptr<TCW::ServerInfo> > > >::~unordered_map (this=0x7ffdfb7ff098, __in_chrg=<optimized out>)
        at /usr/include/c++/4.8.2/bits/unordered_map.h:97
    #14 0x000000000041b424 in TCW::ServerManager::~ServerManager (this=0x7ffdfb7ff040, __in_chrg=<optimized out>)
        at /home/test/tingchiwa/./manager.hpp:36
    #15 0x000000000041b0dc in main () at /home/test/tingchiwa/test/test.cpp:9
  ```
  析构那里出了问题。在 ServerManager 中的析构函数中添加如下代码:
  ```c++
    m_servers.clear();
    m_connects.clear();
  ```