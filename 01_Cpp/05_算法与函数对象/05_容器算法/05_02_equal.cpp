
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

/**
    可能的实现:
    版本一:
    template <class InputIterator1, class InputIterator2>
      bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
    {
      while (first1!=last1) {
        if (!(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
          return false;
        ++first1; ++first2;
      }
      return true;
    }
    版本二:
    template <class InputIterator1, class InputIterator2>
      bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred))
    {
      while (first1!=last1) {
        if (!pred(*first1,*first2))
          return false;
        ++first1; ++first2;
      }
      return true;
    }
    关键点:
        1. 输入迭代器
        2. 二元谓词，返回值为布尔类型
        3. 函数返回值: 布尔类型
 */

/** 大小写不敏感比较，相等返回 true ，不相等返回 false */
struct CaseInsensitive
{
    struct CaseInsensitiveCompare {
        bool operator()(const unsigned char &l, const unsigned char &r) const {
            return std::tolower(l) < std::tolower(r);
        }
        
        inline static bool compare(const unsigned char &l, const unsigned char &r) {
            return std::tolower(l) == std::tolower(r);
        }
    };
    
    /** 字符串的比较。静态函数，独立使用。 */
    static inline bool compare(const std::string &l, const std::string &r) {
        if (l.size() != r.size()) {
            return false;
        }
        
        return std::equal(l.begin(), l.end(), r.begin(), CaseInsensitiveCompare::compare);
    }
    
    /** 字符串按字典序比较 */
    inline bool operator()(const std::string &l, const std::string &r) {
        return std::lexicographical_compare(l.begin(), l.end(),
                                            r.begin(), r.end(),
                                            CaseInsensitiveCompare());
    }
};

int main()
{
    bool bl;
    {
        std::string str1("ABcde");
        std::string str2("aBcdE");
        bl = CaseInsensitive::compare(str1, str2);
        std::cout << std::boolalpha << bl << std::endl;
        std::string str3("aBcd");
        bl = CaseInsensitive::compare(str1, str3);
        std::cout << std::boolalpha << bl << std::endl;
    }
    
    {
        std::cout << std::endl;
        std::map<std::string, int> mapcase;
        mapcase.emplace("abcde", 100);
        mapcase.emplace("ABDef", 202);
        mapcase.emplace("AbceD", 90);
        mapcase.emplace("Abcde", 100);
        for (const auto & ele : mapcase) {
            std::cout << ele.first << " : " << ele.second << std::endl;
        }
        
        std::cout << std::endl;
        std::map<std::string, int, CaseInsensitive> mapnocase;
        mapnocase.emplace("abcde", 100);
        mapnocase.emplace("ABDef", 202);
        mapnocase.emplace("AbceD", 90);
        mapnocase.emplace("Abcde", 100);
        for (const auto & ele : mapnocase) {
            std::cout << ele.first << " : " << ele.second << std::endl;
        }
    }
    
    return 0;
}