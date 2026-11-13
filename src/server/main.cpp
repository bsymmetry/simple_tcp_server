#include <cstdio>
#include <cstdint>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	// args should specify the port # and optionally length of backlog
	int backlog = SOMAXCONN;
	std::uint16_t port = 0;
	try {
		if (argc > 1) {
			backlog = std::stoi(argv[1]);
		}

		if (argc > 2) {
			int parsed_port = std::stoi(argv[2]);
			if (parsed_port < 0 || parsed_port > 65535) {
				throw std::out_of_range("port must be between 0 and 65535");
			}
			port = static_cast<std::uint16_t>(parsed_port);
		}
	} catch (const std::exception& e) {
		std::cout << "Usage: must include port # and optional backlog length" << std::endl;
		std::cerr << "Incorrect number of arguments were provided";
		return EXIT_FAILURE;
	}

	int fd = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in addr{};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	if (bind(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1) {
		std::cout << "Failed to bind to socket" << std::endl;
		std::cerr << "Failed to bind to socket: " << addr.sin_port;
		return EXIT_FAILURE;
	}
	
	if (listen(fd, backlog) == -1) {
		std::cout << "Failed to listen at socket" << std::endl;
		std::cerr << "Failed to listen at socket: " << addr.sin_port;
		return EXIT_FAILURE;
	}

	while (true) {
		int client_fd = accept(fd, nullptr, nullptr);
		if (client_fd == -1) {
			std::cout << "Fialed to accept client" << std::endl;
			std::cerr << "Failed to accept client: " << addr.sin_port;
			continue;
		}

		char buf[100]{};
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
			
