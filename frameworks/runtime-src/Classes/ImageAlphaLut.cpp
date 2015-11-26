//
//  ImageAlphaLut.cpp
//  pixel
//
//  Created by WJDev02 on 15/11/21.
//
//

#include "ImageAlphaLut.h"

// 文件头大小
#define FILEHEADINFO (sizeof(int) * 7 + sizeof(bool) + sizeof(char) * 50)

const unsigned char ImageAlphaLut::BIT[8] = {
    0x01,0x02,0x04,0x08,
    0x10,0x20,0x40,0x80,
};


USING_NS_CC;

ImageAlphaLut::ImageAlphaLut()
: _alphaLut(nullptr)
, _name(nullptr)
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
    CC_SAFE_FREE(_name);
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
    const char * cpath = "/Users/wjdev02/project/luaGameTemplate/res/test/test.bit";
    
//    if (file != "" ) {
//        cpath = file.c_str();
//    }
    
    // 打开文件
    auto fp = fopen(cpath, "rb");
    // 获取文件大小
    fseek(fp, 0, SEEK_END);
    long fs = ftell(fp);
    rewind(fp);
    
    // 分配文件头信息 BUFF
    unsigned char * buff = (unsigned char *)malloc(FILEHEADINFO);
    // 读取文件头信息
    size_t rs = fread(buff, sizeof(unsigned char), FILEHEADINFO, fp);

    CCASSERT(rs == FILEHEADINFO, "Read file info error");

    // 从 BUFF 中提取信息
    int * p = (int *)buff;
    _width          = *(++p);
    _height         = *(++p);
    _offsetX        = *(++p);
    _offsetY        = *(++p);
    _offsetWidth    = *(++p);
    _offsetHeight   = *(++p);
    bool * bp = (bool*)(++p);
    _isOptimize     = *bp;
    
    char * cp = (char*)(++bp);
    _name = (char*)malloc(strlen(cp));
    strcpy(_name, cp);

    // 释放 BUFF
    CC_SAFE_FREE(buff);
    
    // 分配查找表 内存
    _alphaLut = static_cast<unsigned char *>(malloc((fs - FILEHEADINFO) * sizeof(unsigned char)));

    // 读取查找表信息
    rs = fread(_alphaLut, sizeof(unsigned char), fs, fp);
    CCASSERT(fs- FILEHEADINFO == rs, "Read data error");
    
    // 关闭文件
    fclose(fp);
    
    return true;
}


bool ImageAlphaLut::initWithImage(std::string file)
{
    _name = (char *)malloc(file.length());
    strcpy(_name, file.c_str());
    
    
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
    // 分配文件头 BUFF
    unsigned char * buff = (unsigned char *)malloc(FILEHEADINFO);
    
    CCASSERT(buff, "No more mem");
    
    // 基本信息保存到 BUFF
    int * p = (int *)buff;
    *p = 0x89;
    *(++p) = _width;
    *(++p) = _height;
    *(++p) = _offsetX;
    *(++p) = _offsetY;
    *(++p) = _offsetWidth;
    *(++p) = _offsetHeight;

    bool * bp = (bool*)(++p);
    *bp = _isOptimize;
    
    char * cp = (char*)(++bp);
    strcpy(cp, _name);
    
    
//    char *file = "/Users/wjdev02/project/luaGameTemplate/res/test";
//    if (!FileUtils::getInstance()->createDirectory(s))
//        log("create dir fail");
    
    const char * cpath = "/Users/wjdev02/project/luaGameTemplate/res/test/test.bit";
    
    if (path != "" ) {
        cpath = path.c_str();
    }
    
    // 打开文件
    auto fp = fopen(cpath, "wb");

    // 写入文件
    size_t ws = fwrite(buff, sizeof(unsigned char), FILEHEADINFO, fp);
    
    CCASSERT(ws == FILEHEADINFO, "Write file info error");
    
    ws = fwrite(_alphaLut, sizeof(unsigned char), getBufferSize(), fp);
    
    CCASSERT(ws == getBufferSize(), "Write file data error");
    // 关闭文/Users/wjdev02件
    fclose(fp);
    // 释放 BUFF
    CC_SAFE_FREE(buff);
    
    return true;
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