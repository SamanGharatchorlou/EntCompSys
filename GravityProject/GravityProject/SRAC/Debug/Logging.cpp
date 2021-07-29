#include "pch.h"
#include "Logging.h"

#if DEBUG_MODE
static constexpr PriorityLevel LogLevel = PriorityLevel::Log;
#else
static constexpr PriorityLevel LogLevel = PriorityLevel::Log;
#endif

void DebugPrint(int priority, const char* format, ...)
{
#if ENABLE_LOGGING
	if (priority <= LogLevel)
	{
		va_list arg;

		va_start(arg, format);
		vfprintf(stdout, format, arg);
		va_end(arg);
	}
#endif
}


void DebugAssert(int lineNumber, const char* functionName, bool condition, const char* format, ...)
{
	if (!condition)
	{
		printf("ASSERT FAILED: %s::%d - ", functionName, lineNumber);

		va_list arg;

		va_start(arg, format);
		vfprintf(stdout, format, arg);
		va_end(arg);

		// pause the code
		int a; 
		scanf_s("%d", &a);
	}
}


void Unimplemented(int lineNumber, const char* functionName, int priority, const char* format, ...)
{
	if (priority <= LogLevel)
	{
		printf("UNIMPLEMENTED fucntion: %s::%d - ", functionName, lineNumber);

		va_list arg;

		va_start(arg, format);
		vfprintf(stdout, format, arg);
		va_end(arg);
	}
}