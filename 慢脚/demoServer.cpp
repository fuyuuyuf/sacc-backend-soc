#pragma execution_character_set("utf-8")
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32.lib")

int main() {
    system("chcp 65001 > nul");
    // 初始化 Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "WSAStartup 失败" << std::endl;
        return 1;
    }

    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd == INVALID_SOCKET) {
        std::cout << "创建 socket 失败" << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(serverFd, reinterpret_cast<sockaddr*>(&address), sizeof(address)) == SOCKET_ERROR) {
        std::cout << "绑定端口失败" << std::endl;
        closesocket(serverFd);
        WSACleanup();
        return 1;
    }

    if (listen(serverFd, 5) == SOCKET_ERROR) {
        std::cout << "监听失败" << std::endl;
        closesocket(serverFd);
        WSACleanup();
        return 1;
    }

    std::cout << "服务端启动，监听 8080 端口" << std::endl;

    sockaddr_in clientAddress{};
    int clientLength = sizeof(clientAddress);

    int clientFd = accept(serverFd, reinterpret_cast<sockaddr*>(&clientAddress), &clientLength);
    if (clientFd == INVALID_SOCKET) {
        std::cout << "接收连接失败" << std::endl;
        closesocket(serverFd);
        WSACleanup();
        return 1;
    }

    char buffer[1024]{};
    int bytes = recv(clientFd, buffer, sizeof(buffer) - 1, 0);

    if (bytes > 0) {
        std::cout << "收到客户端消息：" << buffer << std::endl;
    }

    std::string response = "Hello World!";
    send(clientFd, response.c_str(), response.size(), 0);

    closesocket(clientFd);
    closesocket(serverFd);
    WSACleanup();
    system("pause");
    return 0;
}