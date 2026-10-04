#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include "network.h"
#include "http.h"

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

void init_graphics() {
    VIDEO_Init();
    WPAD_Init();
    rmode = VIDEO_GetPreferredMode(NULL);
    xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
    CON_Init(xfb, 20, 20, rmode->fbWidth, rmode->xfbHeight, rmode->fbWidth * VI_DISPLAY_PIX_SZ);
    VIDEO_Configure(rmode);
    VIDEO_SetNextFramebuffer(xfb);
    VIDEO_SetBlack(FALSE);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    if (rmode->viTVMode & VI_NON_INTERLACE) VIDEO_WaitVSync();
}

int main(int argc, char **argv) {
    init_graphics();

    printf("\x1b[2;0H");
    printf("==================================================\n");
    printf("         WiiStream - Internet Archive Catalog     \n");
    printf("==================================================\n\n");

    if (init_network() == 0) {
        printf("\nObteniendo catalogo desde Replit...\n");

        char response[2048];
        memset(response, 0, sizeof(response));

        int bytes = http_get("python-flask-server-varguandz.replit.app", 80, "/api/movies", response, sizeof(response));

        if (bytes > 0) {
            printf("\n--- CATALOGO RECIBIDO (%d bytes) ---\n\n", bytes);
            response[600] = '\0';
            printf("%s\n", response);
        } else {
            printf("\nError al conectar con Replit.\n");
        }
    } else {
        printf("Error: No se pudo conectar a la red local.\n");
    }

    printf("\n\nPresiona HOME en el Wiimote para salir.\n");

    while (1) {
        WPAD_ScanPads();
        u32 pressed = WPAD_ButtonsDown(0);
        if (pressed & WPAD_BUTTON_HOME) exit(0);
        VIDEO_WaitVSync();
    }

    return 0;
}
