
## 关于标准库自带的正则表达式
- 是 ECMAScript 语法，而不是经常接触的 PCRE 语法。
- 两者还是有点区别的，标准库自带正则用起来比较费劲。
- 个人不喜欢用 ECMAScript 语法的正则匹配，更适应 PCRE 语法的正则匹配。所以标准库正则这里只作简单了解。

## 基本模板类 std::basic_regex - 定义正则表达式模式串对象
- 定义
  ```c++
    template <class charT, class traits=regex_traits<charT>> class std::basic_regex;
  ```
- 用法示例
  ```c++
    std::basic_regex<char> integer_pattern("(-)?(0x)?([0-9a-zA-Z]+)|((0x)?0)");
    std::basic_regex<char> truthy_pattern("(t|T)(rue)?|1");
    std::basic_regex<char> falsy_pattern("(f|F)(alse)?|0");
  ```
## 基本模板类 std::match_results - 用于保存正则匹配结果
- 定义
  ```c++
    template <class BidirectionalIterator,
              class Alloc=allocator<std::sub_match<BidirectionalIterator>>>
        class std::match_results;
  ```
- 说明
    + 用于存储对一个序列串的正则匹配执行结果。匹配结果中会有一系列的 std::sub_match 类
      型对象与匹配到的子串对应。如果 std::match_results 不为空，第一个 std::sub_match
      存储整个序列串，后续的 std::sub_match 分别存储依次匹配到的子串。可以使用 $0 表示
      第一个 std::sub_match, $2 表示第二个，依此类推。
    + 执行完 std::regex_match, std::regex_search 或 std::regex_iterator 后，会自动填充 
      一个 std::match_results 对象。这个对象无法在这些函数的外部进行修改。
    + 可以像访问容器一样访问 std::match_results 对象中的子串，标准库中对 std::match_results
      定义了 str, length, position 等函数对子串进行操作。
- 相关成员函数
    + 对 std::match_results 的操作
        + `empty`   是否为空
        + `size`    匹配到的个数
    + 迭代器
        + `begin`   指向 std::match_results 的首个
        + `end`     指向 std::match_results 的尾部的下一个
    + 对 std::match_results 中元素的访问
        + `operator[]`  返回 std::sub_match
        + `prefix`      返回整个匹配串中，位于该子串前面的部分
        + `suffix`      返回整个匹配串中，位于该子串后面的部分
        + `length`      该子串的长度
        + `position`    该子串的索引
        + `str`         该子串的长度
    + 格式化
        + `format`      格式化 std::match_results 中的结果

## 基本模板类 std::sub_match
- 定义
  ```c++
    template <class BidirectionalIterator>
        class std::sub_match : public std::pair<BidirectionalIterator, BidirectionalIterator>;
  ```
- 说明
    + 存储 std::match_results 里保存的单独的子匹配对象。 

## 一些常用的模板特化
- typedef std::basic_regex<char>                          regex;
- typedef std::match_results<const char*>                 cmatch;
- typedef std::match_results<std::string::const_iterator> smatch;
- typedef std::sub_match<const char*>                     csub_match;
- typedef std::sub_match<std::string::const_iterator>     ssub_match;

## 可供调用的正则匹配函数

### std::regex_match - 将正则表达式与一个(已知长度的)字符串进行匹配
- 定义(常用)
  ```c++
    template <class charT, class Alloc, class traits>
        bool std::regex_match(const charT* s,
                              std::match_results<const charT*, Alloc>& m,
                              const std::basic_regex<charT, traits>& rgx,
                              std::regex_constants::match_flag_type flags = 
                                                std::regex_constants::match_default);
    template <class ST, class SA, class Alloc, class charT, class traits>
        bool std::regex_match(const std::basic_string<charT, ST, SA>& s,
                              std::match_results<typename std::basic_string<charT, ST, SA>::const_iterator, Alloc>& m,
                              const std::basic_regex<charT, traits>& rgx,
                              std::regex_constants::match_flag_type flags =
                                                std::regex_constants::match_default);
    template <class BidirectionalIterator first, BidirectionalIterator last>
        bool std::regex_match(BidirectionalIterator first,
                              BidirectionalIterator last,
                              std::match_results<BidirectionalIterator, Alloc>& m,
                              const std::basic_regex<charT, traits>& rgx,
                              std::regex_constants::match_flag_type flags = 
                                                std::regex_constants::match_default);
  ```
- 说明
    + 根据 rgx 对 s (或 first 和 last 之间的字符)进行匹配，将执行结果存储到 m 中。
    + 若匹配存在则返回 true，否则返回 false 。

### std::regex_search - 在一个(任意长的)数据流中搜索与正则表达式匹配的字符串


### std::regex_replace - 在一个(任意长的)数据流中搜索与正则表达式匹配的字符串并将其替换

