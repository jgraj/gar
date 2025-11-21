struct m3f {
	union {
		struct {
			f32 _00;
			f32 _01;
			f32 _02;
			f32 _10;
			f32 _11;
			f32 _12;
			f32 _20;
			f32 _21;
			f32 _22;
		};
		f32 data[9];
	};

	constexpr m3f() {};
	constexpr m3f(f32 _00, f32 _01, f32 _02, f32 _10, f32 _11, f32 _12, f32 _20, f32 _21, f32 _22): _00(_00), _01(_01), _02(_02), _10(_10), _11(_11), _12(_12), _20(_20), _21(_21), _22(_22) {}
	constexpr m3f ident(this auto& self) {
		return m3f(
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		);
	}
	constexpr f32& operator[] (this auto& self, size_t index) {
		return self.data[index];
	}
	constexpr const f32& operator[] (this const auto& self, size_t index) {
		return self.data[index];
	}
	m3f transposed(this const auto& self);
};