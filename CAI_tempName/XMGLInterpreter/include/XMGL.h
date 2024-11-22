#pragma once
#ifdef LIB
	#define DLLAPI __declspec(dllexport)
#else
	#define DLLAPI __declspec(dllimport)
#endif // LIB
