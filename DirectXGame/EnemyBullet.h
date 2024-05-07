#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Functions.h"
#include "TextureManager.h"

class EnemyBullet {
public:
	EnemyBullet(){};
	~EnemyBullet(){};

	void Initialize(Model* model,const Vector3& position);
	void Update();
	void Draw(const ViewProjection& viewProjection);
	bool IsDead() const { return isDead_; };

private:
	Vector3 translate{};
	Vector3 velocity = {0, 0, -1};
	Model* model_;
	WorldTransform worldTransform{};
	uint32_t bulletGH_{};
	static const int32_t kLifeTime = 60 * 5;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;
};
