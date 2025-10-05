#ifndef math_h
#define math_h

#include <math.h>
#include <iostream>

#define M_PI 3.14159265358979323846f
#define M_RADPI	57.295779513082f
#define M_PI_F ((float)(M_PI))
#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))
#define DEG2RAD(x) ((float)(x) * (float)(M_PI_F / 180.f))
#define atan2(a, b) ((float)atan2((double)(a), (double)(b)))

namespace engine {

	struct matrix_4x4_t {
		union {
			struct {
				float        _11, _12, _13, _14;
				float        _21, _22, _23, _24;
				float        _31, _32, _33, _34;
				float        _41, _42, _43, _44;

			}; float m[4][4];
		};
	};

	struct matrix_3x4_t {
		float _11, _12, _13, _14;
		float _21, _22, _23, _24;
		float _31, _32, _33, _34;
	};

	class vec4_t {
	public:
		vec4_t() : x(0.f), y(0.f), z(0.f), w(0.f) {}
		vec4_t(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
		~vec4_t() {}

		float x, y, z, w;
	};

	class vec3_t {
	public:
		vec3_t() : x(0.f), y(0.f), z(0.f) {}
		vec3_t(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
		~vec3_t() {}

		float Dot(vec3_t v) const {
			return x * v.x + y * v.y + z * v.z;
		}

		float Distance(vec3_t v) const {
			return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
		}

		vec3_t abs() const {
			return vec3_t(std::abs(x), std::abs(y), std::abs(z));
		}

		float Length() const {
			float ls = x * x + y * y + z * z;
			return sqrt(ls);
		}

		void clamp() {
			if (x > 75.f) {
				x = 75.f;
			}
			else if (x < -75.f) {
				x = -75.f;
			}

			if (z < -180) {
				z += 360.0f;
			}
			else if (z > 180) {
				z -= 360.0f;
			}

			y = 0.f;
		}

		vec4_t Quaternion() const {
			double heading = DEG2RAD(x);
			double attitude = DEG2RAD(y);
			double bank = DEG2RAD(z);

			double c1 = cos(heading / 2);
			double s1 = sin(heading / 2);
			double c2 = cos(attitude / 2);
			double s2 = sin(attitude / 2);
			double c3 = cos(bank / 2);
			double s3 = sin(bank / 2);
			double c1c2 = c1 * c2;
			double s1s2 = s1 * s2;

			vec4_t Quat;
			Quat.w = c1c2 * c3 - s1s2 * s3;
			Quat.x = c1c2 * s3 + s1s2 * c3;
			Quat.y = s1 * c2 * c3 + c1 * s2 * s3;
			Quat.z = c1 * s2 * c3 - s1 * c2 * s3;

			vec4_t Quat2;
			Quat2 = { Quat.y, Quat.z, (Quat.x * -1), Quat.w };

			return Quat2;
		}

		bool empty() const {
			return (x == 0.f && y == 0.f && z == 0.f);
		}

		bool operator==(const vec3_t& in) const {
			return (x == in.x && y == in.y && z == in.z);
		}

		bool operator!=(const vec3_t& in) const {
			return (x != in.x || y != in.y || z != in.z);
		}

		vec3_t operator+(vec3_t v) {
			return vec3_t(x + v.x, y + v.y, z + v.z);
		}

		vec3_t operator-(vec3_t v) {
			return vec3_t(x - v.x, y - v.y, z - v.z);
		}

		vec3_t operator*(float number) const {
			return vec3_t(x * number, y * number, z * number);
		}

		vec3_t& operator/(float fl) {
			x / fl;
			y / fl;
			z / fl;
			return *this;
		}

		vec3_t& operator/=(float fl) {
			x /= fl;
			y /= fl;
			z /= fl;
			return *this;
		}

		vec3_t& operator+=(const vec3_t& v) {
			x += v.x;
			y += v.y;
			z += v.z;
			return *this;
		}

		vec3_t& operator-=(const vec3_t& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			return *this;
		}

		float x, y, z;
	};

	class vec2_t {
	public:
		vec2_t() : x(0.f), y(0.f) {}
		vec2_t(float _x, float _y) : x(_x), y(_y) {}
		~vec2_t() {}

		float Distance(vec2_t v) const {
			return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0)));
		}

		bool operator==(vec2_t& in) {
			return (this->x == in.x && this->y == in.y);
		}

		vec2_t operator+(vec2_t v) {
			return vec2_t(x + v.x, y + v.y);
		}

		vec2_t operator-(vec2_t v) {
			return vec2_t(x - v.x, y - v.y);
		}

		vec2_t operator+=(vec2_t v) {
			return vec2_t(x += v.x, y += v.y);
		}

		vec2_t operator/=(vec2_t v) {
			return vec2_t(x /= v.x, y /= v.y);
		}

		bool empty() const {
			return (x == 0.f && y == 0.f);
		}

		vec2_t& operator/(float fl) {
			x / fl;
			y / fl;
			return *this;
		}

		float x, y;
	};
}

#endif