template <typename Type>
bool ar<Type>::compare(ar<Type> ar1, ar<Type> ar2) {
	if (ar1.len != ar2.len) {
		return false;
	}
	return std::memcmp(ar1.buf, ar2.buf, sizeof(Type) * ar1.len) == 0;
}

template <typename Type>
void ar<Type>::create(this auto& self, size_t new_len) {
	self.len = new_len;
	if (new_len == 0) {
		self.buf = nullptr;
	} else {
		self.buf = (Type*)ctk::mem_alloc(sizeof(Type) * new_len);
		if (self.buf == nullptr) {
			ctk::panic("ctk::ar::create failed: ctk::mem_alloc failed (len:%zu)", new_len);
		}
	}
}

template <typename Type>
void ar<Type>::destroy(this auto& self) {
	ctk::mem_free(self.buf);
	self.buf = nullptr;
}

template <typename Type>
void ar<Type>::bound_check(this const auto& self, size_t index) {
	if (index >= self.len) {
		ctk::panic("ctk::ar::bound_check failed: index %zu is out of bounds (len:%zu)", index, self.len);
	}
}

template <typename Type>
ar<Type>::operator ar<const Type>(this const auto& self) {
	return ar<const Type>(self.buf, self.len);
}

template <typename Type>
const Type& ar<Type>::operator[] (this const auto& self, size_t index) {
	#ifdef CTK_ARR_CHECK
		self.bound_check(index);
	#endif
	return self.buf[index];
}

template <typename Type>
template <typename ConstType>
std::enable_if_t<!std::is_const_v<ConstType>, ConstType&>
ar<Type>::operator[] (this auto& self, size_t index) {
	#ifdef CTK_ARR_CHECK
		self.bound_check(index);
	#endif
	return self.buf[index];
}

template <typename Type>
void ar<Type>::clear(this auto& self) {
	self.len = 0;
}

template <typename Type>
void ar<Type>::resize(this auto& self, size_t len) {
	if (self.len == len) {
		return;
	}
	self.len = len;
	self.buf = (Type*)ctk::mem_realloc(self.buf, sizeof(Type) * self.len);
	if (self.buf == nullptr) {
		ctk::panic("ctk::ar::resize failed: ctk::mem_realloc failed (len:%zu)", self.len);
	}
}

template <typename Type>
gar<Type> ar<Type>::to_gar(this const auto& self) {
	gar<Type> array;
	array.buf = self.buf;
	array.len = self.len;
	array.cap = self.len;
	return array;
}

template <typename Type>
template <typename ConstType>
std::enable_if_t<!std::is_const_v<ConstType>, void>
ar<Type>::copy(this auto& self, ar<const Type> other) {
	std::memcpy(self.buf, other.buf, sizeof(Type) * other.len);
	self.len = other.len;
}

template <typename Type>
template <typename NonConstType>
ar<NonConstType> ar<Type>::clone(this const auto& self) {
	ar<NonConstType> new_array;
	new_array.create(self.len);
	if (self.len != 0) {
		std::memcpy(new_array.buf, self.buf, sizeof(NonConstType) * self.len);
	}
	return new_array;
}

template <typename Type>
template <typename NonConstType>
ar<NonConstType> ar<Type>::clone_deep(this const auto& self) {
	ar<NonConstType> new_array;
	new_array.create(self.len);
	for (size_t a = 0; a < self.len; ++a) {
		new_array[a] = self[a].clone();
	}
	return new_array;
}

template <typename Type>
template <typename NonConstType>
ar<NonConstType> ar<Type>::resize_clone(this const auto& self, size_t len) {
	ar<NonConstType> new_array;
	new_array.create(len);
	if (self.len != 0) {
		std::memcpy(new_array.buf, self.buf, sizeof(NonConstType) * self.len);
	}
	return new_array;
}

template <typename Type>
void ar<Type>::sort_range(this auto&& self, size_t low, size_t high) {
	Type pivot = self[high];
	size_t i = low;
	for (size_t j = low; j < high; j++) {
		if (Type::sort_compare(&self[j], &pivot)) {
			ctk::swap(&self[i], &self[j]);
			i++;
		}
	}
	if (low < high) {
		ctk::swap(&self[i], &self[high]);
		if (i > 0) {
			self.sort_range(low, i - 1);
		}
		self.sort_range(i + 1, high);
	}
}

template <typename Type>
void ar<Type>::sort(this auto&& self) {
	if (self.len <= 1) {
		return;
	}
	self.sort_range(0, self.len - 1);
}