#include <stdio.h>
#include <string.h>
#include <network.h>
#include "network.h"

int init_network(void) {
    printf("Inicializando red...\n");
    
    s32 result = if_config(NULL, NULL, NULL, TRUE, 20);
    if (result < 0) {
        printf("Error al conectar a la red: %d\n", result);
        return -1;
    }

    char my_ip[16];
    if (net_gethostip(my_ip)) {
        printf("Conectado con exito. IP: %s\n", my_ip);
        return 0;
    }

    printf("No se pudo obtener la direccion IP.\n");
    return -1;
}
