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

	#ifdef CTK_WIN32
		WIN32_FIND_DATA find_file_data;
		HANDLE find_handle;
		bool no_more_files;

		void create(const char* path) {
			char search_path[MAX_PATH];
			std::snprintf(search_path, MAX_PATH, "%s\\*", path);
			this->find_handle = ::FindFirstFile(search_path, &this->find_file_data);
			this->no_more_files = false;
			if (this->find_handle == INVALID_HANDLE_VALUE) {
				CTK_PANIC("::FindFirstFile failed (%i)", ::GetLastError());
			}
		}

		void destroy() {
			::FindClose(this->find_handle);
		}

		Entity get_next(bool allow_dirs) {
			if (this->no_more_files == false) {
				const char* file_path = this->find_file_data.cFileName;
				if (::FindNextFile(this->find_handle, &this->find_file_data) != 0) {
					return Entity(file_path, Entity::Type::File);
				} else {
					DWORD error = ::GetLastError();
					if (error != ERROR_NO_MORE_FILES) {
						CTK_PANIC("::FindNextFile failed (%i)", error);
					}
					this->no_more_files = true;
				}
			}
			return Entity(nullptr, Entity::Type::None);
		}
	#endif

	#ifdef CTK_LINUX
		DIR* dir;

		void create(const char* path) {
			this->dir = ::opendir(path);
			if (this->dir == nullptr) {
				CTK_PANIC("opendir failed");
			}
		}

		void destroy() {
			::closedir(this->dir);
		}

		Entity get_next(bool allow_dirs) {
			struct dirent* entry;
			while (true) {
				entry = ::readdir(this->dir);
				if (entry == nullptr) {
					break;
				}
				if (entry->d_type == DT_REG) {
					return Entity(entry->d_name, Entity::Type::File);
				}
				if (allow_dirs && entry->d_type == DT_DIR && std::strcmp(entry->d_name, ".") != 0 && std::strcmp(entry->d_name, "..") != 0) {
					return Entity(entry->d_name, Entity::Type::Dir);
				}
			}
			return Entity(nullptr, Entity::Type::None);
		}
	#endif
};