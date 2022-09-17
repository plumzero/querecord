
// 09 用两个栈实现队列

// 问题:
// 用两个栈实现一个队列。要求实现它的两个函数 push_back 和 pop_front

// 分析:
// 略

#include <stdio.h>
#include <stack>

template<typename T>
class CQueue
{
public:
    CQueue(){}
    ~CQueue(){}
public:
    void push_back(const T& node);
    T pop_front();
private:
    std::stack<T> _as_in;
    std::stack<T> _as_out;
};

template<typename T>
void CQueue<T>::push_back(const T& node)
{
    _as_in.push(node);
}

template<typename T>
T CQueue<T>::pop_front()
{
    if (_as_out.empty()) {
        while (_as_in.size() > 0) {
            _as_out.push(_as_in.top());
            _as_in.pop();
        }
    }

    if (! _as_out.empty()) {
        T node = _as_out.top();
        _as_out.pop();
        return node;
    }

    throw "queue is empty";
}

int main()
{
    CQueue<char> queue;

    queue.push_back('a');
    queue.push_back('b');
    queue.push_back('c');

    char head;
    
    head = queue.pop_front();
    printf("%c\n", head);

    head = queue.pop_front();
    printf("%c\n", head);

    queue.push_back('d');
    head = queue.pop_front();
    printf("%c\n", head);

    queue.push_back('e');
    head = queue.pop_front();
    printf("%c\n", head);

    head = queue.pop_front();
    printf("%c\n", head);

    return 0;
}