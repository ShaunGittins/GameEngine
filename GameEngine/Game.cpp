#include "Game.h"
#include "Scene.h"
#include "Math.h"
#include "GameEngine.h"
using namespace Math;

const float PLAYER_MOVEMENT_SPEED = 0.5f;
const float CAMERA_MOVEMENT_SPEED = 0.3f;

int xMouse = 0, yMouse = 0;
class ControlInput {
public:
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
};

ControlInput controlInput;
ControlInput cameraControlInput;

void Game::Start()
{
}

void Game::End()
{
}

void Game::Input(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
		const Uint8* keyboard_state = SDL_GetKeyboardState(NULL);

		Scene* currentScene = _gameEngine->sceneManager.GetCurrentScene();
		if (currentScene == _gameEngine->sceneManager.GetScene(1)) {
			// Player movement
			controlInput.up = (keyboard_state[SDL_SCANCODE_W] && !(keyboard_state[SDL_SCANCODE_S]));
			controlInput.down = (!keyboard_state[SDL_SCANCODE_W] && (keyboard_state[SDL_SCANCODE_S]));
			controlInput.left = (keyboard_state[SDL_SCANCODE_A] && !(keyboard_state[SDL_SCANCODE_D]));
			controlInput.right = (!keyboard_state[SDL_SCANCODE_A] && (keyboard_state[SDL_SCANCODE_D]));

			// Camera movement
			cameraControlInput.up = (keyboard_state[SDL_SCANCODE_UP] && !(keyboard_state[SDL_SCANCODE_DOWN]));
			cameraControlInput.down = (!keyboard_state[SDL_SCANCODE_UP] && (keyboard_state[SDL_SCANCODE_DOWN]));
			cameraControlInput.left = (keyboard_state[SDL_SCANCODE_LEFT] && !(keyboard_state[SDL_SCANCODE_RIGHT]));
			cameraControlInput.right = (!keyboard_state[SDL_SCANCODE_LEFT] && (keyboard_state[SDL_SCANCODE_RIGHT]));
		}

		// Switch scenes
		if (keyboard_state[SDL_SCANCODE_Y]) {
			if (_gameEngine->sceneManager.GetCurrentSceneNumber() == 0) {
				_gameEngine->sceneManager.SetScene(1);
			}
			else {
				_gameEngine->sceneManager.SetScene(0);
			}
		}
	}

	if (event.type == SDL_MOUSEMOTION)
	{
		SDL_GetMouseState(&xMouse, &yMouse);
	}
}

void Game::Update(Uint32 deltaTime)
{
	Scene* currentScene = _gameEngine->sceneManager.GetCurrentScene();

	if (currentScene == _gameEngine->sceneManager.GetScene(1)) {
		Vector2 movementVec = Vector2(0.0f, 0.0f);

		if (controlInput.left) movementVec += Vector2(-PLAYER_MOVEMENT_SPEED, 0) * deltaTime;
		if (controlInput.right) movementVec += Vector2(PLAYER_MOVEMENT_SPEED, 0) * deltaTime;
		if (controlInput.up) movementVec += Vector2(0, -PLAYER_MOVEMENT_SPEED) * deltaTime;
		if (controlInput.down) movementVec += Vector2(0, PLAYER_MOVEMENT_SPEED) * deltaTime;

		// TODO: Make camera an entity with a transform and velocity component instead of putting code here
		CameraComponent* cam = currentScene->GetMainCamera();
		Vector2 cameraVelocity = { 0.0f, 0.0f };

		if (Entity* player = currentScene->GetEntityByName("Player")) {
			// Player velocity
			player->GetComponent<VelocityComponent>()->_velocity = movementVec;

			// Player rotation
			Vector2 mouseWorldPos = currentScene->CameraToWorldPosition({ static_cast<float>(xMouse), static_cast<float>(yMouse) });
			TransformComponent* playerTransform = player->GetComponent<TransformComponent>();
			playerTransform->_rotation = Math::angleTo(player->GetComponent<TransformComponent>()->_position, mouseWorldPos);

			// Camera follow player
			Vector2 cameraPos = { cam->_cameraRect.x + (cam->_cameraRect.w / 2), cam->_cameraRect.y + (cam->_cameraRect.h / 2) };
			if (Math::distance(cameraPos, playerTransform->_position) > 30) {
				cameraVelocity = Math::velocityTo(cameraPos, playerTransform->_position);
			}
		}

		cam->_cameraRect.x += cameraVelocity._x * CAMERA_MOVEMENT_SPEED * deltaTime;
		cam->_cameraRect.y += cameraVelocity._y * CAMERA_MOVEMENT_SPEED * deltaTime;
	}
}

void Game::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}
