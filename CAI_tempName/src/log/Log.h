#pragma once
#include<CLog.h>
class Log
{
public:
	static void Init();
	inline static std::shared_ptr<CL::CLog>& GetLoger() { return loger; }
private:
	static std::shared_ptr<CL::CLog> loger;
};


#define LogError(...)		Log::GetLoger()->Log(CL::CLog::Error,__VA_ARGS__)
#define LogNotice(...)		Log::GetLoger()->Log(CL::CLog::Notice,__VA_ARGS__)
#define LogNormal(...)		Log::GetLoger()->Log(CL::CLog::Normal,__VA_ARGS__)
#define LogWarning(...)	Log::GetLoger()->Log(CL::CLog::Warning,__VA_ARGS__)