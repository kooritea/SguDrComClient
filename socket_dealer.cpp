#include "socket_dealer.h"
#include "sgudrcom_exception.h"

socket_dealer::socket_dealer() {
	init();
}

bool socket_dealer::init() {
	try {
		client_fd = socket(AF_INET, SOCK_DGRAM, 0);
		if (client_fd < 0)
			throw sgudrcom_exception("failed to create socket");
		return true;
	}
	catch(sgudrcom_exception &e){
		return false;
	}
}

bool socket_dealer::send_udp_pkt(const char *dest, uint16_t port, std::vector<uint8_t> &udp_data_set) {
	struct sockaddr_in server_addr;
	try {
		memset(&server_addr, 0, sizeof(server_addr));
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = inet_addr(dest);
		// server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //注意网络序转换
		server_addr.sin_port = htons(port);

		socklen_t len = sizeof(server_addr);
		size_t data_len = udp_data_set.size();
		char *buf = new char[data_len];
		memcpy(buf, &udp_data_set[0], data_len);

		ssize_t ret = sendto(client_fd, buf, data_len, 0, (struct sockaddr *) &server_addr, len);
		delete[] buf;
		if (ret > 0)
			return true;
	}
	catch(sgudrcom_exception &e){

		return false;
	}
}

bool socket_dealer::recv_udp_pkt(std::vector<uint8_t> &pkt_data) {
	struct sockaddr_in src_addr;
	socklen_t len;
	try {
		char *buf = new char[RECV_BUFF_LEN];
		memset(buf, 0, RECV_BUFF_LEN);

		ssize_t ret = recvfrom(client_fd, buf, RECV_BUFF_LEN, 0, (struct sockaddr *) &src_addr, &len);
		if (ret < 0)
			throw sgudrcom_exception("failed to send packets");

		pkt_data.insert(pkt_data.end(), RECV_BUFF_LEN, 0x00);
		memcpy(&pkt_data[0], &buf, RECV_BUFF_LEN);
		delete[] buf;
		return true;
	}
	catch(sgudrcom_exception &e) {
		return false;
	}
}

socket_dealer::~socket_dealer() {
	close(client_fd); // close socket
}
