#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>
#include "Object.h"

using namespace std;

extern "C" int newObject(lua_State* L)
{
    int n = lua_gettop(L);
    luaL_argcheck(L, n == 2, 1, "invalid size.");
    const char* str = luaL_checkstring(L,1);
    int arg2 = luaL_checkinteger(L,2);
    Object** obj = (Object**) lua_newuserdata(L,sizeof(Object*));

    string name(str);
    *obj = new Object(name,arg2);

    luaL_getmetatable(L, "object");

    lua_setmetatable(L, -2);

    return 1;
}

extern "C" int getValue(lua_State* L)
{
    Object** obj = (Object**)luaL_checkudata(L,1,"object");
    luaL_argcheck(L,*obj != nullptr,1,"expected.");
    lua_pushinteger(L,(*obj)->getValue());
    return 1;
}

extern "C" int getName(lua_State* L)
{
    int n = lua_gettop(L);
    luaL_argcheck(L, n == 1, 1, "invalid size.");
    Object** obj = (Object**)luaL_checkudata(L,1,"object");
    luaL_argcheck(L,*obj != nullptr,1,"expected.");
    lua_pushstring(L,(*obj)->getName().c_str());
    return 1;
}

extern "C" int setValue(lua_State* L)
{
    int n = lua_gettop(L);
    luaL_argcheck(L, n == 2, 1, "invalid size.");
    int arg = luaL_checkinteger(L,2);
    Object** obj = (Object**)luaL_checkudata(L,1,"object");
    luaL_argcheck(L,*obj != NULL,1,"expected.");
    (*obj)->setValue(arg);
    return 1;
}

extern "C" int objectGc(lua_State* L)
{
    Object** obj = (Object**)luaL_checkudata(L,1,"object");
    if( obj )
    {
        delete *obj;
    }

    return 0;
}

extern "C"  int luaopen_libObject(lua_State *L)
{
    luaL_Reg  funcs[] =
    {
        {"new",newObject},
        {"getValue",getValue},
        {"getName",getName},
        {"setValue",setValue},
        {"__gc", objectGc},
        { NULL, NULL }
    };


    //create table and push.
    luaL_newmetatable(L,"object");
    //coyp and push top element.
    lua_pushvalue(L,-1);
    //pop and new index.
    lua_setfield(L, -2, "__index");
    //set element to userdata.
    luaL_setfuncs(L,funcs,0);
    //create new table.
    //luaL_newlib(L, apis);

    return 1;
}
