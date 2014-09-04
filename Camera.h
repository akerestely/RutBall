#pragma once

class Camera
{
	double dx,dz;
	double ry;
public:
	Camera();
	void MoveX(double dx);
	void MoveZ(double dz);
	void RoateY(double ry);
	void Render();
};
