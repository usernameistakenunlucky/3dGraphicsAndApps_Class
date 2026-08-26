#pragma once

#include "Command.h"

class CmdSetShadeMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetShadeMode";
	}

	const char* GetDescription() override
    {
        return
            "SetShadeMode(<shadeMode>)\n"
            "\n"
            "- sets the lighting shade mode\n"
            "- flat: per face lighting\n"
            "- gouraud: per vertex lighting\n"
            "- phong: per pixel lighting\n";
    }
    bool Execute(const std::vector<std::string>&params) override;
};