#pragma once
#include "../wlx_cef/stdafx.h"

class MyApp : public CefApp, public CefRenderProcessHandler
{

public:
	virtual ~MyApp() {}

private:

	IMPLEMENT_REFCOUNTING(MyApp);
};