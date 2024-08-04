#include "RailCamera.h"

void RailCamera::Initialize(Vector3 worldPosition, Vector3 radian) {
	worldTransform_.Initialize();
	worldTransform_.translation_ = worldPosition;
	worldTransform_.rotation_ = radian;
	viewProjection_.farZ = 5000;
	viewProjection_.Initialize();
}

void RailCamera::Update() {
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	worldTransform_.rotation_ = Add(worldTransform_.rotation_, {0, 0, 0});
	worldTransform_.UpdateMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	viewProjection_.matView = inverse(worldTransform_.matWorld_);
#ifdef _DEBUG
	ImGui::Begin("Camera");
	ImGui::DragFloat3("worldPos", &worldTransform_.translation_.x, 1.0f);
	ImGui::DragFloat3("worldRotate", &worldTransform_.rotation_.x, 0.01f);
	ImGui::End();
#endif
}