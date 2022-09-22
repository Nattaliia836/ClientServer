#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>

#pragma warning(disable: 4996)

SOCKET Connections[50];

void ClientHandler(int index) {
	char message[1024] = { 0 };
	while (true) {
		if (recv(Connections[index], message, sizeof(message), 0) == SOCKET_ERROR) {
			std::cout << "Recv function failed with error: " << WSAGetLastError() << std::endl;
			break;
		}
		std::cout << "Client " << index + 1 << ": ";
		std::cout << message << std::endl;
	}
}

int main(int argc, char* argv[]) {
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN service;
	int sizeofservice = sizeof(service);
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(1028);
	service.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&service, sizeof(service));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	for (int i = 0; i < 50; i++) {
		newConnection = accept(sListen, (SOCKADDR*)&service, &sizeofservice);

		if (newConnection == 0) {
			std::cout << "Error\n";
		}
		else {
			std::cout << "Client number " << (i + 1) << " Connected!\n";
			Connections[i] = newConnection;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
		}
	}

	return 0;
}