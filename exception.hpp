#ifdef CBS_WIN32

Win32::Long __stdcall exception_handler(/* EXCEPTION_POINTERS */ void* exception_info);
void use_exception_handler();

#endif