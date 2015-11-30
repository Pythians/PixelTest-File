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
    ImageAlphaHelper();
    explicit ImageAlphaHelper( std::string dir);
    ~ImageAlphaHelper();
    
    void saveToFiles( std::string dir);
    
    inline std::string getDirectory() const
    {
        return _dir;
    }
    
    void setDirectory(std::string dir)
    {
        _dir = dir;
        findFiles();
    }
    
    std::vector<std::string> & getAllFiles()
    {
        return _allFiles;
    };
    
    std::vector<std::string> & getAllFolders()
    {
        return _allFolders;
    }
    
    inline void setClip(bool b)
    {
        _isClip = b;
    }
    
    inline bool getClip() const
    {
        return _isClip;
    }
protected:
    
    void findFiles();
    void readImage();
    void callback(bool b, float load, std::string msg);
    
private:
    cocos2d::Map<std::string, ImageAlphaLut*> _imgAl;
    
    bool _isClip;
    std::string _dir;
    std::vector<std::string> _allFiles;
    std::vector<std::string> _allFolders;
};

#endif /* defined(__luaGameTemplate__ImageAlphaHelper__) */
