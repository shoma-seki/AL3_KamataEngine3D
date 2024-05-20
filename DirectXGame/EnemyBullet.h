#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Functions.h"
#include "TextureManager.h"
#include <math.h>

class EnemyBullet {
public:
	EnemyBullet(){};
	~EnemyBullet(){};

	void Initialize(Model* model, const Vector3& position, const Vector3& velocity_);
	void Update();
	void Draw(const ViewProjection& viewProjection);
	bool IsDead() const { return isDead_; };

	Vector3 GetWorldPosition();

	// 当たり判定
	void OnCollision();

	const float kRadius_ = 2;

private:
	Vector3 translate{};
	Vector3 velocity_ = {0, 0, -1};
	Vector3 scale_ = {1, 1, 1};
	Vector3 rotate_ = {0, 0, 0};
	Model* model_;
	WorldTransform worldTransform_{};
	uint32_t bulletGH_{};
	static const int32_t kLifeTime = 60 * 5;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;
};
