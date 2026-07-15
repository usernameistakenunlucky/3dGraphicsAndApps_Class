#include "PrimitivesManager.h"
#include "Rasterizer.h"

PrimitivesManager::PrimitivesManager()
{

}

PrimitivesManager* PrimitivesManager::Get()
{
	static PrimitivesManager instance;
	return &instance;
}

bool PrimitivesManager::BeginDraw(Topology topology)
{
	_vertexBuffer.clear();
	_topology = topology;
	_drawBegin = true;
	return true;
}

void PrimitivesManager::AddVertex(const Vertex& v)
{
	if (_drawBegin)
	{
		_vertexBuffer.push_back(v);
	}
}

void PrimitivesManager::EndDraw()
{
	if (!_drawBegin)
	{
		return;
	}

	switch (_topology)
	{
	case Topology::Point:
	{
		for (uint32_t i = 0; i < _vertexBuffer.size(); i++)
		{
			Rasterizer::Get()->DrawPoint(_vertexBuffer[i]);
		}
	}
	break;
	case Topology::Line:
	{
		for (uint32_t i = 1; i < _vertexBuffer.size(); i += 2)
		{
			Rasterizer::Get()->DrawLine(_vertexBuffer[i - 1], _vertexBuffer[i]);
		}
	}
	break;
	case Topology::Triangle:
	{
		for (uint32_t i = 2; i < _vertexBuffer.size(); i += 3)
		{
			Rasterizer::Get()->DrawTriangle(_vertexBuffer[i - 2], _vertexBuffer[i - 1], _vertexBuffer[i]);
		}
	}
	break;
	default:;
	}
}
