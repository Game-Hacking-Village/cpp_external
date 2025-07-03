#include <cstdio>
#include <windows.h>

void win() {
    printf("game won!");
    exit(0);
}

int main(int argc, char *argv[]) {
    int test_var = 123;
    printf("set test var to 0 to win\n");
    printf("test var: 0x%p\n", &test_var);

    while (test_var) {
        Sleep(50);
    }

    win();
    return 1;
}
