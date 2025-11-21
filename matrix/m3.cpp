m3f m3f::transposed(this const auto& self) {
	return m3f(
		self.data[0], self.data[3], self.data[6],
		self.data[1], self.data[4], self.data[7],
		self.data[2], self.data[5], self.data[8]
	);
}