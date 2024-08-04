#pragma once
#include "Functions.h"
#include "Model.h"
#include "TextureManager.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <algorithm>
#include <cassert>

class Explosion {
public:
	Explosion() {}
	~Explosion() {}

	void Initialize(Model* model, const Vector3& position, int reflectionCount);
	void Update();
	void Draw(const ViewProjection& viewProjection);

	bool IsDead() { return isDead_; }

	Vector3 GetWorldPosition() {
		// ワールド座標を入れる変数
		Vector3 worldPos;
		worldPos.x = worldTransform_.matWorld_.m[3][0];
		worldPos.y = worldTransform_.matWorld_.m[3][1];
		worldPos.z = worldTransform_.matWorld_.m[3][2];
		return worldPos;
	}

	int reflectionCount_;


private:
	WorldTransform worldTransform_{};
	Model* model_{};
	Vector3 position_{};
	Vector3 scale_{};
	const float kLifeTime = 10.0f;
	float deathTimer_ = 0.0f;
	float t;
	float easedT;

	bool isDead_ = false;

	ObjectColor objectColor_;
};
