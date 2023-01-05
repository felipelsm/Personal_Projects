#pragma once

#include <vector>

struct vector3d
{
	float x, y, z;
};

struct triangle
{
	vector3d point[3];
};

struct mesh
{
	std::vector<triangle> tris;
};

struct mat4x4
{
	float m[4][4] = { 0 };
};