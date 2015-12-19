//
//  ImageAlphaHelper.cpp
//  luaGameTemplate
//
//  Created by WJDev02 on 15/11/26.
//
//

#include "ImageAlphaHelper.h"
#include <dirent.h>

USING_NS_CC;

ImageAlphaHelper * ImageAlphaHelper::create()
{
    auto ret = new ImageAlphaHelper();
    if (ret)
    {
        ret->autorelease();
    }
    return ret;
}

ImageAlphaHelper * ImageAlphaHelper::create(std::string &dir)
{
    auto ret = new ImageAlphaHelper(dir);
    if (ret)
    {
        ret->autorelease();
    }
    return ret;
}

ImageAlphaHelper::ImageAlphaHelper()
: _dir("")
, _isClip(true)
{
}

ImageAlphaHelper::ImageAlphaHelper(std::string dir)
: _dir(dir)
, _isClip(true)
{
    findFiles(_dir);
}

ImageAlphaHelper::~ImageAlphaHelper()
{
}

void ImageAlphaHelper::createAlphaLutsWithFile(const std::string &file)
{
//    auto fn = FileUtils::getInstance()->fullPathForFilename(file);
//    
//    auto fp = fopen(fn.c_str(), "rb");
//    
//    CCASSERT(fp, "Can't open file");
//    fseek(fp, 0, SEEK_END);
//    size_t fl = ftell(fp);
//    rewind(fp);
//    
//
//    auto rl = fread(buff, sizeof(unsigned char), fl, fp);
//    
//    CCASSERT(rl == fl, "Read file error");
//    fclose(fp);
    
    auto data = FileUtils::getInstance()->getDataFromFile(file);
    auto fl = data.getSize();
    
    
    auto buff = data.getBytes();
    data.fastSet(nullptr, 0);
    
    size_t bl = sizeof(int);
    while (bl < fl)
    {
        auto lut = ImageAlphaLut::createWithBuff(buff + bl);
        CCASSERT(lut, "create lut fail");
        _imgAl.insert(lut->getName(), lut);
        bl += FILEHEADINFO - sizeof(int) + lut->getBufferSize();
    }
    
    CC_SAFE_FREE(buff);
}

void ImageAlphaHelper::callback(bool b, float load, std::string msg)
{
    log("-- %f --   msg: %s", load, msg.c_str());
}

void ImageAlphaHelper::findFiles( std::string dir)
{
    dirent * ptr;
//    log("dir : %s ", dir.c_str());
    // 读取文件夹下内容
    DIR * Dir = opendir(dir.c_str());
    
    CCASSERT(Dir, "Can't Read Directory");
    
    int i = 0;
    while (( ptr = readdir(Dir)) != nullptr )
    {
        if (ptr->d_name[0] == '.')
        {
            continue;
        }
        else if (ptr->d_type == DT_DIR )
        {
            _allFolders.push_back(ptr->d_name );
//            log("find a Folder: %s", ptr->d_name);
            findFiles( dir + '/' + ptr->d_name);
        }
        else
        {
            _allFiles.push_back( dir + '/' + ptr->d_name );
//            log("find a File: %s", ptr->d_name);
            ++i;
        }
    }
    closedir(Dir);
    if (i) _total.push_back(i);
}

void ImageAlphaHelper::readImage()
{
    _imgAl.clear();
    std::for_each(_allFiles.begin(), _allFiles.end(), [&](std::string & f)
                  {
                      if (f.find(".png") != std::string::npos)
                      {
//                          log("Add pic: %s", f.c_str());
                          auto img = f.substr(f.find_last_of("/") + 1);
                          if (_isClip)
                          {
                              _imgAl.insert(img, ImageAlphaLut::createWithImageAndClip(f.c_str()));
                          }
                          else
                          {
                              _imgAl.insert( img, ImageAlphaLut::createWithImage(f.c_str()));
                          }
                      }
                  });
}

