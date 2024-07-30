#include "Spring.h"

void Spring::Initialize() { input_ = Input::GetInstance(); }

void Spring::Update() {
	XINPUT_STATE joyState;
	if (!Input::GetInstance()->GetJoystickState(0, joyState)) {
		return;
	}

	playerCollisionSphere.center = player_->GetWorldPosition();
	anoPlayerColSphere.center = anotherPlayer_->GetWorldPosition();

	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER || input_->PushKey(DIK_SPACE)) {
		collisionTime++;
		bool isCanAttack = true;
		for (PlayerBullet* bullet : playerBullets_) {
			if (player_ && anotherPlayer_ && bullet) {
				/*if (bullet->GetWorldPosition().z >= player_->GetWorldPosition().z && bullet->GetWorldPosition().z <= anotherPlayer_->GetWorldPosition().z) {
				    isCanAttack = false;
				} else {
				    isCanAttack = true;
				}*/

				// 撃てるかどうかを判定
				Vector3 frontDirection = {0, 0, 1};
				Vector3 backDirection = {0, 0, -1};

				if (frontDirection == bullet->GetDirection()) {
					isCanAttack = false;
				}
				if (backDirection == bullet->GetDirection()) {
					isCanAttack = false;
				}

				bulletColSphere.center = bullet->GetWorldPosition();
				if (isCollision(playerCollisionSphere, bulletColSphere)) {
					bullet->onCollisionPTime++;
					if (bullet->onCollisionPTime == 1) {
						bullet->onCollisionEnter = true;
					}
				} else {
					bullet->onCollisionPTime = 0;
					bullet->onCollisionEnter = false;
				}
				if (isCollision(anoPlayerColSphere, bulletColSphere)) {
					bullet->onCollisionATime++;
					if (bullet->onCollisionATime == 1) {
						bullet->onCollisionEnter = true;
					}
				} else {
					bullet->onCollisionATime = 0;
					if (isCollision(playerCollisionSphere, bulletColSphere) == false) {
						bullet->onCollisionEnter = false;
					}
				}

				if (bullet->GetShotTime() >= 10 && bullet->onCollisionEnter) {
					bullet->DirectionInverce();
					player_->SetDontAttack();
					collisionTime = 0;
				}
			}
		}
		if (isCanAttack == false) {
			player_->SetDontAttack();
		}
	}
}

void Spring::Draw() {}
