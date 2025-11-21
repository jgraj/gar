#ifdef CBS_WIN32
bool File::exists(const char* path) {
	DWORD attributes = ::GetFileAttributesA(path);
	return (attributes != INVALID_FILE_ATTRIBUTES);
}

char* File::get_exe_dir() {
	char* buffer = alloc_space<char>(MAX_PATH);
	::GetModuleFileNameA(nullptr, buffer, MAX_PATH);
	char* last_backslash = std::strrchr(buffer, '\\');
	if (last_backslash) {
		*last_backslash = '\0';
	}
	return buffer;
}

void MappedFile::create(this MappedFile& self, const char* path) {
	self.file = ::CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (self.file == INVALID_HANDLE_VALUE) {
		ctk::panic("::CreateFileA failed");
	}
	LARGE_INTEGER sz;
	::GetFileSizeEx(self.file, &sz);
	self.size = (size_t)sz.QuadPart;
	self.mapping = ::CreateFileMappingA(self.file, nullptr, PAGE_READONLY, 0, 0, nullptr);
	if (self.mapping == nullptr) {
		::CloseHandle(self.file);
		ctk::panic("::CreateFileMapping failed");
	}
	self.data = (u8*)::MapViewOfFile(self.mapping, FILE_MAP_READ, 0, 0, 0);
	if (self.data == nullptr) {
		::CloseHandle(self.mapping);
		::CloseHandle(self.file);
		ctk::panic("::MapViewOfFile failed");
	}
}

void MappedFile::destroy(this MappedFile& self) {
	::UnmapViewOfFile(self.data);
	::CloseHandle(self.mapping);
	::CloseHandle(self.file);
}

#endif

#ifdef CBS_LINUX
bool File::exists(const char* path) {
	return ::access(path, F_OK) == 0;
}
#endif