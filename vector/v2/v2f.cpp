f32 v2f::sqr_dst(v2f a, v2f b) {
	f32 x = a.x - b.x;
	f32 y = a.y - b.y;
	return x * x + y * y;
}

f32 v2f::dst(v2f a, v2f b) {
	return std::sqrt(sqr_dst(a, b));
}

v2f v2f::add(v2f a, v2f b) {
	return v2f(a.x + b.x, a.y + b.y);
}

v2f v2f::add_f32(v2f a, f32 b) {
	return v2f(a.x + b, a.y + b);
}

v2f v2f::sub(v2f a, v2f b) {
	return v2f(a.x - b.x, a.y - b.y);
}

v2f v2f::sub_f32(v2f a, f32 b) {
	return v2f(a.x - b, a.y - b);
}

v2f v2f::mul(v2f a, v2f b) {
	return v2f(a.x * b.x, a.y * b.y);
}

v2f v2f::mul_f32(v2f a, f32 b) {
	return v2f(a.x * b, a.y * b);
}

v2f v2f::div(v2f a, v2f b) {
	return v2f(a.x / b.x, a.y / b.y);
}

v2f v2f::div_f32(v2f a, f32 b) {
	return v2f(a.x / b, a.y / b);
}

bool v2f::cmp(v2f a, v2f b, f32 epsilon) {
	return f32_cmp(a.x, b.x, epsilon) && f32_cmp(a.y, b.y, epsilon);
}

v2f v2f::lerp(v2f a, v2f b, f64 t) {
	return v2f(f32_lerp(a.x, b.x, t), f32_lerp(a.y, b.y, t));
}

v2f v2f::smooth_step(v2f a, v2f b, f64 t, f64 dt) {
	return v2f(f32_smooth_step(a.x, b.x, t, dt), f32_smooth_step(a.y, b.y, t, dt));
}

v2f v2f::smooth_damp(v2f a, v2f b, f64 t, f64 dt) {
	return v2f(f32_smooth_damp(a.x, b.x, t, dt), f32_smooth_damp(a.y, b.y, t, dt));
}