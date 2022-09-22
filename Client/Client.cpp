#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>

#pragma warning(disable: 4996)

int main(int argc, char* argv[]) {
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN client;
	int sizeofclientService = sizeof(client);
	client.sin_addr.s_addr = inet_addr("127.0.0.1");
	client.sin_port = htons(1028);
	client.sin_family = AF_INET;

	SOCKET Connection;

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&client, sizeof(client)) != 0) {
		std::cout << "Failed connect to server.\n";
		return 1;
	}
	std::cout << "Connected!\n";

	char* message;
	while (true) {
		std::cin.getline(message, sizeof(message));
		send(Connection, message, sizeof(message), NULL);
	}

	return 0;
}