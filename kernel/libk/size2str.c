
#include <stdint.h>
#include <printf.h>

char size[20];
char *sizes[6] = { "B  ", "KiB", "MiB", "GiB", "TiB", "PiB"};

char* size2str( size_t size) {
    float showsize = size;
    int unit = 0;
    while (showsize > 1024.0f) {
        showsize /= 1024.0f;
        unit++;
        }
    snprintf(size, 20, "%.2f %s", showsize, sizes[unit]);
    
    return size;
}