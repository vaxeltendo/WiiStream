#include <stdio.h>
#include <string.h>
#include <gccore.h>
#include <network.h>
#include "http.h"

int http_get(const char *host, u16 port, const char *path, char *buffer, u32 buffer_size) {
    s32 sock = net_socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (sock < 0) return -1;

    struct hostent *he = net_gethostbyname(host);
    if (!he || !he->h_addr_list[0]) {
        net_close(sock);
        return -2;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    memcpy(&server.sin_addr, he->h_addr_list[0], he->h_length);

    if (net_connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        net_close(sock);
        return -3;
    }

    char request[512];
    snprintf(request, sizeof(request),
             "GET %s HTTP/1.1\r\n"
             "Host: %s\r\n"
             "User-Agent: WiiStream/1.0\r\n"
             "Connection: close\r\n\r\n",
             path, host);

    if (net_write(sock, request, strlen(request)) < 0) {
        net_close(sock);
        return -4;
    }

    int total_bytes = 0;
    while (total_bytes < buffer_size - 1) {
        s32 bytes = net_read(sock, buffer + total_bytes, buffer_size - 1 - total_bytes);
        if (bytes <= 0) break;
        total_bytes += bytes;
    }
    buffer[total_bytes] = '\0';

    net_close(sock);
    return total_bytes;
}
