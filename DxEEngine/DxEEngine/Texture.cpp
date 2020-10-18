#include "pch.h"
#include "Texture.h"

#include "StringHelper.h"

USING(dxengine)

Texture::Texture()
    : m_targadata(nullptr)
    , m_texture(nullptr)
    , m_textureView(nullptr)
{
}

Texture::Texture(const Texture& other)
{
}

Texture::~Texture()
{
}

bool Texture::Initialize(ID3D11Device* device, ID3D11DeviceContext* context, WCHAR* filename)
{
    int width = 0;
    int height = 0;

    if (!LoadTarga(filename, height, width))
    {
        return false;
    }

    D3D11_TEXTURE2D_DESC textureDesc;
    textureDesc.Height = height;
    textureDesc.Width = width;
    textureDesc.MipLevels = 0;
    textureDesc.ArraySize = 1;
    textureDesc.Format = DXGI_FORMAT_R8G8B8A8_SNORM;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
    textureDesc.CPUAccessFlags = 0;
    textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

    HRESULT result = device->CreateTexture2D(&textureDesc, NULL, &m_texture);
    FAILED_RETURN(result, false);

    UINT rowPitch = (width * 4) * sizeof(UCHAR);

    context->UpdateSubresource(m_texture, 0, NULL, m_targadata, rowPitch, 0);
    
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    srvDesc.Format = textureDesc.Format;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.MipLevels = -1;

    result = device->CreateShaderResourceView(m_texture, &srvDesc, &m_textureView);
    FAILED_RETURN(result, false);

    context->GenerateMips(m_textureView);

    delete[] m_targadata;
    m_targadata = 0;

    return true;
}

void Texture::Shutdown()
{
    if (m_textureView)
    {
        m_textureView->Release();
        m_textureView = 0;
    }

    if (m_texture)
    {
        m_texture->Release();
        m_texture = 0;
    }

    if (m_targadata)
    {
        delete[] m_targadata;
        m_targadata = 0;
    }
}

ID3D11ShaderResourceView* Texture::GetTexture()
{
    return m_textureView;
}

bool Texture::LoadTarga(WCHAR* filename, int& height, int& width)
{
    FILE* filePtr;
    if (fopen_s(&filePtr, WCharToChar(filename), "rb") != 0) { return false; }

    TargetHeader targaFileHeader;
    UINT count = (UINT)fread(&targaFileHeader, sizeof(TargetHeader), 1, filePtr);
    if (count != 1) { return false; }

    height = (int)targaFileHeader.height;
    width = (int)targaFileHeader.width;
    int bpp = (int)targaFileHeader.bpp;

    if (bpp != 32) { return false; }

    int imageSize = width * height * 4;
    UCHAR* targaImage = new UCHAR[imageSize];
    memset(targaImage, 0, sizeof(UCHAR) * imageSize);
    if (!targaImage) { return false; }

    count = (UINT)fread(targaImage, 1, imageSize, filePtr);
    if (count != imageSize) { return false; }

    if (fclose(filePtr) != 0) { return false; }

    m_targadata = new UCHAR[imageSize];
    memset(m_targadata, 0, sizeof(UCHAR) * imageSize);
    if (!m_targadata) { return false; }

    int index = 0;
    int k = (width * height * 4) - (width * 4);
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            m_targadata[index + 0] = targaImage[k + 2];
            m_targadata[index + 1] = targaImage[k + 1];
            m_targadata[index + 2] = targaImage[k + 0];
            m_targadata[index + 3] = targaImage[k + 3];

            k += 4;
            index += 4;
        }

        k -= (width * 8);
    }

    delete[] targaImage;
    targaImage = 0;

    return true;
}
