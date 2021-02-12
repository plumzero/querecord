
/** 成员模板不能是 virutal.
 *  如果模板允许 virtual, 那么用于实现虚函数的常规虚函数表技术就无法使用了，
 *  因为每次用一个新的实参类型调用时，连接程序就必须向虚表里加入一个表项。
 */

/**
 * 实现思路:
 *    1. 迭代器基类向下派生出迭代器子类；
 *    2. 迭代器子类聚合实例(容器)类，通过后者成员函数重写迭代器基类方法；
 *    3. 实例类聚合迭代器子类作为其[方法类]；
 *  注意: 在第 3 步实现中，实例类应该将迭代器基类作为其成员，以实现多态。这可以通
 *        过指针或引用方式实现。但实例类的中的每个成员应该最好是一个完整的自有对象，
 *        所以这里又设计一个抽象类 Aggregate ，之后从其派生出实例类。
 */
#include "iterator.h"

int main()
{
    BookShelf bookShelf;
    
    bookShelf.append(Book("Around the World in 80 Days"));
    bookShelf.append(Book("Bible"));
    bookShelf.append(Book("Cinderella"));
    bookShelf.append(Book("Daddy-Long-Legs"));
    BookShelfIterator it = bookShelf.iterator();
    
    while (it.hasNext()) {
        Book book = it.next();
        std::cout << book.getName() << std::endl;
    }
    
    return 0;
}
