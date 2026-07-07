#pragma once

#include "Command.h"

class CmdDrawPixels : public Command
{
public:
	const char* GetName() override
	{
		return "DrawPixels";
	}

	const char* GetDescription() override
	{
		return
			"DrawPixels(x1,y1,  x2,y2,  ...)\n"
			"\n"
			"- Draws a pixel at each position (x, y).";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
