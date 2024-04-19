#include "MatrixFunc.h"
//
//Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
//	Matrix4x4 result{};
//	for (int i = 0; i < 4; ++i) {
//		for (int j = 0; j < 4; ++j) {
//			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
//		}
//	}
//	return result;
//}
//
//Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
//	Matrix4x4 result{};
//	for (int i = 0; i < 4; ++i) {
//		for (int j = 0; j < 4; ++j) {
//			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
//		}
//	}
//	return result;
//}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0.0f;
			for (int k = 0; k < 4; ++k) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	return result;
}

//Matrix4x4 inverse(const Matrix4x4& m) {
//	Matrix4x4 a = m;
//	Matrix4x4 result{};
//
//	float buf2 = 0.0f;
//	int n = 4;
//	int i = 0;
//	int j = 0;
//	int k = 0;
//
//
//	for (i = 0; i < n; i++) {
//		for (j = 0; j < n; j++) {
//			if (i == j) {
//				result.m[i][j] = 1.0f;
//			}
//			else {
//				result.m[i][j] = 0.0f;
//			}
//		}
//	}
//
//	for (i = 0; i < n; i++) {
//		buf2 = 1 / a.m[i][i];
//		for (j = 0; j < n; j++) {
//			a.m[i][j] *= buf2;
//			result.m[i][j] *= buf2;
//		}
//		for (j = 0; j < n; j++) {
//			if (i != j) {
//				buf2 = a.m[j][i];
//				for (k = 0; k < n; k++) {
//					a.m[j][k] -= a.m[i][k] * buf2;
//					result.m[j][k] -= result.m[i][k] * buf2;
//				}
//			}
//		}
//	}
//
//	return result;
//}
//Matrix4x4 Transpose(const Matrix4x4& m) {
//	Matrix4x4 result{};
//
//	for (int i = 0; i < 4; ++i) {
//		for (int j = 0; j < 4; ++j) {
//			result.m[i][j] = m.m[j][i];
//		}
//	}
//
//	return result;
//}
//
//Matrix4x4 MakeIdentityMatrix() {
//	Matrix4x4 result{};
//
//	for (int i = 0; i < 4; ++i) {
//		for (int j = 0; j < 4; ++j) {
//			if (i == j) {
//				result.m[i][j] = 1.0f;
//			}
//		}
//	}
//
//	return result;
//}
//
//Matrix4x4 MakeTranslateMatrix(const Vector3Array& translate) {
//	Matrix4x4 result = {
//		1.0f, 0.0f, 0.0f, 0.0f,
//		0.0f, 1.0f, 0.0f, 0.0f,
//		0.0f, 0.0f, 1.0f, 0.0f,
//		translate.vector3[0], translate.vector3[1], translate.vector3[2], 1.0f
//	};
//
//	return result;
//}
//
//Matrix4x4 MakeScaleMatrix(const Vector3Array& scale) {
//	Matrix4x4 result = {
//		scale.vector3[0], 0.0f, 0.0f, 0.0f,
//		0.0f, scale.vector3[1], 0.0f, 0.0f,
//		0.0f, 0.0f, scale.vector3[2], 0.0f,
//		0.0f, 0.0f, 0.0f, 1.0f
//	};
//
//	return result;
//}
//
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result{};

	result = {
				1,0,0,0,
				0,std::cos(radian),std::sin(radian),0,
				0,-std::sin(radian),std::cos(radian),0,
				0,0,0,1
	};

	return result;
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result{};

	result = {
				std::cos(radian),0,-std::sin(radian),0,
				0,1,0,0,
				std::sin(radian),0,std::cos(radian),0,
				0,0,0,1
	};

	return result;
}

Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result{};

	result = {
				std::cos(radian),std::sin(radian),0,0,
				-std::sin(radian),std::cos(radian),0,0,
				0,0,1,0,
				0,0,0,1
	};

	return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result{};
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.x);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.x);
	Matrix4x4 rotateXYZ = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	Vector3Array scaleA = {scale.x, scale.y, scale.z};
	Vector3Array rotateA = {rotate.x, rotate.y, rotate.z};
	Vector3Array translateA = {translate.x, translate.y, translate.z};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			if (j == 3) {
				result.m[i][j] = 0.0f;
			}
			else {
				result.m[i][j] = scaleA.vector3[i] * rotateXYZ.m[i][j];
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		result.m[3][i] = translateA.vector3[i];
	}
	result.m[3][3] = 1.0f;

	return result;
}

