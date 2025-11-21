struct v2f {
	union {
		struct {
			f32 x;
			f32 y;
		};
		f32 data[2];
	};

	constexpr v2f() {};
	constexpr v2f(f32 x, f32 y): x(x), y(y) {}

	f32& operator[] (this auto& self, size_t index) {
		return self.data[index];
	}

	constexpr v2i to_v2i(this const auto& self);

	static constexpr v2f xy(f32 value) {
		return v2f(value, value);
	}

	static f32 sqr_dst(v2f a, v2f b);
	static f32 dst(v2f a, v2f b);
	static v2f add(v2f a, v2f b);
	static v2f add_f32(v2f a, f32 b);
	static v2f sub(v2f a, v2f b);
	static v2f sub_f32(v2f a, f32 b);
	static v2f mul(v2f a, v2f b);
	static v2f mul_f32(v2f a, f32 b);
	static v2f div(v2f a, v2f b);
	static v2f div_f32(v2f a, f32 b);
	static bool cmp(v2f a, v2f b, f32 epsilon);
	static v2f lerp(v2f a, v2f b, f64 t);
	static v2f smooth_step(v2f a, v2f b, f64 t, f64 dt);
	static v2f smooth_damp(v2f a, v2f b, f64 t, f64 dt);

	v2f negated(this const auto& self);
	f32 sqr_len(this const auto& self);
	f32 len(this const auto& self);
	v2f round(this const auto& self);
	v2f ceil(this const auto& self);
};

v2f v2f::negated(this const auto& self) {
	return v2f(-self.x, -self.y);
}

f32 v2f::sqr_len(this const auto& self) {
	return self.x * self.x + self.y * self.y;
}

f32 v2f::len(this const auto& self) {
	return f32_sqrt(self.sqr_len());
}

v2f v2f::round(this const auto& self) {
	return v2f(f32_round(self.x), f32_round(self.y));
}

v2f v2f::ceil(this const auto& self) {
	return v2f(f32_ceil(self.x), f32_ceil(self.y));
}