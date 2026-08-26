#include "LightTypes.h"
#include "Camera.h"
#include "MaterialManager.h"

X::Color DirectionalLight::ComputeLightColor(const Vector3& position, const Vector3& normal)
{
	Camera* camera = Camera::Get();
	MaterialManager* mm = MaterialManager::Get();

	// calculate ambient color
	X::Color ambient = mAmbient * mm->GetMaterialAmbient();

	// calculate diffuse color
	Vector3 L = -mDirection;
	float dot = X::Math::Max(MathHelper::Dot(L, normal), 0.f);
	X::Color diffuse = mDiffuse * mm->GetMaterialDiffuse() * dot;

	// calculate specilar color
	Vector3 v = MathHelper::Normalize(camera->GetPosition() - position);
	Vector3 r = MathHelper::Normalize(L + v);
	float fallOff = X::Math::Max((float)pow(MathHelper::Dot(r, normal), mm->GetMaterialShininess()), 0.f);
	X::Color specular = mSpecular * mm->GetMaterialSpecular() * fallOff;

	// final color
	return ambient + diffuse + specular;
}

void DirectionalLight::SetDirection(const Vector3& direction)
{
	mDirection = MathHelper::Normalize(direction);
}

// point light ----------------------------------------------------------------------

X::Color PointLight::ComputeLightColor(const Vector3& position, const Vector3& normal)
{
	Camera* camera = Camera::Get();
	MaterialManager* mm = MaterialManager::Get();

	// get distance from light
	Vector3 L = mPosition - position;
	float distance = MathHelper::Magnitude(L);
	L /= distance;

	// calculate iL, light intensity
	float attenuation = 1.f / (mKConstant + (mKLinear * distance) + (mKQuadratic * distance * distance));
	float iL = X::Math::Clamp(attenuation, 0.f, 1.f);

	// calculate ambient color
	X::Color ambient = mAmbient * mm->GetMaterialAmbient();

	// calculate diffuse color
	float dot = X::Math::Max(MathHelper::Dot(L, normal), 0.f);
	X::Color diffuse = mDiffuse * mm->GetMaterialDiffuse() * dot * iL;

	// calculate specilar color
	Vector3 v = MathHelper::Normalize(camera->GetPosition() - position);
	Vector3 r = MathHelper::Normalize(L + v);
	float fallOff = X::Math::Max((float)pow(MathHelper::Dot(r, normal), mm->GetMaterialShininess()), 0.f);
	X::Color specular = mSpecular * mm->GetMaterialSpecular() * fallOff * iL;

	// final color
	return ambient + diffuse + specular;
}


void PointLight::SetPosition(const Vector3& position)
{
	mPosition = position;
}

void PointLight::SetAttenuation(float kConstant, float kLinear, float kQuadratic)
{
	mKConstant = kConstant;
	mKLinear = kLinear;
	mKQuadratic = kQuadratic;
}

// spot light ----------------------------------------------------------------------

X::Color SpotLight::ComputeLightColor(const Vector3& position, const Vector3& normal)
{
	Camera* camera = Camera::Get();
	MaterialManager* mm = MaterialManager::Get();

	// get distance from light
	Vector3 L = mPosition - position;
	float distance = MathHelper::Magnitude(L);
	L /= distance;

	// calculate ambient color
	X::Color ambient = mAmbient * mm->GetMaterialAmbient();

	// check to see if position is in the cone
	Vector3 lightDir = -L; // light direction to the point
	float dotDir = MathHelper::Dot(lightDir, mDirection);
	if (dotDir < mCosAngle)
	{
		return ambient;
	}

	// calculate iL, light intensity
	float spot = pow(dotDir, mDecay);
	float attenuation = spot / (mKConstant + (mKLinear * distance) + (mKQuadratic * distance * distance));
	float iL = X::Math::Clamp(attenuation, 0.f, 1.f);

	// calculate diffuse color
	float dot = X::Math::Max(MathHelper::Dot(L, normal), 0.f);
	X::Color diffuse = mDiffuse * mm->GetMaterialDiffuse() * dot * iL;

	// calculate specilar color
	Vector3 v = MathHelper::Normalize(camera->GetPosition() - position);
	Vector3 r = MathHelper::Normalize(L + v);
	float fallOff = X::Math::Max((float)pow(MathHelper::Dot(r, normal), mm->GetMaterialShininess()), 0.f);
	X::Color specular = mSpecular * mm->GetMaterialSpecular() * fallOff * iL;

	// final color
	return ambient + diffuse + specular;
}

void SpotLight::SetPosition(const Vector3& position)
{
	mPosition = position;
}

void SpotLight::SetDirection(const Vector3& direction)
{
	mDirection = MathHelper::Normalize(direction);
}

void SpotLight::SetAttenuation(float kConstant, float kLinear, float kQuadradic)
{
	mKConstant = kConstant;
	mKLinear = kLinear;
	mKQuadratic = kQuadradic;
}

void SpotLight::SetAngle(float angle)
{
	mCosAngle = cos(angle);
}

void SpotLight::SetDecay(float decay)
{
	mDecay = decay;
}