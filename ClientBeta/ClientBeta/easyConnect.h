#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment (lib, "Ws2_32.lib")

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <thread>
#include "TTS.h"



struct sockaddr_in addressInformations; //endereço de socket
int socketAtivo; //socket
int n; //define número de clientes
bool quit; //define se o servidor deve ser fechado
bool sound; // define se deve ser emitido retorno sonoro;
int serverCode;
std::string clientCode;
char arg1[24];
char arg2[1024];

struct client {

	int id; //client id
	struct sockaddr_in client_addr; //endereço do cliente
	SOCKET clientSocket;

};

std::vector <client> clientID(255);

void setup() {

	quit = false;
	n = 0;

	system("echo off && mode 80,40 && color 0a && cls");

	//inicialização de clientes
	for (int i = 0; i < 255; i++) {
		clientID[i] = { -1, NULL };
	}


	//solicitação de ip para preenchimento de endereçamento de socket
	std::cout << "Insert server code: ";
	TTS("Insert Server Code");
	std::cin >> serverCode;
	std::cout << "Insert client access code: ";
	TTS("Insert Client access code.");
	std::cin >> clientCode;

	addressInformations.sin_family = AF_INET; //DEFINE TCP/IP como padrão do socket
	addressInformations.sin_port = htons(4471); //define porta padrão
	addressInformations.sin_addr.s_addr = serverCode; //define ip padrão

}

//INICIALIZA o WINSOCK no OS (necessário apra usar sockets)
void 	easyStartWinSocket() {

	WSADATA wsaData;

	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		std::cout << "WSAStartup failed: %d\n" << iResult << std::endl;
		TTS("Windows Socket API startup failed.Contact Administration");
		system("pause");
		exit(1);
	}

}

//Cria o socket e povoa o endereço correto para socket.
void easySocketCreate() {

	std::cout << endl;
	std::cout << "Creating socket... ";

	int iResult = (socketAtivo = socket(AF_INET, SOCK_STREAM, 0));
	if (iResult == -1) {
		std::cout << "Unable to Initialize Socket. Contact Administration." << std::endl;
		TTS("Unable to Initialize Socket. Contact Administration");
		system("pause");
		exit(1);
	}
	else {
		std::cout << "Ok!" << std::endl;
	}

}

//reserva o socket para este programa
void easyConnect() {

	std::cout << "Connecting... ";

	int iResult = connect(socketAtivo, (sockaddr*)&addressInformations, sizeof(struct sockaddr));
	if (iResult == -1) {
		std::cout << "Failed. Contact Administration." << endl;
		TTS("Connecting failed. Contact Administration");
		system("pause");
		exit(1);
	}

	std::cout << "Sucess!" << endl;
	send(socketAtivo, clientCode.c_str(), strlen(clientCode.c_str()), 0);

}

char* easyRecv() {

	while (!quit) {

		char serverMessage[1024];

		int messageSize;

		messageSize = recv(socketAtivo, serverMessage, 512, NULL);
		serverMessage[messageSize] = '\0';
	
		return(serverMessage);

	}

}

void easySend(std::string messageSent) {

	std::cout << "\\>";
	std::getline(cin, messageSent);
	send(socketAtivo, messageSent.c_str(), strlen(messageSent.c_str()), NULL);
	Beep(800, 400);

}

//termina conexão com o socket
void easyClose() {

	std::cout << "Closing Socket... ";

	if (closesocket(socketAtivo) == -1) {
		std::cout << "Unable to Close";
		exit(1);
	}

	std::cout << "Ending Program." << endl;
	TTS("Ending Program");
	system("pause");

}

void easyConnect(char* argv[]) {

	setup();
	easyStartWinSocket();
	easySocketCreate();
	easyConnect();

}
