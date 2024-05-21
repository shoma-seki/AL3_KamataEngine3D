#pragma once

#include <stdio.h>
#define _USE_MATH_DEFINES
#include <assert.h>
#include <cmath>
#include <ImGuiManager.h>
#include "Vector3.h"
#include "Matrix4x4.h"

struct Vector3Array {
	float vector3[3];
};

//Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
//Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 inverse(const Matrix4x4& matrix);
//Matrix4x4 Transpose(const Matrix4x4& m);
//Matrix4x4 MakeIdentityMatrix();

//Matrix4x4 MakeTranslateMatrix(const Vector3Array& translate);
//Matrix4x4 MakeScaleMatrix(const Vector3Array& scale);
Matrix4x4 MakeRotateXMatrix(float radian);
Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
//Vector3Array Transform(const Vector3Array& point, const Matrix4x4& transformationMatrix);

//Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
//Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
//Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

//Vector3Array RenderingPipeline(const Vector3Array& local, const Matrix4x4& worldMatrix, const Camera3dData& camera);

//void DrawSphere(const Sphere& sphere, const Camera3dData& camera, uint32_t color, uint32_t subdivision);
//void DrawGrid(const Camera3dData& camera);
//void DrawLine(const Camera3dData& camera);