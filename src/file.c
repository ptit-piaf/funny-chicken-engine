#include <string.h>

#include "file.h"

E_uriToFileSystem fn_uriToFileSystem(char* uri, char* filePath)
{
        if(strlen(uri) <= strlen("file:/"))
        {
                if(strlen(uri) == sizeof("file:/")-1 && !strcmp(uri, "file:/"))
                        return NOT_VALID_URI;

                u32 filePathIndex = 0;
                for(u32 i=0; i<strlen(uri); i++)
                {
                        if(uri[i] == '%')
                        {
                                if((    (uri[i+1] >= '0' && uri[i+1] <= '9') ||
                                        (uri[i+1] >= 'A' && uri[i+1] <= 'F') ||
                                        (uri[i+1] >= 'a' && uri[i+1] <= 'f')) &&

                                        ((uri[i+2] >= '0' && uri[i+2] <= '9') ||
                                        (uri[i+2] >= 'A' && uri[i+2] <= 'F') ||
                                        (uri[i+2] >= 'a' && uri[i+2] <= 'f')))
                                {
                                        if(uri[i+1] >= '0' && uri[i+1] <= '9')
                                                filePath[filePathIndex] = (uri[i+1]-'0') * 16;
                                        else if(uri[i+1] >= 'A' && uri[i+1] <= 'F')
                                                filePath[filePathIndex] = (uri[i+1]-'A'+10) * 16;
                                        else if(uri[i+1] >= 'a' && uri[i+1] <= 'f')
                                                filePath[filePathIndex] = (uri[i+1]-'a'+10) * 16;

                                        if(uri[i+2] >= '0' && uri[i+2] <= '9')
                                                filePath[filePathIndex] = uri[i+2]-'0';
                                        else if(uri[i+2] >= 'A' && uri[i+2] <= 'F')
                                                filePath[filePathIndex] = uri[i+2]-'A'+10;
                                        else if(uri[i+2] >= 'a' && uri[i+2] <= 'f')
                                                filePath[filePathIndex] = uri[i+2]-'a'+10;

                                        i+=3;
                                }
                                else
                                return NOT_VALID_URI;

                        }
                        else
                        filePath[filePathIndex] = uri[i];
                        filePathIndex++;
                }
        }

        u32 filePathIndex = 0;
        u32 uriStartIndex = 0;

        if(!strncmp(uri, "file:/", sizeof("file:/")-1))
        {
                uriStartIndex = sizeof("file:/")-1;
                if(uri[uriStartIndex] == '/')
                {
                        uriStartIndex++;
                        while(uri[uriStartIndex] != '/')
                                uriStartIndex++;
                        uriStartIndex++;
                }
                filePathIndex = 1;
                filePath[0] = '/';
        }

        for(u32 i=uriStartIndex; i<strlen(uri); i++)
        {
                if(uri[i] == '%')
                {
                        if((    (uri[i+1] >= '0' && uri[i+1] <= '9') ||
                                (uri[i+1] >= 'A' && uri[i+1] <= 'F') ||
                                (uri[i+1] >= 'a' && uri[i+1] <= 'f')) &&

                                ((uri[i+2] >= '0' && uri[i+2] <= '9') ||
                                (uri[i+2] >= 'A' && uri[i+2] <= 'F') ||
                                (uri[i+2] >= 'a' && uri[i+2] <= 'f')))
                        {
                                if(uri[i+1] >= '0' && uri[i+1] <= '9')
                                        filePath[filePathIndex] = (uri[i+1]-'0') * 16;
                                else if(uri[i+1] >= 'A' && uri[i+1] <= 'F')
                                        filePath[filePathIndex] = (uri[i+1]-'A'+10) * 16;
                                else if(uri[i+1] >= 'a' && uri[i+1] <= 'f')
                                        filePath[filePathIndex] = (uri[i+1]-'a'+10) * 16;

                                if(uri[i+2] >= '0' && uri[i+2] <= '9')
                                        filePath[filePathIndex] = uri[i+2]-'0';
                                else if(uri[i+2] >= 'A' && uri[i+2] <= 'F')
                                        filePath[filePathIndex] = uri[i+2]-'A'+10;
                                else if(uri[i+2] >= 'a' && uri[i+2] <= 'f')
                                        filePath[filePathIndex] = uri[i+2]-'a'+10;

                                i+=3;
                        }
                        else
                        return NOT_VALID_URI;

                }
                else
                filePath[filePathIndex] = uri[i];
                filePathIndex++;
        }

        return SUCCESS;
}


