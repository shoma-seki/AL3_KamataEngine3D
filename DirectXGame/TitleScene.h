#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "WinApp.h"
#include "Windows.h"

#include "PlayerBullet.h"

class TitleScene {
public:
	void Initialize();
	void Update();
	void Draw();

	bool IsFinished() const { return isFinished; }

private:
	ViewProjection viewProjection_;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t texture;
	Sprite* title = nullptr;

	bool isFinished = false;
};
