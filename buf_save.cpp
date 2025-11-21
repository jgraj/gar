void BufSave::skip(this auto& self, size_t size) {
	self.index += size;
}

template <typename Type>
void BufSave::save_many(this auto& self, const Type* src_data, size_t count) {
	size_t size = sizeof(Type) * count;
	std::memcpy(&self.dst_data[self.index], src_data, size);
	self.skip(size);
}

template <typename Type>
void BufSave::save(this auto& self, Type data) {
	self.template save_many<Type>(&data, 1);
}

void BufSave::save_vls(this auto& self, size_t size) {
	if (size <= vls1_max) {
		self.template save<u8>(size & 0x7F);
	} else if (size <= vls2_max) {
		self.template save<u8>((size & 0x7F) | 0x80);
		self.template save<u8>((size >> 7) & 0x7F);
	} else if (size <= vls3_max) {
		self.template save<u8>((size & 0x7F) | 0x80);
		self.template save<u8>(((size >> 7) & 0x7F) | 0x80);
		self.template save<u8>((size >> 14) & 0x7F);
	} else if (size <= vls4_max) {
		self.template save<u8>((size & 0x7F) | 0x80);
		self.template save<u8>(((size >> 7) & 0x7F) | 0x80);
		self.template save<u8>(((size >> 14) & 0x7F) | 0x80);
		self.template save<u8>(size >> 21);
	} else {
		ctk::panic("ctk::BufSave::save_vls failed");
	}
}

template <typename Type, typename LenType>
void BufSave::save_ar(this auto& self, ar<const Type> data) {
	self.template save<LenType>(data.len);
	self.template save_many<Type>(data.buf, data.len);
}