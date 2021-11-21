
## 场景
- 有的时候，代码比较复杂，这个时候再考虑指针的分配与释放，就有点浪费精力。
- 这个时候，用智能指针就很好。如下:
  ```c++
    // 定义
    std::unordered_map<unsigned,
                       std::pair<std::shared_ptr<std::mutex>,
                                 std::shared_ptr<std::condition_variable>>> mtx_conds;
    
    // 赋值
    mtx_conds.emplace(port, std::make_pair(std::make_shared<std::mutex>(),
                                             std::make_shared<std::condition_variable>()));
    m_threads.emplace(port, std::make_shared<std::thread>(std::bind(client_callback,
                                                                    std::placeholders::_1,
                                                                    std::placeholders::_2),
                                                          port,
                                                          this));
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
    // 使用 - 生产线程
    std::unique_lock<std::mutex> guard_in(*mtx_conds[port].first.get());
    que[port].push(xxx);
    mtx_conds[port].second->notify_one();
    
    // 使用 - 消费线程
    while (true) {
        std::unique_lock<std::mutex> guard_in(*mtx_conds[port].first.get());
        if (! mtx_conds[port].second->wait_for(guard_in, std::chrono::seconds(2), 
                                                [port]{ return ! is_running || ! que[port].empty(); })) {
            continue;
        }
        
        if (! is_running) {
            return ;
        }
        
        xxx = que[port].front();
        que[port].pop();
        ...
    }
    
    // 释放
    {
        for (auto iter = mtx_conds.begin(); iter != mtx_conds.end(); iter++) {
            std::lock_guard<std::mutex> locker(*iter->second.first.get());
        }
        is_running = false;
    }

    for (auto iter = mtx_conds.begin(); iter != mtx_conds.end(); iter++) {
        iter->second.second->notify_all();
    }
  ```
- 智能指针，有些情况下确实很不错。