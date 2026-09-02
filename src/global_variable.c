#include <stdio.h>

#include "global_variable.h"

FILE* g_eventFStream;
FILE* g_openglErrorFStream;

void fn_manageMainArg()
{
        g_eventFStream = fopen("event.data", "w");
        g_openglErrorFStream = stderr;
        return;
}
