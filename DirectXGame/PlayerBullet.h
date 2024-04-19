#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <cassert>
#include "TextureManager.h"

class PlayerBullet {
public:
	PlayerBullet() {}
	~PlayerBullet() {}

	void Initialize(Model* model, const Vector3& position);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_{};
	Model* model_{};
	uint32_t bulletGH_{};
	Vector3 position_{};
};
