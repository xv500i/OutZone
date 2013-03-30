
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
	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			std::stringstream sstr(line);
			int x, y, width, height, spriteIndex;
			sstr >> x;
			if (sstr.peek() == ',') sstr.ignore();
			sstr >> y;
			if (sstr.peek() == ',') sstr.ignore();
			sstr >> width;
			if (sstr.peek() == ',') sstr.ignore();
			sstr >> height;
			if (sstr.peek() == ',') sstr.ignore();
			sstr >> spriteIndex;
			GameObject object(x*TILE_WIDTH_IN_PIXELS + width/2, y*TILE_HEIGHT_IN_PIXELS + height/2, spriteIndex, width, height, false);
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
	for (unsigned int i = 0; i < objects.size(); i++) {
		objects[i].render(data);
	}
}