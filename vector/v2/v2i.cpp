i32 v2i::sqr_dst(v2i a, v2i b) {
	i32 x = a.x - b.x;
	i32 y = a.y - b.y;
	return x * x + y * y;
}

f32 v2i::dst(v2i a, v2i b) {
	return std::sqrt((f32)sqr_dst(a, b));
}

v2i v2i::add(v2i a, v2i b) {
	return v2i(a.x + b.x, a.y + b.y);
}

v2i v2i::add_i32(v2i a, i32 b) {
	return v2i(a.x + b, a.y + b);
}

v2i v2i::sub(v2i a, v2i b) {
	return v2i(a.x - b.x, a.y - b.y);
}

v2i v2i::sub_i32(v2i a, i32 b) {
	return v2i(a.x - b, a.y - b);
}

v2i v2i::mul(v2i a, v2i b) {
	return v2i(a.x * b.x, a.y * b.y);
}

v2i v2i::mul_i32(v2i a, i32 b) {
	return v2i(a.x * b, a.y * b);
}

v2i v2i::div(v2i a, v2i b) {
	return v2i(a.x / b.x, a.y / b.y);
}

v2i v2i::div_i32(v2i a, i32 b) {
	return v2i(a.x / b, a.y / b);
}

bool v2i::cmp(v2i a, v2i b) {
	return a.x == b.x && a.y == b.y;
}