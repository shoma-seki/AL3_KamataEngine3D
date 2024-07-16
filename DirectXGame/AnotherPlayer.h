#pragma once
#include "Functions.h"
#include "ImGuiManager.h"
#include "Model.h"
#include "Player.h"
#include "Struct.h"
#include "TextureManager.h"
#include "WorldTransform.h"

class Player;

class AnotherPlayer {
public:
	AnotherPlayer() {}
	~AnotherPlayer() {}

	void Initialize(Model* model, uint32_t GH_);
	void Update();
	void Draw(ViewProjection& viewProjection);

	Vector3 GetWorldPosition();

	void SetPlayer(Player* player) { player_ = player; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t anoPlayerGH_;

	Vector3 translate_;
	Vector3 playerWorldPos_;

	Player* player_ = nullptr;
};
