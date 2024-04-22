#pragma once
#include "Functions.h"
#include "ImGuiManager.h"
#include "Input.h"
#include "MatrixFunc.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <algorithm>
#include <cassert>
#include <list>

class Player {
public:
	Player() {}
	~Player() {
		while (bullets_.back() != nullptr) {
			delete bullets_.back();
		}
	}

	void Initialize(Model* model, uint32_t GH_);
	void Update();
	void Rotate();
	void Draw(ViewProjection& viewProjection);
	void DebugDraw();
	void Attack();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t playerGH_ = 0u;
	// キーボード入力
	Input* input_ = nullptr;

	// プレイヤー
	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.2f;
	// 移動限界座標
	const float kMoveLimitX = 33;
	const float kMoveLimitY = 17;
	// 回転の速さ
	const float kRotSpeed = 0.02f;
	// 弾
	std::list<PlayerBullet*> bullets_;
};
