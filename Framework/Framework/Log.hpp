#pragma once

#include <string>
//#include <array>

namespace FRMWRK {
	// Уровни логгирования необходимы для понимания степени серьёзности ошибки
	enum class LOG_LEVEL {
		TRACE = 0x1,
		DEBUG = 0x2,
		INFO  = 0x3,
		WARN  = 0x4,
		ERR   = 0x5,
		FATAL = 0x6
	};

	// Маппинги для уровней. В логгерах используются, но в данном случае они убраны для простоты
	/*std::array<std::string, 0x6> Level_Mapping = { "TRACE",
												   "DEBUG",
												   "INFO",
												   "WARNING",
												   "ERROR",
												   "FATAL" };*/

	// Класс Log представляет собой простой синхронный логгер. В рамках лабораторных работ 
	//	нецелесообразно было использовать асинхронный в виду наличия в нём многопоточности,
	//  но по своему усмотрению вы можете подключить любой логгер, с которым хотите ознакомиться, на результаты 
	//  лаб это не повлияет
	class Log {
	private:
		static Log* m_Instance;
		FILE*       m_File;

		void m_Init(void);
		void m_Close(void);
		// Логгер для простоты принимает одну строку, а не переменный набор параметров
		void m_Log(LOG_LEVEL level, const char* msg);
	public:
		Log(void);
		~Log(void);

		// Внешний статический метод, позволяющий получить текущий инстанс объекта
		static Log* Get(void);

		void Write(LOG_LEVEL level, const char* msg);
	};

	// Макросы, позволяющие Вам более удобно работать с логгером - используйте их
	#define TRACE(msg) Log::Get()->Write(LOG_LEVEL::TRACE, msg);
	#define DEBUG(msg) Log::Get()->Write(LOG_LEVEL::DEBUG, msg);
	#define INFO(msg)  Log::Get()->Write(LOG_LEVEL::INFO,  msg);
	#define WARN(msg)  Log::Get()->Write(LOG_LEVEL::WARN,  msg);
	#define ERR(msg)   Log::Get()->Write(LOG_LEVEL::ERR,   msg);
	#define FATAL(msg) Log::Get()->Write(LOG_LEVEL::FATAL, msg);
};