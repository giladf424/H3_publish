#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Files.h"

int writeIntToFile(FILE* fp, int value, char const* msg)
{
	int val = value;
	if (fwrite(&val, sizeof(int), 1, fp) != 1)
	{
		printf("%s", msg);
		return 0;
	}
	return 1;
}

int writeCharToFile(FILE* fp, int size, char const* arr, char const* msg)
{
	if (fwrite(arr, sizeof(char), size, fp) != size)
	{
		printf("%s", msg);
		return 0;
	}
	return 1;
}

int writeStringToFile(FILE* fp, char const* str, char const* msg)
{
	int len = strlen(str) + 1;
	if (writeIntToFile(fp, len, msg ) != 1)
	{
		printf("%s", msg);
		return 0;
	}
	if (writeCharToFile(fp, len, str, msg) != 1)
	{
		printf("%s", msg);
		return 0;
	}
	return 1;
}
