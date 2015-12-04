//
//  ImageAlphaHelper.h
//  luaGameTemplate
//
//  Created by WJDev02 on 15/11/26.
//
//

#ifndef __luaGameTemplate__ImageAlphaHelper__
#define __luaGameTemplate__ImageAlphaHelper__

#include "ImageAlphaLut.h"

class ImageAlphaHelper : public cocos2d::Ref
{
    
public:
    
    static ImageAlphaHelper * create();
    static ImageAlphaHelper * create(std::string &dir);
    
    // 多图片文件快速保存
    void saveToFiles( std::string dir );
    // 文件夹下图片保存单一文件
    void saveInOneFile ( std::string dir );
    
    // 返回读取文件的路径
    inline std::string getDirectory() const
    {
        return _dir;
    }
    
    // 清空保存数据  重新读取文件
    void setDirectory(std::string dir)
    {
        _dir = dir;
        _allFiles.clear();
        _allFolders.clear();
        _imgAl.clear();
        _total.clear();
        findFiles(_dir);
    }
    
    // 通过保存的文件创建多个 ImageAlphaLut 对象
    void createAlphaLutsWithFile(const std::string & file);
    
    // 通过文件名获取对应的 ImageAlphaLut 对象
    ImageAlphaLut * getImageImageLut(const std::string & fname) const
    {
        return _imgAl.at(fname);
    }
    
    // 获取全部 ImageAlphaLut 对象
    cocos2d::Map<std::string, ImageAlphaLut*> & getLutMap()
    {
        return _imgAl;
    }
    
    // 获取所有文件名
    std::vector<std::string> & getAllFiles()
    {
        return _allFiles;
    };
    
    // 获取所有文件夹名
    std::vector<std::string> & getAllFolders()
    {
        return _allFolders;
    }
    
    // 获取是否剪裁
    inline void setIsClip(bool b)
    {
        _isClip = b;
    }
    // 设置是否剪裁
    inline bool getIsClip() const
    {
        return _isClip;
    }
protected:
    ImageAlphaHelper();
    // 读取保存文件用 文件路径
    explicit ImageAlphaHelper( std::string dir);
    ~ImageAlphaHelper();
    
    void findFiles( std::string dir);
    void readImage();
    void saveHelper(std::string dir, int num);
    void writeToFlie(FILE * fp, ImageAlphaLut * lut);
    void callback(bool b, float load, std::string msg);
    
private:
    // 保存创建的对象
    cocos2d::Map<std::string, ImageAlphaLut*> _imgAl;
    // 是否剪裁
    bool _isClip;
    // 初始化路径
    std::string _dir;
    std::vector<int> _total;                // 记录文件夹下文件数量
    std::vector<std::string> _allFiles;     // 记录所有文件
    std::vector<std::string> _allFolders;   // 记录所有子文件夹
};

#endif /* defined(__luaGameTemplate__ImageAlphaHelper__) */
