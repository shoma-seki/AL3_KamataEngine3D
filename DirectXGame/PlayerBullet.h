#pragma once
#include "Model.h"
#include "TextureManager.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cassert>
#include "Functions.h"

class PlayerBullet {
public:
	PlayerBullet() {}
	~PlayerBullet() {}

	void Initialize(Model* model, const Vector3& position, const Vector3& velocity_);
	void Update();
	void Draw(const ViewProjection& viewProjection);
	bool IsDead() const { return isDead_; }

private:
	WorldTransform worldTransform_{};
	Model* model_{};
	uint32_t bulletGH_{};
	Vector3 position_{};
	Vector3 velocity_{};
	static const int32_t kLifeTime = 60 * 5;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;
};
