#pragma once
#pragma comment(lib, "../x64/debug/OS10_HTAPI.lib")

#include "../OS10_HTAPI/pch.h"
#include "../OS10_HTAPI/HT.h"

namespace Test
{
	BOOL Test1_Create();
	BOOL Test2_Insert();
	BOOL Test3_Get();
	BOOL Test4_Delete();
	BOOL Test5_Close();
}
#pragma once
