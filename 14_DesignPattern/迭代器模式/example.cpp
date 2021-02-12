
#include <iostream>
#include <string>
#include <vector>

/** 成员模板不能是 virutal.
 *  如果模板允许 virtual, 那么用于实现虚函数的常规虚函数表技术就无法使用了，
 *  因为每次用一个新的实参类型调用时，连接程序就必须向虚表里加入一个表项。
 */

class Iterator {
public:
	template <typename T> T& next();
	virtual bool hasNext() = 0;
};

class Book
{
public:
	Book(std::string n) : name(n) {}
	std::string getName() { return name; }
private:
	std::string name;
};

class Aggregate
{
public:
	virtual Iterator iterator() = 0;
};

class BookShelf : public Aggregate
{
public:
	BookShelf(int maxsize) {
		books.reserve(maxsize);
	}
	Book& operator[](int index) {
		return books.at(index);
	}
	Book& getBookAt(int index) {
		return books.at(index);
	}
	void appendBook(const Book& book) {
		books.push_back(book);
	}
	size_t getLength() {
		return books.size();
	}
	static Iterator iterator() {
		return BookShelfIterator(this);
	}
private:
	std::vector<Book> books;
};

class BookShelfIterator : public Iterator
{
public:
	BookShelfIterator(const BookShelf& bs) {
		bookShelf = bs;
		index = 0;
	}
	bool hasNext() {
		if (index < bookShelf.getLength()) {
			return true;
		} else {
			return false;
		}
	}
	
	Book& next() {
		return bookShelf.getBookAt(index++);
	}

private:
	BookShelf bookShelf;
	size_t    index;
};

int main()
{
	// BookShelf bookShelf = BookShelf(4);
	
	// bookShelf.appendBook(Book("Around the World in 80 Days"));
	// bookShelf.appendBook(Book("Bible"));
	// bookShelf.appendBook(Book("Cinderella"));
	// bookShelf.appendBook(Book("Daddy-Long-Legs"));
	// Iterator it = bookShelf.iterator();
	
	// while (it.hasNext()) {
		// Book book = it.next();
		// std::cout << book.getName() << std::endl;
	// }
	
	return 0;
}