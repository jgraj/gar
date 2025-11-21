v3f rgb_to_hsl(v3f c) {
	float max = c.x > c.y ? (c.x > c.z ? c.x : c.z) : (c.y > c.z ? c.y : c.z);
	float min = c.x < c.y ? (c.x < c.z ? c.x : c.z) : (c.y < c.z ? c.y : c.z);
	float h, s, l = (max + min) / 2.0f;

	if (max == min) {
		h = s = 0.0f; // achromatic
	} else {
		float d = max - min;
		s = l > 0.5f ? d / (2.0f - max - min) : d / (max + min);

		if (max == c.x)
			h = (c.y - c.z) / d + (c.y < c.z ? 6.0f : 0.0f);
		else if (max == c.y)
			h = (c.z - c.x) / d + 2.0f;
		else
			h = (c.x - c.y) / d + 4.0f;

		h /= 6.0f;
	}
	return v3f(h, s, l);
}

float hue2rgb(float p, float q, float t) {
	if (t < 0.0f) t += 1.0f;
	if (t > 1.0f) t -= 1.0f;
	if (t < 1.0f/6.0f) return p + (q - p) * 6.0f * t;
	if (t < 1.0f/2.0f) return q;
	if (t < 2.0f/3.0f) return p + (q - p) * (2.0f/3.0f - t) * 6.0f;
	return p;
}

v3f hsl_to_rgb(v3f hsl) {
	v3f out;
	if (hsl.y == 0.0f) {
		out.x = out.y = out.z = hsl.z; // achromatic
	} else {
		float q = hsl.z < 0.5f ? hsl.z * (1.0f + hsl.y) : hsl.z + hsl.y - hsl.z * hsl.y;
		float p = 2.0f * hsl.z - q;
		out.x = hue2rgb(p, q, hsl.x + 1.0f/3.0f);
		out.y = hue2rgb(p, q, hsl.x);
		out.z = hue2rgb(p, q, hsl.x - 1.0f/3.0f);
	}
	return out;
}

v3f rgb_change_saturation(v3f color, f32 saturation_change) {
	v3f hsl_color = rgb_to_hsl(color);
	hsl_color[1] = f32_clamp(hsl_color[1] + saturation_change, 0.0f, 1.0f);
	return hsl_to_rgb(hsl_color);
}

v3f rgb_change_value(v3f color, f32 value_change) {
	v3f hsl_color = rgb_to_hsl(color);
	hsl_color[2] = f32_clamp(hsl_color[2] + value_change, 0.0f, 1.0f);
	return hsl_to_rgb(hsl_color);
}