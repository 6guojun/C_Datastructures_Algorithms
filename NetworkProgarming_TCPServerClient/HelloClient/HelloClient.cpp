#include "stdafx.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "winsock2.h"

int main(int argc, char** argv)
{
	// define socket
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// define server's address
	SOCKADDR_IN addr;
	// get argument from command line
	if (argc > 1) {
		addr.sin_family = AF_INET;
		printf("Connecting server on IP: %s port: %d \n", (char*)argv[1], atoi((char*)argv[2]));
		addr.sin_addr.s_addr = inet_addr((char*)argv[1]);
		addr.sin_port = htons(atoi((char*)argv[2]));
	}
	else {
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		addr.sin_port = htons(8000);
	}

	// connect client to server by address
	int ret = connect(client, (SOCKADDR *)&addr, sizeof(addr));
	if (ret == SOCKET_ERROR)
	{
		ret = WSAGetLastError();
		printf("Error code: %d", ret);
		system("pause");

		return 1;
	}

	// define buffer that contains data
	char buf[256];
	ret = recv(client, buf, sizeof(buf), 0);
	buf[ret] = 0;
	printf("%s\n", buf);

	while (1)
	{
		printf("Fill your data:");
		gets_s(buf);
		// compare 4 first byte of buf with 'exit' if the same -> break 
		if (strncmp(buf, "exit", 4) == 0)
			break;
		// send buf
		send(client, buf, strlen(buf), 0);
	}

	closesocket(client);
	WSACleanup();

	system("pause");

	return 0;
}
