SGU_OBJS=pcap_dealer.o get_device_addr.o eap_dealer.o md5.o utils.o udp_dealer.o config.o socket_dealer.o main.o
SGU_EXE=SguDrcom
CXX=g++
CC=gcc
CXXFLAGS=
LDFLAGS=
STDVERSION=-std=c++11

main: $(SGU_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -Os -s $(STDVERSION) -o $(SGU_EXE) $(SGU_OBJS) -lpcap -lpthread

pcap_dealer.o: pcap_dealer.h sgudrcom_exception.h def.h log.h
	$(CXX) $(CXXFLAGS) $(STDVERSION) -c pcap_dealer.cpp

get_device_addr.o: get_device_addr.h def.h sgudrcom_exception.h
	$(CXX) $(CXXFLAGS) $(STDVERSION) -c get_device_addr.cpp

eap_dealer.o: eap_dealer.h def.h pcap_dealer.h log.h utils.h
	$(CXX) $(CXXFLAGS) $(STDVERSION) -c eap_dealer.cpp

md5.o: md5.h
	$(CC) $(CFLAGS) -c md5.c

utils.o: utils.h get_device_addr.h md5.h log.h
	$(CXX) $(CXXFLAGS) $(STDVERSION) -c utils.cpp

udp_dealer.o: udp_dealer.h def.h socket_dealer.h log.h
	$(CXX) $(CXXFLAGS) $(STDVERSION) -c udp_dealer.cpp

config.o: config.h
	$(CXX) $(CXXFLAGS) $(STDVERSION) -c config.cpp

socket_dealer.o: socket_dealer.h def.h sgudrcom_exception.h log.h get_device_addr.h utils.h
	$(CXX) $(CXXFLAGS) $(STDVERSION) -c socket_dealer.cpp

main.o: def.h get_device_addr.h config.h log.h eap_dealer.h udp_dealer.h
	$(CXX) $(CXXFLAGS) $(STDVERSION) -c main.cpp

.PHONY: clean
clean:
	-rm -rf $(SGU_EXE) $(SGU_OBJS)