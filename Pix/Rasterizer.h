#pragma once

#include <XEngine.h>
#include "Vertex.h"

enum class FillMode
{
	WireFrame,
	Solid,
};

enum class ShadeMode
{
	Flat,		// per face lighting
	Gouraud,	// per vertex lighting
	Phong		// per pixel
};

class Rasterizer
{
public:
	static Rasterizer* Get();

public:
	void SetColor(X::Color color);
	void SetFillMode(FillMode fillmode);
	void SetShadeMode(ShadeMode shadeMode);
	ShadeMode GetShadeMode() const;

	void DrawPoint(int x, int y);

	// topology renders 
	void DrawPoint(const Vertex& v);
	void DrawLine(const Vertex& a, const Vertex& b);
	void DrawTriangle(const Vertex& a, const Vertex& b, const Vertex& c);

private:
	void DrawFilledTriangle(const Vertex& a, const Vertex& b, const Vertex& c);

	X::Color mColor = X::Colors::White;
	FillMode mFillMode = FillMode::Solid;
	ShadeMode mShadeMode = ShadeMode::Phong;
};