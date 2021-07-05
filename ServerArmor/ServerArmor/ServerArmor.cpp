//Фатхутдинов

#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#pragma warning(disable: 4996) //происходит ошибка при использовании inet_addr, можно исправить с помощью INADDR_ANY
using namespace std;



char **logQuery = new char*[50];


void clientLog(SOCKET connection, int counter, SOCKET &socArray, char query[]) 
{
	
		SOCKET *socArr = &socArray;
		//char *logQ = &logQuery;
		
		cout << query << endl;
		
		logQuery[counter] = query;
		cout << "client number: " << counter << " log: " << logQuery[counter] << endl;
			
}

int main() 
{
	
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) 
	{
		cout << "library fail" << endl;
		exit(1);
	};


	SOCKADDR_IN address;
	address.sin_addr.s_addr = inet_addr("127.0.0.1"); //???? s_addr
	address.sin_port = htons(8000);
	address.sin_family = AF_INET;


	SOCKET socArray[50];
	int numberSoc = 0;
	
	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&address, sizeof(address));

	listen(sListen, SOMAXCONN);

	cout << "Wait connection..." << endl;

	for (int i = 0; i < 50; i++) 
	{
		int sizeAddr = sizeof(address);
		
		SOCKET newConnection = accept(sListen, (SOCKADDR*)&address, &sizeAddr);


		if (newConnection == 0)
		{
			cout << "Client connection error" << endl;
		}
		else
		{
			socArray[i] = newConnection;
			numberSoc++;
			cout << "Client " << numberSoc << " connection done" << endl;
			char message[512] = "Hello, new user!";
			send(newConnection, message, sizeof(message), NULL);
			char query[512];
			recv(socArray[i], query, sizeof(query), NULL);
			clientLog(socArray[i], numberSoc, *socArray, query);
			
			
			
		}
		
	}
	delete[]logQuery;
	system("pause");
	return 0;
}

