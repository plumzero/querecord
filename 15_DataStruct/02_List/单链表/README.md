

## 表数据结构
- 根据存储的不同，又可以分为顺序表和链表(这里以单链表为例)。
- 顺序表可以只采用一种数据结构，一般情况下主要包含 3 个成员，如下:
  ```c
    typedef struct __seq_list {
        DataType list[CAPACITY];
        int      capacity;
        int      size;
    } SeqList;
  ```
  成员分别为同类型数据对象数组、表容量及当前表尺寸。
- 单链表一般由两种数据结构组成，分别为表节点结构和链表上下文结构，各数据结构成员如下:
  ```c
    typedef struct _list_node {
        DataType data;
        struct _list_node* next;
    } ListNode;
    typedef struct _lnk_list {
        int size;
        ListNode* head;
    } LnkList;
  ```
  
## 说明
- 有的链表实现中只采用了一种表节点结构，但此时需要引入一个额外的头节点。这种方式相对来说较
  麻烦，且信息记录不便。
  使用表节点结构和链表上下文结构这种方式，除了能够方便地获取链表长度之外，还可以在 LnkList 中添加一些信息，比如尾指针，表节点回调，甚至可以实现简单的跳表查询。
- 链表数据结构每种结构都包含一个size成员，数据结构List和DList还包含有一个tail成员，为什么
 要在数据结构中包含这些成员呢?
 动态更新链表时，直接通过这些结构成员获得相关信息。通过维护这些成员，取得一个链表
 的尾部结点或者链表的结点个数就成为一种○(1)的操作，且不会为插入和移除操作增添任何
 复杂度。
