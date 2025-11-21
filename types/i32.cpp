i32 i32_min(i32 a, i32 b) {
	return a <= b ? a : b;
}

i32 i32_max(i32 a, i32 b) {
	return a >= b ? a : b;
}

i32 i32_abs(i32 a) {
	return a < 0 ? -a : a;
}

i32 i32_clamp(i32 a, i32 min, i32 max) {
	return i32_min(i32_max(a, min), max);
}