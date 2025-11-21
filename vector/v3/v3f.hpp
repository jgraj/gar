struct v3f {
	union {
		struct {
			f32 x;
			f32 y;
			f32 z;
		};
		f32 data[3];
	};

	constexpr v3f() {}
	constexpr v3f(f32 x, f32 y, f32 z): x(x), y(y), z(z) {}

	f32& operator[] (this auto& self, size_t index) {
		return self.data[index];
	}

	constexpr v3i to_v3i(this const auto& self);

	static constexpr v3f xyz(f32 value) {
		return v3f(value, value, value);
	}

	static v3f scale(v3f a, f32 b);
	static v3f add(v3f a, v3f b);
	static v3f add_f32(v3f a, f32 b);
	static v3f sub(v3f a, v3f b);
	static v3f sub_f32(v3f a, f32 b);
	static v3f mul(v3f a, v3f b);
	static v3f mul_f32(v3f a, f32 b);
	static v3f div(v3f a, v3f b);
	static v3f div_f32(v3f a, f32 b);
	static bool cmp(v3f a, v3f b, f32 epsilon);
	static v3f rand(Random* random, v3f a, v3f b);
	static v3f lerp(v3f a, v3f b, f64 t);
	static v3f smooth_step(v3f a, v3f b, f64 t, f64 dt);
	static v3f smooth_damp(v3f a, v3f b, f64 t, f64 dt);
	static v3f cross(v3f a, v3f b);
	static f32 dot(v3f a, v3f b);
	static f32 sqr_dst(v3f a, v3f b);
	static f32 dst(v3f a, v3f b);

	v3f normalized(this const auto& self);
	v3f negated(this const auto& self);
	f32 sqr_len(this const auto& self);
	f32 len(this const auto& self);
};

v3f v3f::normalized(this const auto& self) {
	f32 len = f32_sqrt(self.x * self.x + self.y * self.y + self.z * self.z);
	if (len <= 0.0f) {
		return self;
	}
	return v3f(self.x / len, self.y / len, self.z / len);
}

v3f v3f::negated(this const auto& self) {
	return v3f(-self.x, -self.y, -self.z);
}

f32 v3f::sqr_len(this const auto& self) {
	return self.x * self.x + self.y * self.y + self.z * self.z;
}

f32 v3f::len(this const auto& self) {
	return f32_sqrt(self.sqr_len());
}