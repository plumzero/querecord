
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <memory>
#include <algorithm>

int main()
{
    // shared_ptr<T>
    {
        std::vector<std::shared_ptr<std::string>> words {
            std::make_shared<std::string>("one"),
            std::make_shared<std::string>("two"),
            std::make_shared<std::string>("three"),
            std::make_shared<std::string>("four")
        };
        
        std::make_heap(std::begin(words), std::end(words),
                        [](const std::shared_ptr<std::string>& p1, const std::shared_ptr<std::string>& p2){
                            return *p1 < *p2;
                        });
    }
   
    // unique_ptr<T> unsupport!
    {
        // std::vector<std::unique_ptr<std::string>> words {
            // std::unique_ptr<std::string>(new std::string("one")),
            // std::unique_ptr<std::string>(new std::string("two")),
            // std::unique_ptr<std::string>(new std::string("three")),
            // std::unique_ptr<std::string>(new std::string("four"))
        // };
        
        // std::make_heap(std::begin(words), std::end(words),
                        // [](const std::unique_ptr<std::string>& p1, const std::unique_ptr<std::string>& p2){
                            // return *p1 < *p2;
                        // });
    }
    
    return 0;
}