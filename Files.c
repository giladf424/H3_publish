#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Files.h"

int writeIntToBFile(FILE* fp, int value, char const* msg)
{
	int val = value;
	if (fwrite(&val, sizeof(int), 1, fp) != 1)
	{
		printf("%s\n", msg);
		return 0;
	}
	return 1;
}

int writeCharToBFile(FILE* fp, int size, char const* arr, char const* msg)
{
	if (fwrite(arr, sizeof(char), size, fp) != size)
	{
		printf("%s\n", msg);
		return 0;
	}
	return 1;
}

int writeStringToBFile(FILE* fp, const char* str, char const* msg)
{
	int len = (int)strlen(str) + 1;
	if (writeIntToBFile(fp, len, msg ) != 1)
	{
		printf("%s\n", msg);
		return 0;
	}
	if (writeCharToBFile(fp, len, str, msg) != 1)
	{
		printf("%s\n", msg);
		return 0;
	}
	return 1;
}

int readIntFromBFile(FILE* fp, int* pValue, const char* msg)
{
	if (fread(pValue, sizeof(int), 1, fp) != 1)
	{
		printf("%s\n", msg);
		return 0;
	}
	return 1;
}

int readCharFromBFile(FILE* fp, char* arr, int len, const char* msg)
{
	if (fread(arr, sizeof(char), len, fp) != len)
	{
		printf("%s\n", msg);
		return 0;
	}
	return 1;
}

//char* readStringFromBFile(FILE* fp, char* arr, const char* msg)
//{
//	int len;
//	if (readIntFromBFile(fp, &len, "Error! the company name length wasn't read from the file") != 1)
//		return 0;
//	arr = (char*)malloc(len * sizeof(char));
//	if (!arr)
//	{
//		printf("Memory alocation error");
//		return 0;
//	}
//	if (fread(arr, sizeof(char), len, fp) != len)
//	{
//		printf("%s\n", msg);
//		free(arr);
//		return 0;
//	}
//	return arr;
//}
