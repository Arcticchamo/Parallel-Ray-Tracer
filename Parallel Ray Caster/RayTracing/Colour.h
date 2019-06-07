#ifndef COLOUR_H
#define COLOUR_H

class Colour
{
public:
	float R, G, B, A;

	Colour() 
	{ 
		R = G = B = A = 0; 
	}

	Colour(float _r, float _g, float _b, float _a)
	{
		R = _r;
		G = _g;
		B = _b;
		A = _a;
	}

	Colour operator* (float _a)
	{
		return Colour(R * _a, G * _a, B * _a, A);
	}

	Colour operator+ (Colour _a)
	{
		return Colour((R + _a.R) / 2, (G + _a.G) / 2, (B + _a.B) / 2, (A + _a.A) / 2);
	}
};

#endif 