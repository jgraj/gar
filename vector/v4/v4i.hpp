struct v4i {
	union {
		struct {
			i32 x;
			i32 y;
			i32 z;
			i32 w;
		};
		i32 data[4];
	};

	constexpr v4i() {};
	constexpr v4i(i32 x, i32 y, i32 z, i32 w): x(x), y(y), z(z), w(w) {}
	
	static constexpr v4i xyzw(i32 value) {
		return v4i(value, value, value, value);
	}
};