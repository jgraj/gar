struct v3i;
struct v3f;

#include "v3i.hpp"
#include "v3f.hpp"

constexpr v3f v3i::to_v3f(this const auto& self) {
	return v3f(self.x, self.y, self.z);
}

constexpr v3i v3f::to_v3i(this const auto& self) {
	return v3i((i32)self.x, (i32)self.y, (i32)self.z);
}