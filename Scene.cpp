/*
 * Scene.cpp
 *
 *  Created on: Sep 10, 2018
 *  Author: John Hall
 */

#include "Scene.h"

#include <iostream>
#include "RenderingEngine.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Vertex.h"
#include <cstdlib>
#include <math.h>
#include <algorithm>
int counter = 0;


Scene::Scene(RenderingEngine* renderer) : renderer(renderer)
{
	changeToSpiralScene(0);
}

Scene::~Scene() {

}

void Scene::displayScene() {
	renderer->RenderScene(objects);
}

void Scene::changeToRandomTriangleScene(int it) {
	sceneType = "RANDOMTRI_SCENE";
	objects.clear();

	int numIts = it*200;
	numIts = std::min(15000, numIts);
	std::cout <<"numits: " << numIts<< "\n" << std::endl;
	//Vertices of initial triangle
		Vertex v1(-0.8, -0.6928);
		Vertex v0(0, 0.6928);
		Vertex v2(0.8, -0.6928);

	Geometry points;
	points.verts.push_back(glm::vec3(v1.x, v1.y, 1.0f));
	points.verts.push_back(glm::vec3(v0.x, v0.y, 1.0f));
	points.verts.push_back(glm::vec3(v2.x, v2.y, 1.0f));
	points.colors.push_back(glm::vec3(1.0,1.0,0.0)); points.colors.push_back(glm::vec3(1.0,1.0,0.0)); points.colors.push_back(glm::vec3(1.0,1.0,0.0));

		int next;
		Vertex currentPt = v0;
		Vertex nextPt(0.0f , 0.0f);

	for (int i = 1; i<=numIts; i++)
		{
			next = rand()%3;
				switch (next)
				{
					case 0: nextPt.x = v0.x; nextPt.y = v0.y;
						break;
					case 1: nextPt.x = v1.x; nextPt.y = v1.y;
						break;
					case 2:	nextPt.x = v2.x; nextPt.y = v2.y;
						break;
				}
		//find midpoint between currentPt and nextPt
			Vertex midPt((nextPt.x+currentPt.x)/2,(nextPt.y+currentPt.y)/2);
			currentPt = midPt;
			points.verts.push_back(glm::vec3(currentPt.x, currentPt.y, 1.0f));
			points.colors.push_back(glm::vec3(0.4f, 0.5f, 1.0f));


		}
		points.drawMode = GL_POINTS;
		//Construct vao and vbos for the triangle
		RenderingEngine::assignBuffers(points);
		//Send the triangle data to the GPU
		//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
		RenderingEngine::setBufferData(points);
		//Add the triangle to the scene objects
		objects.push_back(points);
}

Geometry Scene::moreSquares(int it, float sl, Geometry square){

	float sidelength = sqrt((1/(pow(2,it))));
	std::cout <<"it: " << it%2<< "\n" << std::endl;



	 if (it % 2 == 0) //even iterative levels are squares
	{

		//square vertices
			Vertex v1(-sidelength/2, -sidelength/2);
			Vertex v2(-sidelength/2,sidelength/2);
			Vertex v3(sidelength/2,sidelength/2);
			Vertex v4(sidelength/2,-sidelength/2);
		//create lines from vertices
			square.verts.push_back(glm::vec3(v1.x, v1.y, 1.0f)); //lineA
			square.verts.push_back(glm::vec3(v2.x, v2.y, 1.0f)); //lineA

			square.verts.push_back(glm::vec3(v3.x, v3.y, 1.0f));	//lineB
			square.verts.push_back(glm::vec3(v4.x, v4.y, 1.0f));	//lineB

			square.verts.push_back(glm::vec3(v2.x, v2.y, 1.0f));	//lineC
			square.verts.push_back(glm::vec3(v3.x, v3.y, 1.0f));	//lineC

			square.verts.push_back(glm::vec3(v1.x, v1.y, 1.0f));	//lineD
			square.verts.push_back(glm::vec3(v4.x, v4.y, 1.0f));	//lineD
			for (int i =1; i<=8; i++)
				{
					square.colors.push_back(glm::vec3(0.0, sidelength/sqrt(2)+0.2, 0.0f));
				}

			if (it == 0) {return square;}
			else {
			return moreSquares(it-1,sl,square );}

	}
	else	//else its a diamond level
	{
		//diamond vertices
			Vertex d1(0, sidelength/sqrt(2));
			Vertex d2(-sidelength/sqrt(2),0);
			Vertex d3(0,-sidelength/sqrt(2));
			Vertex d4(sidelength/sqrt(2),0);
		//create lines from vertices
			square.verts.push_back(glm::vec3(d1.x, d1.y, 1.0f)); //lineA
			square.verts.push_back(glm::vec3(d2.x, d2.y, 1.0f)); //lineA

			square.verts.push_back(glm::vec3(d3.x, d3.y, 1.0f));	//lineB
			square.verts.push_back(glm::vec3(d4.x, d4.y, 1.0f));	//lineB

			square.verts.push_back(glm::vec3(d2.x, d2.y, 1.0f));	//lineC
			square.verts.push_back(glm::vec3(d3.x, d3.y, 1.0f));	//lineC

			square.verts.push_back(glm::vec3(d1.x, d1.y, 1.0f));	//lineD
			square.verts.push_back(glm::vec3(d4.x, d4.y, 1.0f));	//lineD
			for (int i =1; i<=8; i++)
				{
					square.colors.push_back(glm::vec3(sidelength/sqrt(2)+0.2, 0.0, 0.0f));
				}
			return moreSquares(it-1, sl,square );
	}


}

