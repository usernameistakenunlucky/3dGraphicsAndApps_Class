#include "Rasterizer.h"
#include "DepthBuffer.h"
#include "LightManager.h"
#include "TextureManager.h"

// a function for drawing a line where the slope is <= 1
// left is the small x position, right is the highest x position
// this allows for indexing in a positive direction (simple math)
void DrawLineHorizontal(const Vertex& left, const Vertex& right)
{
	float dx = right.pos.x - left.pos.x;
	int startX = static_cast<int>(left.pos.x);
	int endX = static_cast<int>(right.pos.x);
	for (int x = startX; x <= endX; x++)
	{
		float t = static_cast<float>(x - startX) / dx;
		Vertex v = LerpVertex(left, right, t);
		Rasterizer::Get()->DrawPoint(v);
	}
}

void DrawLineVertical(const Vertex& low, const Vertex& high)
{
	float dy = high.pos.y - low.pos.y;
	int startY = static_cast<int>(low.pos.y);
	int endY = static_cast<int>(high.pos.y);
	for (int y = startY; y <= endY; y++)
	{
		float t = static_cast<float>(y - startY) / dy;
		Vertex v = LerpVertex(low, high, t);
		Rasterizer::Get()->DrawPoint(v);
	}
}

Rasterizer* Rasterizer::Get()
{
	static Rasterizer sInstance;
	return &sInstance;
}
 
void Rasterizer::SetColor(X::Color color)
{
	mColor = color;
}

void Rasterizer::SetFillMode(FillMode fillmode)
{
	mFillMode = fillmode;
}

void Rasterizer::SetShadeMode(ShadeMode shadeMode)
{
	mShadeMode = shadeMode;
}

ShadeMode Rasterizer::GetShadeMode() const
{
	return mShadeMode;
}

void Rasterizer::DrawPoint(int x, int y)
{
	X::DrawPixel(x, y, mColor);
}

void Rasterizer::DrawPoint(const Vertex& v)
{
	// if screen pos (x, y) has a closer z value, render, otherwise skip
	if (DepthBuffer::Get()->CheckDepthBuffer(v.pos.x, v.pos.y, v.pos.z))
	{
		X::Color pixelColor = TextureManager::Get()->SampleColor(v.color);
		if (mShadeMode == ShadeMode::Phong)
		{
			pixelColor *= LightManager::Get()->ComputeLightColor(v.worldPos, v.norm);
		}
		X::DrawPixel(v.pos.x, v.pos.y, pixelColor);
	}
}

void Rasterizer::DrawLine(const Vertex& a, const Vertex& b)
{
	float dx = b.pos.x - a.pos.x;
	float dy = b.pos.y - a.pos.y;

	if (MathHelper::CheckEqual(dx, 0.0f) || abs(dy / dx) > 1.f)
	{
		if (a.pos.y < b.pos.y)
		{
			DrawLineVertical(a, b);
		}
		else
		{
			DrawLineVertical(b, a);
		}
	}
	else
	{
		if (a.pos.x < b.pos.x)
		{
			DrawLineHorizontal(a, b);
		}
		else
		{
			DrawLineHorizontal(b, a);
		}
	}
}

void Rasterizer::DrawTriangle(const Vertex& a, const Vertex& b, const Vertex& c)
{
	switch (mFillMode)
	{
	case FillMode::WireFrame:
	{
		DrawLine(a, b);
		DrawLine(b, c);
		DrawLine(c, a);
	}
	break;
	case FillMode::Solid:
	{
		std::vector<Vertex> sortedVertices = { a, b, c };
		std::sort(sortedVertices.begin(), sortedVertices.end(),
			[](const Vertex& lhs, const Vertex& rhs)
			{
				return lhs.pos.y < rhs.pos.y;
			});
		DrawFilledTriangle(sortedVertices[0], sortedVertices[1], sortedVertices[2]);
	}
	break;
	default:
		break;
	}
}

void Rasterizer::DrawFilledTriangle(const Vertex& a, const Vertex& b, const Vertex& c)
{
	// values passed in are already sorted where a is the lowest value (top of the screen)
	// and c is the highest value (bottom of the screen, remember positive y goes down)

	float dy = c.pos.y - a.pos.y;
	// if a and b are the same, triangle is a flat top
	if (MathHelper::CheckEqual(a.pos.y, b.pos.y))
	{
		int startY = static_cast<int>(a.pos.y);
		int endY = static_cast<int>(c.pos.y);
		for (int y = startY; y <= endY; y++)
		{
			float t = static_cast<float>(y - startY) / dy;
			Vertex aSide = LerpVertex(a, c, t);
			Vertex bSide = LerpVertex(b, c, t);
			DrawLine(aSide, bSide);
		}
	}
	// if b and c are the same, triagle is a flat bottom
	else if (MathHelper::CheckEqual(b.pos.y, c.pos.y))
	{
		int startY = static_cast<int>(a.pos.y);
		int endY = static_cast<int>(c.pos.y);
		for (int y = startY; y <= endY; y++)
		{
			float t = static_cast<float>(y - startY) / dy;
			Vertex bSide = LerpVertex(a, b, t);
			Vertex cSide = LerpVertex(a, c, t);
			DrawLine(bSide, cSide);
		}
	}
	// no edges, need a split vertex
	else
	{
		float t = (b.pos.y - a.pos.y) / dy;
		Vertex splitVertex = LerpVertex(a, c, t);
		// bottom flat fill
		DrawFilledTriangle(a, b, splitVertex);
		// top is flat fill
		DrawFilledTriangle(b, splitVertex, c);


	}
}

