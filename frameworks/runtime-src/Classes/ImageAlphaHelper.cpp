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
: _dir("/Users/wjdev02/project/luaGameTemplate/res")
, _isClip(true)
{
    findFiles();
}

ImageAlphaHelper::ImageAlphaHelper(std::string dir)
: _dir(dir)
, _isClip(true)
{
    findFiles();
}

ImageAlphaHelper::~ImageAlphaHelper()
{
}

void ImageAlphaHelper::callback(bool b, float load, std::string msg)
{
    log("-- %f --   msg: %s", load, msg.c_str());
}

void ImageAlphaHelper::findFiles( )
{

    std::vector<std::string> files;

    if (FileUtils::getInstance()->isDirectoryExist(_dir))
    {
        auto dir = _dir + "/";
        dirent * ptr;
        DIR * Dir = opendir(dir.c_str());
        
        while (( ptr = readdir(Dir)) != nullptr )
        {
            if (ptr->d_name[0] == '.')
            {
                continue;
            }
            else if (ptr->d_type == DT_DIR )
            {
                _allFolders.push_back(dir + ptr->d_name);
            }
            else
            {
                _allFiles.push_back( dir + ptr->d_name );
            }
        }
    }
}

void ImageAlphaHelper::readImage()
{
    std::for_each(_allFiles.begin(), _allFiles.end(), [&](std::string & f)
                  {
                      if (f.find(".png") != std::string::npos)
                      {
                          auto img = f.substr(f.find_last_of("/") + 1);
                          if (_isClip)
                          {
                              _imgAl.insert(img, ImageAlphaLut::createWithImageAndClip(img));
                          }
                          else
                          {
                              _imgAl.insert( img, ImageAlphaLut::createWithImage(img));
                          }
                      }
                  });
}

void ImageAlphaHelper::saveToFiles(std::string dir)
{
    readImage();
    int i = 0;
    float s = _imgAl.size();
    
    if (FileUtils::getInstance()->isDirectoryExist(dir))
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
    
}
