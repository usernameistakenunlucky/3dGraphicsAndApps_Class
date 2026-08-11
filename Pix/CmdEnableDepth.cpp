#include "CmdEnableDepth.h"
#include "VariableCache.h"
#include "DepthBuffer.h"

bool CmdEnableDepth::Execute(const std::vector<std::string>& params)
{
	// Need at leaset 3 params for name, =, value
	if (params.size() < 1)
	{
		return false;
	}

	bool enable = VariableCache::Get()->GetBool(params[0]);
	DepthBuffer::Get()->SetEnabled(enable);
	return true;
}
