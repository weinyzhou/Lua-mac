#include <lua.h>//Lua 5.1.5
#include <lauxlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int mac_strToint(lua_State *L)
{
	
	int64_t macint=0;
	unsigned int mac[6]={0};
	char macstr[20]={0};
	if (lua_gettop(L) != 1)
		return 0;
	int rv=sscanf(lua_tostring(L,1),"%2x:%2x:%2x:%2x:%2x:%2x",&mac[0],&mac[1],&mac[2],&mac[3],
		&mac[4],&mac[5]);
	
	lua_newtable(L);
	lua_pushinteger(L, mac[0]);
	lua_pushinteger(L,1);
	lua_settable(L, -3);
	lua_pushinteger(L, mac[1]);
	lua_pushinteger(L,2);
	lua_settable(L, -3);
	lua_pushinteger(L, mac[2]);
	lua_pushinteger(L,3);
	lua_settable(L, -3);
	lua_pushinteger(L, mac[3]);
	lua_pushinteger(L,4);
	lua_settable(L, -3);
	lua_pushinteger(L, mac[4]);
	lua_pushinteger(L,5);
	lua_settable(L, -3);
	lua_pushinteger(L, mac[5]);
	lua_pushinteger(L,6);
	lua_settable(L, -3);
	macint=(((int64_t)(mac[0]))<<48) +(((int64_t)(mac[1]))<<32) +(((int64_t)(mac[2]))<<24) +(((int64_t)(mac[3]))<<16) +(((int64_t)(mac[4]))<<8)+ ((int64_t)mac[5]);
	snprintf(macstr,20,"%lld",macint);
	lua_pushstring(L,macstr);

	return 2;
}

static int mac_intTostr(lua_State* L)
{
	int64_t macint=0;
	unsigned int mac[6];
	char macstr[20]={0};
	if(lua_gettop(L)!=1)
		return 0;
	if(lua_isstring(L,1))
		macint=atoll(lua_tostring(L,1));
	else
		macint=lua_tointeger(L,1);
	mac[0]=(macint&0xff0000000000)>>48;
	mac[1]=(macint&0xff00000000)>>32;
	mac[2]=(macint&0xff000000)>>24;
	mac[3]=(macint&0xff0000)>>16;
	mac[4]=(macint&0xff00)>>8;
	mac[5]=macint&0xff;
	snprintf(macstr,20,"%02x:%02x:%02x:%02x:%02x:%02x",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);

	lua_pushstring(L,macstr);
	return 1;
}

static int mac_ipStrToint(lua_State *L)
{
	const char* szIP=NULL;
	int64_t ipint=0;
	unsigned int ip[4]={0};
	char ipstr[20]={0};
	if (lua_gettop(L) != 1)
		return 0;
	int rv=sscanf(lua_tostring(L,1),"%d.%d.%d.%d",&ip[0],&ip[1],&ip[2],&ip[3]);
	
	lua_newtable(L);
	lua_pushinteger(L, ip[0]);
	lua_pushinteger(L,1);
	lua_settable(L, -3);
	lua_pushinteger(L, ip[1]);
	lua_pushinteger(L,2);
	lua_settable(L, -3);
	lua_pushinteger(L, ip[2]);
	lua_pushinteger(L,3);
	lua_settable(L, -3);
	lua_pushinteger(L, ip[3]);
	lua_pushinteger(L,4);
	lua_settable(L, -3);
	

	ipint=(((int64_t)(ip[0]))<<24) +(((int64_t)(ip[1]))<<16) +(((int64_t)(ip[2]))<<8) +(((int64_t)(ip[3]))) ;
	snprintf(ipstr,20,"%lld",ipint);
	lua_pushstring(L,ipstr);

	return 2;
}

static int mac_ipIntTostr(lua_State* L)
{
	int64_t ipint=0;
	unsigned int ip[4];
	char ipstr[20]={0};
	if(lua_gettop(L)!=1)
		return 0;
	ipint=atoll(lua_tostring(L,1));
	ip[0]=(ipint&0xff000000)>>24;
	ip[1]=(ipint&0xff0000)>>16;
	ip[2]=(ipint&0xff00)>>8;
	ip[3]=ipint&0xff;
	
	snprintf(ipstr,20,"%02x:%02x:%02x:%02x",ip[0],ip[1],ip[2],ip[3]);

	lua_pushstring(L,ipstr);
	return 1;
}
//按位异或
static int bit_xor(lua_State* L)
{
	if(lua_gettop(L)!=2)
		return 0;
	int val=lua_tointeger(L,1);
	int val2=lua_tointeger(L,2);
	lua_pushinteger(L,val^val2);
	return 1;
}
//按位与
static int bit_and(lua_State*L)
{
	if(lua_gettop(L)!=2)
		return 0;
	int val=lua_tointeger(L,1);
	int val2=lua_tointeger(L,2);
	lua_pushinteger(L,val&val2);
	return 1;
}
//按位或
static int bit_or(lua_State*L)
{
	if(lua_gettop(L)!=2)
		return 0;
	int val=lua_tointeger(L,1);
	int val2=lua_tointeger(L,2);
	lua_pushinteger(L,val|val2);
	return 1;
}
//按位取反
static int bit_not(lua_State*L)
{
	if(lua_gettop(L)!=1)
		return 0;
	int val=lua_tointeger(L,1);
	lua_pushinteger(L,~val);
	return 1;
}
//右移
static int bit_rshift(lua_State*L)
{
	if(lua_gettop(L)!=2)
		return 0;
	int val=lua_tointeger(L,1);
	int bit=lua_tointeger(L,2);
	lua_pushinteger(L,val>>bit);
	return 1;
}
//左移
static int bit_lshift(lua_State*L)
{
	if(lua_gettop(L)!=2)
		return 0;
	int val=lua_tointeger(L,1);
	int bit=lua_tointeger(L,2);
	lua_pushinteger(L,val<<bit);
	return 1;
}
static const struct luaL_Reg mac_lib[] = {
	{ "strToint", mac_strToint },
	{ "intTostr", mac_intTostr },
	{ "ipStrToint", mac_ipStrToint },
	{ "ipIntTostr", mac_ipIntTostr },
	{ "xor",bit_xor},
	{ "band",bit_and},
	{ "or",bit_or},
	{ "not",bit_not},
	{ "rshift",bit_rshift},
	{ "lshift",bit_lshift},
	{ NULL, NULL }
};

static int settablereadonly(lua_State *L)
{
	return luaL_error(L, "Must not update a read-only table");
}

#define LUA_MACLIBNAME "mac"

LUALIB_API int luaopen_mac(lua_State *L)
{
	luaL_register(L, LUA_MACLIBNAME, mac_lib);

	return 1;
}
