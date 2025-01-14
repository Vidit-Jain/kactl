/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: Basic math
 * Description:
Returns the signed distance between point p and the line containing points a and b. 
Positive value on left side and negative on right as seen from a towards b. a==b gives nan.
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineDistance}
\end{minipage}
 * ExtDesc: P is supposed to be Point<T> or Point3D<T> where T is e.g. double or long long.
It uses products in intermediate steps so watch out for overflow if using int or long long.
Using Point3D will always give a non-negative distance.
For Point3D, call .dist on the result of the cross product.
 * Status: tested
 */
#pragma once

#include "Point.h"

template<class P>
double lineDist(const P& a, const P& b, const P& p) {
	return (double)(b-a).cross(p-a)/(b-a).dist();
}
