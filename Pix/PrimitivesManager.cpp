#include "PrimitivesManager.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include "Camera.h"
#include "MatrixStack.h"

extern float gResolutionX;
extern float gResolutionY;

namespace
{
	Matrix4 GetScreenTransform()
	{
		const float hw = gResolutionX * 0.5f;
		const float hh = gResolutionY * 0.5f;
		return
		{
			hw,  0.0f, 0.0f, 0.0f,
			0.0f, -hh, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			hw,  hh,   0.0f, 1.0f
		};
	}

	Vector3 CreateFaceNormal(const std::vector<Vertex>& triangle)
	{
		// take b-a cross c-a
		const Vector3& a = triangle[0].pos;
		const Vector3& b = triangle[1].pos;
		const Vector3& c = triangle[2].pos;
		Vector3 norm = MathHelper::Normalize(MathHelper::Cross(b - a, c - a));
		return norm;
	}
	bool CullTriangle(CullMode mode, const std::vector<Vertex>& triangle)
	{
		if (mode == CullMode::None)
		{
			return false;
		}
		Vector3 faceNormal = CreateFaceNormal(triangle);
		if (mode == CullMode::Back)
		{
			return faceNormal.z > 0.f;
		}
		if (mode == CullMode::Front)
		{
			return faceNormal.z < 0.f;
		}
		return false;
	}


}

PrimitivesManager::PrimitivesManager()
{

}

PrimitivesManager* PrimitivesManager::Get()
{
	static PrimitivesManager instance;
	return &instance;
}

void PrimitivesManager::OnNewFrame()
{
	mCullMode = CullMode::Back;
}

void PrimitivesManager::SetCullMode(CullMode mode)
{
	mCullMode = mode;
}

bool PrimitivesManager::BeginDraw(Topology topology, bool applyTransform)
{
	_vertexBuffer.clear();
	_topology = topology;
	mApplyTransform = applyTransform;
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

	// apply transformation pipeline
// matLocal -> matWorld -> matView -> matProj -> matScreen
	Matrix4 matWorld = MatrixStack::Get()->GetTransform();
	// view matrix from the camera
	Matrix4 matView = Camera::Get()->GetViewMatrix();
	// projection matrix from the camera
	Matrix4 matProj = Camera::Get()->GetProjectionMatrix();
	// screen space matrix from the screen
	Matrix4 matScreen = GetScreenTransform();
	// full transformation pipeline (comented out for notes, full pipeline)
	//Matrix4 matFinal = matWorld * matView* matProj* matScreen;
	Matrix4 matNDCSpace = matWorld * matView * matProj;

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
				if (mApplyTransform)
				{
					// transform to NDC space, then check facing to see if you can draw, then draw
					// use 3 points of triangle to make a normal direction
					// check the normal if it should be culled, proceed or cancel
					for (size_t t = 0; t < triangle.size(); t++)
					{
						// transform all positions to NDC Space
						triangle[t].pos = MathHelper::TransformCoord(triangle[t].pos, matNDCSpace);
					}

					// triangle in NDC space, if cull mode says to cull, continue, otherwise render
					if (CullTriangle(mCullMode, triangle))
					{
						continue;
					}

					// transformation pipeline (matFinal, transforms from local to screen space)
					for (size_t t = 0; t < triangle.size(); ++t)
					{
						// if already in NDC space, transform again just with the remaining matrices (matScreen)
						triangle[t].pos = MathHelper::TransformCoord(triangle[t].pos, matScreen);
						// after converting to screen space, make sure x and y are whole numbers
						MathHelper::FlattenVectorScreenCoord(triangle[t].pos);
					}
				}
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
