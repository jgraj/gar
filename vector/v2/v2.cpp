struct v2i;
struct v2f;

#include "v2i.cpp"
#include "v2f.cpp"

constexpr v2f v2i::to_v2f() const {
	return v2f(this->x, this->y);
}

constexpr v2i v2f::to_v2i() const {
	return v2i((i32)this->x, (i32)this->y);
}