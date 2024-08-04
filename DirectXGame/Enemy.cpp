#include "Enemy.h"
#include "GameScene.h"

void Enemy::Initialize(Vector3 position, Model* model, Model* bulletModel, uint32_t GH_) {
	assert(model);
	model_ = model;
	bulletModel_ = bulletModel;
	enemyGH_ = GH_;
	translate_ = position;
	worldTransform_.Initialize();

	phase_ = Phase::Approach;
}
void Enemy::Update() {
	switch (phase_) {
	case Phase::Approach:
		ApproachPhase();
		if (std::fabsf(playerWorldPos_.z - GetWorldPosition().z) < 100.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave:
		LeavePhase();
		break;
	default:
		break;
	}
	//(this->*phaseFuncTable[static_cast<size_t>(phase_)])();

	// bullets_.remove_if([](EnemyBullet* bullet) {
	//	if (bullet->IsDead()) {
	//		delete bullet;
	//		return true;
	//	}
	//	return false;
	// });

	/*for (EnemyBullet* bullet : bullets_) {
	    if (bullet) {
	        bullet->Update();
	    }
	}*/
#ifdef DEBUG
	ImGui::Begin("Enemy");
	ImGui::Text("%f  %f  %f", translate_.x, translate_.y, translate_.z);
	ImGui::End();

#endif // DEBUG
}

void Enemy::Fire() {
	// assert(player_);
	//  弾の発射
	attackInterval--;
	if (attackInterval <= 0) {
		attackInterval = kAttackInterval;
		EnemyBullet* newBullets = new EnemyBullet();
		playerWorldPos_ = player_->GetWorldPosition();
		bulletDirection = Normalize(playerWorldPos_ - GetWorldPosition());
		newBullets->Initialize(bulletModel_, translate_, Multiply(1.2f, bulletDirection));
		gameScene_->AddEnemyBullet(newBullets);
	}
}

void Enemy::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection); }

Vector3 Enemy::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

void Enemy::OnCollision() { isAlive = false; }

void Enemy::ApproachPhase() {
	velocity_ = {0, 0, -0.1f};
	translate_ = Add(translate_, velocity_);
	/*if (Length(playerWorldPos_, GetWorldPosition()) < 5.0f) {
	    phase_ = Phase::Leave;
	}*/
	worldTransform_.UpdateMatrix({1, 1, 1}, {0, 0, 0}, translate_);
	Fire();
}

void Enemy::LeavePhase() {
	velocity_ = {0.3f, -0.3f, 0};
	translate_ = Add(translate_, velocity_);
	worldTransform_.UpdateMatrix({1, 1, 1}, {0, 0, 0}, translate_);
}

void (Enemy::*Enemy::phaseFuncTable[])() = {&Enemy::ApproachPhase, &Enemy::LeavePhase};