void Scene::changeToSquareScene(int it){
	sceneType = "SQUARE_SCENE";
	objects.clear();
	Geometry square;

	square = moreSquares(it, 1.0f,square);

			square.drawMode = GL_LINES;
			//Construct vao and vbos for the triangle
			RenderingEngine::assignBuffers(square);
			//Send the triangle data to the GPU
			//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
			RenderingEngine::setBufferData(square);
			//Add the triangle to the scene objects
			objects.push_back(square);
}

void Scene::changeToTriangleScene(int it)
{
	sceneType = "TRIANGLE_SCENE";
	objects.clear();
	//Side-length, height, and vertices of initial triangle
	float sl = 1.6;
	float h = 1.3856; //rounded
	Vertex v1(-0.8, -0.6928);
	Vertex v0(0, 0.6928);
	Vertex v2(0.8, -0.6928);

	if (it <= 0) {
	//Initial triangle
	Geometry triangle;
	triangle.verts.push_back(glm::vec3(v1.x, v1.y, 1.0f));
	triangle.verts.push_back(glm::vec3(v0.x, v0.y, 1.0f));
	triangle.verts.push_back(glm::vec3(v2.x, v2.y, 1.0f));
	//Colors are stored per vertex in the order of the vertices
	triangle.colors.push_back(glm::vec3(0.4f, -0.5f, 1.0f));
	triangle.colors.push_back(glm::vec3(0.4f, 0.0f, 1.0f));
	triangle.colors.push_back(glm::vec3(0.4f, 0.5f, 1.0f));
	triangle.drawMode = GL_TRIANGLES;
		//Construct vao and vbos for the triangle
		RenderingEngine::assignBuffers(triangle);
		//Send the triangle data to the GPU
		//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
		RenderingEngine::setBufferData(triangle);
		//Add the triangle to the scene objects
		objects.push_back(triangle);
	}
	else if (it == 1) {

		Geometry triangle;
		//Triangle 1
			triangle.verts.push_back(glm::vec3(-0.8f, -0.6928f, 1.0f));
			triangle.verts.push_back(glm::vec3(-0.4f, 0.0f, 1.0f));
			triangle.verts.push_back(glm::vec3(0.0f, -0.6928f, 1.0f));
		//Triangle 0
			triangle.verts.push_back(glm::vec3(-0.4f, 0.0f, 1.0f));
			triangle.verts.push_back(glm::vec3(0.0f, 0.6928f, 1.0f));
			triangle.verts.push_back(glm::vec3(0.4f, 0.0f, 1.0f));
		//Triangle 2
			triangle.verts.push_back(glm::vec3(0.0f, -0.6928f, 1.0f));
			triangle.verts.push_back(glm::vec3(0.4f, 0.0f, 1.0f));
			triangle.verts.push_back(glm::vec3(0.8f, -0.6928f, 1.0f));


						triangle.colors.push_back(glm::vec3(abs(-0.8f), -0.6928f, 1.0f));
						triangle.colors.push_back(glm::vec3(abs(-0.4f), 0.0f, 1.0f));
						triangle.colors.push_back(glm::vec3(0.0f, -0.6928f, 1.0f));
					//Triangle 0
						triangle.colors.push_back(glm::vec3(abs(-0.4f), 0.0f, 1.0f));
						triangle.colors.push_back(glm::vec3(0.6f, -0.6928f, 1.0f));
						triangle.colors.push_back(glm::vec3(0.4f, 0.0f, 1.0f));
					//Triangle 2
						triangle.colors.push_back(glm::vec3(0.0f, -0.6928f, 1.0f));
						triangle.colors.push_back(glm::vec3(0.4f, 0.0f, 1.0f));
						triangle.colors.push_back(glm::vec3(0.8f, -0.6928f, 1.0f));


			triangle.drawMode = GL_TRIANGLES;

				//Construct vao and vbos for the triangle
				RenderingEngine::assignBuffers(triangle);

				//Send the triangle data to the GPU
				//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
				RenderingEngine::setBufferData(triangle);

				//Add the triangle to the scene objects
				objects.push_back(triangle);
	}

	else if (it > 1 )
	{
		if (it > 7) {it = 7;}
		Geometry triangle;

		triangle = split3(v1, sl, h, triangle, 0, it);

							triangle.drawMode = GL_TRIANGLES;
							//Construct vao and vbos for the triangle
							RenderingEngine::assignBuffers(triangle);

							//Send the triangle data to the GPU
							//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
							RenderingEngine::setBufferData(triangle);

							//Add the triangle to the scene objects
							objects.push_back(triangle);
	}
}

