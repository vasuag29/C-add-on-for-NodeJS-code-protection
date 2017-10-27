#include "encryption.h"

static char fileNames[FILES][NAMEOFFILES] = {0};
//static char newFileNames[255][40] = {0};

bool encryptFileList(char* folderName) {
	if(! fileInDirectory(folderName, fileNames)) {
		printf("Error in fetch the file list");
		return false;
	}
	char *files = NULL;
	files = fileNames[0];
	while(files != NULL) {
		if(encrypt(files)) {
				files++;
		}
	  else {
			return false;
		}
	}
	return true;
}

bool encrypt( char *fileName)
{
		FILE *inOutFile;   //Declare inFile
		//FILE *outFile;  //Declare outFile
		char Byte;
		char newByte;
		int n;
		inOutFile = fopen(fileName,"rw");

		if(inOutFile == NULL) {
		  printf("Error in opening file/ File not available");
		  return false;
		}	else {
		  printf("\nFile Opened, Encrypting");
			while(1) {
			  while ( !feof( inOutFile ) ) {
					 Byte=fgetc(inOutFile);
					 newByte=Byte+25;
					 fputc(newByte,inOutFile);
			  }
			  printf("End of File");
			  break;
			}
			fclose(inOutFile);
			return true;
		}
}

bool decrypt (char *fileName)
{
	char *fileName
	 FILE *inOutFile; //Declare inFile
	 FILE *outFile; //Declare outFile

	 char Byte;
	 char newByte;
	 int i=0;

	 inOutFile = fopen(fileName,"rw");
	 //outFile = fopen(NEW_FILENAME, "w");
	 if(inOutFile == NULL){
			 printf("Error in opening file / File not available");
			 return false;
	 }
	 else {
		 printf("File Opened, Decrypting");
		 while(1) {
				 printf(".");
				 while ( !feof( inOutFile ) ){
						 Byte=fgetc(inOutFile);
						 newByte=Byte-25;
						 fputc(newByte,inOutFile);
					}
					printf("End of File");
					break;
		 }
     fclose(inOutFile);
		 return true;
	 }
}

bool fileInDirectory(char *folderName) {
   struct dirent *de;  // Pointer for directory entry
	 // opendir() returns a pointer of DIR type.
	 DIR *dr = opendir(folderName);
	 if (dr == NULL) { // opendir returns NULL if couldn't open directory
			 printf("Could not open current directory" );
			 return false;
	 }
	 // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
	 // for readdir()
	 int i = 0;
	 while ((de = readdir(dr)) != NULL) {
					 printf("%s\n", de->d_name);
					 fileNames[i++] = de->d_name;
	 }
	 closedir(dr);
	 return true;
}
