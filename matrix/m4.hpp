struct m4f {
	union {
		struct {
			f32 _00;
			f32 _01;
			f32 _02;
			f32 _03;
			f32 _10;
			f32 _11;
			f32 _12;
			f32 _13;
			f32 _20;
			f32 _21;
			f32 _22;
			f32 _23;
			f32 _30;
			f32 _31;
			f32 _32;
			f32 _33;
		};
		f32 data[16];
	};

	static m4f mul(m4f a, m4f b);

	constexpr m4f() {};
	constexpr m4f(f32 _00, f32 _01, f32 _02, f32 _03, f32 _10, f32 _11, f32 _12, f32 _13, f32 _20, f32 _21, f32 _22, f32 _23, f32 _30, f32 _31, f32 _32, f32 _33): _00(_00), _01(_01), _02(_02), _03(_03), _10(_10), _11(_11), _12(_12), _13(_13), _20(_20), _21(_21), _22(_22), _23(_23), _30(_30), _31(_31), _32(_32), _33(_33) {}
	static constexpr m4f ident() {
		return m4f(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}
	constexpr f32& operator[] (this auto& self, size_t index) {
		return self.data[index];
	}
	constexpr const f32& operator[] (this const auto& self, size_t index) {
		return self.data[index];
	}
	m4f transposed(this const auto& self);
};

m4f m4f::transposed(this const auto& self) {
	return m4f(
		self.data[0], self.data[4], self.data[8],  self.data[12],
		self.data[1], self.data[5], self.data[9],  self.data[13],
		self.data[2], self.data[6], self.data[10], self.data[14],
		self.data[3], self.data[7], self.data[11], self.data[15]
	);
}