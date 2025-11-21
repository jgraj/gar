struct File {
	static bool exists(const char* path);
#ifdef CBS_WIN32
	static char* get_exe_dir();
#endif
};

#ifdef CBS_WIN32

struct MappedFile {
	u8* data;
	size_t size;
	MAYBE_AS(HANDLE, Win32::Handle) file;
	MAYBE_AS(HANDLE, Win32::Handle) mapping;

	void create(this MappedFile& self, const char* path);
	void destroy(this MappedFile& self);
};

#endif