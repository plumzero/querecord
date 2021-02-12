
## std::bitset
- 定义
  ```c++
    template<size_t N> class bitset;
  ```
- 说明
    + 一个 bit 位只有两种可能性: 0 或 1, true 或 false, ...
    + 这个类可以看作是一组 bool 元素，但是在存储空间上进行了优化: 每个元素
      只占用一个比特位。
    + 每个比特位可以独立访问。c++ 语法中没有提供比特类型，但 c++ 提供了特殊
      引用类型 bitset::reference 来访问每个元素。
      ```c++
        class bitset:reference {
            friend class bitset;
            reference();                                // no public constructor
        public:
            ~reference();
            operator bool() const;                      // convert to bool
            reference& operator=(bool x);               // assign bool
            reference& operator=(const reference& x);   // assign bit
            reference& flip();                          // flip bit value
            bool operator~()const;                      // return inverse value
        };
      ```
    + bitset 可以从整型构造，可以转化为整型(to_ulong)或字符串(to_string)。
- 成员函数
    + [] 操作符
        + 从最右边的比特位开始统计。
    + size_t count() const;
        + 统计 bitset 中已经设置的比特数量。
    + size_t size() const;
        + 统计 bitset 中所有比特的数量。
    + bool test(size_t pos) const;
        + 判断某个位置的比特位是否设置。如果设置, 则为 true, 否则为 false 。
        + pos 从最右边的比特位开始统计，从 0 开始计数。
    + bool any() const;
        + 判断 bitset 中是否至少有一个被设置。如果是，则为 true, 否则为 false 。
    + bool none() const;
        + 判断 bitset 中是否所有的 bit 都没有设置。如果都没有，则为 true, 
          否则为 false 。
    + bool all() const;
        + 判断 bitset 中是否所有的 bit 都设置。如果是，则为 true, 否则为 false 。
    + bitset& set();
        + 将 bitset 中的所有比特数进行设置。
    + bitset& reset();
        + 将 bitset 中的所有比特数进行清空。
    + std::string to_string() const;
    + unsigned long to_ulong() const;