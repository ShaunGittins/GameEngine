# GameEngine
## Description
An extension of SDL2 library that implements a base entity component system pattern and a few other basic common game functionality.

## Key feature reference / examples
### Scenes and SceneManager
```
// Create a scene and add it to the scene manager
Scene* scene = new Scene(_renderer, defaultCamera);
_sceneManager->AddScene(scene);

// Add entities to the scene
_sceneManager->GetCurrentScene()->AddEntityToScene(<entity>);

// Switch scene
_sceneManager->SetScene(0);

// Get a specific object from the scene, can be used to update the component
_sceneManager->GetCurrentScene()->GetEntityByName("Player");
```

### Entities
```
// Create an entity
Entity* player = new Entity();

// Add components to an entity
player->AddComponent(new NameComponent("Player"));
```
### Components
```
// Name component gives the entity a name, which then can be used to identify it, this however is not unique, and it's recommended to use entity _id
new NameComponent("Player");

// Render component can draw primitive shapes and sprites
// Both AddRect and AddSprite take in a rectangle { xPosition, yPosition, width, height }
RenderComponent* renderComponent = new RenderComponent(_renderer);
playerRenderComponent->AddRect({ 4, 4, 15, 8 });
playerRenderComponent->AddRect({ 8, 8, 12, 12 });
playerRenderComponent->AddSprite(SDL_LoadBMP("ball.bmp"), { 32, 32, 32, 48 });

// Transform component stores x and y positions in a Vector2, a rotation value and x and y scale in another Vector2
// If the entity has a render component this usually dictates where it appears on the screen
new TransformComponent({ 250, 150 }, 0.0f, { 48, 48 });

// Velocity component is used by transform system to affect the transform component of the entity
// Can be used like below
// Init()
player->AddComponent(new VelocityComponent(Vector2(0, 0)));

// Update()
Vector2 movementVec = Vector2(0.0f, 0.0f);
if (controlInput.left) movementVec += Vector2(-MOVEMENT_SPEED, 0) * deltaTime;
player->GetComponent<VelocityComponent>()->_velocity = movementVec;
```

### Systems
Each scene contains systems that manage particular components. When an entity is added to a scene, the scene will grab a reference to the entities' components and deligate specific types of components to the scene's systems.

For example RenderComponents will be sent to the the scene's RenderSystem. And when it is asked to Render(), it will go through all RenderComponents in the scene and call their Render() function for each RenderComponent that is set to visible.
The RenderSystem also dictates the order of which things are drawn, and also holds onto a "main camera", which offsets where everything is drawn in relation to the camera position.

TransformComponents and VelocityComponents are sent to the TransformSystem. Entities with both transform and velocity components will be affected by the TransformSystem each update when the velocity component values are non-zero.
