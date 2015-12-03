#pragma once
#define _WIN32_WINNT 0x0601

#include <cstdlib>
#include <iostream>
#include "boost\bind.hpp"
#include "boost\asio.hpp"
#include <boost/asio/ip/tcp.hpp>
#include "SLibraries/SBase/string/SString.h"

#pragma warning( push )
#pragma warning(disable: 4251)  // class needs to have dll interface to be used by clients of class

class  CHTTPClient
{
public:
	CSString Request(CP_CSString host, CP_CSString path);
};

#pragma warning( pop )


