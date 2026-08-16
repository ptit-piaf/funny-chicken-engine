#include <string.h>

#include "file.h"

size_t fn_getFileSystemSizeFromUri(char* uri)
{
        u32 returnValue = 0;

        for(u32 i=0; i<strlen(uri); returnValue++, i++)
        {
                if(!uri[i])
                        break;

                if(uri[i] == '%')
                        i+=2;
        }
        return returnValue+1;           // +1 for the \0
}

E_error fn_uriToFileSystem(char* uri, char* filePath)
{
        if(strlen(uri) <= strlen("file:/"))
        {
                if(strlen(uri) == sizeof("file:/")-1 && !strcmp(uri, "file:/"))
                        return HOL_PARSING_FAILED;

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
                                                filePath[filePathIndex] += uri[i+2]-'0';
                                        else if(uri[i+2] >= 'A' && uri[i+2] <= 'F')
                                                filePath[filePathIndex] += uri[i+2]-'A'+10;
                                        else if(uri[i+2] >= 'a' && uri[i+2] <= 'f')
                                                filePath[filePathIndex] += uri[i+2]-'a'+10;

                                        i+=2;
                                }
                                else
                                {
                                        return HOL_PARSING_FAILED;
                                }

                        }
                        else
                        {
                                filePath[filePathIndex] = uri[i];
                        }
                        filePathIndex++;
                }
                filePath[filePathIndex] = '\0';
                return HOLY_SUCCESS;
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
                                        filePath[filePathIndex] += uri[i+2]-'0';
                                else if(uri[i+2] >= 'A' && uri[i+2] <= 'F')
                                        filePath[filePathIndex] += uri[i+2]-'A'+10;
                                else if(uri[i+2] >= 'a' && uri[i+2] <= 'f')
                                        filePath[filePathIndex] += uri[i+2]-'a'+10;

                                i+=2;
                        }
                        else
                        return HOL_NOT_VALID;

                }
                else
                filePath[filePathIndex] = uri[i];
                filePathIndex++;
        }

        filePath[filePathIndex] = '\0';
        return HOLY_SUCCESS;
}



char* fn_getDirPathFromFilePath(char* filePath)
{
        u32 dirPathSize = 0;

        u32 filePathSize = strlen(filePath) + 1;
        for(u32 i=0; i<filePathSize; i++)
        {
                switch(filePath[i])
                {
                        case '/':
                                dirPathSize = i;
                                break;
                        case '\0':
                                goto GO_QUIT_LOOP;
                }
        }

GO_QUIT_LOOP:

        if(!dirPathSize)
                return NULL;

        char* dirPath = malloc(dirPathSize) + 1;

        return memcpy(dirPath, filePath, dirPathSize);
}
