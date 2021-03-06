// TelnetServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "winsock2.h"
#include "stdlib.h"
#include "stdio.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

DWORD WINAPI ClientThread(LPVOID lpParam);
CRITICAL_SECTION CriticalSection;

SOCKET clients[64];
int numClients = 0;

int main(int argc, char** argv)
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (argc > 1) {
		// if it has command line's argument, get it 
		addr.sin_port = htons(atoi((char*)argv[2]));
	}
	else {
		// if it hasn't, get default
		addr.sin_port = htons(5000);
	}

	// listen ip address in port
	bind(listener, (SOCKADDR *)&addr, sizeof(addr));
	listen(listener, 5);

	// while(true) - always accept if get new clients
	while (1)
	{
		SOCKET client = accept(listener, NULL, NULL);

		printf("Co ket noi moi: %d\n", client);

		for (int i = 0; i < numClients; i++)
		{
			char msg[16] = "Co ket noi moi\n";
			send(clients[i], msg, strlen(msg), 0);
		}

		clients[numClients] = client;
		numClients++;

		CreateThread(0, 0, ClientThread, &client, 0, 0);
	}

	closesocket(listener);
	WSACleanup();
	return 0;
}

// return -1 if connect error, return 0 if client disconnect
DWORD WINAPI ClientThread(LPVOID lpParam)
{
	SOCKET client = *(SOCKET *)lpParam;
	int ret;
	char buf[256];
	int flag = 1;

	// login loop: client must pass form before send data
	while (1) {
		send(client, "Username: ", 10, 0);
		ret = recv(client, buf, sizeof(buf), 0);
		if (ret <= 0)
			return -1;
		buf[ret] = 0;
		char username[31];
		memcpy(username, &buf, ret - 1);
		username[ret - 1] = '\0';
		send(client, "Password: ", 10, 0);
		ret = recv(client, buf, sizeof(buf), 0);
		if (ret <= 0)
			return -1;
		buf[ret] = 0;
		char password[31];
		memcpy(password, &buf, ret - 1);
		password[ret - 1] = '\0';
		char filename[] = "c:\\Users\\USER\\source\\repos\\NetworkPrograming_ChatServer\\TelnetServer\\db.txt";
		//open and get the file handle
		FILE* fh;
		fopen_s(&fh, filename, "r");
		//check if file exists
		if (fh == NULL) {
			printf("file does not exists %s", filename);
			return 0;
		}
		//read line by line
		const size_t line_size = 255;
		char* line = (char*)malloc(line_size);
		while (fgets(line, line_size, fh) != NULL) {
			int len = strlen(line);
			for (int i = 0; i < len; i++) {
				if (line[i] == 32) {
					char c_username[31];
					memcpy(c_username, &line[0], i);
					c_username[i] = '\0';
					char c_password[31];
					memcpy(c_password, &line[i + 1], len - i - 2);
					c_password[len - i - 2] = '\0';
					if (strcmp(username, c_username) == 0 && strcmp(password, c_password) == 0) {
						flag = 0;
						break;
					}
				}
			}
		}
		free(fh);
		free(line);// free heap memory
		if (flag == 0) break;
	}

	while (1) {
		InitializeCriticalSection(&CriticalSection);
		EnterCriticalSection(&CriticalSection);
		send(client, "Command: ", 9, 0);
		ret = recv(client, buf, sizeof(buf), 0);
		if (ret <= 0)
			return -1;
		buf[ret - 1] = 0;
		strcat(buf, " > c:\\Users\\USER\\source\\repos\\NetworkPrograming_ChatServer\\TelnetServer\\output.txt");
		printf("%s", buf);
		system(buf);
		LeaveCriticalSection(&CriticalSection);
	}

	closesocket(client);

	return 0;
}

