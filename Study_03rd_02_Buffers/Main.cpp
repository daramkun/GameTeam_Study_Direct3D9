#include "../Framework/Framework.h"

struct MyVertex
{
	float x, y, z;
	D3DCOLOR diffuse;

	static const DWORD D3DFVF_CUSTOM =
		D3DFVF_XYZ | D3DFVF_DIFFUSE;
};

MyVertex vertices[4] = {
		{ -0.5f, 0, 0, D3DCOLOR_XRGB(255, 0, 0) },
		{ 0, 0.5f, 0, D3DCOLOR_XRGB(0, 255, 0) },
		{ 0.5f, 0, 0, D3DCOLOR_XRGB(0, 0, 255) },
		{ 0, -0.5f, 0, D3DCOLOR_XRGB(255, 255, 255) },
};

int indices[6] = {
	0, 1, 2,
	0, 2, 3,
};

IDirect3DVertexBuffer9 * vertexBuffer;
IDirect3DIndexBuffer9 * indexBuffer;

void OnInitial(DEVICEINSTANCE *device)
{
	device->d3dDevice->CreateVertexBuffer(sizeof(MyVertex) * 4, D3DUSAGE_DYNAMIC,
		MyVertex::D3DFVF_CUSTOM, D3DPOOL_DEFAULT, &vertexBuffer,
		nullptr);
	MyVertex * bufferForVertex;
	vertexBuffer->Lock(0, sizeof(MyVertex) * 4, (void**)&bufferForVertex,
		D3DLOCK_DISCARD);
	memcpy(bufferForVertex, vertices, sizeof(vertices));
	vertexBuffer->Unlock();

	device->d3dDevice->CreateIndexBuffer(sizeof(int) * 6, D3DUSAGE_DYNAMIC, D3DFMT_INDEX32,
		D3DPOOL_DEFAULT, &indexBuffer, nullptr);
	int * bufferForIndex;
	indexBuffer->Lock(0, sizeof(int) * 6, (void**)&bufferForIndex, D3DLOCK_DISCARD);
	memcpy(bufferForIndex, indices, sizeof(indices));
	indexBuffer->Unlock();
}

void OnUpdate(float dt)
{

}

void OnDraw(DEVICEINSTANCE *device)
{
	device->d3dDevice->BeginScene();

	device->d3dDevice->SetRenderState(D3DRS_LIGHTING, 0);
	device->d3dDevice->SetFVF(MyVertex::D3DFVF_CUSTOM);
	device->d3dDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(MyVertex));
	device->d3dDevice->SetIndices(indexBuffer);
	device->d3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 2);

	device->d3dDevice->EndScene();
}

void OnDestroy()
{
	vertexBuffer->Release();
	indexBuffer->Release();
}