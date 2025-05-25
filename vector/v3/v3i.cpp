struct v3i {
	union {
		struct {
			i32 x;
			i32 y;
			i32 z;
		};
		i32 data[3];
	};

	constexpr v3i() = default;
	constexpr v3i(i32 _x, i32 _y, i32 _z): x(_x), y(_y), z(_z) {}

	bool operator==(v3i const& other) const {
		return this->x == other.x && this->y == other.y && this->z == other.z;
	}
	
	bool operator!=(v3i const& other) const {
		return this->x != other.x || this->y != other.y || this->z != other.z;
	}

	constexpr v3f to_v3f() const;

	static constexpr v3i xyz(i32 value) {
		return v3i(value, value, value);
	}
	
	static v3i add(v3i a, v3i b) {
		return v3i(a.x + b.x, a.y + b.y, a.z + b.z);
	}
	
	static v3i sub(v3i a, v3i b) {
		return v3i(a.x - b.x, a.y - b.y, a.z - b.z);
	}
	
	static v3i mul(v3i a, v3i b) {
		return v3i(a.x * b.x, a.y * b.y, a.z * b.z);
	}
	
	static v3i div(v3i a, v3i b) {
		return v3i(a.x / b.x, a.y / b.y, a.z / b.z);
	}
};