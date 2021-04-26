
#include <iostream>
#include <map>
#include <string>
#include <cassert>

class Name
{
public:
    std::string firstname {};
    std::string lastname {};
public:
    Name(const std::string& fn, const std::string& sn)
        : firstname(fn), lastname(sn) {}
    Name() = default;
    
    // Less-than operator
    bool operator<(const Name& name) const
    {
        return lastname < name.lastname || (lastname == name.lastname && firstname < name.firstname);
    }
    
    // friend std::istream& operator>>(std::istream& in, Name& name);
    // friend std::ostream& operator<<(std::ostream& out, const Name& box);
};

int main()
{
    std::map<Name, size_t> people;
    
    std::pair<std::map<Name, size_t>::iterator, bool> ret_pr;
    
    // successfully inserted
    ret_pr = people.emplace(Name{"Dan", "Druff"}, 77);
    assert(ret_pr.second);
    
    // successfully inserted
    std::map<Name, size_t>::iterator it;
    it = people.emplace_hint(ret_pr.first, Name{"Cal", "Cutta"}, 62);
    assert(it != ret_pr.first);
    
    // existed alreadly in the map
    it = people.emplace_hint(ret_pr.first, Name{"Dan", "Druff"}, 68);
    
    std::cout << it->first.firstname << "." << it->first.lastname << "=>" << it->second << std::endl;
    
    for (const auto & kv : people) {
        std::cout << kv.first.firstname << "." << kv.first.lastname << "=>" << kv.second << std::endl;
    }
    
    return 0;
}