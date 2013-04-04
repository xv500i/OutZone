
#include "ObjectsLayer.h"
#include <iostream>
#include <sstream>
#include <fstream>


const char* ObjectsLayer::FILE_NAME_PREFIX = "level";
const char* ObjectsLayer::FILE_NAME_SUFIX = "Objects";
const char* ObjectsLayer::FILE_EXT = ".txt";

ObjectsLayer::ObjectsLayer(void) {}

ObjectsLayer::~ObjectsLayer(void) {}


/* Loading */
bool ObjectsLayer::load(int level, GameData *data)
{
	setLevel(level);

	// Open the file
	std::stringstream ss;
	ss << FILE_NAME_PREFIX << level << FILE_NAME_SUFIX << FILE_EXT;
	std::ifstream file(ss.str());

	// Read the file
	std::string line;
	objects = std::vector<GameObject>();
	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			std::stringstream sstr(line);
			int x, y, width, height, spriteIndex;
			char type, objectProperty;
			sstr >> type;
			if (sstr.peek() == ' ') sstr.ignore();
			sstr >> x;
			if (sstr.peek() == ',') sstr.ignore();
			sstr >> y;
			if (sstr.peek() == ' ') sstr.ignore();
			sstr >> width;
			if (sstr.peek() == ',') sstr.ignore();
			sstr >> height;
			if (sstr.peek() == ' ') sstr.ignore();
			sstr >> spriteIndex;
			if (sstr.peek() == ',') sstr.ignore();
			sstr >> objectProperty;
			GameObject object(x*TILE_WIDTH_IN_PIXELS + TILE_WIDTH_IN_PIXELS/2, y*TILE_HEIGHT_IN_PIXELS + TILE_HEIGHT_IN_PIXELS/2, spriteIndex, width, height, false);
			object.setType(type);
			if (objectProperty == 'C') {
				object.setPhantom(false);
				object.setInteractive(false);
			}
			else if (objectProperty == 'P') {
				object.setPhantom(true);
				object.setInteractive(false);
			}
			else if (objectProperty == 'I') {
				object.setPhantom(true);
				object.setInteractive(true);
				object.setAction(STATIC_UP);
			}
			objects.push_back(object);
		}
		return true;
	}
	else {
		std::cout << "Error obrint el fitxer de càrrega de la capa d'objectes del nivell " << level << std::endl;
		return false;
	}
}

/* Updating */
void ObjectsLayer::update(GameData *data)
{
	for (unsigned int i = 0; i < objects.size(); i++) {
		objects[i].update(data);
	}
}

/* Rendering */
void ObjectsLayer::render(GameData *data, Viewport *viewport)
{
	// Simulate an object with the viewport coordinates
	GameObject viewportObject = GameObject(viewport->getLeft() + viewport->getWidth()/2,
										   viewport->getTop() - viewport->getHeight()/2,
										   -1, viewport->getWidth(), viewport->getHeight(), false);
	for (unsigned int i = 0; i < objects.size(); i++) {
		if (objects[i].isIntersecting(viewportObject)) objects[i].render(data);
	}
}

/* Getters */
std::vector<GameObject> ObjectsLayer::getCollisionObjects()
{
	std::vector<GameObject> collisionObjects;
	collisionObjects.reserve(objects.size());
	for (unsigned int i = 0; i < objects.size(); i++) {
		if (objects[i].shouldNotEnterObjects()) collisionObjects.push_back(objects[i]);
	}
	return collisionObjects;
}

std::vector<GameObject> ObjectsLayer::getInteractiveObjects()
{
	std::vector<GameObject> interactiveObjects;
	for (unsigned int i = 0; i < objects.size(); i++) {
		if (objects[i].isInteractive()) interactiveObjects.push_back(objects[i]);
	}
	return interactiveObjects;
}

/* Modifiers */
void ObjectsLayer::removeObject(int index)
{
	objects.erase(objects.begin() + index);
}