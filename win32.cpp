Win32::Handle Win32::CreateThreadSimple(void* lpStartAddress, void* lpParameter) {
	return (Win32::Handle)::CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)lpStartAddress, (LPVOID)lpParameter, 0, nullptr);
}