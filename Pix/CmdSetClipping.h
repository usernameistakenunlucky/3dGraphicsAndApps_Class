#pragma once

#include "Command.h"

class CmdSetClipping : public Command
{
private:



public:

	const char* GetName() override
	{
		return "SetClipping";
	}

	const char* GetDescription() override
	{
		return
			"SetClipping()\n\n"
			"- enables / disables clipping outdise of viewport";
	}

	bool Execute(const std::vector<std::string>& params) override;
};