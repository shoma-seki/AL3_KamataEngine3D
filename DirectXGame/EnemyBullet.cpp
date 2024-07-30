#include "EnemyBullet.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	model_ = model;
	translate = position;
	velocity_ = velocity;
	worldTransform_.Initialize();
	scale_ = {1, 1, 1};
	bulletGH_ = TextureManager::Load("white1x1.png");
	rotate_.y = std::atan2(velocity.x, velocity.z);
	float velocityXZ = Length({velocity.x, 0, velocity.z});
	rotate_.x = std::atan2(-velocity.y, velocityXZ);

	objectColor_.Initialize();
	objectColor_.SetColor({0.882f, 0.227f, 0.176f, 1.0f});
	objectColor_.TransferMatrix();
}

void EnemyBullet::Update() {
	translate = Add(translate, velocity_);
	worldTransform_.UpdateMatrix(scale_, rotate_, translate);
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, &objectColor_); }

Vector3 EnemyBullet::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void EnemyBullet::OnCollision() { isDead_ = true; }
