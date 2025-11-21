template <typename Type> struct ar {
	Type* buf;
	size_t len;

	ar() {}
	ar(Type* buf, size_t len): buf(buf), len(len) {}
	static constexpr ar<Type> empty() { return ar<Type>(nullptr, 0); }
	static bool compare(ar<Type> ar1, ar<Type> ar2);
	void create(this auto& self, size_t new_len);
	void destroy(this auto& self);
	void bound_check(this const auto& self, size_t index);
	operator ar<const Type>(this const auto& self);
	const Type& operator[] (this const auto& self, size_t index);
	template <typename ConstType = Type> std::enable_if_t<!std::is_const_v<ConstType>, ConstType&> operator[] (this auto& self, size_t index);
	void clear(this auto& self);
	void resize(this auto& self, size_t len);
	gar<Type> to_gar(this const auto& self);
	template <typename ConstType = Type> std::enable_if_t<!std::is_const_v<ConstType>, void> copy(this auto& self, ar<const Type> other);
	template <typename NonConstType = std::remove_const_t<Type>> ar<NonConstType> clone(this const auto& self);
	template <typename NonConstType = std::remove_const_t<Type>> ar<NonConstType> clone_deep(this const auto& self);
	template <typename NonConstType = std::remove_const_t<Type>> ar<NonConstType> resize_clone(this const auto& self, size_t len);
	void sort_range(this auto&& self, size_t low, size_t high);
	void sort(this auto&& self);
};