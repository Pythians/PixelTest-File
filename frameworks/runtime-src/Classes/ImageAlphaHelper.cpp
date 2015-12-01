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

void ImageAlphaHelper::callback(bool b, float load, std::string msg)
{
    log("-- %f --   msg: %s", load, msg.c_str());
}

void ImageAlphaHelper::findFiles( std::string dir)
{
    dirent * ptr;
    log("dir : %s ", dir.c_str());
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
            log("find a Folder: %s", ptr->d_name);
            findFiles( dir + '/' + ptr->d_name);
        }
        else
        {
            _allFiles.push_back( dir + '/' + ptr->d_name );
            log("find a File: %s", ptr->d_name);
            ++i;
        }
    }
    _total.push_back(i);
}

void ImageAlphaHelper::readImage()
{
    _imgAl.clear();
    std::for_each(_allFiles.begin(), _allFiles.end(), [&](std::string & f)
                  {
                      if (f.find(".png") != std::string::npos)
                      {
                          log("Add pic: %s", f.c_str());
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
    int i = 0;
    float s = _imgAl.size();
    
    if (_allFolders.empty())
    {
        std::for_each(_imgAl.begin(), _imgAl.end(), [&](std::pair<std::string, ImageAlphaLut*>pair)
                      {
                          if (pair.second->saveToFile(dir))
                          {
                              callback(true, (++i)/ s, "save "+ pair.first +"'s alpha bit file success");
                          }
                          else
                          {
                              callback( false, (++i)/s, "save "+ pair.first + "'s alpha bit file error");
                          }
                      });
    }
    else
    {
        for (int i = 0; i < _allFolders.size(); ++i)
        {
            saveHelper(dir + '/' + _allFolders[i], i);
        }
    }
    _imgAl.clear();
}

void ImageAlphaHelper::saveHelper(std::string dir, int num)
{
    FileUtils::getInstance()->createDirectory(dir);
    log("sub dir : %s", dir.c_str());
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
        else
            log("No find file %s", file.c_str());
    }
}
