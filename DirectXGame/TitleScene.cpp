#include "TitleScene.h"

void TitleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	texture = TextureManager::Load("./Resources./title.png");
	title = Sprite::Create(texture, {640, 360}, {1, 1, 1, 1}, {0.5f, 0.5f});

	viewProjection_.Initialize();

	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);
}

void TitleScene::Update() {}

void TitleScene::Draw() {	
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	
	title->Draw();

	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
}
