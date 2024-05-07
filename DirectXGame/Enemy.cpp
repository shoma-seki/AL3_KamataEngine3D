#include "Enemy.h"

void Enemy::Initialize(Model* model, uint32_t GH_) {
	assert(model);
	model_ = model;
	enemyGH_ = GH_;
	worldTransform_.Initialize();
}
void Enemy::Update() {
	/*switch (phase_) {
	case Phase::Approach:
	    ApproachPhase();
	    if (translate_.z < 0.0f) {
	        phase_ = Phase::Leave;
	    }
	    break;
	case Phase::Leave:
	    LeavePhase();
	    break;
	default:
	    break;
	}*/
	(this->*phaseFuncTable[static_cast<size_t>(phase_)])();

	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	for (EnemyBullet* bullet : bullets_) {
		if (bullet) {
			bullet->Update();
		}
	}

	ImGui::Begin("Enemy");
	ImGui::Text("%f  %f  %f", translate_.x, translate_.y, translate_.z);
	ImGui::End();
}

void Enemy::Fire() {
	// 弾の発射
	attackInterval--;
	if (attackInterval <= 0) {
		attackInterval = kAttackInterval;
		EnemyBullet* newBullets = new EnemyBullet();
		newBullets->Initialize(model_, translate_);
		bullets_.emplace_back(newBullets);
	}
}

void Enemy::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, enemyGH_);
	for (EnemyBullet* bullet : bullets_) {
		if (bullet) {
			bullet->Draw(viewProjection);
		}
	}
}

void Enemy::ApproachPhase() {
	velocity_ = {0, 0, -0.1f};
	translate_ = Add(translate_, velocity_);
	if (translate_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
	worldTransform_.UpdateMatrix({1, 1, 1}, {0, 0, 0}, translate_);
	Fire();
}

void Enemy::LeavePhase() {
	velocity_ = {0.3f, -0.3f, 0};
	translate_ = Add(translate_, velocity_);
	worldTransform_.UpdateMatrix({1, 1, 1}, {0, 0, 0}, translate_);
}

void (Enemy::*Enemy::phaseFuncTable[])() = {&Enemy::ApproachPhase, &Enemy::LeavePhase};
