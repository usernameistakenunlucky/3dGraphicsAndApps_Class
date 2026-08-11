#pragma once
#include "Command.h"

class CmdSetCameraPosition : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraPosition";
	}
	const char* GetDescription() override
	{
		return "SetCameraPosition(x, y, z)\n"
			"\n"
			"- sets the camera position in the scene";
	}
	bool Execute(const std::vector<std::string>& params) override;

};

class CmdSetCameraDirection : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraDirection";
	}
	const char* GetDescription() override
	{
		return "SetCameraDirection(x, y, z)\n"
			"\n"
			"- sets the camera direction, will normalize when set";
	}
	bool Execute(const std::vector<std::string>& params) override;

};

class CmdSetCameraNear : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraNear";
	}
	const char* GetDescription() override
	{
		return "SetCameraNear(nearPlane)\n"
			"\n"
			"- sets the near plane distance for the camera";
	}
	bool Execute(const std::vector<std::string>& params) override;

};

class CmdSetCameraFar : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraFar";
	}
	const char* GetDescription() override
	{
		return "SetCameraFar(farPlane)\n"
			"\n"
			"- sets the far plane distance for the camera";
	}
	bool Execute(const std::vector<std::string>& params) override;

};

class CmdSetCameraFOV : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraFOV";
	}
	const char* GetDescription() override
	{
		return "SetCameraFOV(degrees)\n"
			"\n"
			"- sets the camera field of view in degrees";
	}
	bool Execute(const std::vector<std::string>& params) override;

};