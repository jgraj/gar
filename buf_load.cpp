void BufLoad::skip(this auto& self, size_t size) {
	self.index += size;
}

template <typename Type>
void BufLoad::load_many(this auto& self, Type* dst_data, size_t count) {
	size_t size = sizeof(Type) * count;
	std::memcpy(dst_data, &self.src_data[self.index], size);
	self.skip(size);
}

template <typename Type>
Type BufLoad::load(this auto& self) {
	Type type;
	self.template load_many<Type>(&type, 1);
	return type;
}

size_t BufLoad::load_vls(this auto& self) {
	u32 result = 0;
	size_t shift = 0;
	for (size_t a = 0; a < 3; ++a) {
		u8 byte = self.template load<u8>();
		result |= (u32)(byte & 0x7F) << shift;
		if (!(byte & 0x80)) {
			return result;
		}
		shift += 7;
	}
	u8 byte = self.template load<u8>();
	result |= (u32)byte << 21;
	return result;
}

template <typename Type, typename LenType>
ar<Type> BufLoad::load_ar(this auto& self) {
	LenType len = self.template load<LenType>();
	ar<Type> data;
	data.create(len);
	self.template load_many<Type>(data.buf, len);
	return data;
}