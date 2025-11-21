struct v3i {
	union {
		struct {
			i32 x;
			i32 y;
			i32 z;
		};
		i32 data[3];
	};

	constexpr v3i() {};
	constexpr v3i(i32 x, i32 y, i32 z): x(x), y(y), z(z) {}

	bool operator==(this const auto& self, v3i const& other) {
		return self.x == other.x && self.y == other.y && self.z == other.z;
	}
	
	bool operator!=(this const auto& self, v3i const& other) {
		return self.x != other.x || self.y != other.y || self.z != other.z;
	}

	constexpr v3f to_v3f(this const auto& self);

	static constexpr v3i xyz(i32 value) {
		return v3i(value, value, value);
	}
	
	static v3i add(v3i a, v3i b);
	static v3i sub(v3i a, v3i b);
	static v3i mul(v3i a, v3i b);
	static v3i div(v3i a, v3i b);
};