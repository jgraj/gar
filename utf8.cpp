void UTF8_Iterator::create(this UTF8_Iterator& self, ctk::ar<const u8> target_str) {
	self.target_str = target_str;
	self.byte_index = 0;
	self.char_index = 0;
}

u32 UTF8_Iterator::next_codepoint(this UTF8_Iterator& self) {
	start:
	if (self.byte_index >= self.target_str.len) {
		return 0;
	}
	u8 byte = self.target_str[self.byte_index];
	self.byte_index += 1;
	u32 codepoint = 0;
	i32 bytes_to_read = 0;
	if (byte <= 0x7F) {
		codepoint = byte;
		bytes_to_read = 0;
	} else if ((byte & 0xE0) == 0xC0) {
		codepoint = byte & 0x1F;
		bytes_to_read = 1;
	} else if ((byte & 0xF0) == 0xE0) {
		codepoint = byte & 0x0F;
		bytes_to_read = 2;
	} else if ((byte & 0xF8) == 0xF0) {
		codepoint = byte & 0x07;
		bytes_to_read = 3;
	} else {
		self.byte_index += 1;
		goto start;
	}
	for (i32 a = 0; a < bytes_to_read; ++a) {
		if (self.byte_index >= self.target_str.len) {
			return 0;
		}
		byte = self.target_str[self.byte_index];
		if ((byte & 0xC0) != 0x80) {
			break;
		}
		self.byte_index += 1;
		codepoint = (codepoint << 6) | (byte & 0x3F);
	}
	self.char_index += 1;
	return codepoint;
}