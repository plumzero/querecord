
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

int main()
{
    {
        std::string colors[] = { "red", "orange", "yellow", "green", "cyan", "blue", "purple" };
        
        std::vector<std::shared_ptr<std::string>> vcolors;
        
        for (auto it = std::begin(colors); it != std::end(colors); it++) {
            vcolors.push_back(std::make_shared<std::string>(*it));
        }
        
        // ok. no problem
        auto itBlue = std::find_if(vcolors.begin(), vcolors.end(),
                            [](const std::shared_ptr<std::string>& color) {
                                return *color == "blue";
                            });
        if (itBlue != vcolors.end()) {
            std::cout << "shared_ptr: Get it" << std::endl;
        }
        
        // stored a copy outside
        std::shared_ptr<std::string> acopy = *itBlue;
        std::cout << "shared_ptr: " << *acopy << std::endl;
    }
    
    {
        std::string colors[] = { "red", "orange", "yellow", "green", "cyan", "blue", "purple" };
        
        std::vector<std::unique_ptr<std::string>> vcolors;
        
        for (auto it = std::begin(colors); it != std::end(colors); it++) {
            vcolors.push_back(std::unique_ptr<std::string>(new std::string(*it)));
        }
        
        // ok. no problem
        auto itBlue = std::find_if(vcolors.begin(), vcolors.end(),
                            [](const std::unique_ptr<std::string>& color) {
                                return *color == "blue";
                            });
        if (itBlue != vcolors.end()) {
            std::cout << "unique_ptr: Get it" << std::endl;
        }
        
        // could not store as a copy outside
        // std::unique_ptr<std::string> acopy = *itBlue;    // compiled error
        // std::cout << "unique_ptr: " << *acopy << std::endl;
    }
   
    return 0;
}