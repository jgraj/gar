struct v2f {
	union {
		struct {
			f32 x;
			f32 y;
		};
		f32 data[2];
	};

	constexpr v2f() = default;
	constexpr v2f(f32 _x, f32 _y): x(_x), y(_y) {}

	bool operator==(v2f const& other) const {
		return this->x == other.x && this->y == other.y;
	}
	
	bool operator!=(v2f const& other) const {
		return this->x != other.x || this->y != other.y;
	}

	constexpr v2i to_v2i() const;
	
	v2f round() const {
		return v2f(std::roundf(this->x), std::roundf(this->y));
	}

	v2f ceil() const {
		return v2f(std::ceil(this->x), std::ceil(this->y));
	}

	static constexpr v2f xy(f32 value) {
		return v2f(value, value);
	}

	static f32 sqr_dst(v2f a, v2f b) {
		f32 x = a.x - b.x;
		f32 y = a.y - b.y;
		return x * x + y * y;
	}

	static f32 dst(v2f a, v2f b) {
		return std::sqrt(sqr_dst(a, b));
	}

	static v2f add(v2f a, v2f b) {
		return v2f(a.x + b.x, a.y + b.y);
	}

	static v2f sub(v2f a, v2f b) {
		return v2f(a.x - b.x, a.y - b.y);
	}

	static v2f mul(v2f a, v2f b) {
		return v2f(a.x * b.x, a.y * b.y);
	}

	static v2f mul_f32(v2f a, f32 b) {
		return v2f(a.x * b, a.y * b);
	}

	static v2f div(v2f a, v2f b) {
		return v2f(a.x / b.x, a.y / b.y);
	}

	static v2f div_f32(v2f a, f32 b) {
		return v2f(a.x / b, a.y / b);
	}
};