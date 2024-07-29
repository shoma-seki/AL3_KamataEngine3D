#pragma once
#include "Functions.h"
#include "ImGuiManager.h"
#include "Input.h"
#include "MatrixFunc.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "Sprite.h"
#include "Struct.h"
#include "ViewProjection.h"
#include "WinApp.h"
#include "Windows.h"
#include "WorldTransform.h"
#include <algorithm>
#include <cassert>
#include <list>

class Player {
public:
	Player() {}
	~Player() {
		for (PlayerBullet* bullet : bullets_) {
			if (bullet == nullptr) {
				delete bullet;
			}
		}
		delete sprite2DReticle_;
	}

	void Initialize(Model* model, Model* bulletModel, uint32_t GH_, Vector3 position);
	void Update(const ViewProjection& viewProjection);
	void Rotate();
	void Draw(ViewProjection& viewProjection);
	void DrawUI();
	void DebugDraw();
	void Attack();
	//void SphereDraw();

	void SetDontAttack() { CanAttack_ = false; }

	// 当たり判定
	void OnCollision();

	Vector3 GetWorldPosition();
	Vector3 GetWorld3DReticlePosition();
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

	void SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }

	const float kRadius_ = 2;

	int bulletTime = 0;
	const int kBulletCoolTime = 60;
	bool isBulletOnce = true;

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	Model* bulletModel_ = nullptr;
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
	// 3Dレティクル用ワールドトランスフォーム
	WorldTransform worldTransform3DReticle_;
	Sprite* sprite2DReticle_ = nullptr;

	uint32_t textureReticle;

	//AnotherPlayerにロック
	bool isLocking_;

	//弾を発射しない
	bool CanAttack_;
};
