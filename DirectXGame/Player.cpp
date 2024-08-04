#include "Player.h"

void Player::Initialize(Model* model, Model* bulletModel, uint32_t GH_, Vector3 position) {
	assert(model);
	model_ = model;
	bulletModel_ = bulletModel;
	GH_;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	input_ = Input::GetInstance();
	worldTransform3DReticle_.Initialize();
	textureReticle = TextureManager::Load("./Resources./Reticle.png");
	sprite2DReticle_ = Sprite::Create(textureReticle, {640, 360}, {256, 256, 256, 256}, {0.5f, 0.5f});
}

void Player::Update(const ViewProjection& viewProjection, const Vector3& AnoPlayerPosition) {
	// デスフラグが立った弾を削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
	// 旋回
	Rotate();
	// プレイヤー移動
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	if (input_->PushKey(DIK_A)) {
		move.x -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_D)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_W)) {
		move.y += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_S)) {
		move.y -= kCharacterSpeed;
	}
	// move = {0, 0, 0};
	XINPUT_STATE joyState;

	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		move.x += float(joyState.Gamepad.sThumbLX) / SHRT_MAX * kCharacterSpeed;
		move.y += float(joyState.Gamepad.sThumbLY) / SHRT_MAX * kCharacterSpeed;
	}

	// 画面外に行かないように

	// 攻撃
	Attack();
	// 弾更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}
	// 座標移動
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	// 座標制限
	worldTransform_.translation_.x = std::clamp(worldTransform_.translation_.x, -kMoveLimitX, kMoveLimitX);
	worldTransform_.translation_.y = std::clamp(worldTransform_.translation_.y, -kMoveLimitY, kMoveLimitY);

	// 行列更新
	worldTransform_.UpdateMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	// 足されすぎないための処理
	move = {0, 0, 0};

	const float kDistancePlayerTo3DReticle = 100.0f;
	Vector3 offset = {0, 0, 1.0f};
	offset = Multiply(offset, worldTransform_.matWorld_);
	offset = Multiply(kDistancePlayerTo3DReticle, Normalize(offset));

	// worldTransform3DReticle_.translation_ = Add({0, 0, 10}, GetWorldPosition());
	/*worldTransform3DReticle_.UpdateMatrix({1, 1, 1}, {0, 0, 0}, worldTransform3DReticle_.translation_);
	Vector3 positionReticle = GetWorld3DReticlePosition();*/
	Matrix4x4 matViewport = MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	/*Matrix4x4 matViewProjectionViewport = Multiply(viewProjection.matView, Multiply(viewProjection.matProjection, matViewport));
	positionReticle = Transform(positionReticle, matViewProjectionViewport);
	sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));*/

	POINT mousePosition;
	GetCursorPos(&mousePosition);
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);
	// Vector2 spritePosition = {float(mousePosition.x), float(mousePosition.y)};

	Vector2 spritePosition = sprite2DReticle_->GetPosition();
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		if (float(joyState.Gamepad.sThumbRX) != 0 || float(joyState.Gamepad.sThumbRY) != 0) {
			spritePosition.x += float(joyState.Gamepad.sThumbRX) / SHRT_MAX * 5.0f;
			spritePosition.y -= float(joyState.Gamepad.sThumbRY) / SHRT_MAX * 5.0f;
		}
		sprite2DReticle_->SetPosition(spritePosition);
	}
	sprite2DReticle_->SetPosition(spritePosition);
	Matrix4x4 matVPV = Multiply(viewProjection.matView, Multiply(viewProjection.matProjection, matViewport));
	Matrix4x4 matInverseVPV = inverse(matVPV);
	Vector3 posNear = Vector3(float(spritePosition.x), float(spritePosition.y), 0);
	Vector3 posFar = Vector3(float(spritePosition.x), float(spritePosition.y), 1);
	posNear = Transform(posNear, matInverseVPV);
	posFar = Transform(posFar, matInverseVPV);

	Vector3 mouseDirection = Subtract(posFar, posNear);
	mouseDirection = Normalize(mouseDirection);

	const float kDistanceTestObject = 100;

	// キーが押されたらレティクルの位置を固定
	if (input_->TriggerKey(DIK_E) || joyState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
		/*worldTransform3DReticle_.translation_ = GetWorldPosition();
		worldTransform3DReticle_.translation_.z += 60;*/
		worldTransform3DReticle_.translation_ = AnoPlayerPosition;
		worldTransform3DReticle_.UpdateMatrix({1, 1, 1}, {0, 0, 0}, worldTransform3DReticle_.translation_);
		Vector3 positionReticle = GetWorld3DReticlePosition();
		Matrix4x4 matViewProjectionViewport = Multiply(viewProjection.matView, Multiply(viewProjection.matProjection, matViewport));
		positionReticle = Transform(positionReticle, matViewProjectionViewport);
		sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));
		/*if (isLocking_) {
		    isLocking_ = false;
		} else {
		    isLocking_ = true;
		}*/
	}

	worldTransform3DReticle_.translation_ = Add(posNear, Multiply(kDistanceTestObject, mouseDirection));
	worldTransform3DReticle_.UpdateMatrix({1, 1, 1}, {0, 0, 0}, worldTransform3DReticle_.translation_);
	/*if (isLocking_) {
	} else {
	}*/

	// playerCollisionSphere.center = GetWorldPosition();

