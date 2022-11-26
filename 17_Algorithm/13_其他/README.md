
### 蓄水池算法

随机取一行伪码:
```s
    i = 0               // 记录当前读到的行数
    s = null            // 保存最终选择的那一行
    
    for line in file
        i = i + 1
        r = [0, 1) 之间的随机数
        if r < 1 / i:   // 以 1 / i 的概率将 s 替换成第 i 行
            s = line
    
    return s            // 当读完整个文本文件的时候， s 随机指向任何一行
```

随机取 k 行伪码:
```s
    i = 0
    s = []              // 下标从 1 开始
    for line in file
        i = i + 1
        if i <= k:
            s.append(line)
        else:
            j = [1, i] 之间的随机数
            if j <= k:
                s[j] = line;

    return s
```

- [随机读取文件中某一行](read_certain_line.cpp)
- [随机读取文件中某几行](read_some_lines.cpp)

### 分区

将一个数组中的元素按照一定的条件进行分区(分成左右两个区)，常见的比如快速排序中的分区。这里介绍三种。

- [第一种](partition_1.cpp)
- [第二种](partition_2.cpp)
- [第三种](partition_3.cpp)
