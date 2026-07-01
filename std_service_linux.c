#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

static const char flag[] = "CTF{L1nuXX_Str1ngs_4_4ensics}";

int main(void) {
    if (daemon(0, 0) != 0) return 1;

    void *buf = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (buf == MAP_FAILED) return 1;
    memcpy(buf, flag, sizeof(flag));
    mlock(buf, 4096);

    volatile char sink = 0;
    while (1) {
        sink ^= ((char *)buf)[0];
        usleep(10000);
    }

    return 0;
}
