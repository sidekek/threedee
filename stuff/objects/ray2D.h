#pragma once
#include <numeric>
#include "../globals/globals.h"

#include "vector2.h"

struct ray2D
{
	vector2 start;
	vector2 end;
	float dist;
	square* hitEnt;
	static ray2D trace(vector2 start, vector2 direction)
	{
		ray2D ray { start, start, -1 };
		vector2 point = start;
		bool hit = false;
		while (!hit)
		{
			for (square* object : global::entList)
			{
				if (inRect(point, vector2(object->x, object->y), vector2(object->x + object->radius, object->y + object->radius)) || ray.dist > 1500)
				{
					ray.start = start;
					ray.end = point;
					ray.dist = start.distance(point);
					ray.hitEnt = object;
					hit = true;
					break;
				}
			}
			ray.dist = start.distance(point);
			point.x += direction.x;
			point.y += direction.y;
		}
		return ray;
	}
	//temp
	static bool inRect(vector2 point, vector2 a, vector2 b)
	{
		return (point.x > a.x && point.y > a.y && point.x < b.x&& point.y < b.y);
	}
};