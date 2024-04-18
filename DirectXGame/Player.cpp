#include "Player.h"

void Player::Initialize(Model* model, uint32_t GH_) {
	assert(model);
	model_ = model;
	playerGH_ = GH_;
	worldTransform_.Initialize();
}

void Player::Update() { worldTransform_.TransferMatrix(); }

void Player::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, playerGH_); }
