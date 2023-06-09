#include "BalloonPrefab.h"

#include "BalloonMovementComponent.h"
#include "CollisionBoxComponent.h"
#include "TextureComponent.h"

dae::BalloonPrefab::BalloonPrefab(dae::Scene& scene, const dae::LevelPrefab& level,glm::vec2 startpos)
{
	auto GameObjBalloon = std::make_shared<dae::GameObject>("Enemy");
	GameObjBalloon->SetRelativePosition(startpos);

	//Texture
	auto TextureCpBalloon = std::make_shared<dae::TextureComponent>(GameObjBalloon.get());
	TextureCpBalloon->SetTexture("BomberMan_Ballon.png");
	GameObjBalloon->AddComponent(TextureCpBalloon);

	//Collision
	auto Collider = std::make_shared<dae::CollisionBoxComponent>(GameObjBalloon.get());
	GameObjBalloon->AddComponent(Collider);

	//Movement
	auto MovementBalloon = std::make_shared<dae::BalloonMovementComponent>(GameObjBalloon.get(), level, startpos, 50.f);
	GameObjBalloon->AddComponent(MovementBalloon);

	scene.Add(GameObjBalloon);
}
