#include <stdio.h>

#include "global_variable.h"

FILE* g_eventFStream;
FILE* openglErrorFStream;

void fn_manageMainArg()
{
        g_eventFStream = fopen("event.data", "w");
        openglErrorFStream = fopen("opengl_error.txt", "w");
        return;
}
