#ifdef CBS_WIN32
void Signal::create(this Signal& self) {
	self.event = ::CreateEvent(nullptr, TRUE, FALSE, nullptr);
	if (self.event == nullptr) {
		ctk::panic("::CreateEvent failed");
	}
}

void Signal::destroy(this Signal& self) {
	::CloseHandle(self.event);
}

void Signal::trigger(this Signal& self) {
	::SetEvent(self.event);
}

void Signal::wait(this Signal& self) {
	::WaitForSingleObject(self.event, INFINITE);
}

bool Signal::try_wait(this Signal& self) {
	DWORD result = ::WaitForSingleObject(self.event, 0);
	return result == WAIT_OBJECT_0;
}

void Signal::reset(this Signal& self) {
	::ResetEvent(self.event);
}

#endif
#ifdef CBS_LINUX
void Signal::create(this Signal& self) {
	if (::pthread_mutex_init(&self.mutex, nullptr) != 0) {
		ctk::panic("::pthread_mutex_init failed");
	}
	if (::pthread_cond_init(&self.cond, nullptr) != 0) {
		ctk::panic("::pthread_cond_init failed");
	}
	self.flag = false;
}

void Signal::destroy(this Signal& self) {
	::pthread_mutex_destroy(&self.mutex);
	::pthread_cond_destroy(&self.cond);
}

void Signal::trigger(this Signal& self) {
	::pthread_mutex_lock(&self.mutex);
	self.flag = true;
	::pthread_cond_broadcast(&self.cond);
	::pthread_mutex_unlock(&self.mutex);
}

void Signal::wait(this Signal& self) {
	::pthread_mutex_lock(&self.mutex);
	while (self.flag == false) {
		::pthread_cond_wait(&self.cond, &self.mutex);
	}
	::pthread_mutex_unlock(&self.mutex);
}

bool Signal::try_wait(this Signal& self) {
	::pthread_mutex_lock(&self.mutex);
	bool triggered = self.flag;
	::pthread_mutex_unlock(&self.mutex);
	return triggered;
}

void Signal::reset(this Signal& self) {
	::pthread_mutex_lock(&self.mutex);
	self.flag = false;
	::pthread_mutex_unlock(&self.mutex);
}

#endif