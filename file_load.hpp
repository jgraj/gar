struct FileLoad {
	enum class Error {
		None,
		Default,
	};

#ifdef CBS_WIN32
	Win32::Handle file_handle;
#endif

#ifdef CBS_LINUX
	int file_desc;
#endif

	void create(this auto& self, const char* path);
	void destroy(this auto& self);
	template <typename Type> Error load_many(this auto& self, Type* data, size_t count);
	template <typename Type> Error load(this auto& self, Type* out_data);
	template <typename Type, typename LenType> Error load_ar(this auto& self, ar<Type>* out_array);
};