template <typename Type>
void Smooth<Type>::set(this auto& self, Type value) {
	if (self.changed(value)) {
		self.dirty = true;
	}
	self.value = value;
	self.target = value;
}

template <typename Type>
bool Smooth<Type>::changed(this const auto& self, Type new_value) {
	if constexpr (std::is_same_v<Type, f32>) {
		return f32_cmp(new_value, self.value, 0.0) == false;
	} else if constexpr (std::is_same_v<Type, f64>) {
		return f64_cmp(new_value, self.value, 0.0) == false;
	} else {
		return Type::cmp(new_value, self.value, 0.0) == false;
	}
}

template <typename Type>
bool Smooth<Type>::update(this auto& self, f64 rate, f64 delta_time) {
	Type new_value;
	if constexpr (std::is_same_v<Type, f32>) {
		new_value = f32_smooth_step(self.value, self.target, rate, delta_time);
	} else if constexpr (std::is_same_v<Type, f64>) {
		new_value = f64_smooth_step(self.value, self.target, rate, delta_time);
	} else {
		new_value = Type::smooth_step(self.value, self.target, rate, delta_time);
	}
	bool changed = self.dirty || self.changed(new_value);
	self.value = new_value;
	self.dirty = false;
	return changed;
}