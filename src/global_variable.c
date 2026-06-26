#include <stdio.h>

#include "global_variable.h"

FILE* g_eventFStream;

void fn_manageMainArg()
{
        g_eventFStream = fopen("event.data", "w");
        return;
}
