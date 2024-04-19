#pragma once
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cassert>
#include "Functions.h"
#include "MatrixFunc.h"
#include "ImGuiManager.h"
#include <algorithm>

class Player {
public:
	Player() {}
	~Player() {}

	void Initialize(Model* model, uint32_t GH_);
	void Update();
	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t playerGH_ = 0u;
	//キーボード入力
	Input* input_ = nullptr;

	//プレイヤー
	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.2f;
	//移動限界座標
	const float kMoveLimitX = 33;
	const float kMoveLimitY = 17;
};
