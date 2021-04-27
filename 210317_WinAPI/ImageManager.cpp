#include "ImageManager.h"
#include "Image.h"

HRESULT ImageManager::Init()
{
    return S_OK;
}

void ImageManager::Release()
{
    // ��� �̹����� ���� �޸� ������ �̷�� ����.
    map<string, Image*>::iterator it;
    for (it = mImageDatas.begin(); it != mImageDatas.end(); it++)
    {
        if ((it->second))
        {
            (it->second)->Release();
            delete (it->second);
            (it->second) = nullptr;
        }
    }
    mImageDatas.clear();

    ReleaseSingleton();
}

Image* ImageManager::AddImage(string key, const char* fileName, int width, int height, bool isTransparent, COLORREF transColor)
{
    Image* image = nullptr;

    // �ʿ� Ű�� �ش��ϴ� �����Ͱ� ������ �߰��������� ����
    image = FindImage(key);
    if (image)
    {
        return image;
    }

    // ������ ���� �� �ʿ� �߰�
    image = new Image();
    if (FAILED(image->Init(fileName, width, height, isTransparent, transColor)))
    {
        image->Release();
        delete image;

        return nullptr;
    }

    mImageDatas.insert(make_pair(key, image));
    return image;
}

Image* ImageManager::AddImage(string key, const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
    Image* image = nullptr;

    // �ʿ� Ű�� �ش��ϴ� �����Ͱ� ������ �߰��������� ����
    image = FindImage(key);
    if (image)
    {
        return image;
    }

    // ������ ���� �� �ʿ� �߰�
    image = new Image();
    if (FAILED(image->Init(fileName, width, height,
        maxFrameX, maxFrameY, isTransparent, transColor)))
    {
        image->Release();
        delete image;

        return nullptr;
    }

    mImageDatas.insert(make_pair(key, image));
    return image;
}

void ImageManager::DeleteImage(string key)
{
    map<string, Image*>::iterator it;
    it = mImageDatas.find(key);

    if (it == mImageDatas.end())
    {
        return;
    }

    // �ʿ� key, value pair�� �ִ� ����
    // value�� �ش��ϴ� Image* �����͵� �޸� �����ؾ� �Ѵ�.
    (it->second)->Release();
    delete (it->second);
    (it->second) = nullptr;

    mImageDatas.erase(it);
}

Image* ImageManager::FindImage(string key)
{
    map<string, Image*>::iterator it;
    it = mImageDatas.find(key);

    if (it == mImageDatas.end())
    {
        return nullptr;
    }

    return it->second;
}