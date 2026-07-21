#include "PrimitivesManager.h"
#include "Rasterizer.h"
#include "Clipper.h"

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
			if (!Clipper::Get()->ClipPoint(_vertexBuffer[i]))
			{
				Rasterizer::Get()->DrawPoint(_vertexBuffer[i]);
			}
		}
	}
	break;
	case Topology::Line:
	{
		for (uint32_t i = 1; i < _vertexBuffer.size(); i += 2)
		{
			if (!Clipper::Get()->ClipLine(_vertexBuffer[i - 1], _vertexBuffer[i]))
			{
				Rasterizer::Get()->DrawLine(_vertexBuffer[i - 1], _vertexBuffer[i]);
			}
		}
	}
	break;
	case Topology::Triangle:
	{
		for (uint32_t i = 2; i < _vertexBuffer.size(); i += 3)
		{
			std::vector<Vertex> triangle = {
				_vertexBuffer[i - 2],
				_vertexBuffer[i - 1],
				_vertexBuffer[i]
			};
			if (!Clipper::Get()->ClipTriangle(triangle))
			{
				for (size_t t = 2; t < triangle.size(); t++)
				{
					Rasterizer::Get()->DrawTriangle(triangle[0], triangle[t - 1], triangle[t]);
				}
			}
		}
	}
	break;
	default:;
	}
}
