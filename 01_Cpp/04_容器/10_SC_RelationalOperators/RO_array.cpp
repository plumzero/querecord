
#include <array>
#include <iostream>
#include <string>

int main()
{    
    {
        std::array<double, 10> c1 {
                                    1.23,
                                    2.71828,
                                    3.1415,
                                    4.78,
                                    5.21,
                                    6.18
                                };
        std::array<double, 10> c2 {
                                    1.23,
                                    2.71828,
                                    3.1415,
                                    4.78,
                                    5.21,
                                    6.18,
                                };
        if (c1 == c2) {
            std::cout << "c1 == c2." << std::endl;
        }
    }

    {
        std::array<double, 10> c3 {
                                    1.23,
                                    2.71828,
                                    3.1415,
                                    4.78,
                                    5.21,
                                    6.18
                                };
        std::array<double, 10> c4 {
                                    1.23,
                                    2.71828,
                                    3.1415,
                                    4.78,
                                    5.21,
                                };
        if (c3 != c4) {
            std::cout << "c3 != c4." << std::endl;
        }
    }
    
    {
        std::array<std::string, 5> c5 {
            "Thank you for standing behind me",
            "In all that I do",
            "I hope you're as happy with me",
            "as I am with you",
        };
        
        std::array<std::string, 5> c6 {
            "Thank you for standing behind me",
            "In all that I do",
            "I hope you're as happy with me",
            "As I am with you",
        };
        if (c5 > c6) {
            std::cout << "c5 > c6." << std::endl;
        }
    }
    
    {
        std::array<std::string, 5> c7 {
            "Thank you for standing behind me",
            "In all that I do",
            "I hope you're as happy with me",
            "As I am with you",
        };
        
        std::array<std::string, 5> c8 {
            "Thank you for standing behind me",
            "In all that I do",
            "I hope you're as happy with me",
            "as I am with you",
        };
        if (c7 < c8) {
            std::cout << "c7 < c8." << std::endl;
        }
    }
    
    {
        std::array<std::string, 5> c9 {
            "Thank you for standing behind me",
            "In all that I do",
            "I hope you're as happy with me",
            "as I am with you",
        };
        
        std::array<std::string, 5> c10 {
            "Thank you for standing behind me",
            "In all that I do",
            "I hope you're as happy with me",
            "As I am with you",
        };
        if (c9 >= c10) {
            std::cout << "c9 >= c10." << std::endl;
        }
    }
    
    {
        std::array<std::string, 5> c11 {
            "Thank you for standing behind me",
            "In all that I do",
            "I hope you're as happy with me",
            "As I am with you",
        };
        
        std::array<std::string, 5> c12 {
            "Thank you for standing behind me",
            "In all that I do",
            "I hope you're as happy with me",
            "as I am with you",
        };
        if (c11 <= c12) {
            std::cout << "c11 <= c12." << std::endl;
        }
    }
    
    return 0;
}
