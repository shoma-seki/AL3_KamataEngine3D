#include "Enemy.h"

void Enemy::Initialize(Model* model, uint32_t GH_) {
	assert(model);
	model_ = model;
	enemyGH_ = GH_;
	worldTransform.Initialize();
}
void Enemy::Update() {
	translate_ = Add(translate_, velocity_);
	worldTransform.UpdateMatrix({1, 1, 1}, {0, 0, 0}, translate_);
}

void Enemy::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform, viewProjection, enemyGH_); }
