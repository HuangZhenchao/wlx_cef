#pragma once
//#include "stdafx.h"
//#include "MyClient.h"

class MyApp : public CefApp, public CefBrowserProcessHandler
{

public:	
	virtual ~MyApp() {}

	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override { return this; }

	virtual void OnContextInitialized() override
	{
		CEF_REQUIRE_UI_THREAD();
		
	}

private:

	IMPLEMENT_REFCOUNTING(MyApp);
};