#pragma once

class C_Hit
{
	public:
	C_Hit(){}
	~C_Hit(){}
	
	float GetDistance(Math::Vector2 a_posA, Math::Vector2 a_posB)
	{
		return sqrtf((a_posB.x - a_posA.x) * (a_posB.x - a_posA.x) + (a_posB.y - a_posA.y) * (a_posB.y - a_posA.y));
	}

private:

};