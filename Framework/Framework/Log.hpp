#pragma once

#include <string>
//#include <array>

namespace FRMWRK {
	// ������ ������������ ���������� ��� ��������� ������� ����������� ������
	enum class LOG_LEVEL {
		TRACE = 0x1,
		DEBUG = 0x2,
		INFO  = 0x3,
		WARN  = 0x4,
		ERR   = 0x5,
		FATAL = 0x6
	};

	// �������� ��� �������. � �������� ������������, �� � ������ ������ ��� ������ ��� ��������
	/*std::array<std::string, 0x6> Level_Mapping = { "TRACE",
												   "DEBUG",
												   "INFO",
												   "WARNING",
												   "ERROR",
												   "FATAL" };*/

	// ����� Log ������������ ����� ������� ���������� ������. � ������ ������������ ����� 
	//	��������������� ���� ������������ ����������� � ���� ������� � �� ���������������,
	//  �� �� ������ ���������� �� ������ ���������� ����� ������, � ������� ������ ������������, �� ���������� 
	//  ��� ��� �� ��������
	class Log {
	private:
		static Log* m_Instance;
		FILE*       m_File;

		void m_Init(void);
		void m_Close(void);
		// ������ ��� �������� ��������� ���� ������, � �� ���������� ����� ����������
		void m_Log(LOG_LEVEL level, const char* msg);
	public:
		Log(void);
		~Log(void);

		// ������� ����������� �����, ����������� �������� ������� ������� �������
		static Log* Get(void);

		void Write(LOG_LEVEL level, const char* msg);
	};

	// �������, ����������� ��� ����� ������ �������� � �������� - ����������� ��
	#define TRACE(msg) Log::Get()->Write(LOG_LEVEL::TRACE, msg);
	#define DEBUG(msg) Log::Get()->Write(LOG_LEVEL::DEBUG, msg);
	#define INFO(msg)  Log::Get()->Write(LOG_LEVEL::INFO,  msg);
	#define WARN(msg)  Log::Get()->Write(LOG_LEVEL::WARN,  msg);
	#define ERR(msg)   Log::Get()->Write(LOG_LEVEL::ERR,   msg);
	#define FATAL(msg) Log::Get()->Write(LOG_LEVEL::FATAL, msg);
};