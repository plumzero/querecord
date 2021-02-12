
#include "iterator.h"

/** 迭代子类方法 */
bool BookShelfIterator::hasNext()
{
    if (index < bookShelfRef.size()) {
        return true;
    } else {
        return false;
    }
}

Book& BookShelfIterator::next()
{
    return bookShelfRef.at(index++);
}

/** 实例类方法 */
Book& BookShelf::at(int index)
{
    return books.at(index);
}

BookShelf& BookShelf::append(const Book& book)
{
    books.push_back(book);
    return *this;
}

size_t BookShelf::size()
{
    return books.size();
}

BookShelfIterator BookShelf::iterator()
{
    return BookShelfIterator(*this);
}
