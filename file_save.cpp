struct FileSave {
	#ifdef CTK_WIN32

	#endif

	#ifdef CTK_LINUX
		int file_desc;

		void create(const char* path) {
			this->file_desc = ::creat(path, S_IRUSR | S_IWUSR);
		}
	
		void destroy() {
			::close(this->file_desc);
		}
		
		template <typename Type> void save_many(const Type* data, size_t count) {
			if (::write(this->file_desc, data, sizeof(Type) * count) == -1) {
				CTK_PANIC("::write failed");
			}
		}

		template <typename Type> void save(Type data) {
			this->save_many<Type>(&data, 1);
		}

		template <typename Type, typename LenType> void save_ar(ar<const Type> data) {
			this->save<LenType>(data.len);
			this->save_many<Type>(data.buf, data.len);
		}
	#endif
};