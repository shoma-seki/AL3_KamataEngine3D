#include "Skydome.h"

void Skydome::Initialize(Model* model) {
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0, 0, 0};
	assert(model);
	model_ = model;
}

void Skydome::Update() {}

void Skydome::Draw(const ViewProjection& viewproj) { model_->Draw(worldTransform_, viewproj); }
