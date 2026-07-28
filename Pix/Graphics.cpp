#include "Graphics.h"

#include "Viewport.h"
#include "Clipper.h"

void Graphics::NewFrame()
{
	Viewport::Get()->OnNewFrame();
	Clipper::Get()->OnNewFrame();

	Matrix4 matTrans = Matrix4::Translation({4.f, 10.f, 5.f});
	Matrix4 matRotX = Matrix4::RotationX(45.f * MathHelper::DegToRad);
	Matrix4 matRotY = Matrix4::RotationX(15.f * MathHelper::DegToRad);
	Matrix4 matFinal = matRotX * matRotY * matTrans;
	Matrix4 matInv = MathHelper::Inverse(matFinal);
	Matrix4 matIdentity = matFinal * matInv;
	


	int hi = 0;
	++hi;

}