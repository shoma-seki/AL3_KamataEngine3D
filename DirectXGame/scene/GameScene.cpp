#include "GameScene.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete sprite_;
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// プレイヤーの初期化
	playerGH_ = TextureManager::Load("Player3-2.png");
	sprite_ = Sprite::Create(playerGH_, {100, 50});

	// 3Dモデルの初期化
	model_ = Model::Create();
	worldTransform_.Initialize();
	viewProjection_.Initialize();

	// サウンドデータの読み込み
	soundDH_ = audio_->LoadWave("fanfare.wav");

	// サウンド
	voiceHandle_ = audio_->PlayWave(soundDH_, true);
	
	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// ライン描画の準備
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());

	//軸方向表示
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update() {
	// 2D更新
	Vector2 position = sprite_->GetPosition();
	position.x += 2.0f;
	position.y += 1.0f;
	sprite_->SetPosition(position);

	// サウンド再生
	if (input_->TriggerKey(DIK_SPACE)) {
		// 音声停止
		audio_->StopWave(voiceHandle_);
	}

	// imgui
	ImGui::Begin("Debug1");
	ImGui::Text("Kamata Tarou %d.%d.%d", 2050, 12, 31);
	ImGui::End();

	ImGui::Begin("Debug2");
	ImGui::InputFloat3("InputFloat3", inputFloat3);
	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);
	ImGui::End();

	ImGui::Begin("Debug1");
	ImGui::ShowDemoWindow();
	ImGui::End();

	//デバッグカメラ
	debugCamera_->Update();
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
	/// </summary>
	// 3Dオブジェクト描画
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), playerGH_);

	// グリッド表示
	for (uint32_t xIndex = 0; xIndex <= 16; ++xIndex) {
		lineStart.x = xIndex * 2.0f;
		lineStart.z = 0.0f;
		lineEnd.x = lineStart.x;
		lineEnd.z = 16 * 2.0f;

		lineStart.x -= 16;
		lineStart.z -= 16;
		lineEnd.x -= 16;
		lineEnd.z -= 16;

		PrimitiveDrawer::GetInstance()->DrawLine3d(lineStart, lineEnd, {1.0f, 0.0f, 0.0f, 1.0f});
	}
	for (uint32_t zIndex = 0; zIndex <= 16; ++zIndex) {
		lineStart.x = 0.0f;
		lineStart.z = zIndex * 2.0f;
		lineEnd.x = 16 * 2.0f;
		lineEnd.z = lineStart.z;

		lineStart.x -= 16;
		lineStart.z -= 16;
		lineEnd.x -= 16;
		lineEnd.z -= 16;

		PrimitiveDrawer::GetInstance()->DrawLine3d(lineStart, lineEnd, {0.0f, 0.0f, 1.0f, 1.0f});
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	// プレイヤーを描画
	sprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
