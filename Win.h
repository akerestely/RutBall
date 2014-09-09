#pragma once
#include "glut.h"  /*!< OpenGL Utility Toolkit. */
#include "Point.h"  /*!< Used to manipulate point 2D objects. */
#include "Drawable.h"  /*!< Base abstract class. */

class Win : public Drawable
{
	double dx;
	bool win;
public:
	Win(Point center);
	~Win(void);
	Win(){}
	void SetWin(bool win);
	void Draw();
};
