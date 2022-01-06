<br />
<div align="center">
  <h3 align="center">Game Engine</h3>
</div>

## About

An extension of SDL2 library that implements a base entity component system pattern and a few other basic common game functionality.
For learning purposes, at the moment.

![gameenginegithubpicture2](https://user-images.githubusercontent.com/21079379/148211584-d60b88d5-3c07-4d92-8b58-4771c7d25714.png)

### Key Features
* Design and load entities with preattached components from JSON
* 2D Transform / Velocity components, and basic Vector2D math functions
* Render component that can render multiple primitive shapes or sprites, with layers to define render order
* Viewport / camera offset
* Frame cap + time delta for updates
* Editor interface using Dear ImGUI


## How to

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/ShaunGittins/GameEngine.git
   ```
2. Download SDL2 headers and dev libraries (Windows, Visual Studio Community)
   https://libsdl.org/download-2.0.php
   
3. Add include and library directories
   * Solution Explorer -> Right-Click GameEngine -> Properties -> Configuration Properties -> VC++ Directories
   * Edit Include Directories and add SDL2/include directory from download
   * Edit Library Directories and add SDL2/lib/x86 directory from download
   
4. Let compiler find functions.
   * Solution Explorer -> Right-Click GameEngine -> Properties -> Configuration Properties -> Linker -> Input
   * Edit Additional Dependencies. Add SDL2.lib; SDL2main.lib;
   

### Scenes and SceneManager
```C++
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
```C++
// Create an entity
Entity* player = new Entity();

// Add components to an entity
player->AddComponent(new NameComponent("Player"));
```
### Components
```C++
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


## Other

### Future Features
* OpenGL or an alternative rather than SDL_Renderer to allow shaders to be implemented
* Code component to extend entity functionality
* Message / Event system (and then collision using the system)
* More primitives (circles, triangles)
* UUID
* CMake
* Audio system and components
* Load more file types for sprites
* Improve input system
* Text / Font
