
### 1. 按 Module 模式使用

并不是所有的库都可以按 Module 模式使用。可以通过下列命令查看可以按 Module 使用的库:
```s
    cmake --help-module-list
```
部分输出如下:
```s
    FindSQLite3
    FindSWIG
    FindSelfPackers
    FindSquish
    FindSubversion
    FindTCL
    FindTIFF
    FindVTK
    FindVulkan
    FindWget
    FindWish
    FindZLIB
```

可以通过下列命令查看某个模块支持的环境变量:
```s
    cmake --help-module FindZLIB
```
部分输出如下:
```s
    This module defines the following variables:

    ::

     ZLIB_INCLUDE_DIRS   - where to find zlib.h, etc.
     ZLIB_LIBRARIES      - List of libraries when using zlib.
     ZLIB_FOUND          - True if zlib found.
```

以 zlib 作为示例，使用 cmake 的 find_package 查找方法:
```s
    find_package(ZLIB REQUIRED)
    if (ZLIB_FOUND)
        message("ZLIB_INCLUDE_DIRS="${ZLIB_INCLUDE_DIRS})
        message("ZLIB_LIBRARIES="${ZLIB_LIBRARIES})
        message("ZLIB_VERSION_STRING="${ZLIB_VERSION_STRING})
    else()
        message(FATAL_ERROR "could not find zlib module")
    endif(ZLIB_FOUND)
```
输出如下:
```s
    ZLIB_INCLUDE_DIRS=/usr/local/include
    ZLIB_LIBRARIES=/usr/local/lib/libz.so
    ZLIB_VERSION_STRING=1.2.11
```

### 2. 通过配置环境后按 Module 模式使用

有的库，执行 `cmake --help-module xxx` 命令时可以显示其支持的环境变量信息，但执行`find_package` 命令时却找不到该模块，如 libcurl, 错误如下:
```shell
    CMake Error at /usr/local/share/cmake-3.15/Modules/FindPackageHandleStandardArgs.cmake:137 (message):
      Could NOT find CURL (missing: CURL_LIBRARY CURL_INCLUDE_DIR)
    Call Stack (most recent call first):
      /usr/local/share/cmake-3.15/Modules/FindPackageHandleStandardArgs.cmake:378 (_FPHSA_FAILURE_MESSAGE)
      /usr/local/share/cmake-3.15/Modules/FindCURL.cmake:143 (find_package_handle_standard_args)
      CMakeLists.txt:18 (find_package)
```
这时可以通过 `pkg-config` 命令设置该模块路径到 `find_package` 的查找路径中去。  

`pkg-config` 命令可以在 PKG_CONFIG_PATH 指定的目录下查找对应的 .pc 文件，找到库的所在位置。以 libcurl 为例，其 libcur.pc 文件内容为:
```s
    prefix=/usr/local/libcurl
    exec_prefix=${prefix}
    libdir=${exec_prefix}/lib
    includedir=${prefix}/include
    supported_protocols="DICT FILE FTP GOPHER HTTP IMAP POP3 RTSP SMTP TELNET TFTP"
    supported_features="IPv6 UnixSockets libz"

    Name: libcurl
    URL: https://curl.haxx.se/
    Description: Library to transfer files with ftp, http, etc.
    Version: 7.51.0-DEV
    Libs: -L${libdir} -lcurl
    Libs.private: -lz
    Cflags: -I${includedir} 
```

将 libcur.pc 的查找路径添加到 PKG_CONFIG_PATH 中:
```shell
    # export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/libcurl/lib/pkgconfig
    # echo $PKG_CONFIG_PATH
    :/usr/local/libcurl/lib/pkgconfig
```

也可以在 cmake 执行进程内部设置 PKG_CONFIG_PATH 变量, 完整示例如下:
```s
    SET(ENV{PKG_CONFIG_PATH} "/usr/local/libcurl/lib/pkgconfig")

    find_package(CURL REQUIRED)
    if (CURL_FOUND)
        message("CURL_INCLUDE_DIRS="${CURL_INCLUDE_DIRS})
        message("CURL_LIBRARIES="${CURL_LIBRARIES})
        message("CURL_VERSION_STRING="${CURL_VERSION_STRING})
    else()
        message(FATAL_ERROR "could not find libcurl module")
    endif(CURL_FOUND)
```
输出如下:
```s
    CURL_INCLUDE_DIRS=/usr/local/libcurl/include
    CURL_LIBRARIES=/usr/local/libcurl/lib/libcurl.so
    CURL_VERSION_STRING=7.51.0-DEV
```

### 3. 将库路径添加到 CMAKE_MODULE_PATH 中后再按 Module 使用

能通过 cmake 查看支持的模块信息，并不意味着可以通过 find_package 找到该模块。而 find_package 是通过 CMAKE_MODULE_PATH 上的路径来寻找模块的。所以可以将库模块添加到 CMAKE_MODULE_PATH 中使 find_package 可以找到该模块。

代码示例如下:
```s
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules")
```
具体示例见 cmake_module_path
  
### 4. 直接按文件查找

有时工程不是很大，一个 CMakeLists.txt 就可以搞定，这时可以将第 3 种方式精简一下寻找依赖项。

示例如下:
```s
    find_path(ssl_INCLUDE openssl/ssl.h HINTS "/usr/local/openssl/include"
                                              "/usr/include"
                                              "/usr/local/include"
                                              "/opt/local/include")
    find_library(crypto_LIBRARY crypto  HINTS "/usr/local/openssl/lib"
                                              "/usr/lib"
                                              "/usr/local/lib"
                                              "/opt/local/lib")
    find_library(ssl_LIBRARY    ssl     HINTS "/usr/local/openssl/lib"
                                              "/usr/lib"
                                              "/usr/local/lib"
                                              "/opt/local/lib")
    if(ssl_INCLUDE AND ssl_LIBRARY AND crypto_LIBRARY)
        set(OPENSSL_FOUND TRUE)
        set(OPENSSL_INCLUDE_DIR ${ssl_INCLUDE})
        set(OPENSSL_CRYPTO_LIBRARY ${crypto_LIBRARY})
        set(OPENSSL_SSL_LIBRARY ${ssl_LIBRARY})
        set(OPENSSL_LIBRARIES ${crypto_LIBRARY} ${ssl_LIBRARY})
    else ()
        message(FATAL_ERROR "Failed to locate OpenSSL")
    endif()

    if (OPENSSL_FOUND)
        message("OPENSSL_INCLUDE_DIR=" ${OPENSSL_INCLUDE_DIR})
        message("OPENSSL_CRYPTO_LIBRARY=" ${OPENSSL_CRYPTO_LIBRARY})
        message("OPENSSL_SSL_LIBRARY=" ${OPENSSL_SSL_LIBRARY})
        message("OPENSSL_LIBRARIES=" ${OPENSSL_LIBRARIES})
    else()
        message(FATAL_ERROR "could not find openssl module")
    endif(OPENSSL_FOUND)
```
  
### 按 CONFIG 模式使用

一般使用上面几种方式基本可以解决大部分问题，所以这种模式暂略.