#include "Player.h"

void Player::Initialize(Model* model, uint32_t GH_) {
	assert(model);
	model_ = model;
	playerGH_ = GH_;
	worldTransform_.Initialize();
	input_ = Input::GetInstance();
}

void Player::Update() {
	// 旋回
	Rotate();
	// プレイヤー移動
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}
	// 攻撃
	Attack();
	// 弾更新
	if (bullet_) {
		bullet_->Update();
	}

	// 座標移動
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	// 座標制限
	worldTransform_.translation_.x = std::clamp(worldTransform_.translation_.x, -kMoveLimitX, kMoveLimitX);
	worldTransform_.translation_.y = std::clamp(worldTransform_.translation_.y, -kMoveLimitY, kMoveLimitY);
	// 行列更新
	worldTransform_.UpdateMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	// 足されすぎないための処理
	move = {0, 0, 0};

	DebugDraw();
}

void Player::Rotate() {
	Vector3 rotate{};
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}
	if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	}
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, playerGH_);
	if (bullet_) {
		bullet_->Draw(viewProjection);
	}
}

void Player::DebugDraw() {
	// ImGui
#ifdef _DEBUG
	ImGui::Begin("Player");
	ImGui::Text("translate %f   %f   %f", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
	ImGui::Text("rotate %f   %f   %f", worldTransform_.rotation_.x, worldTransform_.rotation_.y, worldTransform_.rotation_.z);
	ImGui::End();
#endif
}

void Player::Attack() {
	if (input_->TriggerKey(DIK_F)) {
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);
		bullet_ = newBullet;
	}
}
