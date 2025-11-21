#ifdef CBS_WIN32

LONG WINAPI exception_handler(EXCEPTION_POINTERS* exception_info) {
	HANDLE file = ::CreateFileW(L"crash.dmp", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (file != INVALID_HANDLE_VALUE) {
		MINIDUMP_EXCEPTION_INFORMATION mdei;
		mdei.ThreadId = ::GetCurrentThreadId();
		mdei.ExceptionPointers = exception_info;
		mdei.ClientPointers = FALSE;
		::MiniDumpWriteDump(::GetCurrentProcess(), ::GetCurrentProcessId(), file, MiniDumpNormal, (exception_info != 0) ? &mdei : 0, nullptr, nullptr);
		::CloseHandle(file);
	}
	switch (exception_info->ExceptionRecord->ExceptionCode) {
		case EXCEPTION_ACCESS_VIOLATION: {
			ctk::panic("Access violation at address 0x%p\n", exception_info->ExceptionRecord->ExceptionAddress);
			break;
		}
		case EXCEPTION_INT_DIVIDE_BY_ZERO: {
			ctk::panic("Integer divide by zero at address 0x%p\n", exception_info->ExceptionRecord->ExceptionAddress);
			break;
		}
		case EXCEPTION_STACK_OVERFLOW: {
			ctk::panic("Stack overflow at address 0x%p\n", exception_info->ExceptionRecord->ExceptionAddress);
			break;
		}
		default: {
			ctk::panic("Exception code: 0x%08lX at address 0x%p\n", exception_info->ExceptionRecord->ExceptionCode, exception_info->ExceptionRecord->ExceptionAddress);
			break;
		}
	}
	return EXCEPTION_EXECUTE_HANDLER;
}

void use_exception_handler() {
	::SetUnhandledExceptionFilter(exception_handler);
}

#endif