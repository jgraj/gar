struct File {
	static bool exists(const char* path) {
		return ::access(path, F_OK) == 0;
	}
};