#ifdef DEBUG

	ImGui::Begin("Player");
	ImGui::Text("2DReticle:(%f,%f)", sprite2DReticle_->GetPosition().x, sprite2DReticle_->GetPosition().y);
	ImGui::Text("Near:(%+.2f,%+.2f,%+.2f)", posNear.x, posNear.y, posNear.z);
	ImGui::Text("Far:(%+.2f,%+.2f,%+.2f)", posFar.x, posFar.y, posFar.z);
	ImGui::Text("3DReticle:(%+.2f,%+.2f,%+.2f)", worldTransform3DReticle_.translation_.x, worldTransform3DReticle_.translation_.y, worldTransform3DReticle_.translation_.z);
	ImGui::End();

#endif // DEBUG

	DebugDraw();
}

void Player::Rotate() {
	Vector3 rotate{};
	/*if (input_->PushKey(DIK_A)) {
	    worldTransform_.rotation_.y += kRotSpeed;
	}
	if (input_->PushKey(DIK_D)) {
	    worldTransform_.rotation_.y -= kRotSpeed;
	}*/
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
	// model_->Draw(worldTransform3DReticle_, viewProjection, playerGH_);
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Player::DrawUI() { sprite2DReticle_->Draw(); }

void Player::DebugDraw() {
	// ImGui
#ifdef _DEBUG
	ImGui::Begin("Player");
	ImGui::Text("translate %f   %f   %f", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
	ImGui::Text("rotate %f   %f   %f", worldTransform_.rotation_.x, worldTransform_.rotation_.y, worldTransform_.rotation_.z);
	ImGui::End();
#endif
}

void Player::Attack() {

	XINPUT_STATE joyState;
	if (!Input::GetInstance()->GetJoystickState(0, joyState)) {
		return;
	}

	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		bulletTime++;
	} else {
		isBulletOnce = true;
		bulletTime = 0;
	}

	if (CanAttack_) {
		// if (input_->TriggerKey(DIK_SPACE)) {
		//	Vector3 direction_ = Subtract(GetWorld3DReticlePosition(), GetWorldPosition());
		//	direction_ = Normalize(direction_);
		//	// velocity_ = TransformNormal(velocity_, worldTransform_.matWorld_);

		//	PlayerBullet* newBullet = new PlayerBullet();
		//	newBullet->Initialize(
		//	    bulletModel_,
		//	    {
		//	        worldTransform_.matWorld_.m[3][0],
		//	        worldTransform_.matWorld_.m[3][1],
		//	        worldTransform_.matWorld_.m[3][2],
		//	    },
		//	    direction_);
		//	bullets_.push_back(newBullet);
		//}

		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
			// bulletTime++;
			Vector3 direction_ = Subtract(GetWorld3DReticlePosition(), GetWorldPosition());
			direction_ = Normalize(direction_);
			// velocity_ = TransformNormal(velocity_, worldTransform_.matWorld_);

			if (bulletTime % kBulletCoolTime == 0) {
				PlayerBullet* newBullet = new PlayerBullet();
				newBullet->Initialize(
				    bulletModel_,
				    {
				        worldTransform_.matWorld_.m[3][0],
				        worldTransform_.matWorld_.m[3][1],
				        worldTransform_.matWorld_.m[3][2],
				    },
				    direction_);
				bullets_.push_back(newBullet);
			}

			if (isBulletOnce) {
				PlayerBullet* newBullet = new PlayerBullet();
				newBullet->Initialize(
				    bulletModel_,
				    {
				        worldTransform_.matWorld_.m[3][0],
				        worldTransform_.matWorld_.m[3][1],
				        worldTransform_.matWorld_.m[3][2],
				    },
				    direction_);
				bullets_.push_back(newBullet);
				isBulletOnce = false;
			}
		} else {
			isBulletOnce = true;
			bulletTime = 0;
		}
	}

	// 弾を出せるように
	CanAttack_ = true;
}

// void Player::SphereDraw() { DrawSphere(playerCollisionSphere, 10); }

void Player::OnCollision() {
	if (HP >= 0) {
		HP--;
	}
}

Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

Vector3 Player::GetWorld3DReticlePosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	worldPos.x = worldTransform3DReticle_.matWorld_.m[3][0];
	worldPos.y = worldTransform3DReticle_.matWorld_.m[3][1];
	worldPos.z = worldTransform3DReticle_.matWorld_.m[3][2];
	return worldPos;
}
