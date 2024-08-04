#include "RailCamera.h"

void RailCamera::Initialize(Vector3 worldPosition, Vector3 radian) {
	worldTransform_.Initialize();
	worldTransform_.translation_ = worldPosition;
	worldTransform_.rotation_ = radian;
	viewProjection_.farZ = 5000;
	viewProjection_.Initialize();

	srand((unsigned int)time(NULL));
}

void RailCamera::Update() {
	if (isShake_) {
		shakeTime--;
		if (shakeTime < 0) {
			isShake_ = false;
			shakeTime = kShakeTime;
		}

		if (shakeTime > 5) {
			rnd_.x = float(rand() % 70 - 35) / 10.0f;
			rnd_.y = float(rand() % 70 - 35) / 10.0f;
		} else {
			rnd_.x = float(rand() % 30 - 15) / 10.0f;
			rnd_.y = float(rand() % 30 - 15) / 10.0f;
		}
	}

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	worldTransform_.rotation_ = Add(worldTransform_.rotation_, {0, 0, 0});
	worldTransform_.UpdateMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_ + rnd_);
	viewProjection_.matView = inverse(worldTransform_.matWorld_);

	rnd_ = {0, 0, 0};
	worldTransform_.translation_.x = 0;
	worldTransform_.translation_.y = 0;
#ifdef _DEBUG
	ImGui::Begin("Camera");
	ImGui::DragFloat3("worldPos", &worldTransform_.translation_.x, 1.0f);
	ImGui::DragFloat3("worldRotate", &worldTransform_.rotation_.x, 0.01f);
	ImGui::End();
#endif
}