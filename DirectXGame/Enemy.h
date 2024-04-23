#pragma once
#include "Functions.h"
#include "Model.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include "ImGuiManager.h"

enum class Phase {
	Approach,
	Leave
};

class Enemy {
public:
	Enemy() {}
	~Enemy() {}
	void Initialize(Model* model, uint32_t GH_);
	void Update();
	void Draw(ViewProjection& viewProjection);

	//フェーズ関数
	void ApproachPhase();
	void LeavePhase();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t enemyGH_;
	//行動パターンフェーズ
	Phase phase_ = Phase::Approach;

	// エネミー情報
	Vector3 translate_ = {0, 4, 15};
	Vector3 velocity_ = {0, 0, 0};

	//メンバ関数ポインタのテーブル
	static void (Enemy::*phaseFuncTable[])();
};
