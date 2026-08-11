#pragma once

#include "Command.h"

class CmdVarInt : public Command
{
public:
	const char* GetName() override
	{
		return "int";
	}

	const char* GetDescription() override
	{
		return
			"Declares an int variable. Can optionally specify a drag speed, min, and max.\n"
			"\n"
			"syntax: int $<name> = <value>, <speed>, <min>, <max>\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
