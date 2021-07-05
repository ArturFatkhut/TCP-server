//Фатхутдинов

#include <iostream>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#pragma warning(disable: 4996) //происходит ошибка при использовании inet_addr, можно исправить с помощью INADDR_ANY

using namespace std;

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


	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);

	if (connect(Connection, (SOCKADDR*)&address, sizeof(address)) != 0) 
	{
		cout << "Connection error" << endl;
		return(1);
	}
	else
	{
		cout << "Connection done" << endl;

		char mess[512];
		recv(Connection, mess, sizeof(mess), NULL);
		cout << mess << endl;
		char query[512];
		cout << "write query: ";
		cin >> query;
		send(Connection, query, sizeof(query), NULL);
	}

	
	system("pause");

	return 0;
}