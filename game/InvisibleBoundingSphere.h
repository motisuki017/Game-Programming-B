#pragma once
#include "Entity.h"
class InvisibleBoundingSphere :	public Entity
{
public:
	InvisibleBoundingSphere(float rad);
	virtual ~InvisibleBoundingSphere();
public:
	bool Init() override;
	void Update(const GameTime& time) override;
	void Render() override;
	void Release() override;
public:
	// ‹…‚Ì”¼Œa
	float Radius() const;
	bool IsCollide(InvisibleBoundingSphere &ibs) const;
protected:
	float radius;
};

