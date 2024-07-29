#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	model_ = model;
	bulletGH_ = TextureManager::Load("block.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = {};
	position_ = position;
	velocity_ = velocity;

	objectColor_.Initialize();
	objectColor_.SetColor({0.851f, 0.741f, 0.184f, 1.0f});
	objectColor_.TransferMatrix();
}

void PlayerBullet::Update() {
	shotTime_++;

	position_ = Add(position_, velocity_ * speed_);
	worldTransform_.UpdateMatrix({1, 1, 1}, {0, 0, 0}, position_);
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, &objectColor_); }

Vector3 PlayerBullet::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void PlayerBullet::OnCollision() { isDead_ = true; }
