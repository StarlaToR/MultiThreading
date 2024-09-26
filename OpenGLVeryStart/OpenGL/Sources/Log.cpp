#include <windows.h>
#include <Log.h>

using namespace Core::Debug;

void Log::DebugLog(const char* file, int line, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	Log debugLog;
	debugLog.OpenFile("log.txt");
	debugLog.Print(file);
	debugLog.Print("(%i):", line);
	debugLog.Print(format, args);
	char buffer[100];
	sprintf_s(buffer, "%s(%i):%s\n", file, line, format);
	OutputDebugStringA(buffer);
}

void Log::OpenFile(std::filesystem::path const& filename)
{
	logFile.open(filename);
	if (logFile.fail())
		Print("File can't be opened");
}

void Log::Print(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'i')
			{
				int i = va_arg(args, int);
				std::cout << i;
			}
			else if (*format == 'f')
			{
				float i = va_arg(args, double);
				std::cout << i;
			}
			else if (*format == 'c')
			{
				char i = va_arg(args, char);
				std::cout << static_cast<char>(i);
			}
			else if (*format == 's')
			{
				string i = va_arg(args, string);
				std::cout << static_cast<string>(i);
			}
			else
			{
				std::cout << *format;
			}
		}
		else
		{
			std::cout << *format;
		}
		format++;
	}
	std::cout << '\n';
	va_end(args);
}

Log::~Log()
{
	logFile.close();
}