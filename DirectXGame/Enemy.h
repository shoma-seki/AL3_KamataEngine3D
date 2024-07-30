#pragma once
#include "EnemyBullet.h"
#include "Functions.h"
#include "ImGuiManager.h"
#include "Model.h"
#include "Player.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include <list>

class Player;
class GameScene;

enum class Phase { Approach, Leave };

class Enemy {
public:
	Enemy() {}
	~Enemy() {}
	void Initialize(Vector3 position, Model* model, Model* bulletModel, uint32_t GH_);
	void Update();
	void Fire();
	void Draw(ViewProjection& viewProjection);

	void SetPlayer(Player* player) { player_ = player; }
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	Vector3 GetWorldPosition();
	// const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }

	// 当たり判定
	void OnCollision();

	// フェーズ関数
	void ApproachPhase();
	void LeavePhase();

	const float kRadius_ = 2;

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
	uint32_t enemyGH_;
	// 行動パターンフェーズ
	Phase phase_ = Phase::Approach;

	// エネミー情報
	Vector3 translate_ = {0, 4, 60};
	Vector3 velocity_ = {0, 0, 0};

	// メンバ関数ポインタのテーブル
	static void (Enemy::*phaseFuncTable[])();

	// 弾
	// std::list<EnemyBullet*> bullets_;
	Vector3 bulletDirection = {};

	// 弾の間隔
	const int32_t kAttackInterval = 120;
	uint32_t attackInterval = kAttackInterval;

	// プレイヤー
	Player* player_ = nullptr;
	Vector3 playerWorldPos_ = {};

	// ゲームシーン
	GameScene* gameScene_ = nullptr;
};
