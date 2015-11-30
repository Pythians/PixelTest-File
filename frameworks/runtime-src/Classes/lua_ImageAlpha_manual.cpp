//
//  lua_ImageAlpha_01.cpp
//  pixel
//
//  Created by WJDev02 on 15/11/24.
//
//

#include "lua_ImageAlpha_manual.hpp"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "ImageAlphaLut.h"
#include "ImageAlphaHelper.h"


int lua_cocos2dx_ImageAlpha_createWithFile(lua_State * tolua)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua,1,"ImageAlpha",0,&tolua_err)) goto tolua_lerror;
#endif
 
    argc = lua_gettop(tolua) - 1;
    
    if (argc == 1) {
        std::string arg;
        ok &= luaval_to_std_string(tolua, 2, &arg, "ImageAlpha:createWithFile");
        if (ok) {
            auto ret = ImageAlphaLut::createWithFile(arg);
            object_to_luaval<ImageAlphaLut>(tolua,"ImageAlpha",(ImageAlphaLut*)ret);
            return 1;
        }
    }
    
    luaL_error(tolua, "%s has wrong number of arguments: %d, was expecting %d", "ImageAlpha:createWithFile",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua,"#ferror in function 'lua_cocos2dx_ImageAlpha_createWithFile'.",&tolua_err);
#endif
    return 0;
}

int lua_cocos2dx_ImageAlpha_createWithImage(lua_State * tolua)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua,1,"ImageAlpha",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua) - 1;
    
    if (argc == 1) {
        std::string arg;
        ok &= luaval_to_std_string(tolua, 2, &arg, "ImageAlpha:createWithImage");
        if (ok) {
            auto ret = ImageAlphaLut::createWithImage(arg);
            object_to_luaval<ImageAlphaLut>(tolua,"ImageAlpha",(ImageAlphaLut*)ret);
            return 1;
        }
    }
    
    luaL_error(tolua, "%s has wrong number of arguments: %d, was expecting %d", "ImageAlpha:createWithImage",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua,"#ferror in function 'lua_cocos2dx_ImageAlpha_createWithImage'.",&tolua_err);
#endif
    return 0;
}

int lua_cocos2dx_ImageAlpha_createWithImageAndClip(lua_State * tolua)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua,1,"ImageAlpha",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua) - 1;
    
    if (argc == 1) {
        std::string arg;
        ok &= luaval_to_std_string(tolua, 2, &arg, "ImageAlpha:createWithFileAndClip");
        if (ok) {
            auto ret = ImageAlphaLut::createWithImageAndClip(arg);
            object_to_luaval<ImageAlphaLut>(tolua,"ImageAlpha",(ImageAlphaLut*)ret);
            return 1;
        }
    }
    
    luaL_error(tolua, "%s has wrong number of arguments: %d, was expecting %d", "ImageAlpha:createWithFileAndClip",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua,"#ferror in function 'lua_cocos2dx_ImageAlpha_createWithFileAndClip'.",&tolua_err);
#endif
    return 0;
}

