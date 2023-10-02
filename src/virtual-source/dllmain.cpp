#include <streams.h>
#include <initguid.h>
#include "virtual-cam.h"
#include "virtual-audio.h"

#define CreateComObject(clsid, iid, var) CoCreateInstance(clsid, NULL, \
CLSCTX_INPROC_SERVER, iid, (void **)&var);

STDAPI AMovieSetupRegisterServer(CLSID clsServer, LPCWSTR szDescription, 
	LPCWSTR szFileName, LPCWSTR szThreadingModel = L"Both", 
	LPCWSTR szServerType = L"InprocServer32");
STDAPI AMovieSetupUnregisterServer(CLSID clsServer);

// #define NUM_VIDEO_FILTERS 4
// TODO16
#define NUM_VIDEO_FILTERS 16

// {27B05C2D-93DC-474A-A5DA-9BBA34CB2A9C}
DEFINE_GUID(CLSID_OBS_VirtualV,
	0x27b05c2d, 0x93dc, 0x474a, 0xa5, 0xda, 0x9b, 0xba, 0x34, 0xcb, 0x2a, 0x9c);

DEFINE_GUID(CLSID_OBS_VirtualV2,
	0x27b05c2d, 0x93dc, 0x474a, 0xa5, 0xda, 0x9b, 0xba, 0x34, 0xcb, 0x2a, 0x9d);

DEFINE_GUID(CLSID_OBS_VirtualV3,
	0x27b05c2d, 0x93dc, 0x474a, 0xa5, 0xda, 0x9b, 0xba, 0x34, 0xcb, 0x2a, 0x9e);

DEFINE_GUID(CLSID_OBS_VirtualV4,
	0x27b05c2d, 0x93dc, 0x474a, 0xa5, 0xda, 0x9b, 0xba, 0x34, 0xcb, 0x2a, 0x9f);

// TODO16
DEFINE_GUID(CLSID_OBS_VirtualV5,
	0x27b05c2d, 0x93dc, 0x474a, 0xa5, 0xda, 0x9b, 0xba, 0x34, 0xcb, 0x2a, 0xa0);

DEFINE_GUID(CLSID_OBS_VirtualV6,
	0x27b05c2d, 0x93dc, 0x474a, 0xa5, 0xda, 0x9b, 0xba, 0x34, 0xcb, 0x2a, 0xa1);

DEFINE_GUID(CLSID_OBS_VirtualV7,
	0x27b05c2d, 0x93dc, 0x474a, 0xa5, 0xda, 0x9b, 0xba, 0x34, 0xcb, 0x2a, 0xa2);

DEFINE_GUID(CLSID_OBS_VirtualV8,
	0x27b05c2d, 0x93dc, 0x474a, 0xa5, 0xda, 0x9b, 0xba, 0x34, 0xcb, 0x2a, 0xa3);

DEFINE_GUID(CLSID_OBS_VirtualV9,
	0x27b05c2d, 0x93dc, 0x474a, 0xa5, 0xda, 0x9b, 0xba, 0x34, 0xcb, 0x2a, 0xa4);

DEFINE_GUID(CLSID_OBS_VirtualV10,
	0x27b05c2d, 0x93dc, 0x474a, 0xa5, 0xda, 0x9b, 0xba, 0x34, 0xcb, 0x2a, 0xa5);

DEFINE_GUID(CLSID_OBS_VirtualV11,
	0x27b05c2d, 0x93dc, 0x474a, 0xa5, 0xda, 0x9b, 0xba, 0x34, 0xcb, 0x2a, 0xa6);

DEFINE_GUID(CLSID_OBS_VirtualV12,
	0x27b05c2d, 0x93dc, 0x474a, 0xa5, 0xda, 0x9b, 0xba, 0x34, 0xcb, 0x2a, 0xa7);

DEFINE_GUID(CLSID_OBS_VirtualV13,
	0x27b05c2d, 0x93dc, 0x474a, 0xa5, 0xda, 0x9b, 0xba, 0x34, 0xcb, 0x2a, 0xa8);

DEFINE_GUID(CLSID_OBS_VirtualV14,
	0x27b05c2d, 0x93dc, 0x474a, 0xa5, 0xda, 0x9b, 0xba, 0x34, 0xcb, 0x2a, 0xa9);

DEFINE_GUID(CLSID_OBS_VirtualV15,
	0x27b05c2d, 0x93dc, 0x474a, 0xa5, 0xda, 0x9b, 0xba, 0x34, 0xcb, 0x2a, 0xaa);

DEFINE_GUID(CLSID_OBS_VirtualV16,
	0x27b05c2d, 0x93dc, 0x474a, 0xa5, 0xda, 0x9b, 0xba, 0x34, 0xcb, 0x2a, 0xab);

