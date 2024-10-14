#pragma once

/*
pda animation.h

Animation utility functions
*/

//Interpolation functions
inline int linear_interpolate(int a, int b, float t) {
	return (int)((1 - t) * a + t * b);
}

inline SDL_Point linear_interpolate (SDL_Point a, SDL_Point b, float t) {
	SDL_Point res;

	res.x = linear_interpolate(a.x, b.x, t);
	res.y = linear_interpolate(a.y, b.y, t);

	return res;
}
