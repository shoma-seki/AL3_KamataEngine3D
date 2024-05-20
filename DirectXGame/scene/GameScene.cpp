#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
	delete player_;
	delete enemy_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1920, 1040);

	// ワールドトランスフォームとビュープロジェクションの初期化
	worldTransform_.Initialize();
	viewProjection_.Initialize();

	// 画像の読み込み
	playerGH_ = TextureManager::Load("Player3-2.png");
	enemyGH_ = TextureManager::Load("enemy4.png");
	// モデルの生成
	model_ = Model::Create();
	// プレイヤー生成
	player_ = new Player();
	player_->Initialize(model_, playerGH_);
	// エネミー
	enemy_ = new Enemy();
	enemy_->Initialize(model_, enemyGH_);
	// 軸方向表示
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update() {
	player_->Update();
	if (enemy_) {
		enemy_->Update();
		enemy_->SetPlayer(player_);
	}
	// デバッグカメラ切り替え
	if (input_->TriggerKey(DIK_SPACE)) {
		if (isDebugCameraActive_ == true) {
			isDebugCameraActive_ = false;
		} else {
			isDebugCameraActive_ = true;
		}
	}
	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.UpdateMatrix();
	}
	CheckAllCollisions();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	// プレイヤー
	player_->Draw(viewProjection_);
	if (enemy_) {
		enemy_->Draw(viewProjection_);
	}
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() {
	Vector3 posA, posB;
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

#pragma region 自キャラと敵弾の当たり判定
	posA = player_->GetWorldPosition();
	for (EnemyBullet* bullet : enemyBullets) {
		posB = bullet->GetWorldPosition();
		float dis = Length(posA, posB);
		if (player_->kRadius_ + bullet -> kRadius_ >= dis) {
			player_->OnCollision();
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 敵キャラと自弾の当たり判定
	posA = enemy_->GetWorldPosition();
	for (PlayerBullet* bullet : playerBullets) {
		posB = bullet->GetWorldPosition();
		float dis = Length(posA, posB);
		if (enemy_->kRadius_ + bullet->kRadius_ >= dis) {
			enemy_->OnCollision();
			bullet->OnCollision();
		}
	}
#pragma endregion


#pragma region 自弾と敵弾の当たり判定
	for (EnemyBullet* ebullet : enemyBullets) {
		for (PlayerBullet* pbullet : playerBullets) {
			posA = ebullet->GetWorldPosition();
			posB = pbullet->GetWorldPosition();
			float dis = Length(posA, posB);
			if (ebullet->kRadius_ + pbullet->kRadius_ >= dis) {
				ebullet->OnCollision();
				pbullet->OnCollision();
			}
		}
	}
#pragma endregion
}
