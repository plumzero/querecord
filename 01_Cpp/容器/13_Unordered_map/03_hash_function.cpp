
#include <cstdio>
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <ctime>

#define COUNT_FOR_TESTING       1000000

/** 随机字符串生成函数 */
std::string rand_str()
{
    int i, n;
    n = rand() % 5 + 4;
    std::string str;
    str.resize(n);
    for(i = 0; i < n; ++i)
    {
        str[i] = 'a' + rand() % 26;
    }
    
    return str;
}

/** 平方差: 越大越不均匀 */
double variance(const std::vector<int>& v)
{
    int sum = std::accumulate(v.begin(), v.end(), 0);
    
    double avg = (double) sum / v.size();
    
    printf("v.size=%lu, sum=%d, avg=%f\n", v.size(), sum, avg);
    
    double ss = 0;
    std::for_each(v.begin(), v.end(), [&ss, avg](int ele){ ss += (ele - avg) * (ele - avg); });
    
    return ss;
}

/** 用作哈希键的类 */
class Customer
{
public:
    Customer(int n) : fname(rand_str()), lname(rand_str()), no(n) {
        // printf("fname=%s,lname=%s,no=%d\n", fname.c_str(), lname.c_str(), no);
    }
    ~Customer(){}
    
    friend bool operator==(Customer c1, Customer c2);
    
    std::string fname;
    std::string lname;
    int no;
};

/** 按照C++标准库的实现建议， operator== 应实现为外部友元 */
bool operator==(Customer c1, Customer c2)
{
    return c1.fname == c2.fname && c1.lname == c2.lname && c1.no == c2.no;
}

template<typename T>
inline void hash_combine(size_t& seed, const T& val)
{
    seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    // printf("seed=%lu\n", seed);
}

/** 可变参数模板函数声明 */
template<typename... Types>
inline size_t hash_val(const Types&... args);

/** 递归展开方式 */
template<typename T, typename... Types>
inline void hash_val(size_t& seed, const T& val, const Types&... args)
{
    hash_combine(seed, val);
    hash_val(seed, args...);
}

/** 递归终止条件 */
template<typename T>
inline void hash_val(size_t& seed, const T& val)
{
    hash_combine(seed, val);
}

/** 可变参数模板函数定义 */
template<typename... Types>
inline size_t hash_val(const Types&... args)
{
    size_t seed = 0;
    hash_val(seed, args...);

    return seed;
}

/** 对于 std::hash 模板类的特化要放在名字空间 std 中进行 */
namespace std {
    template<>
    struct hash<Customer> {
        size_t operator()(Customer c) const {
            return hash_val(c.fname, c.lname, c.no);
        }
    };
}

int main()
{
    {
        printf("========== test 1 ==========\n");
        int i = 0;
        
        std::unordered_map<Customer, int, std::hash<Customer>> um;
        
        um.rehash(COUNT_FOR_TESTING * 1.4);
        for (i = 0; i < COUNT_FOR_TESTING; i++) {
            um.insert(std::make_pair(Customer(rand() + time(0)), i));
        }
        
        printf("um.size=%lu\n", um.size());
        printf("um.bucket_count=%lu\n", um.bucket_count());
        printf("um.load_factor=%f\n", um.load_factor());
        
        decltype(um.bucket_count()) j;
        std::vector<int> v;
        for (j = 0; j < um.bucket_count(); j++) {
            v.push_back(um.bucket_size(j));
        }
        
        // for (const auto & ele : v) {
            // printf("%d ", ele);
        // }
        // printf("\n");
        
        printf("variance=%f\n", variance(v));
    }
    
    {
        printf("========== test 2 ==========\n");
        int i = 0;
        
        std::unordered_map<Customer, int, std::hash<Customer>> um;
        
        um.rehash(COUNT_FOR_TESTING * 1.4);
        for (i = 0; i < COUNT_FOR_TESTING; i++) {
            um.insert(std::make_pair(Customer(rand() + time(0)), i));
        }
        
        printf("um.size=%lu\n", um.size());
        printf("um.bucket_count=%lu\n", um.bucket_count());
        printf("um.load_factor=%f\n", um.load_factor());
        
        decltype(um.bucket_count()) j;
        std::vector<int> v;
        for (j = 0; j < um.bucket_count(); j++) {
            v.push_back(um.bucket_size(j));
        }
        
        // for (const auto & ele : v) {
            // printf("%d ", ele);
        // }
        // printf("\n");
        
        printf("variance=%f\n", variance(v));
    }
    
    return 0;
}