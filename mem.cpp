void* mem_alloc_no_count(size_t size) {
	return std::malloc(size);
}

void* mem_realloc_no_count(void* ptr, size_t size) {
	return std::realloc(ptr, size);
}

void mem_free_no_count(void* ptr) {
	std::free(ptr);
}