//Vector3Array Transform(const Vector3Array& vector, const Matrix4x4& m) {
//	Vector3Array result{};
//	for (int i = 0; i < 3; i++) {
//		result.vector3[i] = vector.vector3[0] * m.m[0][i] +
//			vector.vector3[1] * m.m[1][i] + vector.vector3[2] * m.m[2][i] + m.m[3][i];
//	}
//	float w = vector.vector3[0] * m.m[0][3] +
//		vector.vector3[1] * m.m[1][3] + vector.vector3[2] * m.m[2][3] + m.m[3][3];
//	assert(w != 0.0f);
//	for (int i = 0; i < 3; i++) {
//		result.vector3[i] /= w;
//	}
//	return result;
//}
//
//Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
//	Matrix4x4 result{};
//
//	result.m[0][0] = (1.0f / aspectRatio) * (1.0f / std::tan(fovY / 2));
//	result.m[0][1] = 0.0f;
//	result.m[0][2] = 0.0f;
//	result.m[0][3] = 0.0f;
//	result.m[1][0] = 0.0f;
//	result.m[1][1] = 1.0f / std::tan(fovY / 2);
//	result.m[1][2] = 0.0f;
//	result.m[1][3] = 0.0f;
//	result.m[2][0] = 0.0f;
//	result.m[2][1] = 0.0f;
//	result.m[2][2] = farClip / (farClip - nearClip);
//	result.m[2][3] = 1.0f;
//	result.m[3][0] = 0.0f;
//	result.m[3][1] = 0.0f;
//	result.m[3][2] = -nearClip * farClip / (farClip - nearClip);
//	result.m[3][3] = 0.0f;
//
//	return result;
//}
//
//Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
//	Matrix4x4 result{};
//
//	result.m[0][0] = 2.0f / (right - left);
//	result.m[0][1] = 0.0f;
//	result.m[0][2] = 0.0f;
//	result.m[0][3] = 0.0f;
//	result.m[1][0] = 0.0f;
//	result.m[1][1] = 2.0f / (top - bottom);
//	result.m[1][2] = 0.0f;
//	result.m[1][3] = 0.0f;
//	result.m[2][0] = 0.0f;
//	result.m[2][1] = 0.0f;
//	result.m[2][2] = 1.0f / (farClip - nearClip);
//	result.m[2][3] = 0.0f;
//	result.m[3][0] = (left + right) / (left - right);
//	result.m[3][1] = (top + bottom) / (bottom - top);
//	result.m[3][2] = nearClip / (nearClip - farClip);
//	result.m[3][3] = 1.0f;
//
//	return result;
//}
//
//Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
//	Matrix4x4 result{};
//
//	result.m[0][0] = width / 2.0f;
//	result.m[0][1] = 0.0f;
//	result.m[0][2] = 0.0f;
//	result.m[0][3] = 0.0f;
//	result.m[1][0] = 0.0f;
//	result.m[1][1] = -(height / 2.0f);
//	result.m[1][2] = 0.0f;
//	result.m[1][3] = 0.0f;
//	result.m[2][0] = 0.0f;
//	result.m[2][1] = 0.0f;
//	result.m[2][2] = maxDepth - minDepth;
//	result.m[2][3] = 0.0f;
//	result.m[3][0] = left + width / 2.0f;
//	result.m[3][1] = top + height / 2.0f;
//	result.m[3][2] = minDepth;
//	result.m[3][3] = 1.0f;
//
//	return result;
//}
//
//Vector3Array RenderingPipeline(const Vector3Array& local, const Matrix4x4& worldMatrix, const Camera3dData& camera) {
//	Vector3Array screen{};
//	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(camera.viewMatrix, camera.projectionMatrix));
//	Vector3Array ndc = Transform(local, worldViewProjectionMatrix);
//	screen = Transform(ndc, camera.viewportMatrix);
//	return screen;
//}
//
//void DrawSphere(const Sphere& sphere, const Camera3dData& camera, uint32_t color, uint32_t subdivision) {
//	const uint32_t kSubdivision = subdivision;
//	const float kLonEvery = float(2.0 * M_PI / kSubdivision);//phi
//	const float kLatEvery = float(2.0 * M_PI / kSubdivision);//theta
//	const float thetaD = float(M_PI) / float(kSubdivision);
//	const float phiD = float(2.0 * M_PI) / float(kSubdivision);
//
//	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
//		float lat = float(-M_PI / 2.0) + kLatEvery * float(latIndex);
//		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
//			float lon = float(lonIndex) * kLonEvery;
//			Vector3Array worldA{};
//			Vector3Array worldB{};
//			Vector3Array worldC{};
//			Vector3Array screenA{};
//			Vector3Array screenB{};
//			Vector3Array screenC{};
//
//			//ワールド座標系でのa,b,cを求める
//			worldA.vector3[0] = sphere.radius * (std::cos(lat) * cos(lon)) + sphere.center.vector3[0];
//			worldA.vector3[1] = sphere.radius * (std::sin(lat)) + sphere.center.vector3[1];
//			worldA.vector3[2] = sphere.radius * (std::cos(lat)) * sin(lon) + sphere.center.vector3[2];
//
//			worldB.vector3[0] = sphere.radius * (std::cos(lat + thetaD) * cos(lon)) + sphere.center.vector3[0];
//			worldB.vector3[1] = sphere.radius * (std::sin(lat + thetaD)) + sphere.center.vector3[1];
//			worldB.vector3[2] = sphere.radius * (std::cos(lat + thetaD) * sin(lon)) + sphere.center.vector3[2];
//
//			worldC.vector3[0] = sphere.radius * (std::cos(lat) * cos(lon + phiD)) + sphere.center.vector3[0];
//			worldC.vector3[1] = sphere.radius * (std::sin(lat)) + sphere.center.vector3[1];
//			worldC.vector3[2] = sphere.radius * (std::cos(lat) * sin(lon + phiD)) + sphere.center.vector3[2];
//
//			//ワールドマトリックス
//			Matrix4x4 aWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, worldA);
//			Matrix4x4 bWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, worldB);
//			Matrix4x4 cWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, worldC);
//
//			//スクリーンに変換
//			screenA = RenderingPipeline({ 0,0,0 }, aWorldMatrix, camera);
//			screenB = RenderingPipeline({ 0,0,0 }, bWorldMatrix, camera);
//			screenC = RenderingPipeline({ 0,0,0 }, cWorldMatrix, camera);
//
//			//線を引く
//			Novice::DrawLine(int(screenA.vector3[0]), int(screenA.vector3[1]), int(screenB.vector3[0]), int(screenB.vector3[1]), color);
//			Novice::DrawLine(int(screenA.vector3[0]), int(screenA.vector3[1]), int(screenC.vector3[0]), int(screenC.vector3[1]), color);
//		}
//	}
//}
//
//void DrawGrid(const Camera3dData& camera) {
//	const float kGridHalfWidth = 2.0f;
//	const uint32_t kSubdivision = 10;
//	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);
//
//	Vector3Array lineStartWorld = {};
//	Vector3Array lineEndWorld = {};
//	Matrix4x4 lineWorldMatrix = {};
//	Vector3Array lineStartScreen = {};
//	Vector3Array lineEndScreen = {};
//
//	static Vector3Array translate = {};
//
//	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
//		lineStartWorld.vector3[0] = xIndex * (kGridHalfWidth * 0.2f);
//		lineStartWorld.vector3[2] = 0.0f;
//		lineEndWorld.vector3[0] = lineStartWorld.vector3[0];
//		lineEndWorld.vector3[2] = kGridEvery * float(kSubdivision);
//
//		lineStartWorld.vector3[0] -= kGridEvery * float(kSubdivision / 2);
//		lineStartWorld.vector3[2] -= kGridEvery * float(kSubdivision / 2);
//		lineEndWorld.vector3[0] -= kGridEvery * float(kSubdivision / 2);
//		lineEndWorld.vector3[2] -= kGridEvery * float(kSubdivision / 2);
//
//		lineWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, translate);
//		lineStartScreen = RenderingPipeline(lineStartWorld, lineWorldMatrix, camera);
//		lineEndScreen = RenderingPipeline(lineEndWorld, lineWorldMatrix, camera);
//
//		if (xIndex != kSubdivision / 2) {
//			Novice::DrawLine(int(lineStartScreen.vector3[0]), int(lineStartScreen.vector3[1]),
//				int(lineEndScreen.vector3[0]), int(lineEndScreen.vector3[1]),
//				0xAAAAAAFF);
//		}
//		else {
//			Novice::DrawLine(int(lineStartScreen.vector3[0]), int(lineStartScreen.vector3[1]),
//				int(lineEndScreen.vector3[0]), int(lineEndScreen.vector3[1]),
//				0x111111FF);
//		}
//	}
//
//	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
//		lineStartWorld.vector3[0] = 0.0f;
//		lineStartWorld.vector3[2] = zIndex * (kGridHalfWidth * 0.2f);
//		lineEndWorld.vector3[0] = kGridEvery * float(kSubdivision);
//		lineEndWorld.vector3[2] = lineStartWorld.vector3[2];
//
//		lineStartWorld.vector3[0] -= kGridEvery * float(kSubdivision / 2);
//		lineStartWorld.vector3[2] -= kGridEvery * float(kSubdivision / 2);
//		lineEndWorld.vector3[0] -= kGridEvery * float(kSubdivision / 2);
//		lineEndWorld.vector3[2] -= kGridEvery * float(kSubdivision / 2);
//
//		lineWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, translate);
//		lineStartScreen = RenderingPipeline(lineStartWorld, lineWorldMatrix, camera);
//		lineEndScreen = RenderingPipeline(lineEndWorld, lineWorldMatrix, camera);
//
//		if (zIndex != kSubdivision / 2) {
//			Novice::DrawLine(int(lineStartScreen.vector3[0]), int(lineStartScreen.vector3[1]),
//				int(lineEndScreen.vector3[0]), int(lineEndScreen.vector3[1]),
//				0xAAAAAAFF);
//		}
//		else {
//			Novice::DrawLine(int(lineStartScreen.vector3[0]), int(lineStartScreen.vector3[1]),
//				int(lineEndScreen.vector3[0]), int(lineEndScreen.vector3[1]),
//				0x111111FF);
//		}
//	}
//
//	ImGui::Begin("Grid");
//
//	ImGui::DragFloat3("translate", translate.vector3, 0.1f, -100, 100);
//
//	ImGui::End();
//}
//
//void DrawLine(const Camera3dData& camera) {
//	Vector3Array lineStartWorld = {};
//	Vector3Array lineEndWorld = {};
//	Matrix4x4 lineWorldMatrix = {};
//	Vector3Array lineStartScreen = {};
//	Vector3Array lineEndScreen = {};
//
//	lineWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, { 0.0f,0.0f,0.0f });
//
//	lineStartWorld.vector3[0] = -100;
//	lineEndWorld.vector3[0] = 100;
//
//	lineStartScreen = RenderingPipeline(lineStartWorld, lineWorldMatrix, camera);
//	lineEndScreen = RenderingPipeline(lineEndWorld, lineWorldMatrix, camera);
//	Novice::DrawLine(int(lineStartScreen.vector3[0]), int(lineStartScreen.vector3[1]),
//		int(lineEndScreen.vector3[0]), int(lineEndScreen.vector3[1]),
//		RED);
//
//	lineStartWorld.vector3[0] = 0;
//	lineEndWorld.vector3[0] = 0;
//	lineStartWorld.vector3[1] = -100;
//	lineEndWorld.vector3[1] = 100;
//
//	lineStartScreen = RenderingPipeline(lineStartWorld, lineWorldMatrix, camera);
//	lineEndScreen = RenderingPipeline(lineEndWorld, lineWorldMatrix, camera);
//	Novice::DrawLine(int(lineStartScreen.vector3[0]), int(lineStartScreen.vector3[1]),
//		int(lineEndScreen.vector3[0]), int(lineEndScreen.vector3[1]),
//		RED);
//
//	lineStartWorld.vector3[0] = 0;
//	lineEndWorld.vector3[0] = 0;
//	lineStartWorld.vector3[1] = 0;
//	lineEndWorld.vector3[1] = 0;
//	lineStartWorld.vector3[2] = -100;
//	lineEndWorld.vector3[2] = 100;
//
//	lineStartScreen = RenderingPipeline(lineStartWorld, lineWorldMatrix, camera);
//	lineEndScreen = RenderingPipeline(lineEndWorld, lineWorldMatrix, camera);
//	Novice::DrawLine(int(lineStartScreen.vector3[0]), int(lineStartScreen.vector3[1]),
//		int(lineEndScreen.vector3[0]), int(lineEndScreen.vector3[1]),
//		RED);
//}
