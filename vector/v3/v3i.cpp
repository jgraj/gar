v3i v3i::add(v3i a, v3i b) {
	return v3i(a.x + b.x, a.y + b.y, a.z + b.z);
}

v3i v3i::sub(v3i a, v3i b) {
	return v3i(a.x - b.x, a.y - b.y, a.z - b.z);
}

v3i v3i::mul(v3i a, v3i b) {
	return v3i(a.x * b.x, a.y * b.y, a.z * b.z);
}

v3i v3i::div(v3i a, v3i b) {
	return v3i(a.x / b.x, a.y / b.y, a.z / b.z);
}