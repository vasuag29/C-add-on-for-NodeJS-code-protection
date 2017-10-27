#include <nan.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <vector>

using namespace std;
using namespace Nan;
using namespace v8;

/////////////////////////////////
bool fileInDirectoryEncryption(char *folderName);
bool encryptFileList(char* folderName);
bool encrypt(const char *fileName);
bool decrypt (char *fileName);
bool isDir(char* name);

std::vector<std::string> vecFileName;
std::vector<std::string> vecNewFileName;

bool isDir(char *name) {
    DIR* directory = opendir(name);
    if(directory != NULL) {
      closedir(directory);
      return true;
    }
    else {
      return false;
    }
}

bool fileInDirectoryEncryption(char *folderName) {
   struct dirent *de;  // Pointer for directory entry
	 // opendir() returns a pointer of DIR type.
	 DIR *dr = opendir(folderName);
	 if (dr == NULL) { // opendir returns NULL if couldn't open directory
			 printf("Could not open current directory" );
			 return false;
	 }
   char temp[100];
	 while ((de = readdir(dr)) != NULL) {
			 printf("Read:%s\n", de->d_name);
       if( isDir(de->d_name) == false) {
           printf("Hello_01");
           strcpy(temp, folderName);
           strcat(temp, "/");
           strcat(temp, de->d_name);
           printf("Path_File_Final:- %s\n", temp);
           vecFileName.push_back(temp);
           strcat(temp, "-");
           vecNewFileName.push_back(temp);
           temp[0] = '\0';
         }
         else {
           printf("This is Directory:- %s\n", de->d_name);
         }
	 }
	 closedir(dr);
   for(int i = 0; i != vecFileName.size() ; i++) {
     cout<<"Length and Data: " << vecFileName[i] << endl;
     std::string tempName = vecFileName[i];
     std::string tempNewName = vecNewFileName[i];
     //char *nameOfFile = tempName;
     bool isSuccess =  encrypt(tempName.c_str(), tempNewName.c_str());
     if(isSuccess == true) {
       cout<<"File Name: " << vecFileName[i] << "Encrypted Successfully"<< endl;
     }
     else {
       cout<<"File Name: " << vecFileName[i] << "Encrypted Failed"<< endl;
       return false;
     }
   }
   return true;
}

bool encrypt(const char *fileName, const char *newFileName)
{
		FILE *inFile;   //Declare inFile
    FILE *outFile;   //Declare inFile
    //char *newFileName = "encryptedfiles/abc.js";
		//FILE *outFile;  //Declare outFile
		char Byte;
		char newByte;
		int n;
		inFile = fopen(fileName,"rb");
    outFile = fopen(newFileName, "w");

		if(inFile == NULL) {
		  printf("Error in opening file/ File not available");
		  return false;
		}
   	else {
		  printf("\nFile Opened, Encrypting");
			while(1) {
			  while ( !feof( inFile ) ) {
					 Byte=fgetc(inFile);
					 newByte=Byte+25;
           //cout<<"Old_Byte: " << Byte << "New_Byte: " <<newByte <<endl;
					 //fputc(newByte,inOutFile);
           fputc(newByte,outFile);

			  }
			  printf("End of File");
			  break;
			}
			fclose(inFile);
      fclose(outFile);
			return true;
		}
}

bool decrypt (char *fileName)
{
	 //char *fileName
	 FILE *inFile; //Declare inFile
	 FILE *outFile; //Declare outFile

	 char Byte;
	 char newByte;
	 int i=0;
   char *fleName  = "encryptedfiles/abc.js";
   char *newName  = "encryptedfiles/lmn.js";
	 inFile = fopen(fleName,"rw");
	 outFile = fopen(newName, "w");
	 if(inFile == NULL){
			 printf("Error in opening file / File not available");
			 return false;
	 }
	 else {
		 printf("File Opened, Decrypting");
		 while(1) {
				 printf(".");
				 while ( !feof( inFile ) ){
						 Byte=fgetc(inFile);
						 newByte=Byte-25;
              fputc(newByte,outFile);
					}
					printf("End of File");
					break;
		 }
     fclose(inFile);
     fclose(outFile);
		 return true;
	 }
}

//////////////////////////////

