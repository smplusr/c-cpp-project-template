#ifdef __linux__

#ifdef __cplusplus
#include<cstring>
#include<dlfcn.h>
#ifndef ECL_COMPILE_INSTRUCTION
	#define ECL_COMPILE_INSTRUCTION "g++ -shared -o tmp.so tmp.c"
#endif
#define ECL_GET_DL_POINTER auto init=reinterpret_cast<void(*)()>(dlsym(lib,"__init__"));
#endif

#ifndef __cplusplus
#include<stdio.h>
#include<stdlib.h>
#include<dlfcn.h>
#include<string.h>
#ifndef ECL_COMPILE_INSTRUCTION
	#define ECL_COMPILE_INSTRUCTION "gcc -shared -o tmp.so tmp.c" 
#endif
#define ECL_GET_DL_POINTER void (*init)()=dlsym(lib,"__init__");
#endif

#define ECL_COMPILE system(ECL_COMPILE_INSTRUCTION);

#define ECL_LOAD_LIB()\
	void *lib;\
	lib=dlopen("./tmp.so",RTLD_LAZY);\
	ECL_GET_DL_POINTER;\
		dlclose(lib); init();\
		system("rm tmp.so");
	
void evalc(const char data[256]){
	FILE *fptr;
	fptr=fopen("tmp.c","w"); fprintf(fptr,"%s",data); fclose(fptr);
		ECL_COMPILE; ECL_LOAD_LIB();
		system("rm tmp.c");
}

void evalf(const char *file){
	char *buffer=(char*)malloc(256);
	strcat(buffer,"cp "); strcat(buffer,file); strcat(buffer," tmp.c "); system(buffer);
		ECL_COMPILE; ECL_LOAD_LIB();
		system("rm tmp.c");
}

#endif