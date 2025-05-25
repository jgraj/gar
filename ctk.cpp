#define _GNU_SOURCE 1
#include <cstdlib>
#include <cstdarg>
#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cmath>
#include <cctype>
#include <cstring>
#include <cinttypes>
#include <climits>

#ifdef _WIN32
#define CTK_WIN32
#define WINVER _WIN32_WINNT_WIN10
#include <windows.h>
#include <dbghelp.h>
#include "exception.cpp"
#endif

#ifdef __linux__
#define CTK_LINUX
#include <unistd.h>
#include <pthread.h>
#include <dirent.h>
#include <fcntl.h>
#endif

#ifndef CTK_PANIC
#define CTK_PANIC(...) std::printf(__VA_ARGS__); std::exit(1);
#endif

#define AR_STR(str) (ar<const u8>(((const u8*)str), sizeof(str)))

typedef float f32;
typedef double f64;
typedef uint8_t u8;
typedef int8_t i8;
typedef uint16_t u16;
typedef int16_t i16;
typedef uint32_t u32;
typedef int32_t i32;
typedef uint64_t u64;
typedef int64_t i64;

namespace ctk {
	struct Thread;
	template <typename T> struct ar;
	template <typename T> struct gar;
	struct v2f;
	struct v2i;
	struct v3f;
	struct v3i;
	struct v4f;
	struct v4i;
	struct m3f;
	struct m4f;

	constexpr f64 pi = 3.14159265358979323846;
	constexpr f64 deg2rad = pi / 180.0;
	constexpr f64 rad2deg = 180.0 / pi;

	template <typename T> inline void swap(T* a, T* b);
	template <typename T> inline T* alloc(T value);
	template <typename T> inline T* alloc_many(const void* value, size_t count);
	template <typename T> inline T* alloc_space(size_t count);
	ar<u8> alloc_format(const char* format, ...);
	ar<u8> load_file(const char* path);

	#include "ar.cpp"
	#include "gar.cpp"
	#include "mutex.cpp"
	#include "thread.cpp"
	#include "directory.cpp"
	#include "file.cpp"
	#include "file_save.cpp"
	#include "file_load.cpp"
	#include "types/size.cpp"
	#include "types/f64.cpp"
	#include "types/f32.cpp"
	#include "types/u8.cpp"
	#include "types/i8.cpp"
	#include "types/u16.cpp"
	#include "types/i16.cpp"
	#include "types/u32.cpp"
	#include "types/i32.cpp"
	#include "types/u64.cpp"
	#include "types/i64.cpp"
	#include "vector/v2/v2.cpp"
	#include "vector/v3/v3.cpp"
	#include "vector/v4/v4.cpp"
	#include "matrix/m3.cpp"
	#include "matrix/m4.cpp"

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

	template <typename T> inline void swap(T* a, T* b) {
		T temp = *a;
		*a = *b;
		*b = temp;
	}

	template <typename T> inline T* alloc(T value) {
		T* ptr = alloc_space<T>(1);
		*ptr = value;
		return ptr;
	}

	template <typename T> inline T* alloc_many(const void* value, size_t count) {
		T* ptr = alloc_space<T>(count);
		std::memcpy(ptr, value, sizeof(T) * count);
		return ptr;
	}

	template <typename T> inline T* alloc_space(size_t count) {
		if (count == 0) {
			CTK_PANIC("count is zero");
		}
		T* ptr = (T*)std::malloc(sizeof(T) * count);
		if (ptr == nullptr) {
			CTK_PANIC("alloc_space failed");
		}
		return ptr;
	}

	ar<u8> alloc_format(const char* format, ...) {
		va_list args;
		va_start(args, format);
		char* string;
		int len = vasprintf(&string, format, args);
		if (len == -1) {
			CTK_PANIC("vasprintf failed");
		}
		va_end(args);
		return ar<u8>((u8*)string, len);
	}

	ar<u8> load_file(const char* path) {
		FILE* file = std::fopen(path, "rb");
		if (file == nullptr) {
			CTK_PANIC("fopen failed");
		}
		std::fseek(file, 0, SEEK_END);
		long file_size = std::ftell(file);
		if (file_size < 0) {
			CTK_PANIC("std::ftell failed");
		}
		std::rewind(file);
		ar<u8> data = ar<u8>::create(file_size);
		size_t bytes_read = std::fread(data.buf, 1, file_size, file);
		if (bytes_read != (size_t)file_size) {
			CTK_PANIC("std::fread failed");
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
			ar<u8> str = ar<u8>::create(1);
			str[0] = '0';
			return str;
		}
		size_t str_len = 0;
		for (u64 a = value; a != 0; a /= 10) {
			str_len += 1;
		}
		ar<u8> str = ar<u8>::create(str_len);
		size_t pos = str_len;
		while (value != 0) {
			pos -= 1;
			str[pos] = '0' + (value % 10);
			value /= 10;
		}
		return str;
	}
}