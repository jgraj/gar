struct Thread {
	struct Arg {
		void (*func)(void*);
		void* arg;
	};

#ifdef CBS_WIN32
	MAYBE_AS(HANDLE, Win32::Handle) handle;
#endif
#ifdef CTK_LINUX
	pthread_t id;
#endif
	bool exists = false;

#ifdef CBS_WIN32
	static MAYBE_AS(DWORD, Win32::DWord) __stdcall bootstrap(MAYBE_AS(LPVOID, void*) param);
#endif
#ifdef CTK_LINUX
	static void* bootstrap(void* param);
#endif

	template <typename Type> void create(this auto& self, void (*func)(Type*), Type* arg);
	void join(this Thread& self);
	bool try_join(this Thread& self);
	void detach(this Thread& self);
};

#ifdef CBS_WIN32

template <typename Type>
void Thread::create(this auto& self, void (*func)(Type*), Type* arg) {
	self.exists = true;
	Thread::Arg* thread_arg = alloc<Thread::Arg>(Thread::Arg((void (*)(void*))func, (void*)arg));
	Thread thread;
	self.handle = Win32::CreateThreadSimple((void*)bootstrap, thread_arg);
	if (self.handle == nullptr) {
		self.exists = false;
	}
}

#endif

#ifdef CTK_LINUX

template <typename Type>
void Thread::create(this auto& self, void (*func)(Type*), Type* arg) {
	self.exists = true;
	Thread::Arg* thread_arg = alloc<Thread::Arg>(Thread::Arg((void (*)(void*))func, (void*)arg));
	int pthread_create_ret = ::pthread_create(&self.id, nullptr, bootstrap, thread_arg);
	if (pthread_create_ret != 0) {
		self.exists = false;
	}
}

#endif