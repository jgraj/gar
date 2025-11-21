template <typename Type> struct gar {
	Type* buf;
	size_t len;
	size_t cap;
	
	gar() {}
	gar(Type* buf, size_t len, size_t cap): buf(buf), len(len), cap(cap) {}
	static constexpr gar<Type> empty() { return gar<Type>(nullptr, 0, 0); }
	void create_cap(this auto& self, size_t cap);
	void create_len(this auto& self, size_t len);
	void create_auto(this auto& self);
	void destroy(this auto& self);
	void bound_check(this const auto& self, size_t index);
	operator gar<const Type>() const;
	const Type& operator[] (this const auto& self, size_t index);
	template <typename ConstType = Type> std::enable_if_t<!std::is_const_v<ConstType>, ConstType&> operator[] (this auto& self, size_t index);
	void clear(this auto& self);
	ar<Type> to_ar(this const auto& self);
	template <typename ConstType = Type> std::enable_if_t<!std::is_const_v<ConstType>, ar<ConstType>> to_ar(this auto& self);
	gar<Type> clone(this const auto& self);
	gar<Type> clone_deep(this const auto& self);
	void resize(this auto& self, size_t cap);
	void grow(this auto& self);
	void push(this auto& self, Type value);
	void push_many(this auto& self, const void* src_ptr, size_t count);
	Type pop(this auto& self);
	void pop_many(this auto& self, size_t count);
	void join(this auto& self, ar<const Type> other);
	void join(this auto& self, gar<const Type> other);
	void insert(this auto& self, size_t index, Type value);
	void insert_many(this auto& self, size_t index, const void* src_ptr, size_t count);
	Type remove(this auto& self, size_t index);
	void remove_many(this auto& self, size_t index, size_t count);
	void sort_range(this auto&& self, size_t low, size_t high);
	void sort(this auto&& self);
};