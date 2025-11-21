v4f v4f::add_f32(v4f a, f32 b) {
	return v4f(a.x + b, a.y + b, a.z + b, a.w + b);
}

v4f v4f::sub_f32(v4f a, f32 b) {
	return v4f(a.x - b, a.y - b, a.z - b, a.w - b);
}

v4f v4f::mul_f32(v4f a, f32 b) {
	return v4f(a.x * b, a.y * b, a.z * b, a.w * b);
}

v4f v4f::div_f32(v4f a, f32 b) {
	return v4f(a.x / b, a.y / b, a.z / b, a.w / b);
}

bool v4f::cmp(v4f a, v4f b, f32 epsilon) {
	return f32_cmp(a.x, b.x, epsilon) && f32_cmp(a.y, b.y, epsilon) && f32_cmp(a.z, b.z, epsilon) && f32_cmp(a.w, b.w, epsilon);
}

v4f v4f::lerp(v4f a, v4f b, f64 t) {
	return v4f(f32_lerp(a.x, b.x, t), f32_lerp(a.y, b.y, t), f32_lerp(a.z, b.z, t), f32_lerp(a.w, b.w, t));
}

v4f v4f::smooth_step(v4f a, v4f b, f64 t, f64 dt) {
	return v4f(f32_smooth_step(a.x, b.x, t, dt), f32_smooth_step(a.y, b.y, t, dt), f32_smooth_step(a.z, b.z, t, dt), f32_smooth_step(a.w, b.w, t, dt));
}

v4f v4f::smooth_damp(v4f a, v4f b, f64 t, f64 dt) {
	return v4f(f32_smooth_damp(a.x, b.x, t, dt), f32_smooth_damp(a.y, b.y, t, dt), f32_smooth_damp(a.z, b.z, t, dt), f32_smooth_damp(a.w, b.w, t, dt));
}