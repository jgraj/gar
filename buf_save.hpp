struct BufSave {
	u8* dst_data;
	size_t index = 0;

	void skip(this auto& self, size_t size);
	template <typename Type> void save_many(this auto& self, const Type* src_data, size_t count);
	template <typename Type> void save(this auto& self, Type data);
	void save_vls(this auto& self, size_t size);
	template <typename Type, typename LenType> void save_ar(this auto& self, ar<const Type> data);
};