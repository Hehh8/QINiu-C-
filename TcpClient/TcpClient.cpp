// TcpClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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
		return err;
	}
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) // 如果数据内的wVersion字段的高位或低位不等于1
	{
		// 清理套接字库
		WSACleanup();
		return -1;
	}

	// 创建tcp套接字
	SOCKET sockCli = socket(AF_INET, SOCK_STREAM, 0);

	// 准备绑定的信息
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	//连接服务器
	connect(sockCli, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	char sendBuf[] = "world";
	char recvBuf[100];

	// 发送数据到服务器
	send(sockCli, sendBuf, strlen(sendBuf) + 1, 0);

	// 接收服务器发送的数据
	recv(sockCli, recvBuf, sizeof(recvBuf), 0);

	cout << recvBuf << endl;

	// 关闭套接字
	closesocket(sockCli);

	// 清理套接字库
	WSACleanup();

	system("pause");
	return 0;
}


