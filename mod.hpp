#pragma once

#ifdef __linux__
#define CBS_LINUX
#endif

// Global switch (0 = use void/void*, 1 = use real types)
#ifndef USE_REAL_TYPES
#define USE_REAL_TYPES 0
#endif

// helpers
#define _CAT_(a,b) a##b
#define _CAT(a,b) _CAT_(a,b)

// base chooser: pick T or Alt based on the global switch
#define MAYBE_AS(T, Alt) _CAT(MAYBE_AS_, USE_REAL_TYPES)(T, Alt)
#define MAYBE_AS_0(T, Alt) Alt
#define MAYBE_AS_1(T, Alt) T

#define _GNU_SOURCE 1
#include <cstring> // memcpy, memcmp, memmove, strcmp, strlen, memset
#include <cstdio> // printf, sprintf
#include <cstdint>
#include <type_traits>

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
	template <typename T> struct ar;
	template <typename T> struct gar;

	constexpr f64 pi = 3.14159265358979323846;
	constexpr f64 deg2rad = pi / 180.0;
	constexpr f64 rad2deg = 180.0 / pi;
	constexpr size_t vls1_max = 0x7F;       // 127
	constexpr size_t vls2_max = 0x3FFF;     // 16,383
	constexpr size_t vls3_max = 0x1FFFFF;   // 2,097,151
	constexpr size_t vls4_max = 0x1FFFFFFF; // 536,870,911

	void log(const char* const format, ...);
	void warn(const char* const format, ...);
	void panic(const char* const format, ...);
	void sleep(u32 ms);
	void pause();
	void exit(int status);
	void open_url(const char* url);
	bool astr_nocase_cmp(const void* s1, const void* s2, size_t size);
	ar<u8> alloc_format(const char* format, ...);
	ar<u8> load_file(const char* path);
	bool str_to_u64(ar<u8> str, u64* out);
	ar<u8> u64_to_str(u64 value);
}

#define AR_STR(str) (ctk::ar<const u8>(((const u8*)str), std::strlen(str)))

namespace ctk {
#ifdef CBS_WIN32
	#include "win32.hpp"
#endif
	#include "mutex.hpp"
	#include "mem.hpp"
	#include "exception.hpp"
	#include "ar.hpp"
	#include "ar.cpp"
	#include "gar.hpp"
	#include "gar.cpp"
	#include "buf_save.hpp"
	#include "buf_save.cpp"
	#include "buf_load.hpp"
	#include "buf_load.cpp"
	#include "time.hpp"
	#include "mgar.hpp"
	#include "mgar.cpp"
	#include "thread.hpp"
	#include "signal.hpp"
	#include "directory.hpp"
	#include "random.hpp"
	#include "file.hpp"
	#include "file_save.hpp"
	#include "file_load.hpp"
	#include "types/size.hpp"
	#include "types/f64.hpp"
	#include "types/f32.hpp"
	#include "types/i32.hpp"
	#include "types/u64.hpp"
	#include "types/i64.hpp"
	#include "vector/v2/v2.hpp"
	#include "vector/v3/v3.hpp"
	#include "vector/v4/v4.hpp"
	#include "matrix/m3.hpp"
	#include "matrix/m4.hpp"
	#include "smooth.hpp"
	#include "smooth.cpp"
	#include "color.hpp"
	#include "utf8.hpp"
}