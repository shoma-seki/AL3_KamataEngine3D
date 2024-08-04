#pragma once
#define _USE_MATH_DEFINES
#include "Matrix4x4.h"
#include "PrimitiveDrawer.h"
#include "Struct.h"
#include "Vector3.h"
#include <assert.h>
#include <cmath>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Vector3 Add(const Vector3& v1, const Vector3& v2);
Vector3 Subtract(const Vector3& v1, const Vector3& v2);
Vector3 Multiply(float scalar, const Vector3& v);
float Dot(const Vector3& v1, const Vector3& v2);
float Length(const Vector3& v);
float Length(const Vector3& v1, const Vector3& v2);
Vector3 Normalize(const Vector3& v);
Vector3 Cross(const Vector3& v1, const Vector3& v2);
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

Vector3 Lerp(const Vector3& startV, const Vector3& endV, float t);
float EaseOutBack(float t);

bool isCollision(const Sphere& s1, const Sphere& s2);
bool isCollision(const Sphere& s1, const Vector3& v);

void DrawSphere(const Sphere& sphere, unsigned int subdivision);