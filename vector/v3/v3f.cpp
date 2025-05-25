struct v3f {
	union {
		struct {
			f32 x;
			f32 y;
			f32 z;
		};
		f32 data[3];
	};

	constexpr v3f() = default;
	constexpr v3f(f32 _x, f32 _y, f32 _z): x(_x), y(_y), z(_z) {}

	bool operator==(v3f const& other) const {
		return this->x == other.x && this->y == other.y && this->z == other.z;
	}
	
	bool operator!=(v3f const& other) const {
		return this->x != other.x || this->y != other.y || this->z != other.z;
	}

	constexpr v3i to_v3i() const;

	static constexpr v3f xyz(f32 value) {
		return v3f(value, value, value);
	}

	static v3f scale(v3f a, f32 b) {
		return v3f(a.x * b, a.y * b, a.z * b);
	}

	static v3f add(v3f a, v3f b) {
		return v3f(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	static v3f sub(v3f a, v3f b) {
		return v3f(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	static v3f mul(v3f a, v3f b) {
		return v3f(a.x * b.x, a.y * b.y, a.z * b.z);
	}

	static v3f div(v3f a, v3f b) {
		return v3f(a.x / b.x, a.y / b.y, a.z / b.z);
	}

	static bool cmp(v3f a, v3f b, f32 epsilon) {
		return f32_cmp(a.x, b.x, epsilon) && f32_cmp(a.y, b.y, epsilon) && f32_cmp(a.z, b.z, epsilon);
	}

	static v3f rand(v3f a, v3f b) {
		return v3f(f32_rand(a.x, b.x), f32_rand(a.y, b.y), f32_rand(a.z, b.z));
	}

	static v3f lerp(v3f a, v3f b, f64 t, f64 dt) {
		return v3f(f32_lerp(a.x, b.x, t, dt), f32_lerp(a.y, b.y, t, dt), f32_lerp(a.z, b.z, t, dt));
	}

	static v3f cross(v3f a, v3f b) {
		return v3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}

	static f32 dot(v3f a, v3f b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	static f32 sqr_dst(v3f a, v3f b) {
		f32 x = a.x - b.x;
		f32 y = a.y - b.y;
		f32 z = a.z - b.z;
		return x * x + y * y + z * z;
	}

	static f32 dst(v3f a, v3f b) {
		return std::sqrt(sqr_dst(a, b));
	}

	v3f normalized() const {
		f32 len = std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
		if (len <= 0.0f) {
			return *this;
		}
		return v3f(this->x / len, this->y / len, this->z / len);
	}

	v3f negated() const {
		return v3f(-this->x, -this->y, -this->z);
	}

	f32 sqr_len() const {
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}

	f32 len() const {
		return std::sqrt(this->sqr_len());
	}
};