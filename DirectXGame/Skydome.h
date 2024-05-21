#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <cassert>
#include "TextureManager.h"

class Skydome {
public:
	void Initialize(Model* model);
	void Update();
	void Draw(const ViewProjection& viewproj);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
};
