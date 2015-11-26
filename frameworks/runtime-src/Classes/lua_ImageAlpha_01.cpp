//
//  lua_ImageAlpha_01.cpp
//  pixel
//
//  Created by WJDev02 on 15/11/24.
//
//

#include "lua_ImageAlpha_01.hpp"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "ImageAlphaLut.h"


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


int lua_cocos2dx_ImageAlpha_alphaFile(lua_State*tolua_S)
{
    int argc = 0;
//    cocos2d::Ref* cobj = nullptr;
    bool ok  = true;
//
//#if COCOS2D_DEBUG >= 1
//    tolua_Error tolua_err;
//#endif
//    
    
//#if COCOS2D_DEBUG >= 1
//    if (!tolua_isusertype(tolua_S,1,"ImageAlpha",0,&tolua_err)) goto tolua_lerror;
//#endif
//    
//    cobj = (cocos2d::Ref*)tolua_tousertype(tolua_S,1,0);
//    
//#if COCOS2D_DEBUG >= 1
//    if (!cobj)
//    {
//        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_Ref_release'", nullptr);
//        return 0;
//    }
//#endif
    
//    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_Ref_release'", nullptr);
            return 0;
        }
//        cobj->release();
//        char paths[100] = "/Users/wjdev02/project/luaGameTemplate/";
//        FILE * f;
//        f = fopen( strcat(paths, "root.txt"), "w");
//        char s[] = {'x','x','-','-'};
//        fwrite(s, sizeof(char), sizeof(s), f);
//        fclose(f);
//        log("--write over--");
        
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ImageAlpha:release",argc, 0);
    return 0;
    
//#if COCOS2D_DEBUG >= 1
//tolua_lerror:
//    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_Ref_release'.",&tolua_err);
//#endif
    
    return 0;

}

int lua_register_COD_ImageAlpha(lua_State* tolua)
{
    tolua_open(tolua);
    
//    tolua_module(tolua, "ImageAlpha", 0);
//    tolua_beginmodule(tolua, "");
    
    tolua_usertype(tolua, "ImageAlpha");
    tolua_cclass(tolua, "ImageAlpha", "ImageAlpha", "cc.Ref", nullptr);
    
    tolua_beginmodule(tolua, "ImageAlpha");
    
    tolua_function(tolua, "createWithFile", lua_cocos2dx_ImageAlpha_createWithFile);
    tolua_function(tolua, "createWithImage", lua_cocos2dx_ImageAlpha_createWithImage);
    tolua_function(tolua, "createWithImageAndClip", lua_cocos2dx_ImageAlpha_createWithImageAndClip);
    tolua_function(tolua, "isPixelAlpha", lua_cocos2dx_ImageAlpha_isPixelAlpha);
    tolua_function(tolua, "saveToFile", lua_cocos2dx_ImageAlpha_saveToFile);
    
    tolua_endmodule(tolua);
    tolua_function(tolua, "alphaFile", lua_cocos2dx_ImageAlpha_alphaFile);
    return 1;
}