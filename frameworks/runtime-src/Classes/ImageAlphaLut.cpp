//
//  ImageAlphaLut.cpp
//  pixel
//
//  Created by WJDev02 on 15/11/21.
//
//

#include "ImageAlphaLut.h"

const unsigned char ImageAlphaLut::BIT[8] = {
    0x01,0x02,0x04,0x08,
    0x10,0x20,0x40,0x80,
};


USING_NS_CC;

ImageAlphaLut::ImageAlphaLut()
: _alphaLut(nullptr)
, _width(0)
, _height(0)
, _offsetX(0)
, _offsetY(0)
, _offsetWidth(0)
, _offsetHeight(0)
, _isOptimize(false)
{
}


ImageAlphaLut::~ImageAlphaLut()
{
    CC_SAFE_FREE(_alphaLut);
}


ImageAlphaLut* ImageAlphaLut::createWithFile(const std::string file){
    
    auto ret = new ImageAlphaLut();
    if (ret && ret->initWithFile(file))
    {
        ret->autorelease();
    }
    else
    {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

ImageAlphaLut* ImageAlphaLut::createWithImage(const std::string file){
    
    auto ret = new ImageAlphaLut();
    if (ret && ret->initWithImage(file))
    {
        ret->autorelease();
    }
    else
    {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

ImageAlphaLut* ImageAlphaLut::createWithImageAndClip(const std::string file){
    
    auto ret = new ImageAlphaLut();
    if (ret && ret->initWithImageAndClip(file))
    {
        ret->autorelease();
    }
    else
    {
        delete ret;
        ret = nullptr;
    }
    return ret;
}


bool ImageAlphaLut::initWithFile(const std::string file)
{
 
    _offsetX = 40;
    _offsetY = 0;
    _offsetWidth = 487;
    _offsetHeight = 403;
    _width = 572;
    _height = 417;
    _isOptimize = true;
    
    auto fp = fopen("/Users/wjdev02/project/luaGameTemplate/res/test/test.bit", "rb");
    
    fseek(fp, 0, SEEK_END);
    long fs = ftell(fp);
    rewind(fp);
    
    _alphaLut = static_cast<unsigned char *>(malloc(fs * sizeof(unsigned char)));
    
    if(fs != fread(_alphaLut, sizeof(unsigned char), fs, fp))
        log("file read error");
    
    fclose(fp);
    
//    printLut();
    
    return true;
}


bool ImageAlphaLut::initWithImage(std::string file)
{
    _name = file;
    bool b = true;
    auto img = new Image();
    
    if (!img->initWithImageFile(file))
        b = false;
    
    auto lengh = img->getDataLen();
    CCASSERT(lengh >= 8, "NO image data");
    
    _width = img->getWidth();
    _height = img->getHeight();
    auto data = img->getData();
    // 初始化 BUFF
    resetBuffer();
    // 提取图片透明信息
    for (int i = 0 ; i < _width * _height; ++i)
    {
        if (data[i*4]) {
            setPixelAlpha(i);
        }
    }
    
    return b;
}

bool ImageAlphaLut::initWithImageAndClip(const std::string file)
{
    bool b = initWithImage(file);
    // 设置偏移
    setOffsetAndSize();
    
    log("offset :  w %d h %d", _offsetWidth, _offsetHeight);
    log("offset :  x %d y %d", _offsetX, _offsetY);
    log("width: %d height: %d", _width,_height);

    
//    saveToFile("");
    
    return b;
}

void ImageAlphaLut::setOffsetAndSize()
{
    // 设置偏移
    for (int i = 0; i < _width; ++i)
    {
        // 从左边列开始，一列一列遍历
        for (int j = 0 ; j < _height; ++j)
        {
            if (getPixelAlpha(i + j * _width))
            {
                // 若有像素，则设置 X 偏移为当前列
                _offsetX = i;
                goto OFFSETX;
            }
        }
    }
OFFSETX:
    for (int i = 0; i < _height; ++i)
    {
        // 从上面第一行开始，一行一行遍历
        for (int j = 0 ; j < _width; ++j)
        {
            if (getPixelAlpha(j + i * _width))
            {
                // 若有像素，则设置 Y 偏移为当前行
                _offsetY = i;
                goto OFFSETY;
            }
        }
    }
OFFSETY:
    auto size = _width * _height;
    // 设置宽高
    // 从右面开始 列 遍历到 X 偏移
    for (int i = 0; i < _width - _offsetX; ++i)
    {
        // 从下面开始 遍历 列像素
        for (int j = 0; j < _height - _offsetY ; ++j)
        {
            // 若有像素， 设置宽 i - X 偏移
            if (getPixelAlpha(size - 1 - i - j * _width))
            {
                _offsetWidth = _width - _offsetX - i;
                goto UPWIDTH;
            }
        }
    }
UPWIDTH:
    auto offsetSize = size - 1 - ( _width - _offsetX - _offsetWidth );
    // 从下面开始遍历到 Y 偏移
    for (int i = 0 ; i < _height - _offsetY; ++i)
    {
        // 从右面开始 遍历 行 像素
        for (int j = 0; j < _offsetWidth; ++j)
        {
            // 若有像素， 设置高 - Y 偏移
            if (getPixelAlpha( offsetSize - j - i * _width ))
            {
                _offsetHeight = _height - _offsetY - i;
                goto UPHEIGHT;
            }
        }
    }
UPHEIGHT:
    // 设置偏移
    _isOptimize = true;
    // 更新 BUFF
    moveBuffer();
}

bool ImageAlphaLut::isPixelAlpha(int x, int y) const
{
    // Y 轴反转
    y = _height - y;
    // 是否偏移
    if (_isOptimize)
    {
        // 判断是否在偏移区内
        if (x > _offsetX && y > _offsetY
            && x < _offsetX + _offsetWidth
            && y < _offsetY + _offsetHeight)
        {
            // 转化为偏移坐标
            x -= _offsetX;
            y -= _offsetY;
            return getPixelAlpha(x + y * _offsetWidth);
        }
        else
            return false;
    }
    else
        return getPixelAlpha(x + y * _width);
}

void ImageAlphaLut::resetBuffer()
{
    // 清除之前的 BUFF
    CC_SAFE_FREE(_alphaLut);
    // 重新分配 BUFF
    _alphaLut = static_cast<unsigned char*>(malloc( _width * _height / 8));
    // 初始化为 0
    memset(_alphaLut, 0, _width * _height / 8);
}

void ImageAlphaLut::moveBuffer()
{
    // Move buffer
    
    // new buffef
    auto buff = static_cast<unsigned char *>(malloc(_offsetWidth * _offsetHeight / 8));
    memset(buff, 0, _offsetWidth * _offsetHeight / 8);
    // 计算前面的偏移
    auto offsetBuff = _width * _offsetY + _offsetX;
    for (int i = 0; i < _offsetHeight; ++i)
    {
        for (int j = 0; j < _offsetWidth; ++j)
        {
            // 复制信息
            if (getPixelAlpha(offsetBuff + i * _width + j)) {
                copyPixelAlpha(i * _offsetWidth + j, buff);
            }
        }
    }
    // 删除原 BUFF
    free(_alphaLut);
    // 指向偏移 BUFF
    _alphaLut = buff;
}

bool ImageAlphaLut::saveToFile(const std::string path)
{
    bool b;

    char *s = "/Users/wjdev02/project/luaGameTemplate/res/test";
    
    if (!FileUtils::getInstance()->createDirectory(s))
        log("create dir fail");
    
//    const char * fnn = "/test.bit";
//    auto fn = strcat(s, fnn);
    auto fp = fopen("/Users/wjdev02/project/luaGameTemplate/res/test/test.bit", "wb+");
//    fseek(fp, 0, SEEK_END);
//    long ls = ftell(fp);
//    rewind(fp);
//    char * bu = (char*)malloc(sizeof(char) * ls);
//
//    ls = fread(bu, 1, ls, fp);
    
    size_t ws = fwrite(_alphaLut, sizeof(unsigned char), getBufferSize(), fp);
    fclose(fp);
    log("-- write %ld", ws);
    
//    log("%s")
    
//    
//    if (path) {
//        
//    }
//    
    return b;
}

void ImageAlphaLut::printLut() const {
    int w = _width;
    int h = _height;
    if (_isOptimize)
    {
        w = _offsetWidth;
        h = _offsetHeight;
    }
    // 遍历输出查找表
    for (int i = 0 ; i < h; ++i)
    {
        // 输出一行
        for (int j = 0; j < w; ++j)
        {
            printf("%d", getPixelAlpha(j + i * w));
        }
        log("");
    }
}