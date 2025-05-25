template <typename T> struct ar {
	T* buf = nullptr;
	size_t len = 0;

	static ar<T> create(size_t len) {
		ar<T> array;
		array.len = len;
		if (len == 0) {
			array.buf = nullptr;
		} else {
			array.buf = (T*)std::malloc(sizeof(T) * len);
			if (array.buf == nullptr) {
				CTK_PANIC("malloc failed (len:%zu)", len);
			}
		}
		return array;
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

	operator ar<const T>() const {
		return ar<const T>{ buf, len };
	}

	const T& operator[] (size_t index) const {
		#ifdef GAR_ABC
			bound_check(index);
		#endif
		return this->buf[index];
	}

	template <typename U = T> std::enable_if_t<!std::is_const_v<U>, U&> operator[] (size_t index) {
		#ifdef GAR_ABC
			bound_check(index);
		#endif
		return this->buf[index];
	}

	void clear() {
		this->len = 0;
	}

	gar<T> to_gar() const {
		gar<T> array;
		array.buf = this->buf;
		array.len = this->len;
		array.cap = this->len;
		return array;
	}

	ar<T> clone() const {
		ar<T> new_array = ar<T>::create(this->len);
		std::memcpy(new_array.buf, this->buf, sizeof(T) * this->len);
		return new_array;
	}

	ar<T> resize_clone(size_t new_len) const {
		ar<T> new_array = ar<T>::create(new_len);
		if (this->len != 0) {
			std::memcpy(new_array.buf, this->buf, sizeof(T) * this->len);
		}
		return new_array;
	}
};