// {B750E5CD-5E7E-4ED3-B675-A5003C439997}
DEFINE_GUID(CLSID_OBS_VirtualA,
	0xb750e5cd, 0x5e7e, 0x4ed3, 0xb6, 0x75, 0xa5, 0x0, 0x3c, 0x43, 0x99, 0x97);

const AMOVIESETUP_MEDIATYPE AMSMediaTypesV =
{
	&MEDIATYPE_Video,
	&MEDIASUBTYPE_YUY2
};

const AMOVIESETUP_MEDIATYPE AMSMediaTypesA =
{
	&MEDIATYPE_Audio,
	&MEDIASUBTYPE_PCM
};

const AMOVIESETUP_PIN AMSPinV =
{
	L"Output",            
	FALSE,                 
	TRUE,                  
	FALSE,                 
	FALSE,                 
	&CLSID_NULL,           
	NULL,                  
	1,                     
	&AMSMediaTypesV
};

const AMOVIESETUP_PIN AMSPinA =
{
	L"Output",             
	FALSE,                 
	TRUE,                  
	FALSE,                 
	FALSE,                 
	&CLSID_NULL,           
	NULL,                  
	1,                     
	&AMSMediaTypesA
};

const AMOVIESETUP_FILTER AMSFilterV =
{
	&CLSID_OBS_VirtualV,  
	L"OBS Virtual Cam",     
	MERIT_DO_NOT_USE,      
	1,                     
	&AMSPinV
};

const AMOVIESETUP_FILTER AMSFilterV2 =
{
	&CLSID_OBS_VirtualV2,
	L"OBS Virtual Cam2",
	MERIT_DO_NOT_USE,
	1,
	&AMSPinV
};

const AMOVIESETUP_FILTER AMSFilterV3 =
{
	&CLSID_OBS_VirtualV3,
	L"OBS Virtual Cam3",
	MERIT_DO_NOT_USE,
	1,
	&AMSPinV
};

const AMOVIESETUP_FILTER AMSFilterV4 =
{
	&CLSID_OBS_VirtualV4,
	L"OBS Virtual Cam4",
	MERIT_DO_NOT_USE,
	1,
	&AMSPinV
};

// TODO16
const AMOVIESETUP_FILTER AMSFilterV5 =
{
	&CLSID_OBS_VirtualV5,
	L"OBS Virtual Cam5",
	MERIT_DO_NOT_USE,
	1,
	&AMSPinV
};

const AMOVIESETUP_FILTER AMSFilterV6 =
{
	&CLSID_OBS_VirtualV6,
	L"OBS Virtual Cam6",
	MERIT_DO_NOT_USE,
	1,
	&AMSPinV
};

const AMOVIESETUP_FILTER AMSFilterV7 =
{
	&CLSID_OBS_VirtualV7,
	L"OBS Virtual Cam7",
	MERIT_DO_NOT_USE,
	1,
	&AMSPinV
};

const AMOVIESETUP_FILTER AMSFilterV8 =
{
	&CLSID_OBS_VirtualV8,
	L"OBS Virtual Cam8",
	MERIT_DO_NOT_USE,
	1,
	&AMSPinV
};

const AMOVIESETUP_FILTER AMSFilterV9 =
{
	&CLSID_OBS_VirtualV9,
	L"OBS Virtual Cam9",
	MERIT_DO_NOT_USE,
	1,
	&AMSPinV
};

const AMOVIESETUP_FILTER AMSFilterV10 =
{
	&CLSID_OBS_VirtualV10,
	L"OBS Virtual Cam10",
	MERIT_DO_NOT_USE,
	1,
	&AMSPinV
};

const AMOVIESETUP_FILTER AMSFilterV11 =
{
	&CLSID_OBS_VirtualV11,
	L"OBS Virtual Cam11",
	MERIT_DO_NOT_USE,
	1,
	&AMSPinV
};

const AMOVIESETUP_FILTER AMSFilterV12 =
{
	&CLSID_OBS_VirtualV12,
	L"OBS Virtual Cam12",
	MERIT_DO_NOT_USE,
	1,
	&AMSPinV
};

const AMOVIESETUP_FILTER AMSFilterV13 =
{
	&CLSID_OBS_VirtualV13,
	L"OBS Virtual Cam13",
	MERIT_DO_NOT_USE,
	1,
	&AMSPinV
};

const AMOVIESETUP_FILTER AMSFilterV14 =
{
	&CLSID_OBS_VirtualV14,
	L"OBS Virtual Cam14",
	MERIT_DO_NOT_USE,
	1,
	&AMSPinV
};

