#include "EnemyBullet.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position,const Vector3& velocity) {
	assert(model);
	model_ = model;
	translate = position;
	velocity_ = velocity;
	worldTransform.Initialize();
	bulletGH_ = TextureManager::Load("white1x1.png");
}

void EnemyBullet::Update() {
	translate = Add(translate, velocity_);
	worldTransform.UpdateMatrix({1, 1, 1}, {0, 0, 0}, translate);
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) { model_->Draw(worldTransform, viewProjection, bulletGH_); }
