struct v2i {
	union {
		struct {
			i32 x;
			i32 y;
		};
		i32 data[2];
	};

	constexpr v2i() = default;
	constexpr v2i(i32 _x, i32 _y): x(_x), y(_y) {}

	bool operator==(v2i const& other) const {
		return this->x == other.x && this->y == other.y;
	}
	
	bool operator!=(v2i const& other) const {
		return this->x != other.x || this->y != other.y;
	}

	constexpr v2f to_v2f() const;
	
	static constexpr v2i xy(i32 value) {
		return v2i(value, value);
	}

	static i32 sqr_dst(v2i a, v2i b) {
		i32 x = a.x - b.x;
		i32 y = a.y - b.y;
		return x * x + y * y;
	}

	static i32 dst(v2i a, v2i b) {
		return std::sqrt(sqr_dst(a, b));
	}

	static v2i add(v2i a, v2i b) {
		return v2i(a.x + b.x, a.y + b.y);
	}

	static v2i sub(v2i a, v2i b) {
		return v2i(a.x - b.x, a.y - b.y);
	}

	static v2i mul(v2i a, v2i b) {
		return v2i(a.x * b.x, a.y * b.y);
	}

	static v2i div(v2i a, v2i b) {
		return v2i(a.x / b.x, a.y / b.y);
	}
};