u64 u64_parse(ar<const u8> str) {
	u64 value = 0;
	for (size_t a = 0; a < str.len; ++a) {
		u8 c = str[a];
		if (c < '0' || c > '9') {
			ctk::panic("u64_parse failed");
		}
		value = value * 10 + (c - '0');
	}
	return value;
}

u64 u64_min(u64 a, u64 b) {
	return a <= b ? a : b;
}

u64 u64_max(u64 a, u64 b) {
	return a >= b ? a : b;
}