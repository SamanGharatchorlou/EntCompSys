#include "pch.h"
#include "RenderColour.h"


RenderColour::RenderColour(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}


RenderColour::RenderColour(Colour colour)
{
	a = alphaMax;

	switch (colour)
	{
	case RenderColour::None:
		r = 0; g = 0; b = 0;
		break;
	case RenderColour::Red:
		r = 255; g = 0; b = 0;
		break;
	case RenderColour::Blue:
		r = 0; g = 0; b = 255;
		break;
	case RenderColour::Purple:
		r = 128; g = 0; b = 128;
		break;
	case RenderColour::Green:
		r = 0; g = 255; b = 0;
		break;
	case RenderColour::Yellow:
		r = 255; g = 255; b = 0;
		break;
	case RenderColour::LightGrey:
		r = 201; g = 201; b = 201;
		break;
	case RenderColour::Black:
		r = 0; g = 0; b = 0;
		break;
	case RenderColour::White:
		r = 255; g = 255; b = 255;
		break;
	case RenderColour::TakeDamage:
		r = 215; g = 0; b = 0;
		break;
	case RenderColour::Invunerable:
		r = 65; g = 65; b = 65;
		break;
	default:
		r = 0; g = 0; b = 0;
		DebugPrint(Warning, "Render colour has not been defined\n");
		break;
	}
}


void RenderColour::setOpacity(float opacity)
{
	opacity = clamp(opacity, 0.0f, 1.0f);
	a = (Uint8)(alphaMax * opacity);
}