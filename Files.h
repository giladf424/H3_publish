#pragma once
#ifndef __FILES__
#define __FILES__

int writeIntToBFile(FILE* fp, int value, char const* msg);
int writeCharToBFile(FILE* fp, int size, char const* arr, char const* msg);
int writeStringToBFile(FILE* fp, char const* str, char const* msg);
int readIntFromBFile(FILE* fp, int* pValue, const char* msg);
int readCharFromBFile(FILE* fp, char* arr, int len, const char* msg);
int readStringFromBFile(FILE* fp, char* arr, const char* msg);
#endif // !__FILES__
