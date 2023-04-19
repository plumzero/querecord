
#include <cassert>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>

class Student
{
private:
    int id;
    std::string name;
    int score_1;
    int score_2;
    int score_3;
    int score_4;
    int score_5;
    
public:
    Student() = default;
    Student(int i, const std::string& n, int s1, int s2, int s3, int s4, int s5)
        : id(i), name(n), score_1(s1), score_2(s2), score_3(s3), score_4(s4), score_5(s5) {}

    friend std::istream& operator>>(std::istream& in, Student& st);
    friend std::ostream& operator<<(std::ostream& out, const Student& st);
};

inline std::istream& operator>>(std::istream& in, Student& st)
{
    return in >> st.id 
              >> st.name 
              >> st.score_1 
              >> st.score_2 
              >> st.score_3 
              >> st.score_4 
              >> st.score_5;
}

inline std::ostream& operator<<(std::ostream& out, const Student& st)
{
    return out << st.id      << ' '
               << st.name    << ' '
               << st.score_1 << ' '
               << st.score_2 << ' '
               << st.score_3 << ' '
               << st.score_4 << ' '
               << st.score_5;
}

int main ()
{
    // 结构体到文件
    {
        std::vector<Student> studs {
            { 1, "小明", 87, 97, 78, 88, 99 },
            { 2, "小丽", 67, 88, 76, 92, 65 },
            { 3, "小王", 56, 73, 64, 81, 65 },
            { 4, "小天", 12, 56, 36, 56, 47 },
            { 5, "小赵", 46, 75, 22, 85, 46 }
        };

        std::ofstream ofs("studs.txt", std::ofstream::out | std::ofstream::binary);
        assert(ofs.is_open());
        
        std::copy(std::begin(studs), std::end(studs), std::ostream_iterator<Student>{ ofs, "\n" });
        
        ofs.close();
    }

    // 文件到结构体
    {
        std::ifstream ifs("studs.txt", std::ifstream::in | std::ifstream::binary);
        assert(ifs.is_open());
        
        std::vector<Student> studs { std::istream_iterator<Student>{ifs}, std::istream_iterator<Student>{} };
        
        std::cout << "size=" << studs.size() << std::endl;
        
        std::copy(std::begin(studs), std::end(studs), std::ostream_iterator<Student>{ std::cout, "\n" });
        
        ifs.close();
    }

    return 0;
}