#pragma once
#include "Functions.h"
#include "Model.h"
#include "TextureManager.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cassert>

class PlayerBullet {
public:
	PlayerBullet() {}
	~PlayerBullet() {}

	void Initialize(Model* model, const Vector3& position, const Vector3& velocity_);
	void Update();
	void Draw(const ViewProjection& viewProjection);
	bool IsDead() const { return isDead_; }

	void DirectionInverce() {
		if (shotTime_ > 10) {
			velocity_ *= -1;
			deathTimer_ = kLifeTime;
			reflectionCount_++;
			if (speed_ < 1.005f) {
				speed_ += 0.001f;
			}
		}
	}

	Vector3 GetWorldPosition();
	int GetShotTime() { return shotTime_; }
	int GetReflectionCount() { return reflectionCount_; }

	// 当たり判定
	void OnCollision();

	Vector3 GetDirection() { return Normalize(velocity_); }

	const float kRadius_ = 2;

	int CollosionTime;

	int onCollisionPTime = 0;
	int onCollisionATime = 0;
	bool onCollisionEnter = false;

private:
	WorldTransform worldTransform_{};
	Model* model_{};
	uint32_t bulletGH_{};
	Vector3 position_{};
	Vector3 velocity_{};
	float speed_ = 1.0f;
	static const int32_t kLifeTime = 60 * 2;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;

	int shotTime_ = 0;

	ObjectColor objectColor_;

	int reflectionCount_;
};
