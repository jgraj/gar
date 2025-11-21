struct v2i;
struct v2f;

#include "v2i.hpp"
#include "v2f.hpp"

constexpr v2f v2i::to_v2f(this const auto& self) {
	return v2f((f32)self.x, (f32)self.y);
}

constexpr v2i v2f::to_v2i(this const auto& self) {
	return v2i((i32)self.x, (i32)self.y);
}