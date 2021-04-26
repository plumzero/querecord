
#include <iostream>
#include <unordered_map>


int main()
{
    // 定义哈希函数
    {
        class Name
        {
        public:
            std::string firstname {};
            std::string lastname {};
        public:
            Name(const std::string& fn, const std::string& sn)
                : firstname(fn), lastname(sn) {}
            Name() = default;
            
            size_t hash() const { return std::hash<std::string>()(firstname + lastname); }
            // 缺省的恒等运算符
            bool operator==(const Name& name) const {
                return firstname == name.firstname && lastname == name.lastname;
            }
        };
        
        class Hash_Name
        {
        public:
            size_t operator()(const Name& name) const { return name.hash(); }
        };
        
        // 构造
        std::unordered_map<Name, size_t, Hash_Name> people {
            { {{"Ann","Ounce"},25}, {{"Bill","Bao"},46}, {{"Jack","Sprat"},77} },
            500,    // Bucket count
            Hash_Name()
        };
    }
    
    {
        class Name
        {
        public:
            std::string firstname {};
            std::string lastname {};
        public:
            Name(const std::string& fn, const std::string& sn)
                : firstname(fn), lastname(sn) {}
            Name() = default;
            
            size_t hash() const { return std::hash<std::string>()(firstname + lastname); }
            // bool operator==(const Name& name) const {
                // return firstname == name.firstname && lastname == name.lastname;
            // }
        };
        
        class Hash_Name
        {
        public:
            size_t operator()(const Name& name) const { return name.hash(); }
        };
        
        // 自定义一个恒等运算符
        class Name_Equal
        {
        public:
            bool operator()(const Name& lhs, const Name& rhs) const {
                return lhs.firstname == rhs.firstname && lhs.lastname == rhs.lastname;
            }
        };
        
        // 构造
        std::unordered_map<Name, size_t, Hash_Name, Name_Equal> people {
            { {{"Ann","Ounce"},25}, {{"Bill","Bao"},46}, {{"Jack","Sprat"},77} },
            500,        // Bucket count
            Hash_Name(),
            Name_Equal()
        };
    }

    return 0;
}