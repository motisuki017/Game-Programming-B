#include "InvisibleBoundingSphere.h"

InvisibleBoundingSphere::InvisibleBoundingSphere(float rad)
{
	radius = rad;
}

InvisibleBoundingSphere::~InvisibleBoundingSphere()
{

}

bool InvisibleBoundingSphere::Init()
{
	return Entity::Init();
}

void InvisibleBoundingSphere::Update(const GameTime& time)
{
	Entity::Update(time);
}

void InvisibleBoundingSphere::Render()
{
	Entity::Render();
}

void InvisibleBoundingSphere::Release()
{
	Entity::Release();
}

float InvisibleBoundingSphere::Radius() const
{
	return radius;
}

bool InvisibleBoundingSphere::IsCollide(InvisibleBoundingSphere &ibs) const
{
	float dist = glm::length(this->WorldPosition() - ibs.WorldPosition());
	return dist < this->Radius() + ibs.Radius();
}
