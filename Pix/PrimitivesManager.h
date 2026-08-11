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

enum class CullMode
{
	None, // no culling used
	Back, // cull anything facing away from the camera
	Front, // cull anything facing the camera
};

class PrimitivesManager
{
public:
	static PrimitivesManager* Get();

	void OnNewFrame();
	void SetCullMode(CullMode mode);

	// Start Acceopting Vertices
	bool BeginDraw(Topology topology, bool applyTransform);

	// ass vertices to the manager
	void AddVertex(const Vertex& v);

	// send all the stored vertices to render, as specified
	// by topology, to the resterizer
	void EndDraw();

private:
	PrimitivesManager();

	std::vector<Vertex> _vertexBuffer;
	Topology _topology = Topology::Point;
	CullMode mCullMode = CullMode::None;
	bool _drawBegin = false;
	bool mApplyTransform = false;
};