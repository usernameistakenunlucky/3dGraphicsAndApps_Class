#pragma once
#include "Command.h"

class CmdEndDraw : public Command
{
private:


public:
	const char* GetName() override
	{
		return "EndDraw";
	}

	const char* GetDescription() override
	{
		return
			"EndDraw()\n\n"
			"- sends the vertices to rasterizer to render";
	}

	bool Execute(const std::vector<std::string>& params) override;
};