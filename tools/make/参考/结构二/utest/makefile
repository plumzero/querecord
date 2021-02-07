
SRCS        = main.cpp http_server.cpp test_hget.cpp

PROJ		= main

CXXFLAGS   += -g -O0 -std=c++11

THREAD_SUPPORT		= -lpthread
ASN1C_SUPPORT		= -I../asn1c ../asn1c/libasn1.a
CURL_SUPPORT		= -I../curl/include ../curl/lib/libcurl.a
PISTACHE_SUPPORT	= -I../pistache/include ../pistache/lib/libpistache.a
CERTMGR_SUPPORT     = -I.. ../libcertmgr.a
DOCTEST_SUPPORT     = -I..

.PHONY: all
all:	
	$(CXX) $(CXXFLAGS) $(SRCS)                      \
		-o $(PROJ)                                  \
		$(CERTMGR_SUPPORT)                          \
		$(ASN1C_SUPPORT)                            \
		$(PISTACHE_SUPPORT)                         \
		$(CURL_SUPPORT)                             \
		$(DOCTEST_SUPPORT)                          \
		$(THREAD_SUPPORT)
		
.PHONY: clean
clean:
	rm -rf $(PROJ)
