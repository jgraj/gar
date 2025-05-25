struct v3i;
struct v3f;

#include "v3i.cpp"
#include "v3f.cpp"

constexpr v3f v3i::to_v3f() const {
	return v3f(this->x, this->y, this->z);
}

constexpr v3i v3f::to_v3i() const {
	return v3i((i32)this->x, (i32)this->y, (i32)this->z);
}