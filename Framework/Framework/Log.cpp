#include "pch.h"

#include <clocale>
#include <time.h>

#include "Log.hpp"

namespace FRMWRK {
	#define LOG_FILE "LogFile.log"
	// Макрос используется для более удобного получения даты и времени при логгировании
	#define __FRMWRK_INIT_DATEANDTIME__  char time[0x9]; \
										 _strtime_s(time, 0x9); \
										 char date[0x9];  \
										 _strdate_s(date, 0x9);

	Log* Log::m_Instance = nullptr;

	Log::Log(void){
		if (m_Instance == nullptr) {
			m_File     = nullptr;
			m_Instance = this;
			m_Init();
		} else {
			ERR("Log already exists!");
		}
	}

	Log::~Log(void) {
		m_Close();
		m_Instance = nullptr;
	}

	void Log::m_Init(void) {
		setlocale(LC_ALL, "rus");

		if (fopen_s(&m_File, LOG_FILE, "w") == 0x0) {
			__FRMWRK_INIT_DATEANDTIME__

			fprintf(m_File, "Log created [%s %s]\n\n\n\n", date, time);
		} else {
			printf("Error by creating a logger!\n");
			m_File = nullptr;
		}
	}

	void Log::m_Close(void) {
		if (m_File == nullptr) {
			return;
		}

		__FRMWRK_INIT_DATEANDTIME__

		fprintf(m_File, "\n\n\nLog ended [%s %s]", date, time);
		fclose(m_File);
	}

	void Log::m_Log(LOG_LEVEL level, const char* msg) {
		__FRMWRK_INIT_DATEANDTIME__

		switch (level) {
			case LOG_LEVEL::TRACE:
				fprintf(m_File, "[TRACE]-[%s %s]: %s\n", date, time, msg);
				break;
			case LOG_LEVEL::DEBUG:
#ifdef DEBUG
				fprintf(m_File, "[DEBUG]-[%s %s]: %s\n", date, time, msg);
#endif // DEBUG
				break;       
			case LOG_LEVEL::INFO:
				fprintf(m_File, "[INFO]-[%s %s]: %s\n", date, time, msg);
				break;
			case LOG_LEVEL::WARN:
				fprintf(m_File, "[WARNING]-[%s %s]: %s\n", date, time, msg);
				break;
			case LOG_LEVEL::ERR:
				fprintf(m_File, "\n[ERROR]-[%s %s]: %s\n\n", date, time, msg);
				break;
			case LOG_LEVEL::FATAL:
				fprintf(m_File, "\n[FATAL]-[%s %s]: %s\n\n", date, time, msg);
		}
	}

	Log* Log::Get(void) {
		return m_Instance;
	}

	void Log::Write(LOG_LEVEL level, const char* msg) {
		this->m_Log(level, msg);
	}
};
