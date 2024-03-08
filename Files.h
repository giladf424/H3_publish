#pragma once
#ifndef __FILES__
#define __FILES__

int writeIntToFile(FILE* fp, int value, char const* msg);
int writeCharToFile(FILE* fp, int size, char const* arr, char const* msg);
int writeStringToFile(FILE* fp, char const* str, char const* msg);
#endif // !__FILES__
