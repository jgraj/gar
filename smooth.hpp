template <typename Type> struct Smooth {
	Type value;
	Type target;
	bool dirty;

	void set(this auto& self, Type value);
	bool changed(this const auto& self, Type new_value);
	bool update(this auto& self, f64 rate, f64 delta_time);
};