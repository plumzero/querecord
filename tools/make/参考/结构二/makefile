

SRCS        = certlog.cpp certasn1.cpp certhget.cpp certconf.cpp cert.cpp certmanager.cpp
OBJS        = $(SRCS:.cpp=.o)

LIB         = libcertmgr.a

CXXFLAGS   += -g -O0 -std=c++11

.PHONY: all
all:
	$(MAKE) -C asn1c
	
	$(CXX) $(CXXFLAGS) -c -o certlog.o     certlog.cpp
	$(CXX) $(CXXFLAGS) -c -o certasn1.o    certasn1.cpp    -I./asn1c
	$(CXX) $(CXXFLAGS) -c -o certhget.o    certhget.cpp
	$(CXX) $(CXXFLAGS) -c -o certconf.o    certconf.cpp
	$(CXX) $(CXXFLAGS) -c -o cert.o        cert.cpp
	$(CXX) $(CXXFLAGS) -c -o certmanager.o certmanager.cpp -I./asn1c
	$(AR) cr $(LIB) $(OBJS)
		
	$(MAKE) -C utest
	
.PHONY: clean
clean:
	rm -rf $(OBJS) $(LIB)
	$(MAKE) -C asn1c clean
	$(MAKE) -C utest clean
