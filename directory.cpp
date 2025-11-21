#ifdef CBS_WIN32
void Directory::create(this auto& self, const char* path) {
	char search_path[MAX_PATH];
	std::snprintf(search_path, MAX_PATH, "%s\\*", path);
	self.find_handle = ::FindFirstFile(search_path, &self.find_file_data);
	self.state = State::First;
	if (self.find_handle == INVALID_HANDLE_VALUE) {
		ctk::panic("::FindFirstFile failed (%i)", ::GetLastError());
	}
}

void Directory::destroy(this auto& self) {
	::FindClose(self.find_handle);
}

Directory::Entity Directory::get_next(this auto& self, bool allow_dirs) {
	while (true) {
		if (self.state == State::Next) {
			if (::FindNextFile(self.find_handle, &self.find_file_data) == 0) {
				break;
			}
		} else {
			self.state = State::Next;
		}
		const char* file_path = self.find_file_data.cFileName;
		if (self.find_file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (allow_dirs && std::strcmp(file_path, ".") != 0 && std::strcmp(file_path, "..") != 0) {
				return Entity(file_path, Entity::Type::Dir);
			}
		} else {
			return Entity(file_path, Entity::Type::File);
		}
	}
	return Entity(nullptr, Entity::Type::None);
}
#endif

#ifdef CBS_LINUX
void Directory::create(this auto& self, const char* path) {
	self.dir = ::opendir(path);
	if (self.dir == nullptr) {
		ctk::panic("opendir failed");
	}
}

void Directory::destroy(this auto& self) {
	::closedir(self.dir);
}

Directory::Entity Directory::get_next(this auto& self, bool allow_dirs) {
	struct dirent* entry;
	while (true) {
		entry = ::readdir(self.dir);
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