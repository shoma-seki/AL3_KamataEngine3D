#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;

	Vector3& operator*=(float s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	Vector3& operator-=(const Vector3& vec) {
		this->x -= vec.x;
		this->y -= vec.y;
		this->z -= vec.z;
		return *this;
	}
	Vector3& operator+=(const Vector3& vec) {
		this->x += vec.x;
		this->y += vec.y;
		this->z += vec.z;
		return *this;
	}
	Vector3& operator/=(float s) {
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}
	bool operator==(const Vector3& vec) {
		if (this->x == vec.x && this->y == vec.y && this->z == vec.z) {
			return true;
		}
		return false;
	}

	bool operator!=(const Vector3& vec) {
		if (this->x != vec.x || this->y != vec.y || this->z != vec.z) {
			return true;
		}
		return false;
	}

	Vector3 operator+(const Vector3& v2) {
		this->x += v2.x;
		this->y += v2.y;
		this->z += v2.z;
		return Vector3(this->x, this->y, this->z);
	}
	Vector3 operator-(const Vector3& v2) {
		this->x -= v2.x;
		this->y -= v2.y;
		this->z -= v2.z;
		return Vector3(this->x, this->y, this->z);
	}
	Vector3 operator*(float s) {
		this->x *= s;
		this->y *= s;
		this->z *= s;
		return Vector3(this->x, this->y, this->z);
	}
	Vector3 operator/(float s) {
		this->x /= s;
		this->y /= s;
		this->z /= s;
	}
};
