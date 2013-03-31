
#include "StaticTilesLayer.h"
#include <iostream>
#include <sstream>


const char* StaticTilesLayer::FILE_NAME_PREFIX = "level";
const char* StaticTilesLayer::FILE_EXT = ".txt";

StaticTilesLayer::StaticTilesLayer(void) {}

StaticTilesLayer::~StaticTilesLayer(void) {}


/* Loading */
bool StaticTilesLayer::load(int level, GameData *data)
{
	setLevel(level);

	// Open the file
	std::stringstream ss;
	ss << FILE_NAME_PREFIX << level << FILE_EXT;
	std::ifstream file(ss.str());

	// Read the file
	std::string line;
	bool b = true;
	if (file.is_open()) {
		while (file.good() && b) {
			getline(file, line);

			if (line.find("header") != std::string::npos) b = loadHeader(file);
			else if (line.find("layer") != std::string::npos) {
				getline(file, line);
				if (line.find("collision") != std::string::npos) b = loadCollisionLayer(file);
				else if (line.find("background") != std::string::npos) b = loadBackgroundLayer(file);
				else if (line.find("hover") != std::string::npos) b = loadHoverLayer(file);
			}
		}
		if (b) return true;
		else {
			std::cout << "Error llegint el fitxer de carrega de les capes estatiques del nivell " << level << std::endl;
			return false;
		}
	}
	else {
		std::cout << "Error obrint el fitxer de carrega de les capes estatiques del nivell " << level << std::endl;
		return false;
	}
}

bool StaticTilesLayer::loadHeader(std::ifstream &file)
{
	std::string line;
	if (file.is_open()) {
		for (unsigned int i = 0; i < 4; i++) {
			getline(file, line);
			if (line.find("tilewidth") != std::string::npos) tileWidthInPixels = TILE_WIDTH_IN_PIXELS;
			else if (line.find("tileheight") != std::string::npos) tileHeightInPixels = TILE_HEIGHT_IN_PIXELS;
			else if (line.find("width") != std::string::npos) widthInTiles = atoi(line.substr(line.find("=") + 1).c_str());
			else if (line.find("height") != std::string::npos) heightInTiles = atoi(line.substr(line.find("=") + 1).c_str());
			else return false;
		}
		backgroundLayer = std::vector<Tile>(widthInTiles*heightInTiles);
		hoverLayer = std::vector<Tile>(widthInTiles*heightInTiles);
		return true;
	}
	else return false;
}

bool StaticTilesLayer::loadCollisionLayer(std::ifstream &file)
{
	std::string line;
	if (file.is_open()) {
		getline(file, line);	// Obtenim i descartem la linea amb "data="
		for (int i = 0; i < heightInTiles; i++) {
			getline(file, line);
			std::stringstream ss(line);
			for (int j = 0; j < widthInTiles; j++) {
				int type;
				ss >> type;
				ss.ignore();	// Ignorem la coma
				if (type == 1) backgroundLayer[i*widthInTiles + j].type = WALL;
				else if (type == 2) backgroundLayer[i*widthInTiles + j].type = HOLE;
				else backgroundLayer[i*widthInTiles + j].type = LAND;
			}
		}
		return true;
	}
	else return false;
}

bool StaticTilesLayer::loadBackgroundLayer(std::ifstream &file)
{
	std::string line;
	if (file.is_open()) {
		getline(file, line);	// Obtenim i descartem la linea amb "data="
		for (int i = 0; i < heightInTiles; i++) {
			getline(file, line);
			std::stringstream ss(line);
			for (int j = 0; j < widthInTiles; j++) {
				ss >> backgroundLayer[i*widthInTiles + j].index;
				ss.ignore();	// Ignorem la coma
			}
		}
		return true;
	}
	else return false;
}

bool StaticTilesLayer::loadHoverLayer(std::ifstream &file)
{
	std::string line;
	if (file.is_open()) {
		getline(file, line);	// Obtenim i descartem la linea amb "data="
		for (int i = 0; i < heightInTiles; i++) {
			getline(file, line);
			std::stringstream ss(line);
			for (int j = 0; j < widthInTiles; j++) {
				ss >> hoverLayer[i*widthInTiles + j].index;
				ss.ignore();	// Ignorem la coma
			}
		}
		return true;
	}
	else return false;
}

