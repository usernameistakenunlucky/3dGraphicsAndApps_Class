#pragma once
#include "Command.h"

class CmdBeginDraw : public Command
{
private:


public:
	const char* GetName() override
	{
		return "BeginDraw";
	}

	const char* GetDescription() override
	{
		const char* theKing = "BeginDraw(topology)\n"
			"\n"
			"- starts storing vertices\n"
			"- topology (point, line, triangle)"
			"- (optional) apply transform to apply 3D pipeline transformation to vertices";

		return theKing;
	}

	bool Execute(const std::vector<std::string>& params) override;
};