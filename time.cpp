#ifdef CBS_WIN32
u64 Time::get_unix_time(){
	const i64 UNIX_TIME_START = 0x019DB1DED53E8000;
	const i64 TICKS_PER_SECOND = 10000000;
	FILETIME ft;
	::GetSystemTimeAsFileTime(&ft);
	LARGE_INTEGER li;
	li.LowPart = ft.dwLowDateTime;
	li.HighPart = (i32)ft.dwHighDateTime;
	return (u64)((li.QuadPart - UNIX_TIME_START) / TICKS_PER_SECOND);
}

void Time::create(this Time& self) {
	::QueryPerformanceCounter((LARGE_INTEGER*)&self.start_counter);
	::QueryPerformanceFrequency((LARGE_INTEGER*)&self.frequency);
	self.last = self.get();
	self.delta = 0.0;
}

f64 Time::get(this const Time& self) {
	LARGE_INTEGER counter;
	::QueryPerformanceCounter(&counter);
	return (f64)(counter.QuadPart - self.start_counter.QuadPart) / (f64)self.frequency.QuadPart;
}
#endif

void Time::update(this Time& self) {
	f64 new_time = self.get();
	self.delta = new_time - self.last;
	self.last = new_time;
}

#ifdef CBS_LINUX
void Time::create(this Time& self) {
	self.last = self.get();
	self.delta = 0.0;
}

f64 Time::get(this const Time& self) {
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	return tv.tv_sec + tv.tv_usec / 1000000.0;
}
#endif