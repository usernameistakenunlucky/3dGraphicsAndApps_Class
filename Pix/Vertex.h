#pragma once

#include "MathHelper.h"
#include <XColors.h>

struct Vertex
{
	Vector3 pos; // position of vertex
	X::Color color; // color of the vertex

	// needed for lighting calculations
	Vector3 norm; // normal at the verstex
	Vector3 worldPos; // position in the world, helps with lighting at the pixel


};

inline Vector3 LerpPosition(const Vector3& a, const Vector3& b, float t)
{
	return {
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t
	};
}

inline Vector3 LerpNormal(const Vector3& a, const Vector3& b, float t)
{
	return MathHelper::Normalize({
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t
	});
}

inline X::Color LerpColor(const X::Color& a, const X::Color& b, float t)
{
	return {
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t,
		a.a + (b.a - a.a) * t
	};
}

inline Vertex LerpVertex(const Vertex& a, const Vertex& b, float t)
{
	Vertex v;
	v.pos = LerpPosition(a.pos, b.pos, t);
	v.color = LerpColor(a.color, b.color, t);
	v.norm = LerpNormal(a.norm, b.norm, t);
	v.worldPos = LerpPosition(a.worldPos, b.worldPos, t);

	// because this is typically done in screen space, x any y should be "pixel positions"
	// to convert float to int / index it floor (pos.y + 0.5f)
	// this is to get PIXEL position when all is calculated
	// otherwise in some functions, the floats miss checks and program infinite loops
	v.pos.x = floor(v.pos.x + 0.5f);
	v.pos.y = floor(v.pos.y + 0.5f);

	return v;
}