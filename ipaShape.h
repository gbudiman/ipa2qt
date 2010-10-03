/*
 * ipaShape.h
 *
 *  Created on: Oct 2, 2010
 *      Author: gbudiman
 */

#ifndef SHAPE_H_
#define SHAPE_H_

class ipaShape {
public:
	int x; // Central posotopm
	int y;
	int shape; // 0:circle, 1:square, 2:triangle
	int color; // 0:read, 1:green, 2:blue

	ipaShape(int ix, int iy, int iShape, int iColor) {
		x = ix;
		y = iy;
		shape = iShape;
		color = iColor;
	}
};
#endif /* SHAPE_H_ */
