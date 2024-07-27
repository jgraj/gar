/// version: 1

#ifndef GAR_PANIC
#define GAR_PANIC printf
#endif

template <typename T>
struct gar;

template <typename T>
struct ar {
	T* buf;
	size_t len;

	ar(): buf(nullptr), len(0) {}

	T& operator [] (size_t index) {
		return this->buf[index];
	}

	static ar<T> alloc(size_t len) {
		ar<T> array;
		array.len = len;
		array.buf = (T*)malloc(sizeof(T) * len);
		if (array.buf == nullptr) {
			GAR_PANIC("%s: malloc failed (len:%zu)", __PRETTY_FUNCTION__, len);
		}
		return array;
	}

	void free() {
		::free(this->buf);
		this->buf = nullptr;
	}

	void clear() {
		this->len = 0;
	}

	gar<T> to_gar();

	ar<T> resize_clone(size_t new_len) {
		ar<T> new_array = alloc(new_len);
		if (this->len != 0) {
			memcpy(new_array.buf, this->buf, sizeof(T) * this->len);
		}
		return new_array;
	}
};

template <typename T>
struct gar {
	T* buf;
	size_t len;
	size_t cap;

	gar(): buf(nullptr), len(0), cap(0) {}

	T& operator [] (size_t index) {
		return this->buf[index];
	}

	static gar<T> alloc(size_t cap) {
		gar<T> array;
		array.len = 0;
		array.cap = cap;
		array.buf = (T*)std::malloc(sizeof(T) * cap);
		if (array.buf == nullptr) {
			GAR_PANIC("%s: malloc failed (cap:%zu)", __PRETTY_FUNCTION__, cap);
		}
		return array;
	}

	void free() {
		std::free(this->buf);
		this->buf = nullptr;
	}

	void clear() {
		len = 0;
	}

	ar<T> to_ar() {
		ar<T> array;
		array.buf = this->buf;
		array.len = this->len;
		return array;
	}

	gar<T> clone() {
		gar<T> new_array = alloc(this->cap);
		new_array.len = this->len;
		memcpy(new_array.buf, this->buf, sizeof(T) * this->len);
		return new_array;
	}

	void grow() {
		this->cap *= 2;
		this->buf = (T*)std::realloc(this->buf, sizeof(T) * this->cap);
		if (this->buf == nullptr) {
			GAR_PANIC("%s: realloc failed (cap:%zu)", __PRETTY_FUNCTION__, this->cap);
		}
	}

	void push(T value) {
		if (this->len == this->cap) {
			this->grow();
		}
		this->buf[this->len] = value;
		this->len += 1;
	}

	void push_many(T* src_ptr, size_t count) {
		size_t old_len = len;
		this->len += count;
		while (this->len >= this->cap) {
			this->grow();
		}
		std::memcpy(&this->buf[old_len], src_ptr, sizeof(T) * count);
	}

	T remove_at(size_t index) {
		if (index < 0 || index >= this->len) {
			GAR_PANIC("%s: index %zu is out of bounds", __PRETTY_FUNCTION__, index);
		}
		T value = this->buf[index];
		this->len -= 1;
		std::memmove(&this->buf[index], &this->buf[index + 1], sizeof(T) * this->len);
		return value;
	}

	void remove_many(size_t index, size_t count) {
		std::memmove(&this->buf[index], &this->buf[index + count], sizeof(T) * (this->len - index - count));
		this->len -= count;
	}
};

template <typename T>
gar<T> ar<T>::to_gar() {
	gar<T> array;
	array.buf = this->buf;
	array.len = this->len;
	array.cap = this->cap;
	return array;
}