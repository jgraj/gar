v3f v3f::scale(v3f a, f32 b) {
	return v3f(a.x * b, a.y * b, a.z * b);
}

v3f v3f::add(v3f a, v3f b) {
	return v3f(a.x + b.x, a.y + b.y, a.z + b.z);
}

v3f v3f::add_f32(v3f a, f32 b) {
	return v3f(a.x + b, a.y + b, a.z + b);
}

v3f v3f::sub(v3f a, v3f b) {
	return v3f(a.x - b.x, a.y - b.y, a.z - b.z);
}

v3f v3f::sub_f32(v3f a, f32 b) {
	return v3f(a.x - b, a.y - b, a.z - b);
}

v3f v3f::mul(v3f a, v3f b) {
	return v3f(a.x * b.x, a.y * b.y, a.z * b.z);
}

v3f v3f::mul_f32(v3f a, f32 b) {
	return v3f(a.x * b, a.y * b, a.z * b);
}

v3f v3f::div(v3f a, v3f b) {
	return v3f(a.x / b.x, a.y / b.y, a.z / b.z);
}

v3f v3f::div_f32(v3f a, f32 b) {
	return v3f(a.x / b, a.y / b, a.z / b);
}

bool v3f::cmp(v3f a, v3f b, f32 epsilon) {
	return f32_cmp(a.x, b.x, epsilon) && f32_cmp(a.y, b.y, epsilon) && f32_cmp(a.z, b.z, epsilon);
}

v3f v3f::rand(Random* random, v3f a, v3f b) {
	return v3f((f32)random->get_f64_range(a.x, b.x), (f32)random->get_f64_range(a.y, b.y), (f32)random->get_f64_range(a.z, b.z));
}

v3f v3f::lerp(v3f a, v3f b, f64 t) {
	return v3f(f32_lerp(a.x, b.x, t), f32_lerp(a.y, b.y, t), f32_lerp(a.z, b.z, t));
}

v3f v3f::smooth_step(v3f a, v3f b, f64 t, f64 dt) {
	return v3f(f32_smooth_step(a.x, b.x, t, dt), f32_smooth_step(a.y, b.y, t, dt), f32_smooth_step(a.z, b.z, t, dt));
}

v3f v3f::smooth_damp(v3f a, v3f b, f64 t, f64 dt) {
	return v3f(f32_smooth_damp(a.x, b.x, t, dt), f32_smooth_damp(a.y, b.y, t, dt), f32_smooth_damp(a.z, b.z, t, dt));
}

v3f v3f::cross(v3f a, v3f b) {
	return v3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

f32 v3f::dot(v3f a, v3f b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

f32 v3f::sqr_dst(v3f a, v3f b) {
	f32 x = a.x - b.x;
	f32 y = a.y - b.y;
	f32 z = a.z - b.z;
	return x * x + y * y + z * z;
}

f32 v3f::dst(v3f a, v3f b) {
	return std::sqrt(sqr_dst(a, b));
}