const AMOVIESETUP_FILTER AMSFilterV15 =
{
	&CLSID_OBS_VirtualV15,
	L"OBS Virtual Cam15",
	MERIT_DO_NOT_USE,
	1,
	&AMSPinV
};

const AMOVIESETUP_FILTER AMSFilterV16 =
{
	&CLSID_OBS_VirtualV16,
	L"OBS Virtual Cam16",
	MERIT_DO_NOT_USE,
	1,
	&AMSPinV
};

const AMOVIESETUP_FILTER AMSFilterA =
{
	&CLSID_OBS_VirtualA,  
	L"OBS Virtual Audio",     
	MERIT_DO_NOT_USE,      
	1,                     
	&AMSPinA             
};

CFactoryTemplate g_Templates[NUM_VIDEO_FILTERS + 1] =
{
	{
		L"OBS-Camera",
		&CLSID_OBS_VirtualV,
		CreateInstance,
		NULL,
		&AMSFilterV
	},
	{
		L"OBS-Camera2",
		&CLSID_OBS_VirtualV2,
		CreateInstance2,
		NULL,
		&AMSFilterV2
	},
	{
		L"OBS-Camera3",
		&CLSID_OBS_VirtualV3,
		CreateInstance3,
		NULL,
		&AMSFilterV3
	},
	{
		L"OBS-Camera4",
		&CLSID_OBS_VirtualV4,
		CreateInstance4,
		NULL,
		&AMSFilterV4
	},
	// TODO16
	{
		L"OBS-Camera5",
		&CLSID_OBS_VirtualV5,
		CreateInstance5,
		NULL,
		&AMSFilterV5
	},
	{
		L"OBS-Camera6",
		&CLSID_OBS_VirtualV6,
		CreateInstance6,
		NULL,
		&AMSFilterV6
	},
	{
		L"OBS-Camera7",
		&CLSID_OBS_VirtualV7,
		CreateInstance7,
		NULL,
		&AMSFilterV7
	},
	{
		L"OBS-Camera8",
		&CLSID_OBS_VirtualV8,
		CreateInstance8,
		NULL,
		&AMSFilterV8
	},
	{
		L"OBS-Camera9",
		&CLSID_OBS_VirtualV9,
		CreateInstance9,
		NULL,
		&AMSFilterV9
	},
	{
		L"OBS-Camera10",
		&CLSID_OBS_VirtualV10,
		CreateInstance10,
		NULL,
		&AMSFilterV10
	},
	{
		L"OBS-Camera11",
		&CLSID_OBS_VirtualV11,
		CreateInstance11,
		NULL,
		&AMSFilterV11
	},
	{
		L"OBS-Camera12",
		&CLSID_OBS_VirtualV12,
		CreateInstance12,
		NULL,
		&AMSFilterV12
	},
	{
		L"OBS-Camera13",
		&CLSID_OBS_VirtualV13,
		CreateInstance13,
		NULL,
		&AMSFilterV13
	},
	{
		L"OBS-Camera14",
		&CLSID_OBS_VirtualV14,
		CreateInstance14,
		NULL,
		&AMSFilterV14
	},
	{
		L"OBS-Camera15",
		&CLSID_OBS_VirtualV15,
		CreateInstance15,
		NULL,
		&AMSFilterV15
	},
	{
		L"OBS-Camera16",
		&CLSID_OBS_VirtualV16,
		CreateInstance16,
		NULL,
		&AMSFilterV16
	},
	{
		L"OBS-Audio",
		&CLSID_OBS_VirtualA,
		CVAudio::CreateInstance,
		NULL,
		&AMSFilterA
	}
};

int g_cTemplates = sizeof(g_Templates) / sizeof(g_Templates[0]);

