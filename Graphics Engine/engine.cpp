
#include <fstream>
#include <strstream>
#include <algorithm>
#include <string>
#include <vector>
#include "win32_platform.h"
#include "maths.h"
using namespace std;



class GraphicsEngine3D //: public WindowEngine
{
public:
	GraphicsEngine3D()
	{
		string sAppName = "3D Demo";
	}

	
private:
	mesh meshCube;
	mat4x4 matProj;

	float fTheta;

	void MultiplyMatrixVector(vector3d& i, vector3d& o, mat4x4& m)
	{
		o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
		o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
		o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
		float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

		if (w != 0.0f)
		{
			o.x /= w; o.y /= w; o.z /= w;
		}
	}

public:
	void OnUserCreate()
	{
		meshCube.tris = {

			// SOUTH
			{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

			// EAST                                                      
			{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
			{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

			// NORTH                                                     
			{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
			{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

			// WEST                                                      
			{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

			// TOP                                                       
			{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
			{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

			// BOTTOM                                                    
			{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
			{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		};

		// Projection Matrix
		float fNear = 0.1f;
		float fFar = 1000.0f;
		float fFov = 90.0f;
		float fAspectRatio = (float)render_state.height / (float)render_state.width;
		float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

		matProj.m[0][0] = fAspectRatio * fFovRad;
		matProj.m[1][1] = fFovRad;
		matProj.m[2][2] = fFar / (fFar - fNear);
		matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
		matProj.m[2][3] = 1.0f;
		matProj.m[3][3] = 0.0f;
	}

	void OnUserUpdate(float fElapsedTime)
	{
		// Clear Screen
		Fill(0, 0, render_state.width, render_state.height, PIXEL_SOLID, FG_BLACK);

		// Set up rotation matrices
		mat4x4 matRotZ, matRotX;
		fTheta += 1.0f * fElapsedTime;

		// Rotation Z
		matRotZ.m[0][0] = cosf(fTheta);
		matRotZ.m[0][1] = sinf(fTheta);
		matRotZ.m[1][0] = -sinf(fTheta);
		matRotZ.m[1][1] = cosf(fTheta);
		matRotZ.m[2][2] = 1;
		matRotZ.m[3][3] = 1;

		// Rotation X
		matRotX.m[0][0] = 1;
		matRotX.m[1][1] = cosf(fTheta * 0.5f);
		matRotX.m[1][2] = sinf(fTheta * 0.5f);
		matRotX.m[2][1] = -sinf(fTheta * 0.5f);
		matRotX.m[2][2] = cosf(fTheta * 0.5f);
		matRotX.m[3][3] = 1;

		// Draw Triangles
		for (auto tri : meshCube.tris)
		{
			triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

			// Rotate in Z-Axis
			MultiplyMatrixVector(tri.point[0], triRotatedZ.point[0], matRotZ);
			MultiplyMatrixVector(tri.point[1], triRotatedZ.point[1], matRotZ);
			MultiplyMatrixVector(tri.point[2], triRotatedZ.point[2], matRotZ);

			// Rotate in X-Axis
			MultiplyMatrixVector(triRotatedZ.point[0], triRotatedZX.point[0], matRotX);
			MultiplyMatrixVector(triRotatedZ.point[1], triRotatedZX.point[1], matRotX);
			MultiplyMatrixVector(triRotatedZ.point[2], triRotatedZX.point[2], matRotX);

			// Offset into the screen
			triTranslated = triRotatedZX;
			triTranslated.point[0].z = triRotatedZX.point[0].z + 3.0f;
			triTranslated.point[1].z = triRotatedZX.point[1].z + 3.0f;
			triTranslated.point[2].z = triRotatedZX.point[2].z + 3.0f;

			// Project triangles from 3D --> 2D
			MultiplyMatrixVector(triTranslated.point[0], triProjected.point[0], matProj);
			MultiplyMatrixVector(triTranslated.point[1], triProjected.point[1], matProj);
			MultiplyMatrixVector(triTranslated.point[2], triProjected.point[2], matProj);

			// Scale into view
			triProjected.point[0].x += 1.0f; triProjected.point[0].y += 1.0f;
			triProjected.point[1].x += 1.0f; triProjected.point[1].y += 1.0f;
			triProjected.point[2].x += 1.0f; triProjected.point[2].y += 1.0f;
			triProjected.point[0].x *= 0.5f * (float)render_state.width;
			triProjected.point[0].y *= 0.5f * (float)render_state.height;
			triProjected.point[1].x *= 0.5f * (float)render_state.width;
			triProjected.point[1].y *= 0.5f * (float)render_state.height;
			triProjected.point[2].x *= 0.5f * (float)render_state.width;
			triProjected.point[2].y *= 0.5f * (float)render_state.height;

			// Rasterize triangle
			DrawTriangle(triProjected.point[0].x, triProjected.point[0].y,
				triProjected.point[1].x, triProjected.point[1].y,
				triProjected.point[2].x, triProjected.point[2].y,
				PIXEL_SOLID, FG_WHITE);

		}
	}

};




int main()
{
	GraphicsEngine3D demo;
	if (demo.ConstructConsole(256, 240, 4, 4))
		demo.Start();
	return 0;