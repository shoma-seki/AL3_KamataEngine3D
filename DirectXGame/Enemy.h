#pragma once
#include "EnemyBullet.h"
#include "Functions.h"
#include "ImGuiManager.h"
#include "Model.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include <list>

enum class Phase { Approach, Leave };

class Enemy {
public:
	Enemy() {}
	~Enemy() {
		for (EnemyBullet* bullet : bullets_) {
			if (bullet == nullptr) {
				delete bullet;
			}
		}
	}
	void Initialize(Model* model, uint32_t GH_);
	void Update();
	void Fire();
	void Draw(ViewProjection& viewProjection);

	// フェーズ関数
	void ApproachPhase();
	void LeavePhase();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t enemyGH_;
	// 行動パターンフェーズ
	Phase phase_ = Phase::Approach;

	// エネミー情報
	Vector3 translate_ = {0, 4, 15};
	Vector3 velocity_ = {0, 0, 0};

	// メンバ関数ポインタのテーブル
	static void (Enemy::*phaseFuncTable[])();

	// 弾
	std::list<EnemyBullet*> bullets_;

	// 弾の間隔
	const int32_t kAttackInterval = 30;
	uint32_t attackInterval = kAttackInterval;
};
