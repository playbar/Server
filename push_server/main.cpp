#include <iostream>
#include <sys/signal.h>
#include "push_app.h"
#include "timer/Timer.hpp"
#include "util.h"

int main(int argc, const char * argv[])
{
    // insert code here...
    printf("start push server...\n");
    signal(SIGPIPE, SIG_IGN);
    CPushApp::GetInstance()->Init();
    CPushApp::GetInstance()->Start();
    writePid();
    while (true)
    {
        S_Sleep(1000);
    }
    return 0;
}
