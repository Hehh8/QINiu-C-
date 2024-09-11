// TcpServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
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
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	// 准备绑定的信息
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	// 端口0-65535, 1024以下的端口是系统保留的.
	addrSrv.sin_port = htons(6000);

	// 绑定套接字到本机
	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	// 监听
	listen(sockSrv, 10);

	cout << "Server start at port: 6000" << endl;

	SOCKADDR addrCli;
	int len = sizeof(SOCKADDR);

	char recvBuf[100];
	char sendBuf[100];
	while (true)
	{
		// 接收连接请求,返回针对客户的套接字
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrCli, &len);

		sprintf_s(sendBuf, 100, "hello");
		send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);
		// 接受或发送数据
		recv(sockConn, recvBuf, 100, 0);

		cout << recvBuf << endl;

		// 关闭套接字
		closesocket(sockConn);
	}

	// 关闭套接字
	closesocket(sockSrv);

	// 清理套接字库
	WSACleanup();

	system("pause");
	return 0;
}

