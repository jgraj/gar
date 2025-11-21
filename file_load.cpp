#ifdef CBS_WIN32
	void FileLoad::create(this auto& self, const char* path) {
		self.file_handle = ::CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (self.file_handle == INVALID_HANDLE_VALUE) {
			ctk::panic("CreateFile failed");
		}
	}

	void FileLoad::destroy(this auto& self) {
		::CloseHandle(self.file_handle);
	}

	template <typename Type>
	FileLoad::Error FileLoad::load_many(this auto& self, Type* data, size_t count) {
		DWORD bytes_read;
		return (::ReadFile(self.file_handle, data, sizeof(Type) * count, &bytes_read, nullptr) == 0 || bytes_read != sizeof(Type) * count) ? Error::Default : Error::None;
	}
#endif

#ifdef CBS_LINUX
	void FileLoad::create(this auto& self, const char* path) {
		self.file_desc = ::open(path, O_RDONLY, 0);
	}

	void FileLoad::destroy(this auto& self) {
		::close(self.file_desc);
	}

	template <typename Type>
	FileLoad::Error FileLoad::load_many(this auto& self, Type* data, size_t count) {
		return ::read(self.file_desc, data, sizeof(Type) * count) == -1 ? Error::Default : Error::None;
	}
#endif

template <typename Type>
FileLoad::Error FileLoad::load(this auto& self, Type* out_data) {
	return self.template load_many<Type>(out_data, 1);
}

template <typename Type, typename LenType>
FileLoad::Error FileLoad::load_ar(this auto& self, ar<Type>* out_array) {
	LenType len;
	Error error = self.template load<LenType>(&len);
	if (error != Error::None) {
		return error;
	}
	ar<Type> data;
	data.create(len);
	error = self.template load_many<Type>(data.buf, len);
	if (error != Error::None) {
		data.destroy();
		return error;
	}
	*out_array = data;
	return Error::None;
}