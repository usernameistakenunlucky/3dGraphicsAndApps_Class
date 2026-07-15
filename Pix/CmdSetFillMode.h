#pragma once

#include "Command.h"

class CmdSetFillMode : public Command
{
private:



public:

	const char* GetName() override
	{
		return "SetFillMode";
	}

	const char* GetDescription() override
	{
		return
			"SetFillMode(fillMode)\n\n"
			"- sets triangle fill mode (wireframe, solid)";
	}

	bool Execute(const std::vector<std::string>& params) override;
};