STDAPI RegisterFilters(BOOL bRegister,int reg_video_filters)
{
	HRESULT hr = NOERROR;
	WCHAR achFileName[MAX_PATH];
	char achTemp[MAX_PATH];
	ASSERT(g_hInst != 0);

	if (0 == GetModuleFileNameA(g_hInst, achTemp, sizeof(achTemp)))
		return AmHresultFromWin32(GetLastError());

	MultiByteToWideChar(CP_ACP, 0L, achTemp, lstrlenA(achTemp) + 1,
		achFileName, NUMELMS(achFileName));

	hr = CoInitialize(0);
	if (bRegister) {

		hr = AMovieSetupRegisterServer(CLSID_OBS_VirtualA, L"OBS-Audio",
			achFileName);

		for (int i = 0; i < reg_video_filters; i++) {
			hr |= AMovieSetupRegisterServer(*(g_Templates[i].m_ClsID),
				g_Templates[i].m_Name, achFileName);
		}

	}

	if (SUCCEEDED(hr)) {

		IFilterMapper2 *fm = 0;
		hr = CreateComObject(CLSID_FilterMapper2, IID_IFilterMapper2, fm);

		if (SUCCEEDED(hr)) {
			if (bRegister) {
				IMoniker *moniker_audio = 0;
				REGFILTER2 rf2;
				rf2.dwVersion = 1;
				rf2.dwMerit = MERIT_DO_NOT_USE;
				rf2.cPins = 1;
				rf2.rgPins = &AMSPinA;
				hr = fm->RegisterFilter(CLSID_OBS_VirtualA, L"OBS-Audio",
					&moniker_audio, &CLSID_AudioInputDeviceCategory, NULL, &rf2);
				rf2.rgPins = &AMSPinV;
				for (int i = 0; i < reg_video_filters; i++) {
					IMoniker *moniker_video = 0;
					hr = fm->RegisterFilter(*(g_Templates[i].m_ClsID), 
						g_Templates[i].m_Name, &moniker_video, 
						&CLSID_VideoInputDeviceCategory, NULL, &rf2);
				}

			} else {
				hr = fm->UnregisterFilter(&CLSID_AudioInputDeviceCategory, 0, 
					CLSID_OBS_VirtualA);

				for (int i = 0; i < reg_video_filters; i++) {
					hr = fm->UnregisterFilter(&CLSID_VideoInputDeviceCategory, 0,
						*(g_Templates[i].m_ClsID));
				}
			}
		}

		if (fm)
			fm->Release();
	}

	if (SUCCEEDED(hr) && !bRegister){
		hr = AMovieSetupUnregisterServer(CLSID_OBS_VirtualA);
		for (int i = 0; i < reg_video_filters; i++) {
			hr = AMovieSetupUnregisterServer(*(g_Templates[i].m_ClsID));
		}
	}

	CoFreeUnusedLibraries();
	CoUninitialize();
	return hr;
}

STDAPI DllInstall(BOOL bInstall, _In_opt_ LPCWSTR pszCmdLine)
{
	if (!bInstall)
		return RegisterFilters(FALSE, NUM_VIDEO_FILTERS);
	else if (lstrcmpW(pszCmdLine, L"1") == 0)
		return RegisterFilters(TRUE, 1);
	else if (lstrcmpW(pszCmdLine, L"2") == 0)
		return RegisterFilters(TRUE, 2);
	else if (lstrcmpW(pszCmdLine, L"3") == 0)
		return RegisterFilters(TRUE, 3);
	// TODO16
	else if (lstrcmpW(pszCmdLine, L"4") == 0)
		return RegisterFilters(TRUE, 4);
	else if (lstrcmpW(pszCmdLine, L"5") == 0)
		return RegisterFilters(TRUE, 5);
	else if (lstrcmpW(pszCmdLine, L"6") == 0)
		return RegisterFilters(TRUE, 6);
	else if (lstrcmpW(pszCmdLine, L"7") == 0)
		return RegisterFilters(TRUE, 7);
	else if (lstrcmpW(pszCmdLine, L"8") == 0)
		return RegisterFilters(TRUE, 8);
	else if (lstrcmpW(pszCmdLine, L"9") == 0)
		return RegisterFilters(TRUE, 9);
	else if (lstrcmpW(pszCmdLine, L"10") == 0)
		return RegisterFilters(TRUE, 10);
	else if (lstrcmpW(pszCmdLine, L"11") == 0)
		return RegisterFilters(TRUE, 11);
	else if (lstrcmpW(pszCmdLine, L"12") == 0)
		return RegisterFilters(TRUE, 12);
	else if (lstrcmpW(pszCmdLine, L"12") == 0)
		return RegisterFilters(TRUE, 12);
	else if (lstrcmpW(pszCmdLine, L"13") == 0)
		return RegisterFilters(TRUE, 13);
	else if (lstrcmpW(pszCmdLine, L"14") == 0)
		return RegisterFilters(TRUE, 14);
	else if (lstrcmpW(pszCmdLine, L"15") == 0)
		return RegisterFilters(TRUE, 15);
	else
		return RegisterFilters(TRUE, NUM_VIDEO_FILTERS);
}

STDAPI DllRegisterServer()
{
	return RegisterFilters(TRUE, NUM_VIDEO_FILTERS);
}

STDAPI DllUnregisterServer()
{
	return RegisterFilters(FALSE, NUM_VIDEO_FILTERS);
}

extern "C" BOOL WINAPI DllEntryPoint(HINSTANCE, ULONG, LPVOID);

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  dwReason, LPVOID lpReserved)
{
	return DllEntryPoint((HINSTANCE)(hModule), dwReason, lpReserved);
}