Geometry Scene::split3(Vertex v1, float sl, float h, Geometry triangle, int recursionLvl, int numIts){
	if ( recursionLvl == numIts-1) {
		//Baby triangle (1)
				triangle.verts.push_back(glm::vec3(v1.x, v1.y , 1.0f));
				triangle.verts.push_back(glm::vec3(v1.x+(0.25*sl), v1.y+(0.5*h), 1.0f));
				triangle.verts.push_back(glm::vec3(v1.x+(0.5*sl), v1.y , 1.0f));
		//Baby triangle (0)
				triangle.verts.push_back(glm::vec3(v1.x+(0.25*sl), v1.y+(0.5*h), 1.0f));
				triangle.verts.push_back(glm::vec3(v1.x+(0.5*sl), v1.y+(h), 1.0f));
				triangle.verts.push_back(glm::vec3(v1.x+(0.75*sl), v1.y+(0.5*h) , 1.0f));
		//Baby triangle (2)
				triangle.verts.push_back(glm::vec3(v1.x+(0.5*sl), v1.y, 1.0f));
				triangle.verts.push_back(glm::vec3(v1.x+(0.75*sl), v1.y+(0.5*h), 1.0f));
				triangle.verts.push_back(glm::vec3(v1.x+(sl), v1.y , 1.0f));


		//color it
				//Baby triangle (1)
						triangle.colors.push_back(glm::vec3(abs(v1.x+(sl))*2, (v1.y)*2 , 1));
						triangle.colors.push_back(glm::vec3(abs(v1.x+(0.25*sl))*2, (v1.y+(0.5*h))*2, 1));
						triangle.colors.push_back(glm::vec3(abs(v1.x+(0.5*sl))*2, (v1.y)*2, 1.0f));
				//Baby triangle (0)
						triangle.colors.push_back(glm::vec3(abs(v1.x+(0.25*sl))*2, -abs((v1.y+(0.5*h))*2), 1));
						triangle.colors.push_back(glm::vec3(abs(v1.x+(0.5*sl))*2, -abs((v1.y+(h))*2), 1));
						triangle.colors.push_back(glm::vec3(abs(v1.x+(0.75*sl))*2, -abs((v1.y+(0.5*h))*2) , 1));
				//Baby triangle (2)
						triangle.colors.push_back(glm::vec3(abs(v1.x+(0.5*sl))*2, (v1.y)*2, 1));
						triangle.colors.push_back(glm::vec3(abs(v1.x+(0.75*sl))*2, (v1.y+(0.5*h))*2, 1));
						triangle.colors.push_back(glm::vec3(abs(v1.x+(sl))*2, (v1.x)*2 , 1));

return triangle;
	}
	else if ( recursionLvl < numIts) {

		//v1's of the 3 child triangles of the parent triangle that called split3(...)
				Vertex w1(v1.x, v1.y);
				Vertex w0(v1.x+(0.25*sl), v1.y+(0.5*h));
				Vertex w2(v1.x+(0.5*sl), v1.y);
		triangle = split3(w1, sl/2, h/2, triangle, recursionLvl+1, numIts);
		triangle = split3(w0, sl/2, h/2, triangle, recursionLvl+1, numIts);
		triangle = split3(w2, sl/2, h/2, triangle, recursionLvl+1, numIts);

	}



	return triangle;
}

