#ifdef CBS_WIN32
	void FileSave::create(this auto& self, const char* path) {
		self.file_handle = ::CreateFileA(path, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (self.file_handle == INVALID_HANDLE_VALUE) {
			ctk::panic("::CreateFile failed");
		}
	}

	void FileSave::destroy(this auto& self) {
		::CloseHandle(self.file_handle);
	}
	
	template <typename Type>
	void FileSave::save_many(this auto& self, const Type* data, size_t count) {
		DWORD bytes_written;
		if (!::WriteFile(self.file_handle, data, sizeof(Type) * count, &bytes_written, nullptr)) {
			ctk::panic("::WriteFile failed");
		}
	}
#endif

#ifdef CBS_LINUX
	void FileSave::create(this auto& self, const char* path) {
		self.file_desc = ::creat(path, S_IRUSR | S_IWUSR);
	}

	void FileSave::destroy(this auto& self) {
		::close(self.file_desc);
	}
	
	template <typename Type>
	void FileSave::save_many(this auto& self, const Type* data, size_t count) {
		if (::write(self.file_desc, data, sizeof(Type) * count) == -1) {
			ctk::panic("::write failed");
		}
	}
#endif

template <typename Type>
void FileSave::save(this auto& self, Type data) {
	self.template save_many<Type>(&data, 1);
}

template <typename Type, typename LenType>
void FileSave::save_ar(this auto& self, ar<const Type> data) {
	self.template save<LenType>(data.len);
	self.template save_many<Type>(data.buf, data.len);
}