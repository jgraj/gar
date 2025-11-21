struct Directory {
	struct Entity {
		enum class Type {
			None,
			File,
			Dir,
		};

		const char* path;
		Type type;
	};

#ifdef CBS_WIN32
	enum class State {
		First,
		Next,
	};

	Win32::FindDataA find_file_data;
	Win32::Handle find_handle;
	State state;
#endif

#ifdef CBS_LINUX
	DIR* dir;
#endif

	void create(this auto& self, const char* path);
	void destroy(this auto& self);
	Entity get_next(this auto& self, bool allow_dirs);
};