f32 f32_sin(f32 a) {
	return std::sinf(a);
}

f32 f32_cos(f32 a) {
	return std::cosf(a);
}

f32 f32_tan(f32 a) {
	return std::tan(a);
}

f32 f32_atan(f32 a) {
	return std::atan(a);
}

f32 f32_pow(f32 a, f32 b) {
	return std::powf(a, b);
}

f32 f32_log(f32 a) {
	return std::logf(a);
}

f32 f32_min(f32 a, f32 b) {
	return a <= b ? a : b;
}

f32 f32_max(f32 a, f32 b) {
	return a >= b ? a : b;
}

i32 f32_ceil(f32 a) {
	return (i32)std::ceil(a);
}

i32 f32_floor(f32 a) {
	i32 i = (i32)a;
	return (a < 0.0f && a != (f32)i) ? (i - 1) : i;
}

f32 f32_round(f32 a) {
	return std::roundf(a);
}

f32 f32_sqrt(f32 a) {
	return std::sqrt(a);
}

f32 f32_clamp(f32 a, f32 min, f32 max) {
	return f32_min(f32_max(a, min), max);
}

f32 f32_abs(f32 a) {
	return a < 0.0f ? -a : a;
}

bool f32_cmp(f32 a, f32 b, f32 epsilon) {
	return std::fabs(a - b) <= epsilon;
}

f32 f32_bounce(f32 a) {
	return 1.0f - f32_abs((a * 2.0f) - 1.0f);
}

f32 f32_lerp(f32 a, f32 b, f64 t) {
	return a + (b - a) * (f32)t;
}

f32 f32_smooth_step(f32 a, f32 b, f64 t, f64 dt) {
	f64 ht = -t / std::log2(0.001);
	return b + (a - b) * (f32)std::exp2(-dt / ht);
}

f32 f32_smooth_damp(f32 a, f32 b, f64 smoothing, f64 delta_time) {
	f64 t = 1.0 - std::exp(-smoothing * delta_time);
	return f32_lerp(a, b, t);
}