#include "pch.h"
#include "TextureRender.h"

#include <fstream>
#include <corecrt_wstring.h>

USING(dxengine)

bool TextureRender::Initialize(ID3D11Device* device, HWND hwnd)
{
	WCHAR vsPath[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, vsPath);
	WCHAR psPath[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, psPath);
	std::wcscat(vsPath, L"\\Shader\\Texture.vs");
	std::wcscat(psPath, L"\\Shader\\Texture.ps");

    return InitializeShader(device, hwnd, vsPath, psPath);
}

void TextureRender::Shutdown()
{
	ShutdownShader();
}

bool TextureRender::Render(ID3D11DeviceContext* context, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture)
{
	if (!SetShaderParameters(context, worldMatrix, viewMatrix, projectionMatrix, texture))
	{
		return false;
	}

	RenderShader(context, indexCount);

    return true;
}

bool TextureRender::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{
	HRESULT result;
	ID3D10Blob* errorMessage = nullptr;

	ID3D10Blob* vertexShaderBuffer = nullptr;
	result = D3DCompileFromFile(vsFilename, NULL, NULL
		, "TextureVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS
		, 0, &vertexShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		}
		else
		{
			MessageBox(hwnd, vsFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	ID3D10Blob* pixelShaderBuffer = nullptr;
	result = D3DCompileFromFile(psFilename, NULL, NULL
		, "TexturePixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS
		, 0, &pixelShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		}
		else
		{
			MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer()
		, vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	FAILED_RETURN(result, false);

	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer()
		, pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	FAILED_RETURN(result, false);

	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	polygonLayout[0].SemanticName			= "POSITION";
	polygonLayout[0].SemanticIndex			= 0;
	polygonLayout[0].Format					= DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[0].InputSlot				= 0;
	polygonLayout[0].AlignedByteOffset		= 0;
	polygonLayout[0].InputSlotClass			= D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate	= 0;

	polygonLayout[1].SemanticName			= "TEXCOORD";
	polygonLayout[1].SemanticIndex			= 0;
	polygonLayout[1].Format					= DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot				= 0;
	polygonLayout[1].AlignedByteOffset		= D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass			= D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate	= 0;

	UINT numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	result = device->CreateInputLayout(polygonLayout, numElements
		, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize()
		, &m_layout);
	FAILED_RETURN(result, false);

	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

	D3D11_BUFFER_DESC matrixBufferDesc;
	matrixBufferDesc.Usage					= D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth				= sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags				= D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags			= D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags				= 0;
	matrixBufferDesc.StructureByteStride	= 0;

	result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	FAILED_RETURN(result, false);

	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter			= D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU		= D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV		= D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW		= D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias		= 0.0f;
	samplerDesc.MaxAnisotropy	= 1;
	samplerDesc.ComparisonFunc	= D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0]	= 0;
	samplerDesc.BorderColor[1]	= 0;
	samplerDesc.BorderColor[2]	= 0;
	samplerDesc.BorderColor[3]	= 0;
	samplerDesc.MinLOD			= 0;
	samplerDesc.MaxLOD			= D3D11_FLOAT32_MAX;

	result = device->CreateSamplerState(&samplerDesc, &m_sampleState);
	FAILED_RETURN(result, false);

    return true;
}

void TextureRender::ShutdownShader()
{
	IRender::ShutdownShader();
}

void TextureRender::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	IRender::OutputShaderErrorMessage(errorMessage, hwnd, shaderFilename);
}

bool TextureRender::SetShaderParameters(ID3D11DeviceContext* context, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D11ShaderResourceView* texture)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	unsigned int bufferNumber;

	// Transpose the matrices to prepare them for the shader.
	worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projectionMatrix = XMMatrixTranspose(projectionMatrix);

	// Lock the constant buffer so it can be written to.
	result = context->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	FAILED_RETURN(result, false);

	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// Unlock the constant buffer.
	context->Unmap(m_matrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Finanly set the constant buffer in the vertex shader with the updated values.
	context->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);
	context->PSSetShaderResources(0, 1, &texture);

	return true;
}

void TextureRender::RenderShader(ID3D11DeviceContext* context, int indexCount)
{
	IRender::RenderShader(context, indexCount);
}
