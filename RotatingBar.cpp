#include<iostream>
#include <chrono>
#include <thread>
using namespace std;

int main()
{
    char chars[] = { '-', '\\', '|', '/' };
    unsigned int i;

    for (i = 0; ; ++i) {
        printf("%c\r", chars[i % sizeof(chars)]);
        fflush(stdout);
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    return 0;
}