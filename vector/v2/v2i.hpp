struct v2i {
	union {
		struct {
			i32 x;
			i32 y;
		};
		i32 data[2];
	};

	constexpr v2i() {};
	constexpr v2i(i32 x, i32 y): x(x), y(y) {}

	bool operator==(this const auto& self, v2i const& other) {
		return self.x == other.x && self.y == other.y;
	}
	
	bool operator!=(this const auto& self, v2i const& other) {
		return self.x != other.x || self.y != other.y;
	}

	constexpr v2f to_v2f(this const auto& self);
	
	static constexpr v2i xy(i32 value) {
		return v2i(value, value);
	}

	static i32 sqr_dst(v2i a, v2i b);
	static f32 dst(v2i a, v2i b);
	static v2i add(v2i a, v2i b);
	static v2i add_i32(v2i a, i32 b);
	static v2i sub(v2i a, v2i b);
	static v2i sub_i32(v2i a, i32 b);
	static v2i mul(v2i a, v2i b);
	static v2i mul_i32(v2i a, i32 b);
	static v2i div(v2i a, v2i b);
	static v2i div_i32(v2i a, i32 b);
	static bool cmp(v2i a, v2i b);
};