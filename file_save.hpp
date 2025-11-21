struct FileSave {
	#ifdef CBS_WIN32
		Win32::Handle file_handle;
	#endif

	#ifdef CBS_LINUX
		int file_desc;
	#endif

	void create(this auto& self, const char* path);
	void destroy(this auto& self);
	template <typename Type> void save_many(this auto& self, const Type* data, size_t count);
	template <typename Type> void save(this auto& self, Type data);
	template <typename Type, typename LenType> void save_ar(this auto& self, ar<const Type> data);
};