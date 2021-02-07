

SRCS        = certlog.cpp certasn1.cpp certhget.cpp certconf.cpp cert.cpp certmanager.cpp

CT_PROJ		= main
CT_SRCS		= main.cpp

HS_PROJ		= http_server
HS_SRCS		= http_server.cpp

HC_PROJ		= http_client
HC_SRCS		= http_client.cpp

CXXFLAGS   += -g -O0 -std=c++11

THREAD_SUPPORT		= -lpthread
ASN1C_SUPPORT		= -I./asn1c ./asn1c/libasn1.a
CURL_SUPPORT		= -I./curl/include ./curl/lib/libcurl.a
PISTACHE_SUPPORT	= -I./pistache/include ./pistache/lib/libpistache.a

.PHONY: all
all:
	$(MAKE) -C asn1c
	
	$(CXX) $(CXXFLAGS) $(SRCS) $(CT_SRCS)           \
		-o $(CT_PROJ)                               \
		$(ASN1C_SUPPORT)                            \
		$(CURL_SUPPORT)
	
	$(CXX) $(CXXFLAGS) $(HS_SRCS)                   \
		-o $(HS_PROJ)                               \
		$(ASN1C_SUPPORT)                            \
		$(PISTACHE_SUPPORT)                         \
		$(THREAD_SUPPORT)
	
	$(CXX) $(CXXFLAGS) $(SRCS) $(HC_SRCS)           \
		-o $(HC_PROJ)                               \
		$(ASN1C_SUPPORT)                            \
		$(CURL_SUPPORT)
		
.PHONY: clean
clean:
	rm -rf $(CT_PROJ)
	rm -rf $(HS_PROJ)
	rm -rf $(HC_PROJ)
# $(MAKE) -C asn1c clean
