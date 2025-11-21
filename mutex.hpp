struct Mutex {
#ifdef CBS_WIN32
	Win32::CriticalSection critical_section;
#endif
#ifdef CBS_LINUX
	pthread_mutex_t pthread_mutex;
#endif

	void create(this Mutex& self);
	void destroy(this Mutex& self);
	void lock(this Mutex& self);
	bool try_lock(this Mutex& self);
	void unlock(this Mutex& self);
};