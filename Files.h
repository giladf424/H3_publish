#pragma once
#ifndef __FILES__
#define __FILES__

int writeIntToBFile(FILE* fp, int value, char const* msg);
int writeCharToBFile(FILE* fp, int size, char const* arr, char const* msg);
int writeStringToBFile(FILE* fp, char const* str, char const* msg);
#endif // !__FILES__
