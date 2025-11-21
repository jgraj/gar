struct Time {
#ifdef CBS_WIN32
	MAYBE_AS(LARGE_INTEGER, Win32::LargeInteger) start_counter;
	MAYBE_AS(LARGE_INTEGER, Win32::LargeInteger) frequency;
#endif
	f64 last;
	f64 delta;

	static u64 get_unix_time();

	void create(this Time& self);
	void update(this Time& self);
	f64 get(this const Time& self);
};