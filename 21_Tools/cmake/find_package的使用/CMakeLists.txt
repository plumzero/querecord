
cmake_minimum_required(VERSION 2.8)

project(find_package_useage)

## [1] 直接查找到模块
find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
    message("ZLIB_INCLUDE_DIRS=" ${ZLIB_INCLUDE_DIRS})
    message("ZLIB_LIBRARIES=" ${ZLIB_LIBRARIES})
    message("ZLIB_VERSION_STRING=" ${ZLIB_VERSION_STRING})
else()
    message(FATAL_ERROR "could not find zlib module")
endif(ZLIB_FOUND)

## [2] 通过设置环境变量后查找到模块
SET(ENV{PKG_CONFIG_PATH} "/usr/local/libcurl/lib/pkgconfig")

find_package(CURL REQUIRED)
if (CURL_FOUND)
    message("CURL_INCLUDE_DIRS=" ${CURL_INCLUDE_DIRS})
    message("CURL_LIBRARIES=" ${CURL_LIBRARIES})
    message("CURL_VERSION_STRING=" ${CURL_VERSION_STRING})
else()
    message(FATAL_ERROR "could not find libcurl module")
endif(CURL_FOUND)

## [4] 直接按文件查找
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