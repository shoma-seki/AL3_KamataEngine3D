#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>
#include <fstream>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
	delete player_;
	delete anotherPlayer;
	for (Enemy* enemy : enemy_) {
		delete enemy;
	}
	delete modelSkydome_;
	delete skydome_;
	delete railCamera_;
	for (EnemyBullet* bullet : enemyBullets_) {
		delete bullet;
	}
	for (Explosion* explosion : explosion_) {
		delete explosion;
	}
	delete spring_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1920, 1040);

	// レールカメラ
	railCamera_ = new RailCamera();
	railCamera_->Initialize({0, 0, -1000}, {0, 0, 0});

	// ワールドトランスフォームとビュープロジェクションの初期化
	worldTransform_.Initialize();
	viewProjection_.Initialize();

	// 画像の読み込み
	playerGH_ = TextureManager::Load("Player3-2.png");
	enemyGH_ = TextureManager::Load("enemy4.png");
	// モデルの生成
	model_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	modelEnemy_ = Model::CreateFromOBJ("Enemy", true);
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_);
	// プレイヤー生成
	player_ = new Player();
	Vector3 playerPosition = {0, 0, 30};
	playerModel_ = Model::CreateFromOBJ("Player", true);
	playerBulletModel_ = Model::CreateFromOBJ("PlayerBullet", true);
	player_->Initialize(playerModel_, playerBulletModel_, playerGH_, playerPosition);
	player_->SetParent(&railCamera_->GetWorldTransform());
	// もう一人の自分
	AnotherPlayerModel_ = Model::CreateFromOBJ("AnotherPlayer", true);
	anotherPlayer = new AnotherPlayer();
	anotherPlayer->Initialize(AnotherPlayerModel_, playerGH_);
	anotherPlayer->SetPlayer(player_);
	// 跳ね返し
	spring_ = new Spring();
	spring_->Initialize();
	spring_->SetPlayer(player_);
	spring_->SetAnotherPlayer(anotherPlayer);

	// 軸方向表示
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	LoadEnemyPopData();

	TextureManager::Load("./Resources./Reticle.png");

	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);
}

void GameScene::Update() {
	UpdateEnemyPopCommands();

	railCamera_->Update();

	// 跳ね返しUpdate
	spring_->SetPlayerBullet(player_->GetBullets());
	spring_->Update();

	// 爆発
	BulletExplosion();

	player_->Update(viewProjection_, anotherPlayer->GetWorldPosition());
	anotherPlayer->Update();
	for (Enemy* enemy : enemy_) {
		enemy->Update();
	}
	enemy_.remove_if([](Enemy* enemy) {
		if (enemy->IsAlive() == false) {
			delete enemy;
			return true;
		}
		return false;
	});

	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Update();
	}
	enemyBullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// 爆発
	for (Explosion* explosion : explosion_) {
		explosion->Update();
	}

	skydome_->Update();
	// デバッグカメラ切り替え
	if (input_->TriggerKey(DIK_F)) {
		if (isDebugCameraActive_ == true) {
			isDebugCameraActive_ = false;
		} else {
			isDebugCameraActive_ = true;
		}
	}
	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
		// viewProjection_.UpdateMatrix();
	}
	CheckAllCollisions();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	// プレイヤー
	player_->Draw(viewProjection_);
	anotherPlayer->Draw(viewProjection_);
	for (Enemy* enemy : enemy_) {
		enemy->Draw(viewProjection_);
	}
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Draw(viewProjection_);
	}
	// 爆発
	for (Explosion* explosion : explosion_) {
		explosion->Draw(viewProjection_);
	}
	skydome_->Draw(viewProjection_);
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

	// player_->SphereDraw();

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	player_->DrawUI();
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckAllCollisions() {
	Vector3 posA, posB;
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	// std::list<EnemyBullet*> enemyBullets = {};
	/*for (Enemy* enemy : enemy_) {
	    enemyBullets.emplace_back(enemy->GetBullets());
	}*/

#pragma region 自キャラと敵弾の当たり判定
	posA = player_->GetWorldPosition();
	for (EnemyBullet* bullet : enemyBullets_) {
		posB = bullet->GetWorldPosition();
		float dis = Length(posA, posB);
		if (player_->kRadius_ + bullet->kRadius_ >= dis) {
			player_->OnCollision();
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 敵キャラと自弾の当たり判定
	for (Enemy* enemy : enemy_) {
		posA = enemy->GetWorldPosition();
		for (PlayerBullet* bullet : playerBullets) {
			posB = bullet->GetWorldPosition();
			float dis = Length(posA, posB);
			if (enemy->kRadius_ + bullet->kRadius_ >= dis) {
				enemy->OnCollision();
				bullet->OnCollision();
			}
		}
	}
#pragma endregion

#pragma region 爆発と敵の当たり判定

	for (Enemy* enemy : enemy_) {
		for (Explosion* explode : explosion_) {
			Sphere exlodeSphere{.center = explode->GetWorldPosition(), .radius = (float)explode->reflectionCount_};
			Sphere enemySphere{.center = enemy->GetWorldPosition(), .radius = 2.0f};

			if (isCollision(exlodeSphere, enemySphere)) {
				enemy->OnCollision();
			}
		}
	}

#pragma endregion

#pragma region 自弾と敵弾の当たり判定
	/*for (EnemyBullet* ebullet : enemyBullets_) {
	    posA = ebullet->GetWorldPosition();
	    for (PlayerBullet* pbullet : playerBullets) {
	        posB = pbullet->GetWorldPosition();
	        float dis = Length(posA, posB);
	        if (ebullet->kRadius_ + pbullet->kRadius_ >= dis) {
	            ebullet->OnCollision();
	            pbullet->OnCollision();
	        }
	    }
	}*/
#pragma endregion
}

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) { enemyBullets_.push_back(enemyBullet); }

void GameScene::LoadEnemyPopData() {
	std::ifstream file;
	file.open("./Resources./enemyPop.csv");
	assert(file.is_open());

	enemyPopCommands << file.rdbuf();

	file.close();
}

void GameScene::UpdateEnemyPopCommands() {
	if (isWait_) {
		waitTime_--;
		if (waitTime_ <= 0) {
			isWait_ = false;
		}
		return;
	}

	std::string line;

	while (getline(enemyPopCommands, line)) {
		std::istringstream line_stream(line);

		std::string word;

		getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}
		if (word.find("POP") == 0) {
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());
			PopEnemy({x, y, z});
		} else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			int32_t waitTime = atoi(word.c_str());

			isWait_ = true;
			waitTime_ = waitTime;

			break;
		}
	}
}

void GameScene::BulletExplosion() {
	std::list<PlayerBullet*> bullets = player_->GetBullets();
	for (PlayerBullet* bullet : bullets) {
		if (bullet->IsDead()) {
			Explosion* newExplosion = new Explosion();
			newExplosion->Initialize(playerBulletModel_, bullet->GetWorldPosition(), bullet->GetReflectionCount());
			explosion_.emplace_back(newExplosion);
		}
	}
	explosion_.remove_if([](Explosion* explode) {
		if (explode->IsDead()) {
			delete explode;
			return true;
		}
		return false;
	});
}

void GameScene::PopEnemy(Vector3 position) {
	enemy_.emplace_back(new Enemy());
	enemy_.back()->Initialize(position, modelEnemy_, playerBulletModel_, enemyGH_);
	enemy_.back()->SetPlayer(player_);
	enemy_.back()->SetGameScene(this);
}
