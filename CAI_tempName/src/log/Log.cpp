#include "caipch.h"
#include "Log.h"

std::shared_ptr<CL::CLog> Log::loger;

void Log::Init()
{
	loger = std::make_shared<CL::CLog>();
	loger->SetSavePath("../x64/bin/Debug/record.log");
	loger->Log(CL::CLog::Notice, "Log init complete");
}
