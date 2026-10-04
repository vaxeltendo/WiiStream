#ifndef HTTP_H
#define HTTP_H

#include <gctypes.h>

int http_get(const char *host, u16 port, const char *path, char *buffer, u32 buffer_size);

#endif
