/*
The following routines are all exported by japi.dll:

char* MemStrSearch(unsigned char *start, unsigned char *end, char *str);
bool MemPatternCompare(unsigned char *address, unsigned char *pattern, unsigned char *mask, unsigned long length);
unsigned char* MemPatternSearch(unsigned char *start, unsigned char *end, unsigned char *pattern, unsigned char *mask, unsigned long length);

PIMAGE_SECTION_HEADER GetImageSectionHeaders(HMODULE hModule, WORD *count);
PIMAGE_SECTION_HEADER GetImageSectionHeader(HMODULE hModule, unsigned char name[8]);

void	jAPI jBindNative(void *routine, char *name, char *prototype);
void	jAddNative(void *routine, char *name, char *prototype);
jString jAPI jStrMap(char *str);
char*	jAPI jStrGet(jString strid);
*/
// - Andy Scott aka xttocs


#include <windows.h>
#include <stdio.h>

#define jNATIVE	__stdcall
#define jAPI	__msfastcall

#define FloatAsInt(f) (*(long*)&f)
#define IntAsFloat(i) (*(float*)&i)

typedef long jString;
typedef long jInt;
typedef long jReal;

typedef void	(jAPI *jpAddNative)(void *routine, char *name, char *prototype);
typedef jString (jAPI *jpStrMap)	(char *str);
typedef char *	(jAPI *jpStrGet)	(jString strid);

jpAddNative		jAddNative;
jpStrMap		jStrMap;
jpStrGet		jStrGet;

#pragma warning ( disable : 4996 )


jString jNATIVE test(jString js, char *fnname)
{
	char *s;
	s = jStrGet(js);
	s[0] = 'A';
	return jStrMap(s);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);

		HMODULE hjApi = GetModuleHandle("japi.dll");

		jAddNative	= (jpAddNative)GetProcAddress(hjApi, "jAddNative");
		jStrMap		= (jpStrMap)*GetProcAddress(hjApi, "jStrMap");
		jStrGet		= (jpStrGet)*GetProcAddress(hjApi, "jStrGet");

		jAddNative(test, "test", "(S)S");
	}
    return TRUE;
}
