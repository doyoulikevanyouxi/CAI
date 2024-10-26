#pragma once
#ifdef CLOG_PLATFORM_WINDOWS
	#ifdef CLOG_DLL
		#define	CLOG_API __declspec(dllexport)
	#else 
		#define CLOG_API __declspec(dllimport)
	#endif // DEMO_DLL 
#else
#error only support Windows
#endif
