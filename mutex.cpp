#ifdef CBS_WIN32
void Mutex::create(this Mutex& self) {
	::InitializeCriticalSection((CRITICAL_SECTION*)&self.critical_section);
}

void Mutex::destroy(this Mutex& self) {
	::DeleteCriticalSection((CRITICAL_SECTION*)&self.critical_section);
}

void Mutex::lock(this Mutex& self) {
	::EnterCriticalSection((CRITICAL_SECTION*)&self.critical_section);
}

bool Mutex::try_lock(this Mutex& self) {
	return ::TryEnterCriticalSection((CRITICAL_SECTION*)&self.critical_section) != FALSE;
}

void Mutex::unlock(this Mutex& self) {
	::LeaveCriticalSection((CRITICAL_SECTION*)&self.critical_section);
}
#endif

#ifdef CBS_LINUX
void Mutex::create(this Mutex& self) {
	::pthread_mutex_init(&self.pthread_mutex, nullptr);
}

void Mutex::destroy(this Mutex& self) {
	::pthread_mutex_destroy(&self.pthread_mutex);
}

void Mutex::lock(this Mutex& self) {
	::pthread_mutex_lock(&self.pthread_mutex);
}

bool Mutex::try_lock(this Mutex& self) {
	return ::pthread_mutex_trylock(&self.pthread_mutex) == 0;
}

void Mutex::unlock(this Mutex& self) {
	::pthread_mutex_unlock(&self.pthread_mutex);
}
#endif