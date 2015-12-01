//
//  ImageAlphaLut.h
//  pixel
//
//  Created by WJDev02 on 15/11/21.
//
//

#ifndef __pixel__ImageAlphaLut__
#define __pixel__ImageAlphaLut__

#include "cocos2d.h"

class ImageAlphaLut : public cocos2d::Ref
{
    
    
public:
    // 从文件创建查找表
    static ImageAlphaLut * createWithFile(const std::string file);
    // 创建图标透明查找表
    static ImageAlphaLut * createWithImage(const std::string image);
    // 创建图标透明查找表，去多余透明像素
    static ImageAlphaLut * createWithImageAndClip(const std::string image);
    
    
    // 检测像素 X Y 为原始图片坐标
    bool isPixelAlpha(int x, int y) const;
    // 保存 BUFF 为文件
    bool saveToFile(const std::string path) const;
    
    void printLut() const;  // 输出

    // 返回是否优化
    inline bool isOptimize()const {return _isOptimize;}
    inline int getWidth() const {return _width;}                    // 返回原始宽
    inline int getHeight() const {return _height;}                  // 返回原始高
    inline int getOffsetX() const {return _offsetX;}                // 返回偏移 X
    inline int getOffsetY() const {return _offsetY;}                // 返回偏移 Y
    inline int getOffsetWidth() const {return _offsetWidth;}        // 返回偏移宽
    inline int getOffsetHeight() const { return _offsetHeight;}     // 返回偏移高
    inline char * getName() const { return _name;}             // 返回引用图片名
    int getBufferSize()const                                        // 返回 BUFF 占用
    {
        if (_isOptimize)
        {
            return _offsetWidth * _offsetHeight / 8;
        }
        else
        {
            return _width * _height / 8;
        }
    }

private:
    // 查找表 BUFF
    unsigned char * _alphaLut;
    // 图片名
    char * _name;
    // 原始宽高
    int _width;
    int _height;
    // 偏移
    int _offsetX;
    int _offsetY;
    // 偏移后宽高
    int _offsetWidth;
    int _offsetHeight;
    // 是否偏移
    bool _isOptimize;

    // 16 位掩码
    const static unsigned char BIT[8];
    
    inline void setPixelAlpha(int idx)
    {
        _alphaLut[idx / 8] |= BIT[idx % 8];
    }
    
    inline bool getPixelAlpha(int idx) const
    {
        return _alphaLut[idx / 8] & BIT[idx % 8];
    }
    
    inline void copyPixelAlpha(int idx, unsigned char * buff)
    {
        buff[idx / 8] |= BIT[idx % 8];
    }
    
    void setOffsetAndSize();
    void resetBuffer();
    void moveBuffer();

protected:
    ImageAlphaLut();
    virtual ~ImageAlphaLut();
    
    virtual bool initWithFile(const std::string file);
    virtual bool initWithImage(const std::string image);
    virtual bool initWithImageAndClip( const std::string file);

};

#endif /* defined(__pixel__ImageAlphaLut__) */