void ImageAlphaHelper::saveToFiles(std::string dir)
{
    readImage();
    
    if (_allFolders.empty())
    {
        std::for_each(_imgAl.begin(), _imgAl.end(), [&](std::pair<std::string, ImageAlphaLut*>pair)
                      {
                          pair.second->saveToFile(dir);
                      });
    }
    else
    {
        for (int i = 0; i < _allFolders.size(); ++i)
        {
            saveHelper(dir + '/' + _allFolders[i], i);
        }
    }
}

void ImageAlphaHelper::saveHelper(std::string dir, int num)
{
    FileUtils::getInstance()->createDirectory(dir);
//    log("sub dir : %s", dir.c_str());
    int i = 0, max = _total[num];
    for (int j = num; j > 0; --j)
    {
        i += _total[j-1];
        max += _total[j-1];
    }
    
    for (; i < max; ++i)
    {
        auto img = _allFiles[i];
        auto file = img.substr(img.find_last_of("/") + 1);
        auto lut = _imgAl.at(file);
        if (lut)
        {
            lut->saveToFile(dir);
        }
//        else
//            log("No find file %s", file.c_str());
    }
}

void ImageAlphaHelper::saveInOneFile(std::string dir)
{
    readImage();
    FileUtils::getInstance()->createDirectory(dir);
    if (_allFolders.empty())
    {
        auto fn = dir + '/' + _dir.substr(_dir.find_last_of("/")  + 1 ) + '.' + FILEEXTENSION;
//        log("save file name : %s" ,fn.c_str());
        
        auto fp = fopen(fn.c_str(), "wb");
        CCASSERT(fp, "Open file error");
        int p = 0x89;
        size_t l = fwrite(&p, sizeof(int), 1, fp);
        CCASSERT(l == 1, "Set head error");
        
        std::for_each(_imgAl.begin(), _imgAl.end(), [&](std::pair<std::string, ImageAlphaLut*>pair)
                      {
                          this->writeToFlie(fp, pair.second);
                      });
        
        fclose(fp);
    }
    else
    {
        for (int i = 0; i < _allFolders.size(); ++i )
        {
            auto folder = _allFolders[i];
            auto fn = dir + '/' + folder.substr(folder.find_last_of("/") + 1 ) + '.' + FILEEXTENSION;
//            log("Save file name : %s", fn.c_str());
            
            auto fp = fopen(fn.c_str(), "wb");
            CCASSERT(fp, "Open file error");
            int p = 0x89;
            size_t l = fwrite(&p, sizeof(int), 1, fp);
            CCASSERT(l == 1, "set head error");
            
            for (int j = 0; j < _total[i]; ++j)
            {
                auto file = _allFiles[j].substr(_allFiles[j].find_last_of("/") + 1);
//                log(" -- sub file : %s",file.c_str());
                writeToFlie(fp, _imgAl.at(file));
            }
            
            fclose(fp);
        }
    }
}

void ImageAlphaHelper::writeToFlie(FILE *fp, ImageAlphaLut *lut)
{
    if (lut == nullptr)
    {
        return;
    }
    unsigned char * buff = (unsigned char *)malloc(FILEHEADINFO - sizeof(int));
    
    CCASSERT(buff, "No more memory");
    
    int * p = (int *)buff;
    *p = lut->getWidth();
    *(++p) = lut->getHeight();
    *(++p) = lut->getOffsetX();
    *(++p) = lut->getOffsetY();
    *(++p) = lut->getOffsetWidth();
    *(++p) = lut->getOffsetHeight();
    
    bool * bp = (bool *)(++p);
    *bp = lut->isOptimize();
    
    char * cp = (char *)(++bp);
    strcpy(cp, lut->getName());
    
    size_t len = fwrite(buff, sizeof(unsigned char), FILEHEADINFO - sizeof(int), fp);
    CC_SAFE_FREE(buff);
    
    CCASSERT(len == FILEHEADINFO - sizeof(int), "write file error");
    
    len = fwrite(lut->getBuffer(), sizeof(unsigned char), lut->getBufferSize(), fp);
    
    CCASSERT(len == lut->getBufferSize(), "write file error");
}
