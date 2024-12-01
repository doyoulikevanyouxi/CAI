 #include "caipch.h"
#include "Path.h"

void Path::AddPoint(const float& x, const float& y)
{
	if (y > height.get())
		height.set(y);
	if (x > width.get())
		width.set(x);
	//lineGeometry.AddPoint(Point(x, y));
}
