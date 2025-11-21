f64 f64_parse(ar<const u8> str) {
	size_t i = 0;
	bool negative = false;
	// sign
	if (i < str.len && str[i] == '-') {
		negative = true;
		i++;
	}
	// integer part
	f64 value = 0.0;
	bool has_integer = false;
	while (i < str.len && str[i] >= '0' && str[i] <= '9') {
		has_integer = true;
		value = value * 10.0 + (str[i] - '0');
		i++;
	}
	// fractional part
	if (i < str.len && str[i] == '.') {
		i++;
		f64 fraction = 0.0;
		f64 divisor = 1.0;
		bool has_fraction = false;
		while (i < str.len && str[i] >= '0' && str[i] <= '9') {
			has_fraction = true;
			fraction = fraction * 10.0 + (str[i] - '0');
			divisor *= 10.0;
			i++;
		}
		if (has_fraction) {
			value += fraction / divisor;
		}
	}
	// exponent part
	if (i < str.len && (str[i] == 'e' || str[i] == 'E')) {
		i++;
		bool exp_negative = false;
		if (i < str.len && (str[i] == '+' || str[i] == '-')) {
			exp_negative = (str[i] == '-');
			i++;
		}
		u64 exponent = 0;
		bool has_exponent = false;
		while (i < str.len && str[i] >= '0' && str[i] <= '9') {
			has_exponent = true;
			exponent = exponent * 10 + (str[i] - '0');
			i++;
		}
		if (has_exponent) {
			f64 pow10 = 1.0;
			f64 base = 10.0;
			u64 exp = exponent;
			// fast exponentiation
			while (exp > 0) {
				if (exp & 1) {
					pow10 *= base;
				}
				base *= base;
				exp >>= 1;
			}
			if (exp_negative) {
				value /= pow10;
			} else {
				value *= pow10;
			}
		}
	}

	if (i != str.len || (!has_integer && value == 0.0)) {
		ctk::panic("f64_parse failed");
	}

	return negative ? -value : value;
}

f64 f64_min(f64 a, f64 b) {
	return a <= b ? a : b;
}

f64 f64_max(f64 a, f64 b) {
	return a >= b ? a : b;
}

f64 f64_round(f64 a) {
	return std::round(a);
}

f64 f64_clamp(f64 a, f64 min, f64 max) {
	return f64_min(f64_max(a, min), max);
}

bool f64_cmp(f64 a, f64 b, f64 epsilon) {
	return std::fabs(a - b) <= epsilon;
}

f64 f64_lerp(f64 a, f64 b, f64 t) {
	return a + (b - a) * t;
}

f64 f64_smooth_step(f64 a, f64 b, f64 t, f64 dt) {
	f64 ht = -t / std::log2(0.001);
	return b + (a - b) * std::exp2(-dt / ht);
}

f64 f64_smooth_damp(f64 a, f64 b, f64 smoothing, f64 delta_time) {
	f64 t = 1.0 - std::exp(-smoothing * delta_time);
	return f64_lerp(a, b, t);
}