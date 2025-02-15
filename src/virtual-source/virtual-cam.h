#pragma once

extern "C"
{
#include "libswscale/swscale.h" 
};

#include "../queue/share_queue_read.h"
#include <deque>

#define DECLARE_PTR(type, ptr, expr) type* ptr = (type*)(expr);

EXTERN_C const GUID CLSID_OBS_VirtualV;
EXTERN_C const GUID CLSID_OBS_VirtualV2;
EXTERN_C const GUID CLSID_OBS_VirtualV3;
EXTERN_C const GUID CLSID_OBS_VirtualV4;
// TODO16
EXTERN_C const GUID CLSID_OBS_VirtualV5;
EXTERN_C const GUID CLSID_OBS_VirtualV6;
EXTERN_C const GUID CLSID_OBS_VirtualV7;
EXTERN_C const GUID CLSID_OBS_VirtualV8;
EXTERN_C const GUID CLSID_OBS_VirtualV9;
EXTERN_C const GUID CLSID_OBS_VirtualV10;
EXTERN_C const GUID CLSID_OBS_VirtualV11;
EXTERN_C const GUID CLSID_OBS_VirtualV12;
EXTERN_C const GUID CLSID_OBS_VirtualV13;
EXTERN_C const GUID CLSID_OBS_VirtualV14;
EXTERN_C const GUID CLSID_OBS_VirtualV15;
EXTERN_C const GUID CLSID_OBS_VirtualV16;

class CVCamStream;

struct format
{
	format(int width_, int height_, int64_t time_per_frame_) {
		width = width_;
		height = height_;
		time_per_frame = time_per_frame_;
	}
	int width;
	int height;
	int64_t time_per_frame;
};

extern CUnknown * WINAPI CreateInstance(LPUNKNOWN lpunk, HRESULT *phr);
extern CUnknown * WINAPI CreateInstance2(LPUNKNOWN lpunk, HRESULT *phr);
extern CUnknown * WINAPI CreateInstance3(LPUNKNOWN lpunk, HRESULT *phr);
extern CUnknown * WINAPI CreateInstance4(LPUNKNOWN lpunk, HRESULT *phr);
// TODO16
extern CUnknown * WINAPI CreateInstance5(LPUNKNOWN lpunk, HRESULT *phr);
extern CUnknown * WINAPI CreateInstance6(LPUNKNOWN lpunk, HRESULT *phr);
extern CUnknown * WINAPI CreateInstance7(LPUNKNOWN lpunk, HRESULT *phr);
extern CUnknown * WINAPI CreateInstance8(LPUNKNOWN lpunk, HRESULT *phr);
extern CUnknown * WINAPI CreateInstance9(LPUNKNOWN lpunk, HRESULT *phr);
extern CUnknown * WINAPI CreateInstance10(LPUNKNOWN lpunk, HRESULT *phr);
extern CUnknown * WINAPI CreateInstance11(LPUNKNOWN lpunk, HRESULT *phr);
extern CUnknown * WINAPI CreateInstance12(LPUNKNOWN lpunk, HRESULT *phr);
extern CUnknown * WINAPI CreateInstance13(LPUNKNOWN lpunk, HRESULT *phr);
extern CUnknown * WINAPI CreateInstance14(LPUNKNOWN lpunk, HRESULT *phr);
extern CUnknown * WINAPI CreateInstance15(LPUNKNOWN lpunk, HRESULT *phr);
extern CUnknown * WINAPI CreateInstance16(LPUNKNOWN lpunk, HRESULT *phr);

class CVCam : public CSource
{
public:
	DECLARE_IUNKNOWN;
	//////////////////////////////////////////////////////////////////////////
	//  IUnknown
	//////////////////////////////////////////////////////////////////////////
	
	STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void **ppv);
	IFilterGraph *GetGraph() { return m_pGraph; }
	FILTER_STATE GetState(){ return m_State; }
	CVCam(LPUNKNOWN lpunk, HRESULT *phr, const GUID id, int mode);
