#pragma once

#include "Command.h"

class CmdEnableDepth : public Command
{
public:
	const char* GetName() override
	{
		return "EnableDepth";
	}

	const char* GetDescription() override
	{
		return
			"CmdEnableDepth(enable)\n"
			"\n"
			"- enable / disable depth buffer";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