/* Rendering */
void StaticTilesLayer::render(GameData *data, Viewport *viewport) 
{
	// Get min and max X and Y of the tiles that are on-screen
	int minX, maxX, minY, maxY;
	minX = viewport->getLeft()/tileWidthInPixels;
	minY = heightInTiles - viewport->getTop()/tileHeightInPixels;
	maxX = (viewport->getLeft() + viewport->getWidth())/tileWidthInPixels;
	maxY = heightInTiles - (viewport->getTop() - viewport->getHeight())/tileHeightInPixels;

	for (int i = 0; i < heightInTiles; i++) {
		for (int j = 0; j < widthInTiles; j++) {
			if (j >= minX && j <= maxX && i >= minY && i <= maxY) {	// Render only if visible
				int index = backgroundLayer[i*widthInTiles + j].index;
				if (index != 0) renderTile(index, tileWidthInPixels*j, tileHeightInPixels*i, 0, data);
				index = hoverLayer[i*widthInTiles + j].index;
				if (index != 0) renderTile(index, tileWidthInPixels*j, tileHeightInPixels*i, 2, data);
			}
		}
	}
}

void StaticTilesLayer::renderTile(int tileIndex, int posX, int posY, int depth, GameData *data) 
{
	// Obtain the tile offset
	float tileOffsetX, tileOffsetY;
	data->getTileSheetTileOffset(getTileSheetIndex(), &tileOffsetX, &tileOffsetY);	

	// Obtain the tile position inside the texture
	int s, t;
	data->getTileSheetTilePosition(getTileSheetIndex(), tileIndex, &s, &t);
	float coordS = s*tileOffsetX;
	float coordT = t*tileOffsetY;

	// Rendering
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, data->getTileSheetID(getTileSheetIndex()));
	glPushMatrix();
	glTranslatef(posX, -posY, 0.0f);
	glBegin(GL_QUADS);
		// Top-left
		glTexCoord2f(coordS, coordT);
		glVertex3i(0, heightInTiles*tileHeightInPixels, depth);	
		// Top-right
		glTexCoord2f(coordS + tileOffsetX, coordT);
		glVertex3i(tileWidthInPixels, heightInTiles*tileHeightInPixels, depth);
		// Bottom-right
		glTexCoord2f(coordS + tileOffsetX, coordT + tileOffsetY);
		glVertex3i(tileWidthInPixels, heightInTiles*tileHeightInPixels - tileHeightInPixels, depth);	
		// Bottom-left
		glTexCoord2f(coordS, coordT + tileOffsetY);
		glVertex3i(0, heightInTiles*tileHeightInPixels - tileHeightInPixels, depth);	
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

/* Getters */
void StaticTilesLayer::getSizeInTiles(int *width, int *height)
{
	*width = widthInTiles;
	*height = heightInTiles;
}

void StaticTilesLayer::getSizeInPixels(int *width, int *height)
{
	int widthInTiles, heightInTiles;
	int tileWidth, tileHeight;
	getSizeInTiles(&widthInTiles, &heightInTiles);
	getTileSizeInPixels(&tileWidth, &tileHeight);
	*width = widthInTiles*tileWidth;
	*height = heightInTiles*tileHeight;
}

void StaticTilesLayer::getTileSizeInPixels(int *width, int *height)
{
	*width = tileWidthInPixels;
	*height = tileHeightInPixels;
}

int StaticTilesLayer::getTileSheetIndex()	// TOCHANGE: Descomentar a mesura que s'afegeixin tileSheets
{
	int level = getLevel();
	switch (level) {
	case 1: return GameData::LEVEL1_TILES_INDEX;
	//case 2: return GameData::LEVEL2_TILES_INDEX;
	//...
	default: return -1;
	}
}

std::vector<bool>& StaticTilesLayer::getCollisionMap()
{
	std::vector<bool> collisionMap = std::vector<bool>(backgroundLayer.size());
	for (unsigned int i = 0; i < backgroundLayer.size(); i++) {
		if (backgroundLayer[i].type == WALL || backgroundLayer[i].type == HOLE) collisionMap[i] = true;
		else collisionMap[i] = false;
	}
	return collisionMap;
}