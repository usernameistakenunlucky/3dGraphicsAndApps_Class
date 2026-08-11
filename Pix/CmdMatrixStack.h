#pragma once

#include "Command.h"

class CmdPushTranslation : public Command
{
public:
	const char* GetName() override
	{
		return "PushTranslation";
	}
	const char* GetDescription() override
	{
		return "PushTranslation(x, y, z)\n"
			"\n"
			"- push a translation matrix into the matrix stack";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushRotationX : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationX";
	}
	const char* GetDescription() override
	{
		return "PushRotationX(degrees)\n"
			"\n"
			"- push a rotation around the x axis matrix into the matrix stack";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushRotationY : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationY";
	}
	const char* GetDescription() override
	{
		return "PushRotationY(degrees)\n"
			"\n"
			"- push a rotation around the y axis matrix into the matrix stack";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushRotationZ : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationZ";
	}
	const char* GetDescription() override
	{
		return "PushRotationZ(degrees)\n"
			"\n"
			"- push a rotation around the z axis matrix into the matrix stack";
	}
	bool Execute(const std::vector<std::string>& params) override;
};


class CmdPushScaling : public Command
{
public:
	const char* GetName() override
	{
		return "PushScaling";
	}
	const char* GetDescription() override
	{
		return "PushScaling(x, y, z)\n"
			"\n"
			"- push a scale matrix into the matrix stack";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPopMatrix : public Command
{
public:
	const char* GetName() override
	{
		return "PopMatrix";
	}
	const char* GetDescription() override
	{
		return
			"PopMatrix()\n"
			"\n"
			"- pops the last matrix on the matrix stack";
	}
	bool Execute(const std::vector<std::string>& params) override;
};