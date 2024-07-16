#pragma once
#include "AnotherPlayer.h"
#include "Functions.h"
#include "ImGuiManager.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "Struct.h"
#include "list"

class Player;
class AnotherPlayer;
class PlayerBullet;

class Spring {
public:
	Spring() {}
	~Spring() {}

	void Initialize();
	void Update();
	void Draw();

	void SetPlayer(Player* player) { player_ = player; }
	void SetAnotherPlayer(AnotherPlayer* anoP) { anotherPlayer_ = anoP; }
	void SetPlayerBullet(std::list<PlayerBullet*> playerB) { playerBullets_ = playerB; }

private:
	Player* player_ = nullptr;
	AnotherPlayer* anotherPlayer_ = nullptr;
	std::list<PlayerBullet*> playerBullets_;

	Sphere anoPlayerColSphere{
	    .center = {0, 0, 0},
          .radius = 2
    };
	Sphere playerCollisionSphere{
	    .center = {0, 0, 0},
          .radius = 2
    };
	Sphere bulletColSphere{
	    .center = {0, 0, 0},
          .radius = 1
    };

	int inputTime_;
	bool isOnce_;
};
