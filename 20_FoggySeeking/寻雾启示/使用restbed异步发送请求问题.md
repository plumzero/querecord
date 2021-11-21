
## 问题说明
- 描述
    + 调用 restbed 同步发送(restbed::Http:sync)http请求时，出现崩溃(Core Dump)或异常(请求得不到响应，表现为状态码为0)。

- 测试场景
    + 多线程发送队列内的 http 请求，通过锁保护请求队列。大致代码如下:
      ```c++
        // 线程
        while (1) {
            std::unique_lock<std::mutex> guard_in(mtx);
            cond.wait(guard_in, ...);
            
            auto req = reqQue.front();
            reQue.pop();
            guard_in.unlock();      /** 主动释放锁 */
            
            /** deal with sth before send req */
            auto response = restbed::Http::sync(req);
            /** deal with sth after recv the response */
        }
      ```

- 原因分析
    + gdb 调试发现，在调用 sync 时出错。错误原因有两个，一个是套接字也是共用资源，没有对其进行保护。还有一个原因是 sync 实质上也是异步发送，如下:
      ```c++
        const shared_ptr< Response > Http::sync( const shared_ptr< Request > request, const shared_ptr< const Settings >& settings )
        {
            auto response = Http::async( request, nullptr, settings );
            response.wait( );
            
            return response.get( );
        }
      ```
      只不过是异步发送之后原地等待。 
    + `async` 函数内部采用 aio 的通信机制。虽然实现了真正的并行处理，但在多线程情况下，如果不注意对共享资源的保护，很容易产生一些奇怪的问题。

## 解析办法
- 对 sync 也进行锁保护。

## 使用 NIO 还是 AIO？
- NIO 同步非阻塞模型与 AIO 异步非阻塞模型。
- 使用什么要看应用场景。 NIO 可以接收更多的连接，但对业务的处理仍然是同步的。而 AIO 真正实现了对业务的异步处理。
- NIO 简单可控，使用灵活，可以结合多线程/线程池进行使用，并对高并发数据进行有效处理。 AIO 复杂，较为碎片化，因为异步处理的本质是多线程，这就可能会造成使用 AIO 在处理高并发业务时涉及到大量线程的创建、执行、切换与销毁等，对于系统环境的鲁棒性是一个考验。