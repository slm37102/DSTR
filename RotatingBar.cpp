#include<iostream>
#include <chrono>
#include <thread>
using namespace std;

int main()
{
    char chars[] = { '-', '\\', '|', '/' };
    unsigned int i;

    for (i = 0; ; ++i) { // this loop iterates every 100ms
        printf("%c\r", chars[i % sizeof(chars)]); // %c to print characters and \r to move the cursor back to front of this line
        fflush(stdout);
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    return 0;
}
