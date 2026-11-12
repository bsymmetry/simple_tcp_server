#include <cstdio>
#include <sys/sockets.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>

void main(int argc, char* argv[]) {
	// args should specify the port # and optionally length of backlog
	if (argc < 1) {
		std::cout << "Usage: must include port # and optional backlog length" << std::endl;
		std::cerr << "Incorrect number of arguments were provided";
		return EXIT_FAILURE;
	}

	int backlog_length = argc > 1 ? argv[1] : SOMAXCONN;
	int fd = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in addr{};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(agrv[0]);

	if (bind(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1) {
		std::cout << "Failed to bind to socket" << std::endl;
		std::cerr << "Failed to bind to socket: " << addr.sin_port;
		return EXIT_FAILURE;
	}
	
	if (listen(fd, backlog_length) == -1) {
		std::cout << "Failed to listen at socket" << std::endl;
		std::cerr << "Failed to listen at socket: " << add.sin_port;
		return EXIT_FAILURE;
	}

	while (true) {
		int client_fd = accept(fd, nullptr, nullptr);
		if (client_fd == -1) {
			std::cout << "Fialed to accept client" << std::endl;
			std::cerr << "Failed to accept client: " << addr.sin_port;
			continue;
		}

		char[] buf[100]{};
		int char_read = read(client_fd, buf, 100);
		if (char_read == -1) {
			std::cout << "Failed to read from client" << std::endl;
			std::cerr << "Failed to read from client. Error: " << errno;
			close(client_fd);
			continue;
		}

		int char_written = write(client_fd, buf, 100);
		if (char_written == -1) {
			std::cout << "Failed to write to client" << std::endl;
			std::cerr << "Failed to write to client. Error: " << errno;
			close(client_fd);
			continue;
		}	
	}


	return EXIT_SUCCESS;
}
			
