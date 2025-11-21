struct Signal {
#ifdef CBS_WIN32
	MAYBE_AS(HANDLE, Win32::Handle) event;
#endif
#ifdef CBS_LINUX
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	bool flag;
#endif

	void create(this Signal& self);
	void destroy(this Signal& self);
	void trigger(this Signal& self);
	void wait(this Signal& self);
	bool try_wait(this Signal& self);
	void reset(this Signal& self);
};