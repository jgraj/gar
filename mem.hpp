#ifdef CTK_MEM_CHECK
ctk::Mutex mem_check_mutex;
size_t alloc_counter = 0;
size_t free_counter = 0;

void init_alloc_count() {
	mem_check_mutex.create();
}

void print_alloc_count() {
	std::printf("alloc: %zu\nfree: %zu\n", alloc_counter, free_counter);
	if (free_counter > alloc_counter) {
		std::printf("invalid diff: -%zu\n", free_counter - alloc_counter);
	} else {
		std::printf("diff: %zu\n", alloc_counter - free_counter);
	}
}

void deinit_alloc_count() {
	mem_check_mutex.destroy();
}
#endif

void* mem_alloc_no_count(size_t size);
void* mem_realloc_no_count(void* ptr, size_t size);
void mem_free_no_count(void* ptr);
void* mem_alloc(size_t size);
void* mem_realloc(void* ptr, size_t size);
void mem_free(void* ptr);

#if CBS_MOD == 0

void* mem_alloc(size_t size) {
	void* ptr = mem_alloc_no_count(size);
#ifdef CTK_MEM_CHECK
	if (size > 0) {
		mem_check_mutex.lock();
		alloc_counter += 1;
		mem_check_mutex.unlock();
	}
#endif
	return ptr;
}

void* mem_realloc(void* ptr, size_t size) {
	return mem_realloc_no_count(ptr, size);
}

void mem_free(void* ptr) {
	mem_free_no_count(ptr);
#ifdef CTK_MEM_CHECK
	if (ptr != nullptr) {
		mem_check_mutex.lock();
		free_counter += 1;
		mem_check_mutex.unlock();
	}
#endif
}

#endif

template <typename Type> Type* alloc_space(size_t count) {
	if (count == 0) {
		ctk::panic("ctk::alloc_space failed: count is zero");
	}
	Type* ptr = (Type*)mem_alloc(sizeof(Type) * count);
	if (ptr == nullptr) {
		ctk::panic("ctk::alloc_space failed: ctk::alloc_space failed");
	}
	return ptr;
}

template <typename Type> Type* alloc(Type value) {
	Type* ptr = alloc_space<Type>(1);
	*ptr = value;
	return ptr;
}

template <typename Type> Type* alloc_many(const void* value, size_t count) {
	Type* ptr = alloc_space<Type>(count);
	std::memcpy(ptr, value, sizeof(Type) * count);
	return ptr;
}

template <typename Type> void swap(Type* a, Type* b) {
	Type temp = *a;
	*a = *b;
	*b = temp;
}