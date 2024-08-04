#include "Functions.h"

Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 result{};
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return result;
}

float Dot(const Vector3& v1, const Vector3& v2) {
	float result{};
	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return result;
}

float Length(const Vector3& v) {
	float result{};
	result = sqrtf((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return result;
}

float Length(const Vector3& v1, const Vector3& v2) {
	float result{};
	float subX = v1.x - v2.x;
	float subY = v1.y - v2.y;
	float subZ = v1.z - v2.z;
	result = sqrtf((subX * subX) + (subY * subY) + (subZ * subZ));
	return result;
}

Vector3 Normalize(const Vector3& v) {
	Vector3 result{};
	float length = Length(v);
	if (length != 0) {
		result.x = v.x / length;
		result.y = v.y / length;
		result.z = v.z / length;
	}
	return result;
}

Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return result;
}

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m) {
	Vector3 result{v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0], v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1], v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]};
	return result;
}

Vector3 Lerp(const Vector3& startV, const Vector3& endV, float t) {
	Vector3 result;
	result.x = (1.0f - t) * startV.x + t * endV.x;
	result.y = (1.0f - t) * startV.y + t * endV.y;
	result.z = (1.0f - t) * startV.z + t * endV.z;
	return result;
}

float EaseOutBack(float t) {
	const float c1 = 1.70158f;
	const float c3 = c1 + 1.0f;
	return 1.0f + c3 * std::powf(t - 1.0f, 3.0f) + c1 * std::powf(t - 1.0f, 2.0f);
}

bool isCollision(const Sphere& s1, const Sphere& s2) {
	if (Length(s1.center, s2.center) <= s1.radius + s2.radius) {
		return true;
	}
	return false;
}

bool isCollision(const Sphere& s1, const Vector3& v) {
	if (Length(s1.center, v) <= s1.radius) {
		return true;
	}
	return false;
}

void DrawSphere(const Sphere& sphere, unsigned int subdivision) {
	const unsigned int kSubdivision = subdivision;
	const float kLonEvery = float(2.0 * M_PI / kSubdivision); // phi
	const float kLatEvery = float(2.0 * M_PI / kSubdivision); // theta
	const float thetaD = float(M_PI) / float(kSubdivision);
	const float phiD = float(2.0 * M_PI) / float(kSubdivision);

	for (unsigned int latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = float(-M_PI / 2.0) + kLatEvery * float(latIndex);
		for (unsigned int lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = float(lonIndex) * kLonEvery;
			Vector3 worldA{};
			Vector3 worldB{};
			Vector3 worldC{};
			Vector3 screenA{};
			Vector3 screenB{};
			Vector3 screenC{};

			// ワールド座標系でのa,b,cを求める
			worldA.x = sphere.radius * (std::cos(lat) * cos(lon)) + sphere.center.x;
			worldA.y = sphere.radius * (std::sin(lat)) + sphere.center.y;
			worldA.z = sphere.radius * (std::cos(lat)) * sin(lon) + sphere.center.z;

			worldB.x = sphere.radius * (std::cos(lat + thetaD) * cos(lon)) + sphere.center.x;
			worldB.y = sphere.radius * (std::sin(lat + thetaD)) + sphere.center.y;
			worldB.z = sphere.radius * (std::cos(lat + thetaD) * sin(lon)) + sphere.center.z;

			worldC.x = sphere.radius * (std::cos(lat) * cos(lon + phiD)) + sphere.center.x;
			worldC.y = sphere.radius * (std::sin(lat)) + sphere.center.y;
			worldC.z = sphere.radius * (std::cos(lat) * sin(lon + phiD)) + sphere.center.z;

			// PrimitiveDrawer::GetInstance()->DrawLine3d(worldA, worldB, {1.0f, 1.0f, 1.0f, 1.0f});
			// PrimitiveDrawer::GetInstance()->DrawLine3d(worldA, worldC, {1.0f, 1.0f, 1.0f, 1.0f});

			//// ワールドマトリックス
			// Matrix4x4 aWorldMatrix = MakeAffineMatrix({1, 1, 1}, {0, 0, 0}, worldA);
			// Matrix4x4 bWorldMatrix = MakeAffineMatrix({1, 1, 1}, {0, 0, 0}, worldB);
			// Matrix4x4 cWorldMatrix = MakeAffineMatrix({1, 1, 1}, {0, 0, 0}, worldC);

			//// スクリーンに変換
			// screenA = RenderingPipeline({0, 0, 0}, aWorldMatrix, camera);
			// screenB = RenderingPipeline({0, 0, 0}, bWorldMatrix, camera);
			// screenC = RenderingPipeline({0, 0, 0}, cWorldMatrix, camera);

			// 線を引く
			/*Novice::DrawLine(int(screenA.v[0]), int(screenA.v[1]), int(screenB.v[0]), int(screenB.v[1]), color);
			Novice::DrawLine(int(screenA.v[0]), int(screenA.v[1]), int(screenC.v[0]), int(screenC.v[1]), color);*/
		}
	}
}
