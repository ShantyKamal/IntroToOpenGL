/*
 * Scene.h
 *	Class for storing objects in a scene
 *  Created on: Sep 10, 2018
 *      Author: cb-ha
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <string>
#include <sstream>
#include "Geometry.h"
#include "Vertex.h"

//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
class RenderingEngine;

class Scene {

public:
	Scene(RenderingEngine* renderer);
	virtual ~Scene();

	//Send geometry to the renderer
	void displayScene();

	//scene change functions
	void changeToTriangleScene(int it);
	void changeToSquareScene(int it);
	Geometry moreSquares(int it, float sl, Geometry square);
	void changeToSpiralScene(int it);
	Geometry split3(Vertex v1, float sl, float h, Geometry triangle, int recursionLvl, int numIts);
	void changeToRandomTriangleScene(int it);
	void iterationUp();
	void iterationDown();
	void switchScene(int direction); //-1 = left, 1 = right


private:
	std::string sceneType;
	RenderingEngine* renderer;

	//list of objects in the scene
	std::vector<Geometry> objects;
};

#endif /* SCENE_H_ */
