#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "DebugCamera.h"
#include "Enemy.h"
#include "Skydome.h"
#include "RailCamera.h"

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

	///<summary>
	///衝突判定と応答
	/// </summary>
	void CheckAllCollisions();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	// ワールドトランスフォームとビュープロジェクションの初期化
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	
	//テクスチャハンドル
	uint32_t playerGH_ = 0;
	uint32_t enemyGH_ = 0;
	//モデル
	Model* model_ = nullptr;
	Model* modelSkydome_ = nullptr;
	//プレイヤー
	Player* player_ = nullptr;
	//天球
	Skydome* skydome_ = nullptr;
	//エネミー
	Enemy* enemy_ = nullptr;
	//カメラ
	RailCamera* railCamera_ = nullptr;
	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	//デバッグカメラ有効
	bool isDebugCameraActive_ = false;

	/// </summary>
};
