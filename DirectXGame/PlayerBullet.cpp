#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position) {
	assert(model);
	model_ = model;
	bulletGH_ = TextureManager::Load("block.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = {};
	position_ = position;
}

void PlayerBullet::Update() { worldTransform_.UpdateMatrix({1, 1, 1}, {0, 0, 0}, position_); }

void PlayerBullet::Draw(const ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, bulletGH_); }
