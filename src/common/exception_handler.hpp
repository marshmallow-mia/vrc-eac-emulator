#pragma once

#define CRASHLOG_NO_WINDOWS_H
#include <crashlog/crashlog.hpp>
#include <crashlog/address.hpp>
#include <crashlog/exception.hpp>
#include <winuser.h>

#include <sstream>

class exception_handler {
	static LONG WINAPI TopLevelExceptionFilter(struct _EXCEPTION_POINTERS *ExceptionInfo) {
		auto info = crashlog::parse(ExceptionInfo);
		std::ostringstream stream;
		
		stream << "========= Exception Info ==========" << std::endl;
		crashlog::ExceptionMetadata metadata = info.exceptionMetadata;
		stream << "Exception At: " << crashlog::addressToString(metadata.address) << std::endl;
		stream << "Exception Code: " << std::hex << metadata.exceptionCode << " (" << metadata.exceptionName << ")" << std::endl;
		for (const auto& [key, value] : metadata.additionalInfo) {
			std::string valString = std::visit([](auto&& arg) -> std::string {
				std::ostringstream oss;
				oss << arg;
				return oss.str();
			}, value);
			stream << "  " << key << ": " << valString << std::endl;
		}
		
		stream << "========= Stack Trace ===========" << std::endl;
		crashlog::StackTrace stackTrace = info.stacktrace;
		for (const auto& frame : stackTrace) {
			stream << crashlog::addressToString(frame) << std::endl;
		}
		
		stream << "=========== Registers ================" << std::endl;
		for (const auto& [regName, regValue] : info.registers) {
			stream << regName << ": " << std::hex << regValue << std::endl;
		}

		printf("%s\n", stream.str().c_str());
		MessageBoxA(nullptr, stream.str().c_str(), "Crashed!", MB_OK | MB_ICONERROR);

		return 0;
	}

public:
	static void init() {
		crashlog::initialize();
		SetUnhandledExceptionFilter(&TopLevelExceptionFilter);
	}
};
