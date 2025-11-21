struct v4f {
	union {
		struct {
			f32 x;
			f32 y;
			f32 z;
			f32 w;
		};
		f32 data[4];
	};

	constexpr v4f() {};
	constexpr v4f(f32 x, f32 y, f32 z, f32 w): x(x), y(y), z(z), w(w) {}

	f32& operator[] (this auto& self, size_t index) {
		return self.data[index];
	}

	static constexpr v4f xyzw(f32 value) {
		return v4f(value, value, value, value);
	}

	static v4f add_f32(v4f a, f32 b);
	static v4f sub_f32(v4f a, f32 b);
	static v4f mul_f32(v4f a, f32 b);
	static v4f div_f32(v4f a, f32 b);
	static bool cmp(v4f a, v4f b, f32 epsilon);
	static v4f lerp(v4f a, v4f b, f64 t);
	static v4f smooth_step(v4f a, v4f b, f64 t, f64 dt);
	static v4f smooth_damp(v4f a, v4f b, f64 t, f64 dt);
};