#include "AnotherPlayer.h"

void AnotherPlayer::Initialize( Model* model, uint32_t GH_) {
	model_ = model;
	GH_;
	worldTransform_.Initialize(); 
}

void AnotherPlayer::Update() {
	if(player_){ 
		playerWorldPos_ = player_->GetWorldPosition();
	}
	translate_ = playerWorldPos_;
	translate_.z += 60;
	worldTransform_.UpdateMatrix({1, 1, 1}, {0, 0, 0}, translate_);
}

void AnotherPlayer::Draw(ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection); 
}

Vector3 AnotherPlayer::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}