int lua_cocos2dx_ImageAlpha_isPixelAlpha(lua_State * tolua)
{
    int argc = 0;
    bool ok  = true;
    ImageAlphaLut * cobj = nullptr;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua,1,"ImageAlpha",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (ImageAlphaLut*)tolua_tousertype(tolua, 1, 0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua,"invalid 'cobj' in function 'lua_cocos2dx_ImageAlpha_isPixelAlpha'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua) - 1;
    
    if (argc == 2) {
        int x;
        ok &= luaval_to_int32(tolua, 2, &x);
        if (ok) {
            int y;
            ok &= luaval_to_int32(tolua, 3, &y);
            if (ok) {
                bool b = cobj->isPixelAlpha(x, y);
                lua_pushboolean(tolua, b);
                return 1;
            }
        }
    }
    
    luaL_error(tolua, "%s has wrong number of arguments: %d, was expecting %d \n", "ImageAlpha:isPixelAlpha",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua,"#ferror in function 'lua_cocos2dx_ImageAlpha_isPixelAlpha'.",&tolua_err);
#endif
    return 0;
}

int lua_cocos2dx_ImageAlpha_saveToFile(lua_State * tolua)
{
    int argc = 0;
    bool ok  = true;
    ImageAlphaLut * cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua,1,"ImageAlpha",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (ImageAlphaLut*)tolua_tousertype(tolua, 1, 0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua,"invalid 'cobj' in function 'lua_cocos2dx_ImageAlpha_saveToFile'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua) - 1;
    
    if (0 == argc)
    {
        bool b = cobj->saveToFile();
        lua_pushboolean(tolua, b);
        return 1;
    }
    if (argc == 1) {
        std::string arg;
        ok &= luaval_to_std_string(tolua, 2, &arg, "ImageAlpha:saveToFile");
        if (ok) {
            bool b = cobj->saveToFile(arg);
            lua_pushboolean(tolua, b);
            return 1;
        }
    }
    
    luaL_error(tolua, "%s has wrong number of arguments: %d, was expecting %d", "ImageAlpha:saveToFile",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua,"#ferror in function 'lua_cocos2dx_ImageAlpha_saveToFile'.",&tolua_err);
#endif
    return 0;
}

int lua_cocos2dx_ImageAlpha_isOptimize(lua_State* tolua_S)
{
    int argc = 0;
    ImageAlphaLut * cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ImageAlpha",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (ImageAlphaLut*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ImageAlpha_isOptimize'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        auto ret = cobj->isOptimize();
        tolua_pushboolean(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImageAlpha:isOptimize",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ImageAlpha_isOptimize'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_ImageAlpha_getWidth(lua_State* tolua_S)
{
    int argc = 0;
    ImageAlphaLut * cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ImageAlpha",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (ImageAlphaLut*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ImageAlpha_getWidth'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        auto ret = cobj->getWidth();
        tolua_pushnumber(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImageAlpha:getWidth",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ImageAlpha_getWidth'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_ImageAlpha_getHeight(lua_State* tolua_S)
{
    int argc = 0;
    ImageAlphaLut * cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ImageAlpha",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (ImageAlphaLut*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ImageAlpha_getHeight'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        auto ret = cobj->getHeight();
        tolua_pushnumber(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImageAlpha:getHeight",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ImageAlpha_getHeight'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_ImageAlpha_getOffsetX(lua_State* tolua_S)
{
    int argc = 0;
    ImageAlphaLut * cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ImageAlpha",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (ImageAlphaLut*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ImageAlpha_getOffsetX'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        auto ret = cobj->getOffsetX();
        tolua_pushnumber(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImageAlpha:getOffsetX",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ImageAlpha_getOffsetX'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_ImageAlpha_getOffsetY(lua_State* tolua_S)
{
    int argc = 0;
    ImageAlphaLut * cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ImageAlpha",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (ImageAlphaLut*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ImageAlpha_getOffsetY'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        auto ret = cobj->getOffsetY();
        tolua_pushnumber(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImageAlpha:getOffsetY",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ImageAlpha_getOffsetY'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_ImageAlpha_getOffsetWidth(lua_State* tolua_S)
{
    int argc = 0;
    ImageAlphaLut * cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ImageAlpha",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (ImageAlphaLut*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ImageAlpha_getOffsetWidth'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        auto ret = cobj->getOffsetWidth();
        tolua_pushnumber(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImageAlpha:getOffsetWidth",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ImageAlpha_getOffsetWidth'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_ImageAlpha_getOffsetHeight(lua_State* tolua_S)
{
    int argc = 0;
    ImageAlphaLut * cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ImageAlpha",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (ImageAlphaLut*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ImageAlpha_getOffsetHeight'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        auto ret = cobj->getOffsetHeight();
        tolua_pushnumber(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImageAlpha:getOffsetHeight",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ImageAlpha_getOffsetHeight'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_ImageAlpha_getBufferSize(lua_State* tolua_S)
{
    int argc = 0;
    ImageAlphaLut * cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ImageAlpha",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (ImageAlphaLut*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ImageAlpha_getBufferSize'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        auto ret = cobj->getBufferSize();
        tolua_pushnumber(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImageAlpha:getBufferSize",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ImageAlpha_getBufferSize'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_ImageAlpha_getName(lua_State* tolua_S)
{
    int argc = 0;
    ImageAlphaLut * cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ImageAlpha",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (ImageAlphaLut*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ImageAlpha_getName'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        auto ret = cobj->getName();
        tolua_pushstring(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImageAlpha:getName",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ImageAlpha_getName'.",&tolua_err);
#endif
    
    return 0;
}

//////////////////////////////////////////////////////////////////////////////

int lua_cocos2dx_ImageAlphaHelper_constructor(lua_State* tolua_S)
{
    int argc = 0;
    ImageAlphaHelper * cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
    
    argc = lua_gettop(tolua_S)-1;
    do {
        if (argc == 0)
        {
            cobj = new ImageAlphaHelper();
        }
        else if (argc == 1)
        {
            std::string arg0;
            
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ImageAlphaHelper:saveToFiles");
            if(!ok)
            {
                tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ImageAlphaHelper_saveToFiles'", nullptr);
                return 0;
            }
            cobj = new ImageAlphaHelper(arg0);
        }
        else
        {
            break;
        }
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ImageAlphaHelper");
        return 1;
    } while (0);
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImageAlphaHelper:ImageAlphaHelper",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ImageAlphaHelper_constructor'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_ImageAlphaHelper_getAllFiles(lua_State* tolua_S)
{
    int argc = 0;
    ImageAlphaHelper * cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ImageAlphaHelper",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (ImageAlphaHelper*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ImageAlphaHelper_getAllFiles'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        std::vector<std::string> ret = cobj->getAllFiles();
        ccvector_std_string_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImageAlphaHelper:getAllFiles",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ImageAlphaHelper_getAllFiles'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_ImageAlphaHelper_getAllFolders(lua_State* tolua_S)
{
    int argc = 0;
    ImageAlphaHelper * cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ImageAlphaHelper",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (ImageAlphaHelper*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ImageAlphaHelper_getAllFolders'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        std::vector<std::string> ret = cobj->getAllFolders();
        ccvector_std_string_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImageAlphaHelper:getAllFolders",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ImageAlphaHelper_getAllFolders'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_ImageAlphaHelper_getDirectory(lua_State* tolua_S)
{
    int argc = 0;
    ImageAlphaHelper * cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ImageAlphaHelper",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (ImageAlphaHelper*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ImageAlphaHelper_getDirectory'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        std::string ret = cobj->getDirectory();
        tolua_pushstring(tolua_S, ret.c_str());
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImageAlphaHelper:getDirectory",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ImageAlphaHelper_getDirectory'.",&tolua_err);
#endif
    
    return 0;
}


int lua_cocos2dx_ImageAlphaHelper_getClip(lua_State* tolua_S)
{
    int argc = 0;
    ImageAlphaHelper * cobj = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ImageAlphaHelper",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (ImageAlphaHelper*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ImageAlphaHelper_getClip'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        auto ret = cobj->getClip();
        tolua_pushboolean(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImageAlphaHelper:getClip",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ImageAlphaHelper_getClip'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_ImageAlphaHelper_setClip(lua_State* tolua_S)
{
    int argc = 0;
    ImageAlphaHelper* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ImageAlphaHelper",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (ImageAlphaHelper*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ImageAlphaHelper_setClip'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        bool arg0;
        
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ImageAlphaHelper:setClip");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ImageAlphaHelper_setClip'", nullptr);
            return 0;
        }
        cobj->setClip(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImageAlphaHelper:setClip",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ImageAlphaHelper_setClip'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_ImageAlphaHelper_setDirectory(lua_State* tolua_S)
{
    int argc = 0;
    ImageAlphaHelper* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ImageAlphaHelper",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (ImageAlphaHelper*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ImageAlphaHelper_setDirectory'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        std::string arg0;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ImageAlphaHelper:setDirectory");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ImageAlphaHelper_setDirectory'", nullptr);
            return 0;
        }
        cobj->setDirectory(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImageAlphaHelper:setDirectory",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ImageAlphaHelper_setDirectory'.",&tolua_err);
#endif
    
    return 0;
}

int lua_cocos2dx_ImageAlphaHelper_saveToFiles(lua_State* tolua_S)
{
    int argc = 0;
    ImageAlphaHelper* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ImageAlphaHelper",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (ImageAlphaHelper*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_ImageAlphaHelper_saveToFiles'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        std::string arg0;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ImageAlphaHelper:saveToFiles");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_ImageAlphaHelper_saveToFiles'", nullptr);
            return 0;
        }
        cobj->saveToFiles(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImageAlphaHelper:saveToFiles",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_ImageAlphaHelper_saveToFiles'.",&tolua_err);
#endif
    
    return 0;
}

int lua_register_COD_ImageAlphaHelper(lua_State* luaS)
{
    tolua_usertype(luaS, "ImageAlphaHelper");
    tolua_cclass(luaS, "ImageAlphaHelper", "ImageAlphaHelper", "cc.Ref", nullptr);
    
    tolua_beginmodule(luaS, "ImageAlphaHelper");
    
    tolua_function(luaS, "new", lua_cocos2dx_ImageAlphaHelper_constructor);
    tolua_function(luaS, "getAllfiles", lua_cocos2dx_ImageAlphaHelper_getAllFiles);
    tolua_function(luaS, "getAllFolders", lua_cocos2dx_ImageAlphaHelper_getAllFolders);
    tolua_function(luaS, "getDirectory", lua_cocos2dx_ImageAlphaHelper_getDirectory);
    tolua_function(luaS, "getClip", lua_cocos2dx_ImageAlphaHelper_getClip);
    tolua_function(luaS, "setClip", lua_cocos2dx_ImageAlphaHelper_setClip);
    tolua_function(luaS, "setDirectory", lua_cocos2dx_ImageAlphaHelper_setDirectory);
    tolua_function(luaS, "saveToFiles", lua_cocos2dx_ImageAlphaHelper_saveToFiles);
    
    
    tolua_endmodule(luaS);
    return 1;
}

int lua_register_COD_ImageAlphaLut(lua_State* tolua)
{
    
    tolua_usertype(tolua, "ImageAlpha");
    tolua_cclass(tolua, "ImageAlpha", "ImageAlpha", "cc.Ref", nullptr);
    
    tolua_beginmodule(tolua, "ImageAlpha");
    
    tolua_function(tolua, "createWithFile", lua_cocos2dx_ImageAlpha_createWithFile);
    tolua_function(tolua, "createWithImage", lua_cocos2dx_ImageAlpha_createWithImage);
    tolua_function(tolua, "createWithImageAndClip", lua_cocos2dx_ImageAlpha_createWithImageAndClip);
    tolua_function(tolua, "isPixelAlpha", lua_cocos2dx_ImageAlpha_isPixelAlpha);
    tolua_function(tolua, "saveToFile", lua_cocos2dx_ImageAlpha_saveToFile);
    tolua_function(tolua, "isClip", lua_cocos2dx_ImageAlpha_isOptimize);
    tolua_function(tolua, "getHeight", lua_cocos2dx_ImageAlpha_getHeight);
    tolua_function(tolua, "getWidth", lua_cocos2dx_ImageAlpha_getWidth);
    tolua_function(tolua, "getOffsetX", lua_cocos2dx_ImageAlpha_getOffsetX);
    tolua_function(tolua, "getOffsetY", lua_cocos2dx_ImageAlpha_getOffsetY);
    tolua_function(tolua, "getOffsetWidth", lua_cocos2dx_ImageAlpha_getOffsetWidth);
    tolua_function(tolua, "getOffsetHeight", lua_cocos2dx_ImageAlpha_getOffsetHeight);
    tolua_function(tolua, "getBufferSize", lua_cocos2dx_ImageAlpha_getBufferSize);
    tolua_function(tolua, "getName", lua_cocos2dx_ImageAlpha_getName);

    
    tolua_endmodule(tolua);
    return 1;
}

int lua_register_COD_ImageAlpha(lua_State* tolua)
{
    tolua_open(tolua);

    lua_register_COD_ImageAlphaLut(tolua);
    lua_register_COD_ImageAlphaHelper(tolua);
    
    return 1;
}