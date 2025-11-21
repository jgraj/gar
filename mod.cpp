#include <cmath>
#include <cstdarg>
#include <cstdlib>
#include <climits>
#include <cctype>

#ifdef CBS_WIN32
#define WINVER _WIN32_WINNT_WIN10
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <synchapi.h>
#include <profileapi.h>
#include <processthreadsapi.h>
#include <bcrypt.h>
#include <shellapi.h>
#include <dbghelp.h>
#include <mmeapi.h>
#endif

#ifdef CBS_LINUX
#include <pthread.h>
#include <dirent.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/random.h>
#include <errno.h>
#endif

#define USE_REAL_TYPES 1
#include "mod.hpp"

namespace ctk {
#ifdef CBS_WIN32
	#include "win32.cpp"
#endif
	#include "mutex.cpp"
	#include "mem.cpp"
	#include "exception.cpp"
	#include "time.cpp"
	#include "thread.cpp"
	#include "signal.cpp"
	#include "directory.cpp"
	#include "random.cpp"
	#include "file.cpp"
	#include "file_save.cpp"
	#include "file_load.cpp"
	#include "types/size.cpp"
	#include "types/f64.cpp"
	#include "types/f32.cpp"
	#include "types/i32.cpp"
	#include "types/u64.cpp"
	#include "types/i64.cpp"
	#include "vector/v2/v2.cpp"
	#include "vector/v3/v3.cpp"
	#include "vector/v4/v4.cpp"
	#include "matrix/m3.cpp"
	#include "matrix/m4.cpp"
	#include "color.cpp"
	#include "utf8.cpp"

	void log(const char* const format, ...) {
		SYSTEMTIME st;
		::GetSystemTime(&st);
		va_list args;
		va_start(args, format);
		char* string;
		vasprintf(&string, format, args);
		va_end(args);
		std::printf("[%02d:%02d:%02d] %s\n", st.wHour, st.wMinute, st.wSecond, string);
		std::free(string);
	}

	void warn(const char* const format, ...) {
		va_list args;
		va_start(args, format);
		char* string;
		vasprintf(&string, format, args);
		va_end(args);
		std::printf("WARNING: %s\n", string);
		::MessageBoxA(nullptr, string, "Warning", MB_ICONWARNING | MB_SYSTEMMODAL);
		std::free(string);
	}

	void panic(const char* const format, ...) {
		va_list args;
		va_start(args, format);
		char* string;
		vasprintf(&string, format, args);
		va_end(args);
		std::printf("PANIC: %s\n", string);
#ifdef CBS_DEBUG
		__debugbreak();
#else
		::MessageBoxA(nullptr, string, "Panic", MB_ICONERROR | MB_SYSTEMMODAL);
#endif
		std::free(string);
		ctk::exit(1);
	}

	void sleep(u32 ms) {
#ifdef CBS_WIN32
		::Sleep(ms);
#endif
#ifdef CBS_LINUX
		::usleep(ms * 1000);
#endif
	}

	void pause() {
#ifdef CBS_WIN32
		::Sleep(INFINITE);
#endif
#ifdef CBS_LINUX
		::pause();
#endif
	}

	void exit(i32 status) {
#ifdef CBS_WIN32
		::ExitProcess((UINT)status);
#endif
#ifdef CBS_LINUX
		::_exit(status);
#endif
	}

	void open_url(const char* url) {
#ifdef CBS_WIN32
		::ShellExecuteA(nullptr, "open", url, nullptr, nullptr, SW_SHOWNORMAL);
#endif
	}

	bool astr_nocase_cmp(const void* s1, const void* s2, size_t size) {
		for (size_t a = 0; a < size; ++a) {
			char c1 = ((char*)s1)[a] | 0x20;
			char c2 = ((char*)s2)[a] | 0x20;
			if (c1 != c2) {
				return false;
			}
		}
		return true;
	}

	ar<u8> alloc_format(const char* format, ...) {
		va_list args;
		va_start(args, format);
		char* string;
		int len = vasprintf(&string, format, args);
		if (len == -1) {
			ctk::panic("ctk::alloc_format failed: vasprintf failed");
		}
		va_end(args);
		#ifdef CTK_MEM_CHECK
		alloc_counter += 1;
		#endif
		return ar<u8>((u8*)string, (size_t)len);
	}

	ar<u8> load_file(const char* path) {
		FILE* file = std::fopen(path, "rb");
		if (file == nullptr) {
			ctk::panic("ctk::load_file failed: fopen failed");
		}
		std::fseek(file, 0, SEEK_END);
		long file_size = std::ftell(file);
		if (file_size < 0) {
			ctk::panic("ctk::load_file failed: std::ftell failed");
		}
		std::rewind(file);
		ar<u8> data;
		data.create((size_t)file_size);
		size_t bytes_read = std::fread(data.buf, 1, (size_t)file_size, file);
		if (bytes_read != (size_t)file_size) {
			ctk::panic("ctk::load_file failed: std::fread failed");
		}
		std::fclose(file);
		return data;
	}

	bool str_to_u64(ar<u8> str, u64* out) {
		u64 value = 0;
		size_t a = 0;
		while (a < str.len && isspace(str[a])) {
			a += 1;
		}
		if (a >= str.len) {
			return false;
		}
		for (; a < str.len; ++a) {
			if (!isdigit(str[a])) {
				return false;
			}
			u8 digit = str[a] - '0';
			if (value > (UINT64_MAX / 10) || (value == (UINT64_MAX / 10) && digit > (UINT64_MAX % 10))) {
				return false;
			}
			value = value * 10 + digit;
		}
		*out = value;
		return true;
	}

	ar<u8> u64_to_str(u64 value) {
		if (value == 0) {
			ar<u8> str;
			str.create(1);
			str[0] = '0';
			return str;
		}
		size_t str_len = 0;
		for (u64 a = value; a != 0; a /= 10) {
			str_len += 1;
		}
		ar<u8> str;
		str.create(str_len);
		size_t pos = str_len;
		while (value != 0) {
			pos -= 1;
			str[pos] = '0' + (u8)(value % 10);
			value /= 10;
		}
		return str;
	}
}