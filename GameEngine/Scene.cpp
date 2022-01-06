#include "Scene.h"
#include "NameComponent.h"

Scene::Scene(RenderSystem* renderSystem, TransformSystem* transformSystem)
{
	_renderSystem = renderSystem;
	_transformSystem = transformSystem;
}

Scene::~Scene()
{
	delete _renderSystem;
	delete _transformSystem;

	for (auto& entity : entities) {
		delete entity;
	}
	entities.clear();
}

void Scene::AddEntityToScene(Entity* entity)
{
	if (VelocityComponent* velocityComponent = entity->GetComponent<VelocityComponent>()) {
		_transformSystem->AddComponentReference(velocityComponent);
	}

	if (RenderComponent* renderComponent = entity->GetComponent<RenderComponent>()) {
		_renderSystem->AddComponentReference(renderComponent);
	}
	
	entities.push_back(entity);
}

void Scene::AddEntitiesFromJSON(std::string filename)
{
	// Load JSON file to document
	std::ifstream ifs(filename);
	IStreamWrapper isw(ifs);
	Document document;
	document.ParseStream(isw);

	// Load document to entities
	assert(document.HasMember("entities"));
	const Value& entities = document["entities"];
	assert(entities.IsArray());

	for (SizeType i = 0; i < entities.Size(); i++) {
		Entity* entity = new Entity();
		const Value& components = entities[i]["components"];

		if (components.HasMember("name")) {
			string name = components["name"].GetString();
			entity->AddComponent(new NameComponent(name));
		}

		if (components.HasMember("render")) {
			RenderComponent* renderComponent = new RenderComponent(_renderSystem->GetRenderer());
			renderComponent->layer = components["render"]["layer"].GetInt();

			if (components["render"].HasMember("rectangles")) {
				const Value& rectangles = components["render"]["rectangles"];
				for (SizeType j = 0; j < rectangles.Size(); j++) {
					float x = rectangles[j]["x"].GetFloat();
					float y = rectangles[j]["y"].GetFloat();
					float width = rectangles[j]["width"].GetFloat();
					float height = rectangles[j]["height"].GetFloat();
					renderComponent->AddRect({ x, y, width, height });
				}
			}

			if (components["render"].HasMember("sprites")) {
				const Value& sprites = components["render"]["sprites"];
				for (SizeType j = 0; j < sprites.Size(); j++) {
					float x = sprites[j]["x"].GetFloat();
					float y = sprites[j]["y"].GetFloat();
					float width = sprites[j]["width"].GetFloat();
					float height = sprites[j]["height"].GetFloat();
					string filename = sprites[j]["filename"].GetString();
					float originX = 0.0f;
					float originY = 0.0f;
					double angle = 0;
					if (sprites[j].HasMember("originX") && sprites[j].HasMember("originY") && sprites[j].HasMember("angle")) {
						originX = sprites[j]["originX"].GetFloat();
						originY = sprites[j]["originY"].GetFloat();
						angle = sprites[j]["angle"].GetDouble();
					}
					renderComponent->AddSprite(filename, { x, y, width, height }, originX, originY, angle);
				}
			}

			entity->AddComponent(renderComponent);
		}

		if (components.HasMember("transform")) {
			float x = components["transform"]["xPosition"].GetFloat();
			float y = components["transform"]["yPosition"].GetFloat();
			float rotation = components["transform"]["rotation"].GetFloat();
			float xScale = components["transform"]["xScale"].GetFloat();
			float yScale = components["transform"]["yScale"].GetFloat();
			entity->AddComponent(new TransformComponent({ x, y }, rotation, { xScale, yScale }));
		}

		if (components.HasMember("velocity")) {
			float x = components["velocity"]["x"].GetFloat();
			float y = components["velocity"]["y"].GetFloat();
			entity->AddComponent(new VelocityComponent(Vector2(x, y)));
		}

		AddEntityToScene(entity);
	}
}

Entity* Scene::GetEntityByName(std::string name)
{
	// TODO: Add unique names
	for (auto& entity : entities) {
		NameComponent* nameComponent = entity->GetComponent<NameComponent>();
		if (nameComponent) {
			if (nameComponent->_name == name) {
				return entity;
			}
		}
	}
	return nullptr;
}

Entity* Scene::GetEntityByID(uint64_t id)
{
	for (auto& entity : entities) {
		if (entity->_id = id) {
			return entity;
		}
	}
	return nullptr;
}

void Scene::SetMainCamera(CameraComponent* mainCamera)
{
	_renderSystem->SetMainCamera(mainCamera);
}

CameraComponent* Scene::GetMainCamera()
{
	return _renderSystem->GetMainCamera();
}

Vector2 Scene::CameraToWorldPosition(Vector2 positionInCamera)
{
	return { GetMainCamera()->_cameraRect.x + positionInCamera._x, GetMainCamera()->_cameraRect.y + positionInCamera._y };
}

void Scene::Update()
{
	_transformSystem->Update();
}

void Scene::Render()
{
	_renderSystem->Render();
}
