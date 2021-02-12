
## 说明

作为基本的序列容器，除了和 std::vector 与 std::deque 一样具有 erase 函数外，std::list 还提供了 remove 和 remove_if 函数。

因为底层数据结构不同，std::vector 与 std::deque 的 remove 操作是低效的，所以没有提供相关操作。

序列容器均具有的 erase 函数:
```c++
    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);
```
std::list 所特有的 remove/remove_if 函数:
```c++
    void remove(const value_type& val);
    template<typename Predicate> void remove_if(Predicate pred);
```

比较可以看出，erase 通过迭代器对某个元素值或某段区间内的元素进行删除。remove/remove_if 是逐个将容器内元素与某个同类型对象作对比，或者逐个判断容器内元素是否满足某个条件，之后再作删除。

## 测试内容

remove/remove_if 的使用测试

## 测试结果

与预想一致。