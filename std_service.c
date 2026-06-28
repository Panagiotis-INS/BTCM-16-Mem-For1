#include <stdio.h>
#include <string.h>
#include <windows.h>

static const char flag[] = "CTF{Str1ngs_4_4ensics}";

int main(void) {
    FreeConsole();

    SIZE_T min_ws = 256 * 1024, max_ws = 2 * 1024 * 1024;
    SetProcessWorkingSetSize(GetCurrentProcess(), min_ws, max_ws);

    char *buf = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!buf) return 1;
    memcpy(buf, flag, sizeof(flag));
    VirtualLock(buf, 4096);

    volatile char sink = 0;
    while (1) {
        sink ^= buf[0];
        Sleep(10);
    }

    return 0;
}
