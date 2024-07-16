#include "Spring.h"

void Spring::Initialize() {}

void Spring::Update() {
	XINPUT_STATE joyState;
	if (!Input::GetInstance()->GetJoystickState(0, joyState)) {
		return;
	}

	playerCollisionSphere.center = player_->GetWorldPosition();
	anoPlayerColSphere.center = anotherPlayer_->GetWorldPosition();

	for (PlayerBullet* bullet : playerBullets_) {
		if (player_ && anotherPlayer_ && bullet) {
			if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
				inputTime_++;
			} else {
				inputTime_ = 0;
			}

			if (inputTime_ == 1) {
				isOnce_ = true;
			} else {
				isOnce_ = false;
			}

			bulletColSphere.center = bullet->GetWorldPosition();
			if (isOnce_) {
				if (isCollision(playerCollisionSphere, bulletColSphere)) {
					bullet->DirectionInverce();
					player_->SetDontAttack();
				}
				if (isCollision(anoPlayerColSphere, bulletColSphere)) {
					bullet->DirectionInverce();
					player_->SetDontAttack();
				}
			}
		}
	}
}

void Spring::Draw() {}