NAN_METHOD(PassNumber) {
    Nan::Maybe<double> value = Nan::To<double>(info[0]);
    Local<Number> retval = Nan::New(value.FromJust() + 42);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(PassInteger) {
    if ( info.Length() < 1 ) {
        return;
    }
    if ( !info[0]->IsInt32()) {
        return;
    }
    int value = info[0]->IntegerValue();
    Local<Integer> retval = Nan::New(value + 42);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(PassBoolean) {
    if ( info.Length() < 1 ) {
        return;
    }
    if ( !info[0]->IsBoolean()) {
        return;
    }
    bool value = info[0]->BooleanValue();
    Local<Boolean> retval = Nan::New(!value);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(PassString) {
    if ( info.Length() < 1 ) {
        return;
    }
    if ( !info[0]->IsString()) {
        return;
    }
    v8::String::Utf8Value val(info[0]->ToString());

    std::string str (*val);
    std::reverse(str.begin(), str.end());

    info.GetReturnValue().Set(Nan::New<String>(str.c_str()).ToLocalChecked());
}

NAN_METHOD(PassObject) {
    if ( info.Length() > 0 ) {
        Local<Object> input = info[0]->ToObject();

        // Make property names to access the input object
        Local<String> x_prop = Nan::New<String>("x").ToLocalChecked();
        Local<String> y_prop = Nan::New<String>("y").ToLocalChecked();
        Local<String> sum_prop = Nan::New<String>("sum").ToLocalChecked();
        Local<String> product_prop = Nan::New<String>("product").ToLocalChecked();

        // create the return object
        Local<Object> retval = Nan::New<Object>();

        // pull x and y out of the input.  We'll get NaN if these weren't set,
        // or if x / y aren't able to be converted to numbers.
        double x = Nan::Get(input, x_prop).ToLocalChecked()->NumberValue();
        double y = Nan::Get(input, y_prop).ToLocalChecked()->NumberValue();

        // set the properties on the return object
        Nan::Set(retval, sum_prop, Nan::New<Number>(x+y));
        Nan::Set(retval, product_prop, Nan::New<Number>(x*y));

        info.GetReturnValue().Set(retval);
    }
}

// Increment each value in the array parameter,
// Return a new array with the squares of the original
// array and a 'sum_of_squares' property.
NAN_METHOD(IncrementArray) {
    Local<Array> array = Local<Array>::Cast(info[0]);

    Local<String> ss_prop = Nan::New<String>("sum_of_squares").ToLocalChecked();
    Local<Array> squares = New<v8::Array>(array->Length());
    double ss = 0;

    for (unsigned int i = 0; i < array->Length(); i++ ) {
      if (Nan::Has(array, i).FromJust()) {
        // get data from a particular index
        double value = Nan::Get(array, i).ToLocalChecked()->NumberValue();

        // set a particular index - note the array parameter
        // is mutable
        Nan::Set(array, i, Nan::New<Number>(value + 1));
        Nan::Set(squares, i, Nan::New<Number>(value * value));
        ss += value*value;
      }
    }
    // set a non index property on the returned array.
    Nan::Set(squares, ss_prop, Nan::New<Number>(ss));
    info.GetReturnValue().Set(squares);
}

NAN_METHOD(AddArray) {
    if ( info.Length() > 0 ) {
        Local<Object> input = info[0]->ToObject();
        Local<String> a_prop = Nan::New<String>("a").ToLocalChecked();
        Local<String> b_prop = Nan::New<String>("b").ToLocalChecked();

        double a = Nan::Get(input, a_prop).ToLocalChecked()->NumberValue();
        Local<Array> b = Local<Array>::Cast(Nan::Get(input, b_prop).ToLocalChecked());

        for (unsigned int i = 0; i < b->Length(); i++ ) {
            if (Nan::Has(b, i).FromJust()) {
                // get data from a particular index
                double value = Nan::Get(b, i).ToLocalChecked()->NumberValue();

                // set a particular index - note the array parameter
                // is mutable
                Nan::Set(b, i, Nan::New<Number>(value + a));
            }
        }
    }
}

NAN_METHOD(ParseFolder) {
  v8::String::Utf8Value folderName(info[0]->ToString());
  if ( (info.Length() < 1) && (!info[0]->IsString())) {
      return;
  }
  char *nameFolder = *(folderName);
  bool temp = fileInDirectoryEncryption(nameFolder);
  if(temp) {

  }
  else {

  }

}

NAN_METHOD(decrypt) {
  //v8::String::Utf8Value fileName = info[0];
  v8::String::Utf8Value fileName(info[0]->ToString());
  if ( (info.Length() < 1) && (!info[0]->IsString())) {
      return;
  }
  char *fNames = *(fileName);
  bool success =  decrypt(fNames);
  if(success) {

  }
  else{
    //file reading error
  }

}

NAN_MODULE_INIT(Init) {
   Nan::Set(target, New<String>("pass_number").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(PassNumber)).ToLocalChecked());
   Nan::Set(target, New<String>("pass_integer").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(PassInteger)).ToLocalChecked());
   Nan::Set(target, New<String>("pass_boolean").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(PassBoolean)).ToLocalChecked());
   Nan::Set(target, New<String>("pass_string").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(PassString)).ToLocalChecked());
   Nan::Set(target, New<String>("pass_object").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(PassObject)).ToLocalChecked());
   Nan::Set(target, New<String>("pass_array").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(IncrementArray)).ToLocalChecked());
   Nan::Set(target, New<String>("add_array").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(AddArray)).ToLocalChecked());

    Nan::Set(target, New<String>("parse_folder").ToLocalChecked(),
         GetFunction(New<FunctionTemplate>(ParseFolder)).ToLocalChecked());
    Nan::Set(target, New<String>("decrypt").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(decrypt)).ToLocalChecked());
}

NODE_MODULE(addon_source, Init)
