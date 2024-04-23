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

	ImGui::Begin("Enemy");
	ImGui::Text("%f  %f  %f", translate_.x, translate_.y, translate_.z);
	ImGui::End();
}

void Enemy::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, enemyGH_); }

void Enemy::ApproachPhase() {
	velocity_ = {0, 0, -0.1f};
	translate_ = Add(translate_, velocity_);
	if (translate_.z<0.0f) {
		phase_ = Phase::Leave;
	}
	worldTransform_.UpdateMatrix({1, 1, 1}, {0, 0, 0}, translate_);
}

void Enemy::LeavePhase() {
	velocity_ = {0.3f, -0.3f, 0};
	translate_ = Add(translate_, velocity_);
	worldTransform_.UpdateMatrix({1, 1, 1}, {0, 0, 0}, translate_);
}

void (Enemy::*Enemy::phaseFuncTable[])() = {&Enemy::ApproachPhase, &Enemy::LeavePhase};
