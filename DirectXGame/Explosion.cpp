#include "Explosion.h"

void Explosion::Initialize(Model* model, const Vector3& position, int reflectionCount) {
	assert(model);
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = {};
	position_ = position;

	objectColor_.Initialize();
	objectColor_.SetColor({0.99999f, 0.00001f, 0.00001f, 0.5f});
	objectColor_.TransferMatrix();

	if (reflectionCount != 0) {
		reflectionCount_ = reflectionCount + 2;
	}
}

void Explosion::Update() {
	deathTimer_++;
	t = deathTimer_ / kLifeTime;
	easedT = std::clamp(t, 0.0f, 1.0f);
	if (t >= 1.0f) {
		isDead_ = true;
	}
	easedT = EaseOutBack(easedT);

	scale_ = Lerp(Vector3{0, 0, 0}, Vector3{(float)reflectionCount_, (float)reflectionCount_, (float)reflectionCount_}, easedT);

	worldTransform_.UpdateMatrix(scale_, {0, 0, 0}, position_);
}

void Explosion::Draw(const ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, &objectColor_); }
