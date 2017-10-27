#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FILES 255
#define NAMEOFFILES 40

bool fileInDirectory( char *folderName);

bool encryptFileList(char* folderName);

bool encrypt( char *fileName);

bool decrypt (char *fileName);

#endif //ENCRYPTION_H
