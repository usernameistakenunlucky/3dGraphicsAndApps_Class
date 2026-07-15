#pragma once
#include "Command.h"

class CmdVertex : public Command
{
public:

	const char* GetName() override
	{
		return "Vertex";
	}
	const char* GetDescription() override
	{
		return
			"Vertex(x, y)\n"                 // only a 2D position
			"Vertex(x, y, z)\n"              // only a 3D position
			"Vertex(x, y, r, g, b)\n"        // a 2D position with color
			"Vertex(x, y, z, r, g, b)\n"     // a 3D position with color
			"\n"
			"- adds vertex to the primitives manager before render";
	}

	bool Execute(const std::vector<std::string>& params) override;
};