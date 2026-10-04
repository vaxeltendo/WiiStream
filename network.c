#include <stdio.h>
#include <string.h>
#include <gccore.h>
#include <network.h>
#include <arpa/inet.h>
#include "network.h"

int init_network(void) {
    printf("Inicializando red...\n");

    s32 result = net_init();
    if (result < 0) {
        printf("Error al iniciar la pila de red: %d\n", result);
        return -1;
    }

    char localip[16] = {0};
    char netmask[16] = {0};
    char gateway[16] = {0};

    result = if_config(localip, netmask, gateway, TRUE, 20);
    if (result < 0) {
        printf("Error de configuracion red (DHCP): %d\n", result);
        return -1;
    }

    u32 ip = net_gethostip();
    if (ip != 0) {
        struct in_addr addr;
        addr.s_addr = ip;
        printf("Conectado con exito. IP: %s\n", inet_ntoa(addr));
        return 0;
    }

    printf("No se pudo obtener la direccion IP.\n");
    return -1;
}
