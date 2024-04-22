#pragma once
#include "Functions.h"
#include "Model.h"
#include "TextureManager.h"
#include "WorldTransform.h"

class Enemy {
public:
	Enemy() {}
	~Enemy() {}
	void Initialize(Model* model, uint32_t GH_);
	void Update();
	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransform{};
	Model* model_ = nullptr;
	uint32_t enemyGH_;

	// エネミー情報
	Vector3 translate_ = {0, 4, 10};
	Vector3 velocity_ = {0, 0, -0.1f};
};
