
## 说明
- 至今为止，除了一些示例程序外，还没有在接触的生产项目或开源实现中看到有使用 try_lock
  的案例。
- 这是一个好现象。它暗示我们: 不用怕，这只是最普通不过的加锁应用场景了。
- try_lock 的应用场景也不是很复杂，对它的使用更多的是出于稳妥的考虑。以 std::unique_lock 为例。

## 以最常见的生产消费为例
- 示例代码
  ```c++
    /** global variable */
    std::mutex mtx;
    std::cond_variable cond;
    std::queue  que;

    // 生产者线程
    while(1) {
        /** prepare it */
        // std::string msg;
        std::unique_lock<std::mutex> locker(mtx);
        que.push(std::move(msg));
        cond.notify_one();
        /** other deal */
    }
  
    // 消费者线程
    while (1) {
        /** prepare it */
        std::unique_lock<std::mutex> locker(mtx);
        if (! cond.wait(locker, std::chrono::seconds(5), [&que](){ return ! que.empty(); })) {
            continue;
        }
        std::string msg = std::move(que.front());
        que.pop();
        /** deal with */
    }
  ```
- 上面的示例程序中，如果生产者获得锁，就执行加锁，并生产一条消息，之后通知消费者可以消费。
  如果消费者获得锁，调用 wait 函数后，如果队列不为空，就独占队列继续向下执行处理过程；如果
  队列为空，消费者就会立即释放锁(这样生产者就可以获得该锁进行生产)，直到收到来自生产者的条
  件脉冲后重新获得该锁，独占队列向下执行。
  
## 如果消费者发生了一些变化
- 可能会遇到这种情况，消费者线程也会生产一些消息。比如在生产者生产消费之前，消费者线程要根据
  业务需要事先产生一条消息推送到队列中。这个时候并不能确定生产者线程是否比生产者先获得这把锁。
  如果是，就通过一定手段对生产者解锁或者等待生产者锁超时到达后自动获得这把锁。
- 不过即使事先已经确定生产者在这之前，并不会获得这把锁，为了体现对资源的独占，也应该加锁。这
  里当然也可以直接进行 lock, 不过略显生硬，try_lock 更合适一些。
- 示例代码
  ```c++
    /** global variable */
    std::mutex mtx;
    std::cond_variable cond;
    std::queue  que;

    // 生产者线程
    while(1) {
        /** prepare it */
        // std::string msg;
        std::unique_lock<std::mutex> locker(mtx);
        que.push(std::move(msg));
        cond.notify_one();
        /** other deal */
    }
  
    // 消费者线程
    try {
        std::unique_lock<std::mutex> locker(mtx, std::defer_lock);
    } catch(std::exception& e) {
        std::cout << "exception occurs: " << e.what() << std::endl;
        /** deal with */
    }
    while (1) {
        /** prepare it */
        std::unique_lock<std::mutex> locker(mtx);
        if (! cond.wait(locker, std::chrono::seconds(5), [&que](){ return ! que.empty(); })) {
            continue;
        }
        std::string msg = std::move(que.front());
        que.pop();
        /** deal with */
    }
  ```
- 注意: 向 std::unique_lock 只传入互斥对象 mtx 时，构造即加锁，如果再执行 try_lock 会报系统异常
  std::system_error，具体错误为 resource_deadlock_would_occur，所以要使用 try_lock 时，要延后加锁。
  ```c++
    std::unique_lock<std::mutex> locker(mtx, std::defer_lock);
  ```