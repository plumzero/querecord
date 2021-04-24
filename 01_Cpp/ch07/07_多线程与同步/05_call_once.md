
为了保证在多线程中某个函数仅被调用一次，比如，需要初始化某个对象，而这个对象只能初始化一次时，就可以用 std::call_once 来保证函数在多线程环境中只被调用一次。

使用 std::call_once 时，需要一个 once_flag 作为 call_once 的入参。

用法示例:
```c++
    class XPool
    {
        std::vector<std::shared_ptr<std::thread>> m_ths
        std::once_flag m_flag;
    public:
        XPool()
        {
            for (int i = 0; i < 10; i++) {
                m_ths.push_back(std::make_shared<std::thread>([](){/*...*/}));
            }
        }
        ~XPool()
        {
            std::call_once(m_flag, [this]{ stop_once(); });
        }
        // 所有的线程，只释放一次
        void stop_once()
        {
            for (auto th : m_ths) {
                if (th) {
                    th->join();
                }
            }
            m_ths.clear();  
        }
    };
```