void Scene::changeToSpiralScene(int it)
{
	//it = revolutions
	int scale = 20;
	sceneType = "SPIRAL_SCENE";
	objects.clear();
	it = std::min(it, 4);
	std::cout <<"numits: " << it<< "\n" << std::endl;
	//Create a single triangle
	//Additional triangles can be created by pushing groups of three more vertices into the verts vector
	Geometry circle;
	int numSegments = 100;
	float du = 2 * 3.14f / numSegments;
	for (float u = 0; u < 2*(it+1) * 3.14f; u += du)
	{
		//vertex at this value of u
		circle.verts.push_back(glm::vec3((u * sin(u))/scale, (u * cos(u))/scale, 1.0));
		//color at this value of u
		circle. colors.push_back(glm::vec3(1-(u/scale),0, 1-(u/scale)));
	}

	circle.drawMode = GL_LINE_STRIP;

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(circle);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(circle);

	//Add the triangle to the scene objects
	objects.push_back(circle);
}

void Scene::switchScene(int direction)
{

	if (direction == -1)
	{
		if (sceneType == "RANDOMTRI_SCENE")
			{counter = 0; changeToTriangleScene(counter);}

		else if(sceneType == "TRIANGLE_SCENE" )
			{counter=0; changeToSpiralScene(counter);}

		else if(sceneType == "SPIRAL_SCENE")
		{counter=0; changeToSquareScene(counter);}

		else if (sceneType == "SQUARE_SCENE")
			{counter = 0; changeToRandomTriangleScene(counter);}

	}
	else if (direction == 1)
	{

		if (sceneType == "SQUARE_SCENE")
			{counter=0;changeToSpiralScene(counter);}

		else if(sceneType == "SPIRAL_SCENE" )
			{counter=0;changeToTriangleScene(counter);}

		else if(sceneType == "TRIANGLE_SCENE")
		{ counter=0;changeToRandomTriangleScene(counter);}

		else if (sceneType == "RANDOMTRI_SCENE")
			{counter=0;changeToSquareScene(counter);
			}
		}
}

void Scene::iterationUp()
{//std::cout << "iteration up for triangle scene! " << counter << std::endl;
	++counter;

	if (sceneType == "TRIANGLE_SCENE")
		{changeToTriangleScene(counter);}

	else if (sceneType == "SPIRAL_SCENE")
		{changeToSpiralScene(counter);}

	else if (sceneType == "RANDOMTRI_SCENE")
		{changeToRandomTriangleScene(counter);}

	else if (sceneType == "SQUARE_SCENE")
		{changeToSquareScene(counter);}
}

void Scene::iterationDown()
{
	--counter;

	if (sceneType == "TRIANGLE_SCENE")
		{changeToTriangleScene(counter);}

	else if (sceneType == "SPIRAL_SCENE")
		{changeToSpiralScene(counter);}

	else if (sceneType == "RANDOMTRI_SCENE")
		{changeToRandomTriangleScene(counter);}

	else if (sceneType == "SQUARE_SCENE")
		{changeToSquareScene(counter);}
}

