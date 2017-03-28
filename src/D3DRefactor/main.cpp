// include the basic Windows header files and the Direct3D header files
#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>

// include the Direct3D library file
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

// Define the screen resolution
#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

// Vertex struct
struct Vert
{
    FLOAT X, Y, Z; // position
    D3DXCOLOR Color; // color
};

// global declarations
IDXGISwapChain * g_swapChain;          // The pointer to the swap chain interface
ID3D11Device * g_dev;                  // The pointer to our Direct3D device interface
ID3D11DeviceContext * g_devCon;        // The pointer to our Direct3D device context
ID3D11RenderTargetView * g_backBuffer; // The back buffer render target
ID3D11InputLayout * g_layout;          // The input layout object

// Shader objects
ID3D11VertexShader * g_VS;             // the vertex shader
ID3D11PixelShader * g_PS;              // the pixel shader

ID3D11Buffer * g_VBuffer;

// function prototypes
void InitD3D(HWND hWnd);      // sets up and initializes Direct3D
void InitPipeline(void);      // initialize the rendering pipeline
void InitGraphics(void);      // initialize the graphics data for rendering
void RenderFrame(void);       // renders a single frame
void CleanD3D(void);          // closes Direct3D and releases memory

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    HWND hWnd;
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    // wc.hbrBackground = (HBRUSH) COLOR_WINDOW; // Disabled so that the window doesn't have a background
    wc.lpszClassName = "WindowClass";

    RegisterClassEx(&wc);

    RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
    
    hWnd = CreateWindowEx(NULL,
                          "WindowClass",
                          "Our First Direct3D Program",
                          WS_OVERLAPPEDWINDOW,
                          300,
                          300,
                          wr.right - wr.left,
                          wr.bottom - wr.top,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hWnd, nCmdShow);

    // set up and initialize Direct3D
    InitD3D(hWnd);

    // enter the main loop:

    MSG msg;
    
    while (TRUE)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                break;
        }

        RenderFrame();
    }

    // clean up DirectX and COM
    CleanD3D();

    return msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    } break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

// this function initializes and prepares Direct3D for use
void InitD3D(HWND hWnd)
{
    // create a struct to hold information about the swap chain
    DXGI_SWAP_CHAIN_DESC scd;

    // clear out the struct for use
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    // fill the swap chain description struct
    scd.BufferCount = 1;                                // one back buffer
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // use 32-bit color
    scd.BufferDesc.Width = SCREEN_WIDTH;                // set the back buffer width
    scd.BufferDesc.Height = SCREEN_HEIGHT;              // set the back buffer height
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;  // how swap chain is to be used
    scd.OutputWindow = hWnd;                            // the window to be used
    scd.SampleDesc.Count = 4;                           // how many multisamples
    scd.Windowed = TRUE;                                // windowed/full-screen mode
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // allow full-screen switching

    // create a device, device context and swap chain using the information in the scd struct
    D3D11CreateDeviceAndSwapChain(NULL,
                                  D3D_DRIVER_TYPE_HARDWARE,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  D3D11_SDK_VERSION,
                                  &scd,
                                  &g_swapChain,
                                  &g_dev,
                                  NULL,
                                  &g_devCon);

    // get the address of the back buffer
    ID3D11Texture2D * pBackBuffer;
    g_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*) &pBackBuffer);

    // use the back buffer address to create the render target
    g_dev->CreateRenderTargetView(pBackBuffer, NULL, &g_backBuffer);
    pBackBuffer->Release();

    // set the render target as the back buffer
    g_devCon->OMSetRenderTargets(1, &g_backBuffer, NULL);

    // Set the viewport
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = SCREEN_WIDTH;
    viewport.Height = SCREEN_HEIGHT;

    g_devCon->RSSetViewports(1, &viewport);

    InitPipeline();
    InitGraphics();
}

// this is the function used to render a single frame
void RenderFrame()
{
    // clear the back buffer to a deep blue
    g_devCon->ClearRenderTargetView(g_backBuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));

    // select which vertex buffer to display
    UINT stride = sizeof(Vert);
    UINT offset = 0;
    g_devCon->IASetVertexBuffers(0, 1, &g_VBuffer, &stride, &offset);

    // select which primitive type we are using
    g_devCon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // draw the vertex buffer to the back buffer
    g_devCon->Draw(3, 0);

    // switch the back buffer and the front buffer
    g_swapChain->Present(0, 0);
}

// this is the function that cleans up Direct3D and COM
void CleanD3D()
{
    // Switch to fullscreen mode because D3D can't close in fullscreen mode
    g_swapChain->SetFullscreenState(FALSE, NULL);

    // close and release all existing COM objects
    g_layout->Release();
    g_VS->Release();
    g_PS->Release();
    g_VBuffer->Release();
    g_swapChain->Release();
    g_backBuffer->Release();
    g_dev->Release();
    g_devCon->Release();
}

void InitGraphics()
{
    // create a triangle using the Vert struct
    Vert OurVertices[] =
    {
        {  0.0f,   0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f) },
        {  0.45f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f) },
        { -0.45f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f) },
    };

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DYNAMIC;             // write access by CPU and read access by GPU
    bd.ByteWidth = sizeof(Vert) * 6;            // size is the Vert struct * 3
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;    // use as a vertex buffer
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // allow CPU to write in buffer

    g_dev->CreateBuffer(&bd, NULL, &g_VBuffer); // create the buffer

    // copy the vertices into the buffer
    D3D11_MAPPED_SUBRESOURCE ms;
    g_devCon->Map(g_VBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms); // map the buffer
    memcpy(ms.pData, OurVertices, sizeof(OurVertices));                 // copy the data
    g_devCon->Unmap(g_VBuffer, NULL);                                   // unmap the buffer
}

void InitPipeline()
{
    // load and compile the two shaders
    ID3D10Blob * VS, * PS;
    D3DX11CompileFromFile("shaders\\shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
    D3DX11CompileFromFile("shaders\\shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

    // encapsulate both shaders into the shader objects
    g_dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &g_VS);
    g_dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &g_PS);

    // set the shader objects
    g_devCon->VSSetShader(g_VS, 0, 0);
    g_devCon->PSSetShader(g_PS, 0, 0);
    
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    g_dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &g_layout);
    g_devCon->IASetInputLayout(g_layout);        
}
