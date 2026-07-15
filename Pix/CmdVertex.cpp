#include "CmdVertex.h"
#include "PrimitivesManager.h"

bool CmdVertex::Execute(const std::vector<std::string>& params)
{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;

	float r = 1.f;
	float g = 1.f;
	float b = 1.f;

	if (params.size() == 2) // only 2D position
	{
		x = std::stof(params[0]);
		y = std::stof(params[1]);
	}
	else if (params.size() == 3) // only 2D position
	{
		x = std::stof(params[0]);
		y = std::stof(params[1]);
		z = std::stof(params[2]);
	}
	else if (params.size() == 5) // 2D position and color
	{
		x = std::stof(params[0]);
		y = std::stof(params[1]);
		r = std::stof(params[2]);
		g = std::stof(params[3]);
		b = std::stof(params[4]);
	}
	else if (params.size() == 6) // 3D position and color
	{
		x = std::stof(params[0]);
		y = std::stof(params[1]);
		z = std::stof(params[2]);
		r = std::stof(params[3]);
		g = std::stof(params[4]);
		b = std::stof(params[5]);
	}
	else 
	{ 
		bool theKing = false;
		return theKing;
	}

	Vertex v;
	v.pos = { x, y, z };
	v.color = { r, g, b, 1.f };
	PrimitivesManager::Get()->AddVertex(v);
	return true;

}