protected:
	CVCamStream *stream = nullptr;

};

class CVCamStream : public CSourceStream, public IAMStreamConfig, public IKsPropertySet
{
public:

	//////////////////////////////////////////////////////////////////////////
	//  IUnknown
	//////////////////////////////////////////////////////////////////////////
	STDMETHODIMP QueryInterface(REFIID riid, void **ppv);
	STDMETHODIMP_(ULONG) AddRef() { return GetOwner()->AddRef(); }
	STDMETHODIMP_(ULONG) Release() { return GetOwner()->Release(); }

	//////////////////////////////////////////////////////////////////////////
	//  IQualityControl
	//////////////////////////////////////////////////////////////////////////
	STDMETHODIMP Notify(IBaseFilter * pSender, Quality q);

	//////////////////////////////////////////////////////////////////////////
	//  IAMStreamConfig
	//////////////////////////////////////////////////////////////////////////
	HRESULT STDMETHODCALLTYPE SetFormat(AM_MEDIA_TYPE *pmt);
	HRESULT STDMETHODCALLTYPE GetFormat(AM_MEDIA_TYPE **ppmt);
	HRESULT STDMETHODCALLTYPE GetNumberOfCapabilities(int *piCount, int *piSize);
	HRESULT STDMETHODCALLTYPE GetStreamCaps(int iIndex, AM_MEDIA_TYPE **pmt,
		BYTE *pSCC);

	//////////////////////////////////////////////////////////////////////////
	//  IKsPropertySet
	//////////////////////////////////////////////////////////////////////////
	HRESULT STDMETHODCALLTYPE Set(REFGUID guidPropSet, DWORD dwID, 
		void *pInstanceData, DWORD cbInstanceData, void *pPropData, DWORD cbPropData);

	HRESULT STDMETHODCALLTYPE Get(REFGUID guidPropSet, DWORD dwPropID, 
		void *pInstanceData, DWORD cbInstanceData, void *pPropData, 
		DWORD cbPropData, DWORD *pcbReturned);

	HRESULT STDMETHODCALLTYPE QuerySupported(REFGUID guidPropSet, 
		DWORD dwPropID, DWORD *pTypeSupport);

	//////////////////////////////////////////////////////////////////////////
	//  CSourceStream
	//////////////////////////////////////////////////////////////////////////
	CVCamStream(HRESULT *phr, CVCam *pParent, LPCWSTR pPinName, int mode);
	~CVCamStream();

	HRESULT FillBuffer(IMediaSample *pms);
	HRESULT DecideBufferSize(IMemAllocator *pIMemAlloc, ALLOCATOR_PROPERTIES *pProperties);
	HRESULT CheckMediaType(const CMediaType *pMediaType);
	HRESULT GetMediaType(int iPosition,CMediaType *pmt);
	HRESULT SetMediaType(const CMediaType *pmt);
	HRESULT OnThreadCreate(void);
	HRESULT OnThreadDestroy(void);
	
private:

	bool ListSupportFormat(void);
	bool CheckObsSetting(void);
	bool ValidateResolution(long width, long height);
	void SetSyncTimeout();
	void SetGetTimeout();
	void SetConvertContext(void);

	CVCam *parent;
	std::deque<format> format_list;

	//for Fillbuffer() use
	share_queue queue = {};
	bool reset_mode = false;
	int queue_mode = 0;
	int format = 0;
	int get_timeout = 20;
	uint8_t* dst;
	uint32_t frame_width = 0;
	uint32_t frame_height = 0;
	uint64_t obs_start_ts = 0;
	uint64_t dshow_start_ts = 0;
	uint64_t time_perframe = 0;
	uint64_t system_start_time = 0;
	uint64_t sync_timeout = 0;
	REFERENCE_TIME  prev_end_ts = 0;

	//obs format related
	bool use_obs_format_init = false;
	int obs_format = 0;
	uint32_t obs_width = 1920;
	uint32_t obs_height = 1080;
	uint64_t obs_frame_time = 333333;
	dst_scale_context scale_info;

};
