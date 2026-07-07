#pragma once
#include "Command.h"

class CmdSetColor : public Command
{
private:





public:

	const char* GetName() override
	{
		return "SetColor";
	}

	const char* GetDescription() override
	{
		return "SetColor(r, g, b)\n";
		"\n";
		"- Set the color of the next pixel using red, green, and blue/n";
		"- Values  are from 0.0 - 1.0";
	}

	bool Execute(const std::vector<std::string>& params) override;


};