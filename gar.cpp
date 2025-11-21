template <typename Type>
void gar<Type>::create_cap(this auto& self, size_t cap) {
	self.len = 0;
	self.cap = cap;
	if (cap == 0) {
		self.buf = nullptr;
	} else {
		self.buf = (Type*)ctk::mem_alloc(sizeof(Type) * cap);
		if (self.buf == nullptr) {
			ctk::panic("ctk::gar::create_cap failed: ctk::mem_alloc failed (cap:%zu)", cap);
		}
	}
}

template <typename Type>
void gar<Type>::create_len(this auto& self, size_t len) {
	self.create_cap(len);
	self.len = len;
}

template <typename Type>
void gar<Type>::create_auto(this auto& self) {
	self.create_cap(8);
}

template <typename Type>
void gar<Type>::destroy(this auto& self) {
	ctk::mem_free(self.buf);
	self.buf = nullptr;
}

template <typename Type>
void gar<Type>::bound_check(this const auto& self, size_t index) {
	if (index >= self.len) {
		ctk::panic("ctk::gar::bound_check failed: index %zu is out of bounds (len:%zu)", index, self.len);
	}
}

template <typename Type>
gar<Type>::operator gar<const Type>() const {
	return gar<const Type>(buf, len, cap);
}

template <typename Type>
const Type& gar<Type>::operator[] (this const auto& self, size_t index) {
	#ifdef CTK_ARR_CHECK
		self.bound_check(index);
	#endif
	return self.buf[index];
}

template <typename Type>
template <typename ConstType>
std::enable_if_t<!std::is_const_v<ConstType>, ConstType&>
gar<Type>::operator[] (this auto& self, size_t index) {
	#ifdef CTK_ARR_CHECK
		self.bound_check(index);
	#endif
	return self.buf[index];
}

template <typename Type>
void gar<Type>::clear(this auto& self) {
	self.len = 0;
}

template <typename Type>
ar<Type> gar<Type>::to_ar(this const auto& self) {
	return ar<Type>(self.buf, self.len);
}

template <typename Type>
template <typename ConstType>
std::enable_if_t<!std::is_const_v<ConstType>, ar<ConstType>>
gar<Type>::to_ar(this auto& self) {
	return ar<ConstType>(self.buf, self.len);
}

template <typename Type>
gar<Type> gar<Type>::clone(this const auto& self) {
	gar<Type> new_array;
	new_array.create_cap(self.cap);
	new_array.len = self.len;
	if (self.len != 0) {
		std::memcpy(new_array.buf, self.buf, sizeof(Type) * self.len);
	}
	return new_array;
}

template <typename Type>
gar<Type> gar<Type>::clone_deep(this const auto& self) {
	gar<Type> new_array;
	new_array.create_cap(self.cap);
	new_array.len = self.len;
	for (size_t a = 0; a < self.len; ++a) {
		new_array[a] = self[a].clone();
	}
	return new_array;
}

template <typename Type>
void gar<Type>::resize(this auto& self, size_t cap) {
	self.cap = cap;
	self.buf = (Type*)ctk::mem_realloc(self.buf, sizeof(Type) * self.cap);
	if (self.buf == nullptr) {
		ctk::panic("ctk::gar::resize failed: ctk::mem_realloc failed (cap:%zu)", self.cap);
	}
}

template <typename Type>
void gar<Type>::grow(this auto& self) {
	self.resize(self.cap < 8 ? 8 : self.cap * 2);
}

template <typename Type>
void gar<Type>::push(this auto& self, Type value) {
	if (self.len == self.cap) {
		self.grow();
	}
	self.buf[self.len] = value;
	self.len += 1;
}

template <typename Type>
void gar<Type>::push_many(this auto& self, const void* src_ptr, size_t count) {
	size_t old_len = self.len;
	self.len += count;
	while (self.len >= self.cap) {
		self.grow();
	}
	std::memcpy(&self.buf[old_len], src_ptr, sizeof(Type) * count);
}

template <typename Type>
Type gar<Type>::pop(this auto& self) {
	if (self.len == 0) {
		ctk::panic("ctk::gar::pop failed: len is zero");
	}
	self.len -= 1;
	return self.buf[self.len];
}

template <typename Type>
void gar<Type>::pop_many(this auto& self, size_t count) {
	if (self.len < count) {
		ctk::panic("ctk::gar::pop_many failed: len is zero");
	}
	self.len -= count;
}

template <typename Type>
void gar<Type>::join(this auto& self, ar<const Type> other) {
	self.push_many(other.buf, other.len);
}

template <typename Type>
void gar<Type>::join(this auto& self, gar<const Type> other) {
	self.push_many(other.buf, other.len);
}

template <typename Type>
void gar<Type>::insert(this auto& self, size_t index, Type value) {
	if (index > self.len) {
		ctk::panic("ctk::gar::insert failed: index %zu is out of bounds (len:%zu)", index, self.len);
	}
	if (self.len == self.cap) {
		self.grow();
	}
	std::memmove(&self.buf[index + 1], &self.buf[index], sizeof(Type) * (self.len - index));
	self.buf[index] = value;
	self.len += 1;
}

template <typename Type>
void gar<Type>::insert_many(this auto& self, size_t index, const void* src_ptr, size_t count) {
	if (count == 0) {
		ctk::panic("ctk::gar::insert_many failed: count is zero");
	}
	if (index >= self.len) {
		ctk::panic("ctk::gar::insert_many failed: index %zu is out of bounds (len:%zu)", index, self.len);
	}
	self.len += count;
	while (self.len >= self.cap) {
		self.grow();
	}
	std::memmove(&self.buf[index + count], &self.buf[index], sizeof(Type) * (self.len - index - count));
	std::memcpy(&self.buf[index], src_ptr, sizeof(Type) * count);
}

template <typename Type>
Type gar<Type>::remove(this auto& self, size_t index) {
	if (index >= self.len) {
		ctk::panic("ctk::gar::remove failed: index %zu is out of bounds (len:%zu)", index, self.len);
	}
	Type value = self.buf[index];
	self.len -= 1;
	std::memmove(&self.buf[index], &self.buf[index + 1], sizeof(Type) * (self.len - index));
	return value;
}

template <typename Type>
void gar<Type>::remove_many(this auto& self, size_t index, size_t count) {
	if (count == 0) {
		ctk::panic("ctk::gar::remove_many failed: count is zero");
	}
	if (index + count > self.len) {
		ctk::panic("ctk::gar::remove_many failed: index %zu+%zu is out of bounds (len:%zu)", index, count, self.len);
	}
	std::memmove(&self.buf[index], &self.buf[index + count], sizeof(Type) * (self.len - index - count));
	self.len -= count;
}

template <typename Type>
void gar<Type>::sort_range(this auto&& self, size_t low, size_t high) {
	self.to_ar().sort_range(low, high);
}

template <typename Type>
void gar<Type>::sort(this auto&& self) {
	self.to_ar().sort();
}