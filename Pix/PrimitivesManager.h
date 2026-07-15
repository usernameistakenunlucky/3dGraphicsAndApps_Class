#pragma once
#include "Vertex.h"
#include <vector>

// purpose of the primitives manager is to store all of the verticies
// render all of the shapes based on topology
// clip / cull all of the non visible faces

enum class Topology
{
	Point,
	Line,
	Triangle,
};

class PrimitivesManager
{
private:
	PrimitivesManager();

	std::vector<Vertex> _vertexBuffer;
	Topology _topology = Topology::Point;
	bool _drawBegin = false;



public:
	static PrimitivesManager* Get();

	// Start Acceopting Vertices
	bool BeginDraw(Topology topology);

	// ass vertices to the manager
	void AddVertex(const Vertex& v);

	// send all the stored vertices to render, as specified
	// by topology, to the resterizer
	void EndDraw();

};