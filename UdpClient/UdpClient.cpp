// UdpClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
	// 初始化套接字库
	WORD mVersion;
	WSADATA wsaData;
	int err;
	mVersion = MAKEWORD(1, 1);
	err = WSAStartup(mVersion, &wsaData);
	if (err != 0)
	{
		return 0;
	}
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return -1;
	}

	// 创建UDP套接字
	SOCKET sockCli = socket(AF_INET, SOCK_DGRAM, 0);

	// 准备绑定的信息
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6002);

	SOCKADDR_IN addrCli;
	int len = sizeof(SOCKADDR);

	char sendBuf[] = "send from udp client";
	char recvBuf[100];

	sendto(sockCli, sendBuf, strlen(sendBuf) + 1, 0, (SOCKADDR*)&addrSrv, len);
	cout << "sent to server:" << sendBuf << endl;

	recvfrom(sockCli, recvBuf, 100, 0, (SOCKADDR*)&addrCli, &len);
	cout << "recvive from server:" << recvBuf << endl;

	closesocket(sockCli);
	WSACleanup();

	system("pause");
	return 0;
}

