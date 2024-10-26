#pragma once
#include<CLog.h>
namespace CAITF {
	class Log
	{
	public:
		static void init();
		inline static std::shared_ptr<CL::CLog>& GetLoger() { return loger; }
	private:
		static std::shared_ptr<CL::CLog> loger;
	};
}


#define LogError(...)		CAITF::Log::GetLoger()->Log(CL::CLog::Error,__VA_ARGS__)
#define LogNotice(...)		CAITF::Log::GetLoger()->Log(CL::CLog::Notice,__VA_ARGS__)
#define LogNormal(...)		CAITF::Log::GetLoger()->Log(CL::CLog::Normal,__VA_ARGS__)
#define LogWarning(...)	CAITF::Log::GetLoger()->Log(CL::CLog::Warning,__VA_ARGS__)