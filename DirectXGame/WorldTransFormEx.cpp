#include "WorldTransform.h"
#include "MatrixFunc.h"

void WorldTransform::UpdateMatrix(Vector3 scale, Vector3 rotate, Vector3 translate) {
	matWorld_ = MakeAffineMatrix(scale, rotate, translate);
	TransferMatrix();
}