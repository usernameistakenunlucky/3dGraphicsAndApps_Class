#include "CmdDrawPixels.h"

#include "Rasterizer.h"
#include "Vector2.h"

bool CmdDrawPixels::Execute(const std::vector<std::string>& params)
{
	// Need at least one x,y pair, and params must come in complete pairs
	if (params.size() < 2 || params.size() % 2 != 0)
	{
		return false;
	}

	std::vector<Vector2> pixels;
	pixels.reserve(params.size() / 2); // meh

	for (size_t i = 0; i < params.size(); i += 2)
	{
		float x = std::stof(params[i]);
		float y = std::stof(params[i + 1]);
		pixels.emplace_back(x, y);
	}

	// Draw all pixels
	for (const auto& pixel : pixels)
	{
		Rasterizer::Get()->DrawPoint((int)pixel.x, (int)pixel.y);
	}

	return true;
}