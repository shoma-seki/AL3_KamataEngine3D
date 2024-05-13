#include "EnemyBullet.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	model_ = model;
	translate = position;
	velocity_ = velocity;
	worldTransform.Initialize();
	scale_ = {0.5f, 0.5f, 3.0f};
	bulletGH_ = TextureManager::Load("white1x1.png");
	rotate_.y = std::atan2(velocity.x, velocity.z);
	float velocityXZ = Length({velocity.x, 0, velocity.z});
	rotate_.x = std::atan2(-velocity.y, velocityXZ);
}

void EnemyBullet::Update() {
	translate = Add(translate, velocity_);
	worldTransform.UpdateMatrix(scale_, rotate_, translate);
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) { model_->Draw(worldTransform, viewProjection, bulletGH_); }
