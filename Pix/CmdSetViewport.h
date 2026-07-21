#pragma once

#include "Command.h"

class CmdSetViewport : public Command
{
private:



public:

	const char* GetName() override
	{
		return "SetViewport";
	}

	const char* GetDescription() override
	{
		return
			"SetViewport(x, y, width, height, <show>)\n\n"
			"- create viewport rect with x, y, width and height";
	}

	bool Execute(const std::vector<std::string>& params) override;
};