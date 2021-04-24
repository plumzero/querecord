
#include <iostream>
#include <string>
#include <memory>
#include <map>

struct ResponseImpl
{   
    double                                  m_version{1.1};
    int                                     m_status_code{200};
    std::string                             m_protocol{"HTTP"};
    std::string                             m_status_message{"OK"};
    std::multimap<std::string, std::string> m_headers{};
    std::string                             m_body{};
};

class Response
{
public:
    Response() : m_pimpl(new ResponseImpl){}
    ~Response(){}
public:
    double      get_version() const { return m_pimpl->m_version; }
    int         get_status_code() const { return m_pimpl->m_status_code; }
    std::string get_protocol() const { return m_pimpl->m_protocol; }
    std::string get_status_message() const { return m_pimpl->m_status_message; }
private:
    std::unique_ptr<ResponseImpl> m_pimpl;
};

int main()
{
    auto resource = std::make_shared<Response>();
    
    std::cout << resource->get_version() << std::endl;
    std::cout << resource->get_status_code() << std::endl;
    std::cout << resource->get_protocol() << std::endl;
    std::cout << resource->get_status_message() << std::endl;
    
    return 0;
}