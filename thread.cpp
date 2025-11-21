#ifdef CBS_WIN32

DWORD __stdcall Thread::bootstrap(LPVOID param) {
	Thread::Arg* thread_arg = (Thread::Arg*)param;
	thread_arg->func(thread_arg->arg);
	mem_free(thread_arg);
	return 0;
}

void Thread::join(this Thread& self) {
	if (self.exists == false) {
		return;
	}
	if (::WaitForSingleObject(self.handle, INFINITE) != WAIT_OBJECT_0) {
		ctk::panic("::WaitForSingleObject failed");
	}
	::CloseHandle(self.handle);
	self.exists = false;
}

bool Thread::try_join(this Thread& self) {
	if (self.exists == false) {
		return true;
	}
	DWORD wait_value = ::WaitForSingleObject(self.handle, 0);
	if (wait_value == WAIT_FAILED) {
		ctk::panic("::WaitForSingleObject failed");
	}
	if (wait_value == WAIT_OBJECT_0) {
		self.exists = false;
		return true;
	}
	return false;
}

void Thread::detach(this Thread& self) {
	::CloseHandle(self.handle);
}

#endif

#ifdef CBS_LINUX

void* Thread::bootstrap(void* param) {
	Thread::Arg* thread_arg = (Thread::Arg*)param;
	thread_arg->func(thread_arg->arg);
	mem_free(thread_arg);
	return nullptr;
}

void Thread::join(this Thread& self) {
	if (self.exists == false) {
		return;
	}
	::pthread_join(self.id, nullptr);
	self.exists = false;
}

bool Thread::try_join(this Thread& self) {
	if (self.exists == false) {
		return true;
	}
	int join_value = ::pthread_tryjoin_np(self.id, nullptr);
	if (join_value == 0) {
		self.exists = false;
		return true;
	}
	return false;
}

void Thread::detach(this Thread& self) {
	::pthread_detach(self.id);
}

#endif