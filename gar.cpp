template <typename T> struct gar {
	T* buf = nullptr;
	size_t len = 0;
	size_t cap = 0;

	static gar<T> create(size_t cap) {
		gar<T> array;
		array.len = 0;
		array.cap = cap;
		if (cap == 0) {
			array.buf = nullptr;
		} else {
			array.buf = (T*)std::malloc(sizeof(T) * cap);
			if (array.buf == nullptr) {
				CTK_PANIC("std::malloc failed (cap:%zu)", cap);
			}
		}
		return array;
	}

	static gar<T> create_auto() {
		return gar<T>::create(8);
	}

	void destroy() {
		std::free(this->buf);
		this->buf = nullptr;
	}

	void bound_check(size_t index) const {
		if (index >= this->len) {
			CTK_PANIC("index %zu is out of bounds (len:%zu)", index, this->len);
		}
	}

	operator gar<const T>() const {
		return gar<const T>{ buf, len, cap };
	}

	const T& operator[] (size_t index) const {
		#ifdef CTK_ABC
			bound_check(index);
		#endif
		return this->buf[index];
	}

	template <typename U = T> std::enable_if_t<!std::is_const_v<U>, U&> operator[] (size_t index) {
		#ifdef CTK_ABC
			bound_check(index);
		#endif
		return this->buf[index];
	}

	void clear() {
		len = 0;
	}

	ar<T> to_ar() const {
		ar<T> array;
		array.buf = this->buf;
		array.len = this->len;
		return array;
	}

	gar<T> clone() const {
		gar<T> new_array = gar<T>::create(this->cap);
		new_array.len = this->len;
		std::memcpy(new_array.buf, this->buf, sizeof(T) * this->len);
		return new_array;
	}

	void grow() {
		this->cap *= 2;
		this->buf = (T*)std::realloc(this->buf, sizeof(T) * this->cap);
		if (this->buf == nullptr) {
			CTK_PANIC("std::realloc failed (cap:%zu)", this->cap);
		}
	}

	void push(T value) {
		if (this->len == this->cap) {
			this->grow();
		}
		this->buf[this->len] = value;
		this->len += 1;
	}

	void push_many(const void* src_ptr, size_t count) {
		size_t old_len = len;
		this->len += count;
		while (this->len >= this->cap) {
			this->grow();
		}
		std::memcpy(&this->buf[old_len], src_ptr, sizeof(T) * count);
	}

	T pop() {
		if (this->len == 0) {
			CTK_PANIC("len is zero");
		}
		this->len -= 1;
		return this->buf[this->len];
	}

	void pop_many(size_t count) {
		if (this->len < count) {
			CTK_PANIC("len is zero");
		}
		this->len -= count;
	}

	void join(ar<T> other) {
		this->push_many(other.buf, other.len);
	}

	void join(gar<T> other) {
		this->push_many(other.buf, other.len);
	}

	void insert(size_t index, T value) {
		if (index > this->len) {
			CTK_PANIC("index %zu is out of bounds (len:%zu)", index, this->len);
		}
		if (this->len == this->cap) {
			this->grow();
		}
		std::memmove(&this->buf[index + 1], &this->buf[index], sizeof(T) * (this->len - index));
		this->buf[index] = value;
		this->len += 1;
	}

	void insert_many(size_t index, const void* src_ptr, size_t count) {
		if (count == 0) {
			CTK_PANIC("count is zero");
		}
		if (index >= this->len) {
			CTK_PANIC("index %zu is out of bounds (len:%zu)", index, this->len);
		}
		this->len += count;
		while (this->len >= this->cap) {
			this->grow();
		}
		std::memmove(&this->buf[index + count], &this->buf[index], sizeof(T) * (this->len - index - count));
		std::memcpy(&this->buf[index], src_ptr, sizeof(T) * count);
	}

	T remove(size_t index) {
		if (index >= this->len) {
			CTK_PANIC("index %zu is out of bounds (len:%zu)", index, this->len);
		}
		T value = this->buf[index];
		this->len -= 1;
		std::memmove(&this->buf[index], &this->buf[index + 1], sizeof(T) * (this->len - index));
		return value;
	}

	void remove_many(size_t index, size_t count) {
		if (count == 0) {
			CTK_PANIC("count is zero");
		}
		if (index + count > this->len) {
			CTK_PANIC("index %zu+%zu is out of bounds (len:%zu)", index, count, this->len);
		}
		std::memmove(&this->buf[index], &this->buf[index + count], sizeof(T) * (this->len - index - count));
		this->len -= count;
	}
};