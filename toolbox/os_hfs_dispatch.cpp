#include <cerrno>
#include <cctype>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <deque>
#include <string>

#include <sys/xattr.h>
#include <sys/stat.h>
#include <sys/paths.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <strings.h>

#include <cpu/defs.h>
#include <cpu/CpuModule.h>
#include <cpu/fmem.h>

#include "os.h"
#include "os_internal.h"
#include "toolbox.h"
#include "stackframe.h"

using ToolBox::Log;
using namespace ToolBox::Errors;

namespace OS {

	uint16_t PBGetCatInfo(uint32_t paramBlock)
	{

		return 0;
	}

	uint16_t PBOpenDF(uint32_t paramBlock)
	{
		Log("     PBOpenDF\n");
		// same as Open but slightly different handling of . files.
		return OS::Open(0xa000);
	}

	uint16_t HFSDispatch(uint16_t trap)
	{

		// TODO -- check new hfs bit ( (trap & 0x0200) == 0x0200)
		// TODO -- check async bit ((trap & 0x0400) == 0x0400)

		uint32_t selector = cpuGetDReg(0);
		uint32_t paramBlock = cpuGetAReg(0);

		Log("%04x HFSDispatch(%08x, %08x)\n", trap, selector, paramBlock);

		switch (selector)
		{
			//case 0x0009:
				//return PBGetCatInfo(paramBlock);
				//break;

			case 0x1a:
				return PBOpenDF(paramBlock);
				break;

			default:
				fprintf(stderr, "HFSDispatch: selector %08x not implemented\n", 
					selector);
				exit(1);
		}
		return 0;
	}



}