#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

#pragma comment(lib, "ws2_32.lib")

#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480 // How much is printed out to the screen

SOCKET createSocket(void){
	SOCKET recvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (recvSocket == INVALID_SOCKET)
	{
		printf("ERROR: socket unsuccessful\r\n");
		system("pause");
		exit(EXIT_FAILURE);
	}
	return recvSocket;
}

void connectToServer(SOCKET recvSocket, SOCKADDR_IN recvSockAddr){
	if (connect(recvSocket, (SOCKADDR*)&recvSockAddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		printf("ERROR: socket could not connect\r\n");
		closesocket(recvSocket);
		WSACleanup();
		exit(EXIT_FAILURE);
	}
}

void sendInitialRequest(SOCKET recvSocket, const char* host_name){
	char request[200];
	sprintf(request, "GET /var/2 HTTP/1.1\r\nHost:%s\r\n\r\n", host_name);  // add Host header with host_name value
	send(recvSocket, request, strlen(request), 0);
}

void receiveResponse(SOCKET recvSocket, char* buffer){
	int numrcv = recv(recvSocket, buffer, MAXBUFLEN, NO_FLAGS_SET);
	if (numrcv == SOCKET_ERROR)
	{
		printf("ERROR: recvfrom unsuccessful\r\n");
		int status = closesocket(recvSocket);
		if (status == SOCKET_ERROR)
			printf("ERROR: closesocket unsuccessful\r\n");
		status = WSACleanup();
		if (status == SOCKET_ERROR)
			printf("ERROR: WSACleanup unsuccessful\r\n");
		system("pause");
		exit(EXIT_FAILURE);
	}
}

void sendSecretRequest(SOCKET recvSocket, char* host_name, char* buffer){
	char secret[50];
	char request[200];
	strcpy(secret, strstr(buffer, "secret"));
	sprintf(request, "GET /var/2?%s HTTP/1.1\r\nHost:%s\r\n\r\n", secret, host_name);
	send(recvSocket, request, strlen(request), 0);
}

int calculateSideDiagonalSum(char* buffer){
	char* start = strstr(buffer, "Content-Length");
	while (!isdigit(*start) && *start) start++;
	while (isdigit(*start) && *start) start++;
	while (!isdigit(*start) && *start) start++;

	int size = 0;
	for (int i = 0; i < strlen(start); i++){
		if (start[i] == '\n') size++;
	}
	size++;

	char* end = start;
	int** array = (int**)malloc(size*sizeof(int));
	for (int i = 0; i < size; i++)
		array[i] = (int*)malloc(size*sizeof(int));
	int sum = 0;
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			array[i][j] = strtol(start, &end, 10);
			if (j == size - i - 1) sum += array[i][j];
			start = end;
			while (!isdigit(*start) && start[0] != '-' && *start) start++;
		}
	}
	for (int i = 0; i < size; i++)
		free(array[i]);
	free(array);

	return sum;
}

void sendFinalPOST(SOCKET recvSocket, char* host_name, int sum){
	char data[30];
	char request[200];
	sprintf(data, "result=%d", sum);
	printf("Sum on side diagonal: %d\n", sum);
	sprintf(request, "POST /var/2 HTTP/1.0\r\n"
		"Host: %s\r\n"
		"Content-type: application/x-www-form-urlencoded\r\n" //thanks stackoverflow for that
		"Content-length: %d\r\n\r\n"
		"%s\r\n", host_name, strlen(data), data);
	send(recvSocket, request, strlen(request) + 1, 0);
}

int main(void) {
	WSADATA Data;
	SOCKADDR_IN recvSockAddr;
	SOCKET recvSocket;
	int status;
	int numrcv = 0;
	struct hostent * remoteHost;
	char * ip;
	const char * host_name = "pb-homework.appspot.com";
	char buffer[MAXBUFLEN];
	memset(buffer, 0, MAXBUFLEN);
	// Initialize Windows Socket DLL
	status = WSAStartup(MAKEWORD(2, 2), &Data);
	if (status != 0)
	{
		printf("ERROR: WSAStartup unsuccessful\r\n");
		return 0;
	}
	// Get IP address from host name
	remoteHost = gethostbyname(host_name);
	ip = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
	printf("IP address is: %s.\n", ip);
	memset(&recvSockAddr, 0, sizeof(recvSockAddr)); // zero the sockaddr_in structure
	recvSockAddr.sin_port = htons(PORT); // specify the port portion of the address
	recvSockAddr.sin_family = AF_INET; // specify the address family as Internet
	recvSockAddr.sin_addr.s_addr = inet_addr(ip); // specify ip address

	// Create socket
	recvSocket = createSocket();

	// Connect
	connectToServer(recvSocket, recvSockAddr);

	// Send request
	sendInitialRequest(recvSocket, host_name);

	// Receieve
	receiveResponse(recvSocket, buffer);

	//Send request with secret param
	sendSecretRequest(recvSocket, host_name, buffer);

	receiveResponse(recvSocket, buffer);

	//Parse buffer and calculate side diagonal sum
	int sum = calculateSideDiagonalSum(buffer);

	printf("\nServer response:\n%s\n", buffer);

	//Send POST-request with calculation result
	sendFinalPOST(recvSocket, host_name, sum);
	
	for (int i = strlen(buffer); i >= 0; i--)
		buffer[i] = '\0';

	//Receiving "Success" if I'm a good coder.
	receiveResponse(recvSocket, buffer);

	printf("\nServer response:\n\n%s\n", buffer);

	closesocket(recvSocket);

	getchar();
	return EXIT_SUCCESS;
}
