#pragma once

#include "AnotherPlayer.h"
#include "Audio.h"
#include "DebugCamera.h"
#include "DirectXCommon.h"
#include "Enemy.h"
#include "Explosion.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "PrimitiveDrawer.h"
#include "RailCamera.h"
#include "Skydome.h"
#include "Spring.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <sstream>
#include <string>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	///< summary>
	/// 衝突判定と応答
	///  </summary>
	void CheckAllCollisions();

	///< summary>
	/// 敵弾を追加する
	///  </summary>
	void AddEnemyBullet(EnemyBullet* enemyBullet);

	///< summary>
	/// 敵弾を追加する
	///  </summary>
	void LoadEnemyPopData();

	///< summary>
	/// 敵弾を追加する
	///  </summary>
	void UpdateEnemyPopCommands();

	///< summary>
	/// 爆発させる
	///  </summary>
	void BulletExplosion();

	void PopEnemy(Vector3 position);

	bool IsFinished() { return isFinished; }

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	// ワールドトランスフォームとビュープロジェクションの初期化
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	// テクスチャハンドル
	uint32_t playerGH_ = 0;
	uint32_t enemyGH_ = 0;
	// モデル
	Model* model_ = nullptr;
	Model* modelSkydome_ = nullptr;
	Model* modelEnemy_ = nullptr;
	Model* playerBulletModel_ = nullptr;
	Model* playerModel_ = nullptr;
	Model* AnotherPlayerModel_ = nullptr;
	// プレイヤー
	Player* player_ = nullptr;
	AnotherPlayer* anotherPlayer = nullptr;
	// 爆発
	std::list<Explosion*> explosion_;
	// 跳ね返しクラス
	Spring* spring_ = nullptr;
	// 天球
	Skydome* skydome_ = nullptr;
	// エネミー
	std::list<Enemy*> enemy_;
	// エネミー弾
	std::list<EnemyBullet*> enemyBullets_;
	// カメラ
	RailCamera* railCamera_ = nullptr;
	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;
	// 敵発生コマンド
	std::stringstream enemyPopCommands;
	// フラグ
	bool isWait_;
	int waitTime_;
	bool isFinished = false;
	bool isGameOver = false;
	bool isClear = false;

	//ハート
	uint32_t heart1T;
	uint32_t heart2T;
	uint32_t heart3T;
	Sprite* heart1 = nullptr;
	Sprite* heart2 = nullptr;
	Sprite* heart3 = nullptr;

	//操作
	uint32_t sousaT;
	Sprite* sousa = nullptr;

	//時間
	int gameTime = 0;
	int gameOverTime = 0;
	int clearTime = 0;

	//ゲームオーバー
	uint32_t texture;
	Sprite* title = nullptr;

	//クリア
	uint32_t clearT;
	Sprite* clear = nullptr;

	//サウンド
	uint32_t damage;
	uint32_t explodeS;
	uint32_t gameBgm;
	uint32_t pon;

	uint32_t gameBgmV;

	/// </summary>
};
