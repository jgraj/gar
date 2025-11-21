u32 Random::ChaCha20::rotl32(u32 var, u32 hops) {
	return (var << hops) | (var >> (32 - hops));
}

void Random::ChaCha20::qr(u32* a, u32* b, u32* c, u32* d) {
	*a += *b;
	*d ^= *a;
	*d = rotl32(*d, 16);
	*c += *d;
	*b ^= *c;
	*b = rotl32(*b, 12);
	*a += *b;
	*d ^= *a;
	*d = rotl32(*d, 8);
	*c += *d;
	*b ^= *c;
	*b = rotl32(*b, 7);
}

void Random::ChaCha20::block(const u32 in[16], u32 out[16]) {
	std::memcpy(out, in, 64);
	for (size_t a = 0; a < 10; ++a) { // 20 rounds, 2 per loop
		// column round
		qr(&out[0], &out[4], &out[ 8], &out[12]);
		qr(&out[1], &out[5], &out[ 9], &out[13]);
		qr(&out[2], &out[6], &out[10], &out[14]);
		qr(&out[3], &out[7], &out[11], &out[15]);
		// diagonal round
		qr(&out[0], &out[5], &out[10], &out[15]);
		qr(&out[1], &out[6], &out[11], &out[12]);
		qr(&out[2], &out[7], &out[ 8], &out[13]);
		qr(&out[3], &out[4], &out[ 9], &out[14]);
	}
	for (size_t a = 0; a < 16; ++a) {
		out[a] += in[a];
	}
}

u32 Random::load32_le(const u8* src) {
	return ((u32)src[0]) | ((u32)src[1] <<  8) | ((u32)src[2] << 16) | ((u32)src[3] << 24);
}

void Random::store32_le(u8* dst, u32 value) {
	dst[0] = (u8)value;
	dst[1] = (u8)(value >> 8);
	dst[2] = (u8)(value >> 16);
	dst[3] = (u8)(value >> 24);
}

bool Random::os_fill_random(void* dst, size_t size) {
	#ifdef CBS_WIN32
		return ::BCryptGenRandom(nullptr, (PUCHAR)dst, (ULONG)size, BCRYPT_USE_SYSTEM_PREFERRED_RNG) != 0;
	#endif
	#ifdef CBS_LINUX
		size_t off = 0;
		while (off < size) {
			ssize_t r = ::getrandom((u8*)dst + off, size - off, 0);
			if (r < 0) {
				if (errno == EINTR) {
					continue;
				}
				return true;
			}
			off += (size_t)r;
		}
		return 0;
	#endif
}