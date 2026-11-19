#include <server.h>

int main(int argc, char* argv[]) {

	int EXIT = server(argc, argv);

	return EXIT == 0? EXIT_SUCCESS : EXIT_FAILURE;
}
			
