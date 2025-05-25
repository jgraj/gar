struct FileLoad {
	#ifdef CTK_WIN32

	#endif

	#ifdef CTK_LINUX
		int file_desc;

		void create(const char* path) {
			this->file_desc = ::open(path, O_RDONLY, 0);
		}
	
		void destroy() {
			::close(this->file_desc);
		}

		template <typename Type> void load_many(Type* data, size_t count) {
			if (::read(this->file_desc, data, sizeof(Type) * count) == -1) {
				CTK_PANIC("::read failed");
			}
		}

		template <typename Type> Type load() {
			Type type;
			this->load_many<Type>(&type, 1);
			return type;
		}

		template <typename Type, typename LenType> ar<Type> load_ar() {
			LenType len = this->load<LenType>();
			ar<Type> data = ar<Type>::create(len);
			this->load_many<Type>(data.buf, len);
			return data;
		}
	#endif
};