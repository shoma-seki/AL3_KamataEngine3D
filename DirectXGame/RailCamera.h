#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Functions.h"
#include "MatrixFunc.h"
#include "ImGuiManager.h"

class RailCamera {
public:
	void Initialize(Vector3 worldPosition, Vector3 radian);
	void Update();

	const ViewProjection& GetViewProjection() { return viewProjection_; }
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	Vector3 velocity_ = {0, 0, 0};
};
