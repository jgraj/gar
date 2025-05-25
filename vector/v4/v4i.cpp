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

	constexpr v4i() = default;
	constexpr v4i(i32 _x, i32 _y, i32 _z, i32 _w): x(_x), y(_y), z(_z), w(_w) {}
	
	static constexpr v4i xyzw(i32 value) {
		return v4i(value, value, value, value);
	}
};