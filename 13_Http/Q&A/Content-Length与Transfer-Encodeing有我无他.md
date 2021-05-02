
## 关于 Content-Length 和 Transfer-Encodeing
- 如果你对一个 http 请求或响应同时设置这两个关键字，在抓包时会出现错误。这说明 http 协议要求如果已经使用了二者其中一个关键字，
  那么就不能使用另一个。
- 这在一些 http 引擎中也可见端倪:
  ```c++
    if ( request->get_header( "Transfer-Encoding", String::lowercase ) == "chunked" )
    {
        session->fetch( "\r\n", read_chunk_size );
    }
    else if ( request->has_header( "Content-Length" ) )
    {
        int length = request->get_header( "Content-Length", 0 );

        session->fetch( length, [ ]( const shared_ptr< Session > session, const Bytes& )
        {
            const auto request = session->get_request( );
            const auto body = request->get_body( );

            fprintf( stdout, "Complete body content: %.*s\n", static_cast< int >( body.size( ) ), body.data( ) );
            session->close( OK );
        } );
    }
    else
    {
        session->close( BAD_REQUEST );
    }
  ```