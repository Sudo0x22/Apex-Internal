#pragma once
#include<d3d11.h>
#include<dxgi.h>

#include"../../../modules/modules.hpp"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

#if defined _M_X64
typedef uint64_t uintx_t;
#elif defined _M_IX86
typedef uint32_t uintx_t;
#endif

static uintx_t* MethodsTable = NULL;

typedef HRESULT(__stdcall* oPresent_t)(IDXGISwapChain*, UINT, UINT);
typedef LRESULT(__stdcall* oWndProc_t)(HWND, UINT, WPARAM, LPARAM);
HRESULT(*ResizeOriginal)(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) = nullptr;

typedef BOOL(__stdcall* oCursor_t)(bool);
typedef BOOL(__stdcall* oShowCursor_t)(int, int);

typedef struct
{
	DWORD hModuleSize;
	HINSTANCE hModule;
	IMAGE_NT_HEADERS nt_headers;
	IMAGE_DOS_HEADER dos_header;
	BYTE* memory_bytes;
} ID3D11, * PID3D11;

class D3D11
{
public:
	oPresent_t oPresent = 0;
	oWndProc_t oWndProc = 0;
	oCursor_t oCursor = 0;
	oShowCursor_t oShowCursor = 0;
	//oResizeBuffer_t oResizeBuffer = 0;
public:
	ID3D11Device* pDevice = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pRenderTargetView = nullptr;
public:
	HWND hWindow = 0;
	WNDCLASSEX WindowClass;
	HWND WindowHwnd = 0;
}; D3D11* pD3D11 = new D3D11();