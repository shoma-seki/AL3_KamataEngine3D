#include "MatrixFunc.h"
#include "WorldTransform.h"

void WorldTransform::UpdateMatrix(Vector3 scale, Vector3 rotate, Vector3 translate) {
	matWorld_ = MakeAffineMatrix(scale, rotate, translate);

	if (parent_) {
		matWorld_ = Multiply(matWorld_, parent_->matWorld_);
	}

	TransferMatrix();
}