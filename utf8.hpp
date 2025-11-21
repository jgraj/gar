struct UTF8_Iterator {
	ctk::ar<const u8> target_str;
	size_t byte_index;
	size_t char_index;

	void create(this UTF8_Iterator& self, ctk::ar<const u8> target_str);
	u32 next_codepoint(this UTF8_Iterator& self);
};