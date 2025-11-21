struct Random {
	struct ChaCha20 {
		static u32 rotl32(u32 var, u32 hops);
		static void qr(u32* a, u32* b, u32* c, u32* d);
		static void block(const u32 in[16], u32 out[16]);
	};

	u32 state[16];
	u8 keystream[64];
	size_t available;

	static u32 load32_le(const u8* src);
	static void store32_le(u8* dst, u32 value);
	static bool os_fill_random(void* dst, size_t size);

	void create(this auto& self);
	void refill(this auto& self);
	void get_bytes(this auto& self, u8* dst, size_t size);
	template<typename Type> Type get(this auto& self);
	template<typename Type> void get_many(this auto& self, Type* buf, size_t count);
	f64 get_f64(this auto& self);
	f64 get_f64_range(this auto& self, f64 min, f64 max);
};

void Random::create(this auto& self) {
	u8 key[32];
	u8 nonce[12];
	if (os_fill_random(key, sizeof(key)) || os_fill_random(nonce, sizeof(nonce))) {
		ctk::panic("os_fill_random failed");
	}
	self.state[0] = 0x61707865;
	self.state[1] = 0x3320646e;
	self.state[2] = 0x79622d32;
	self.state[3] = 0x6b206574;
	for (size_t a = 0; a < 8; ++a) {
		self.state[4 + a] = load32_le(key + 4 * a);
	}
	self.state[12] = 0;
	self.state[13] = load32_le(nonce + 0);
	self.state[14] = load32_le(nonce + 4);
	self.state[15] = load32_le(nonce + 8);
	self.available = 0;
}

void Random::refill(this auto& self) {
	u32 block[16];
	ChaCha20::block(self.state, block);
	for (size_t a = 0; a < 16; ++a) {
		store32_le(self.keystream + 4 * a, block[a]);
	}
	self.state[12] += 1;
	self.available = 64;
}

void Random::get_bytes(this auto& self, u8* dst, size_t size) {
	size_t off = 0;
	while (size > 0) {
		if (self.available == 0) {
			self.refill();
		}
		size_t n = self.available;
		if (n > size) {
			n = size;
		}
		std::memcpy(dst + off, self.keystream + (64 - self.available), n);
		self.available -= n;
		off += n;
		size -= n;
	}
}

template<typename Type>
Type Random::get(this auto& self) {
	Type value;
	self.get_bytes((u8*)&value, sizeof(Type));
	return value;
}

template<typename Type>
void Random::get_many(this auto& self, Type* buf, size_t count) {
	for (size_t a = 0; a < count; ++a) {
		self.get_bytes((u8*)&buf[a], sizeof(Type));
	}
}

f64 Random::get_f64(this auto& self) {
	u64 hi = self.template get<u32>() & 0x001FFFFFull;
	u64 lo = self.template get<u32>();
	u64 x = (hi << 32) | lo;
	return (f64)x / 9007199254740992.0;
}

f64 Random::get_f64_range(this auto& self, f64 min, f64 max) {
	return self.get_f64() * (max - min) + min;
}