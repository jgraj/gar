struct BufLoad {
	const u8* src_data;
	size_t index = 0;

	void skip(this auto& self, size_t size);
	template <typename Type> void load_many(this auto& self, Type* dst_data, size_t count);
	template <typename Type> Type load(this auto& self);
	size_t load_vls(this auto& self);
	template <typename Type, typename LenType> ar<Type> load_ar(this auto& self);
};