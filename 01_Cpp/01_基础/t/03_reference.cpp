
#include <iostream>
#include <string>
#include <vector>

struct Pair {
    std::string name;
    double      val;        // name 出现的次数
};

std::vector<Pair> pairs;

double& value(const std::string& s) {
    int i = 0;
    for (i = 0; i < pairs.size(); i++)
        if (s == pairs[i].name) return pairs[i].val;
    Pair p = { s, 0 };
    pairs.push_back(p);
    return pairs[pairs.size() - 1].val;
}

int main() {
    std::string buf;
    while (std::cin >> buf) value(buf)++;
    for (std::vector<Pair>::const_iterator p = pairs.begin(); p != pairs.end(); p++)
        std::cout << p->name << " : " << p->val << std::endl;
    return 0;
}