/*
** Lua binding: ObjetosExportados
*/

#include "tolua.h"
#include "SCR_Objetos.h"

#ifndef __cplusplus
#include <stdlib.h>
#endif
#ifdef __cplusplus
 extern "C" int tolua_bnd_takeownership (lua_State* L); // from tolua_map.c
#else
 int tolua_bnd_takeownership (lua_State* L); /* from tolua_map.c */
#endif
#include <string.h>

/* Exported function */
TOLUA_API int tolua_ObjetosExportados_open (lua_State* tolua_S);
LUALIB_API int luaopen_ObjetosExportados (lua_State* tolua_S);


/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CICRCamera (lua_State* tolua_S)
{
 CICRCamera* self = (CICRCamera*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}

static int tolua_collect_CICRActor (lua_State* tolua_S)
{
 CICRActor* self = (CICRActor*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}

static int tolua_collect_CICRPosition (lua_State* tolua_S)
{
 CICRPosition* self = (CICRPosition*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"CICRCamera");
 tolua_usertype(tolua_S,"CICRActor");
 tolua_usertype(tolua_S,"CICRPosition");
}

/* get function: mPosX of class  CICRPosition */
static int tolua_get_CICRPosition_CICRPosition_mPosX(lua_State* tolua_S)
{
  CICRPosition* self = (CICRPosition*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mPosX'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->mPosX);
 return 1;
}

/* set function: mPosX of class  CICRPosition */
static int tolua_set_CICRPosition_CICRPosition_mPosX(lua_State* tolua_S)
{
  CICRPosition* self = (CICRPosition*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mPosX'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mPosX = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: mPosY of class  CICRPosition */
static int tolua_get_CICRPosition_CICRPosition_mPosY(lua_State* tolua_S)
{
  CICRPosition* self = (CICRPosition*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mPosY'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->mPosY);
 return 1;
}

/* set function: mPosY of class  CICRPosition */
static int tolua_set_CICRPosition_CICRPosition_mPosY(lua_State* tolua_S)
{
  CICRPosition* self = (CICRPosition*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mPosY'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mPosY = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: mPosZ of class  CICRPosition */
static int tolua_get_CICRPosition_CICRPosition_mPosZ(lua_State* tolua_S)
{
  CICRPosition* self = (CICRPosition*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mPosZ'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->mPosZ);
 return 1;
}

/* set function: mPosZ of class  CICRPosition */
static int tolua_set_CICRPosition_CICRPosition_mPosZ(lua_State* tolua_S)
{
  CICRPosition* self = (CICRPosition*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mPosZ'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mPosZ = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* method: new of class  CICRPosition */
static int tolua_ObjetosExportados_CICRPosition_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CICRPosition",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CICRPosition* tolua_ret = (CICRPosition*)  new CICRPosition();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"CICRPosition");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: new of class  CICRPosition */
static int tolua_ObjetosExportados_CICRPosition_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CICRPosition",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,3,0,&tolua_err) || 
 !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  float PosX = ((float)  tolua_tonumber(tolua_S,2,0));
  float PosY = ((float)  tolua_tonumber(tolua_S,3,0));
  float PosZ = ((float)  tolua_tonumber(tolua_S,4,0));
 {
  CICRPosition* tolua_ret = (CICRPosition*)  new CICRPosition(PosX,PosY,PosZ);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"CICRPosition");
 }
 }
 return 1;
tolua_lerror:
 return tolua_ObjetosExportados_CICRPosition_new00(tolua_S);
}

/* method: delete of class  CICRPosition */
static int tolua_ObjetosExportados_CICRPosition_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CICRPosition",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CICRPosition* self = (CICRPosition*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
 tolua_release(tolua_S,self);
 delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}

/* get function: ICR_ActorPos of class  CICRActor */
static int tolua_get_CICRActor_CICRActor_ICR_ActorPos(lua_State* tolua_S)
{
  CICRActor* self = (CICRActor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ICR_ActorPos'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->ICR_ActorPos,"CICRPosition");
 return 1;
}

/* set function: ICR_ActorPos of class  CICRActor */
static int tolua_set_CICRActor_CICRActor_ICR_ActorPos(lua_State* tolua_S)
{
  CICRActor* self = (CICRActor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ICR_ActorPos'",NULL);
 if (!tolua_isusertype(tolua_S,2,"CICRPosition",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ICR_ActorPos = *((CICRPosition*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* get function: ICR_ActorId of class  CICRActor */
static int tolua_get_CICRActor_CICRActor_ICR_ActorId(lua_State* tolua_S)
{
  CICRActor* self = (CICRActor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ICR_ActorId'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->ICR_ActorId);
 return 1;
}

/* set function: ICR_ActorId of class  CICRActor */
static int tolua_set_CICRActor_CICRActor_ICR_ActorId(lua_State* tolua_S)
{
  CICRActor* self = (CICRActor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ICR_ActorId'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ICR_ActorId = ((int)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: ICR_ActorName of class  CICRActor */
static int tolua_get_CICRActor_CICRActor_ICR_ActorName(lua_State* tolua_S)
{
  CICRActor* self = (CICRActor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ICR_ActorName'",NULL);
#endif
 tolua_pushstring(tolua_S,(const char*)self->ICR_ActorName);
 return 1;
}

/* set function: ICR_ActorName of class  CICRActor */
static int tolua_set_CICRActor_CICRActor_ICR_ActorName(lua_State* tolua_S)
{
  CICRActor* self = (CICRActor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'ICR_ActorName'",NULL);
 if (!tolua_isstring(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->ICR_ActorName = ((char*)  tolua_tostring(tolua_S,2,0));
 return 0;
}

/* method: new of class  CICRActor */
static int tolua_ObjetosExportados_CICRActor_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CICRActor",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CICRActor* tolua_ret = (CICRActor*)  new CICRActor();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"CICRActor");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: new of class  CICRActor */
static int tolua_ObjetosExportados_CICRActor_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CICRActor",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isusertype(tolua_S,3,"CICRPosition",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,4,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  char* pICR_Name = ((char*)  tolua_tostring(tolua_S,2,0));
  CICRPosition* pICR_Position = ((CICRPosition*)  tolua_tousertype(tolua_S,3,0));
  int pICR_ActorType = ((int)  tolua_tonumber(tolua_S,4,0));
 {
  CICRActor* tolua_ret = (CICRActor*)  new CICRActor(pICR_Name,pICR_Position,pICR_ActorType);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"CICRActor");
 }
 }
 return 1;
tolua_lerror:
 return tolua_ObjetosExportados_CICRActor_new00(tolua_S);
}

/* method: delete of class  CICRActor */
static int tolua_ObjetosExportados_CICRActor_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CICRActor",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CICRActor* self = (CICRActor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
 tolua_release(tolua_S,self);
 delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}

/* method: GetName of class  CICRActor */
static int tolua_ObjetosExportados_CICRActor_GetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CICRActor",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CICRActor* self = (CICRActor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetName'",NULL);
#endif
 {
  char* tolua_ret = (char*)  self->GetName();
 tolua_pushstring(tolua_S,(const char*)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetName'.",&tolua_err);
 return 0;
#endif
}

/* method: SetName of class  CICRActor */
static int tolua_ObjetosExportados_CICRActor_SetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CICRActor",0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CICRActor* self = (CICRActor*)  tolua_tousertype(tolua_S,1,0);
  char* pICR_Name = ((char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetName'",NULL);
#endif
 {
  self->SetName(pICR_Name);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetName'.",&tolua_err);
 return 0;
#endif
}

/* method: SetPos of class  CICRActor */
static int tolua_ObjetosExportados_CICRActor_SetPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CICRActor",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"CICRPosition",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CICRActor* self = (CICRActor*)  tolua_tousertype(tolua_S,1,0);
  CICRPosition* pICR_Position = ((CICRPosition*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPos'",NULL);
#endif
 {
  self->SetPos(pICR_Position);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPos'.",&tolua_err);
 return 0;
#endif
}

/* method: GetPos of class  CICRActor */
static int tolua_ObjetosExportados_CICRActor_GetPos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CICRActor",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CICRActor* self = (CICRActor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPos'",NULL);
#endif
 {
  CICRPosition tolua_ret =  self->GetPos();
 {
#ifdef __cplusplus
 void* tolua_obj = new CICRPosition(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_CICRPosition),"CICRPosition");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CICRPosition));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"CICRPosition");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPos'.",&tolua_err);
 return 0;
#endif
}

/* method: Walk of class  CICRActor */
static int tolua_ObjetosExportados_CICRActor_Walk00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CICRActor",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"CICRPosition",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CICRActor* self = (CICRActor*)  tolua_tousertype(tolua_S,1,0);
  CICRPosition* pICR_Position = ((CICRPosition*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Walk'",NULL);
#endif
 {
  self->Walk(pICR_Position);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Walk'.",&tolua_err);
 return 0;
#endif
}

/* method: Stop of class  CICRActor */
static int tolua_ObjetosExportados_CICRActor_Stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CICRActor",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CICRActor* self = (CICRActor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Stop'",NULL);
#endif
 {
  self->Stop();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Stop'.",&tolua_err);
 return 0;
#endif
}

/* get function: mPos of class  CICRCamera */
static int tolua_get_CICRCamera_CICRCamera_mPos(lua_State* tolua_S)
{
  CICRCamera* self = (CICRCamera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mPos'",NULL);
#endif
 tolua_pushusertype(tolua_S,(void*)&self->mPos,"CICRPosition");
 return 1;
}

/* set function: mPos of class  CICRCamera */
static int tolua_set_CICRCamera_CICRCamera_mPos(lua_State* tolua_S)
{
  CICRCamera* self = (CICRCamera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mPos'",NULL);
 if (!tolua_isusertype(tolua_S,2,"CICRPosition",0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mPos = *((CICRPosition*)  tolua_tousertype(tolua_S,2,0));
 return 0;
}

/* method: new of class  CICRCamera */
static int tolua_ObjetosExportados_CICRCamera_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CICRCamera",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  CICRCamera* tolua_ret = (CICRCamera*)  new CICRCamera();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"CICRCamera");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: new of class  CICRCamera */
static int tolua_ObjetosExportados_CICRCamera_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"CICRCamera",0,&tolua_err) || 
 !tolua_isusertype(tolua_S,2,"CICRPosition",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  CICRPosition* pos = ((CICRPosition*)  tolua_tousertype(tolua_S,2,0));
 {
  CICRCamera* tolua_ret = (CICRCamera*)  new CICRCamera(pos);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"CICRCamera");
 }
 }
 return 1;
tolua_lerror:
 return tolua_ObjetosExportados_CICRCamera_new00(tolua_S);
}

/* method: delete of class  CICRCamera */
static int tolua_ObjetosExportados_CICRCamera_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CICRCamera",0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CICRCamera* self = (CICRCamera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
 tolua_release(tolua_S,self);
 delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}

/* method: Move of class  CICRCamera */
static int tolua_ObjetosExportados_CICRCamera_Move00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"CICRCamera",0,&tolua_err) || 
 !tolua_isnumber(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  CICRCamera* self = (CICRCamera*)  tolua_tousertype(tolua_S,1,0);
  int D = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Move'",NULL);
#endif
 {
  self->Move(D);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Move'.",&tolua_err);
 return 0;
#endif
}

/* function: ICR_SystemOk */
static int tolua_ObjetosExportados_ICR_SystemOk00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  bool tolua_ret = (bool)  ICR_SystemOk();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ICR_SystemOk'.",&tolua_err);
 return 0;
#endif
}

/* function: ICR_SystemRunning */
static int tolua_ObjetosExportados_ICR_SystemRunning00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  bool tolua_ret = (bool)  ICR_SystemRunning();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ICR_SystemRunning'.",&tolua_err);
 return 0;
#endif
}

/* function: ICR_RegisterKbFunction */
static int tolua_ObjetosExportados_ICR_RegisterKbFunction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnumber(tolua_S,1,0,&tolua_err) || 
 !tolua_isstring(tolua_S,2,0,&tolua_err) || 
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  int tcl = ((int)  tolua_tonumber(tolua_S,1,0));
  char* nmFunc = ((char*)  tolua_tostring(tolua_S,2,0));
 {
  ICR_RegisterKbFunction(tcl,nmFunc);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ICR_RegisterKbFunction'.",&tolua_err);
 return 0;
#endif
}

/* function: ICR_ShutDown */
static int tolua_ObjetosExportados_ICR_ShutDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  ICR_ShutDown();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ICR_ShutDown'.",&tolua_err);
 return 0;
#endif
}

/* function: ICR_HoldPipelines */
static int tolua_ObjetosExportados_ICR_HoldPipelines00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  ICR_HoldPipelines();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ICR_HoldPipelines'.",&tolua_err);
 return 0;
#endif
}

/* function: ICR_FreePipelines */
static int tolua_ObjetosExportados_ICR_FreePipelines00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  ICR_FreePipelines();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ICR_FreePipelines'.",&tolua_err);
 return 0;
#endif
}

/* Open lib function */
LUALIB_API int luaopen_ObjetosExportados (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
 tolua_constant(tolua_S,"ICR_FRONT",ICR_FRONT);
 tolua_constant(tolua_S,"ICR_BACK",ICR_BACK);
 tolua_constant(tolua_S,"ICR_LEFT",ICR_LEFT);
 tolua_constant(tolua_S,"ICR_RIGHT",ICR_RIGHT);
 tolua_constant(tolua_S,"ICR_ESC_KEY",ICR_ESC_KEY);
 tolua_constant(tolua_S,"ICR_A_KEY",ICR_A_KEY);
 tolua_constant(tolua_S,"ICR_B_KEY",ICR_B_KEY);
 tolua_constant(tolua_S,"ICR_C_KEY",ICR_C_KEY);
 tolua_constant(tolua_S,"ICR_D_KEY",ICR_D_KEY);
 tolua_constant(tolua_S,"ICR_E_KEY",ICR_E_KEY);
 tolua_constant(tolua_S,"ICR_F_KEY",ICR_F_KEY);
 tolua_constant(tolua_S,"ICR_G_KEY",ICR_G_KEY);
 tolua_constant(tolua_S,"ICR_H_KEY",ICR_H_KEY);
 tolua_constant(tolua_S,"ICR_I_KEY",ICR_I_KEY);
 tolua_constant(tolua_S,"ICR_J_KEY",ICR_J_KEY);
 tolua_constant(tolua_S,"ICR_K_KEY",ICR_K_KEY);
 tolua_constant(tolua_S,"ICR_L_KEY",ICR_L_KEY);
 tolua_constant(tolua_S,"ICR_M_KEY",ICR_M_KEY);
 tolua_constant(tolua_S,"ICR_N_KEY",ICR_N_KEY);
 tolua_constant(tolua_S,"ICR_O_KEY",ICR_O_KEY);
 tolua_constant(tolua_S,"ICR_P_KEY",ICR_P_KEY);
 tolua_constant(tolua_S,"ICR_Q_KEY",ICR_Q_KEY);
 tolua_constant(tolua_S,"ICR_R_KEY",ICR_R_KEY);
 tolua_constant(tolua_S,"ICR_S_KEY",ICR_S_KEY);
 tolua_constant(tolua_S,"ICR_T_KEY",ICR_T_KEY);
 tolua_constant(tolua_S,"ICR_U_KEY",ICR_U_KEY);
 tolua_constant(tolua_S,"ICR_V_KEY",ICR_V_KEY);
 tolua_constant(tolua_S,"ICR_W_KEY",ICR_W_KEY);
 tolua_constant(tolua_S,"ICR_X_KEY",ICR_X_KEY);
 tolua_constant(tolua_S,"ICR_Y_KEY",ICR_Y_KEY);
 tolua_constant(tolua_S,"ICR_Z_KEY",ICR_Z_KEY);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"CICRPosition","CICRPosition","",tolua_collect_CICRPosition);
#else
 tolua_cclass(tolua_S,"CICRPosition","CICRPosition","",NULL);
#endif
 tolua_beginmodule(tolua_S,"CICRPosition");
 tolua_variable(tolua_S,"mPosX",tolua_get_CICRPosition_CICRPosition_mPosX,tolua_set_CICRPosition_CICRPosition_mPosX);
 tolua_variable(tolua_S,"mPosY",tolua_get_CICRPosition_CICRPosition_mPosY,tolua_set_CICRPosition_CICRPosition_mPosY);
 tolua_variable(tolua_S,"mPosZ",tolua_get_CICRPosition_CICRPosition_mPosZ,tolua_set_CICRPosition_CICRPosition_mPosZ);
 tolua_function(tolua_S,"new",tolua_ObjetosExportados_CICRPosition_new00);
 tolua_function(tolua_S,"new",tolua_ObjetosExportados_CICRPosition_new01);
 tolua_function(tolua_S,"delete",tolua_ObjetosExportados_CICRPosition_delete00);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"CICRActor","CICRActor","",tolua_collect_CICRActor);
#else
 tolua_cclass(tolua_S,"CICRActor","CICRActor","",NULL);
#endif
 tolua_beginmodule(tolua_S,"CICRActor");
 tolua_variable(tolua_S,"ICR_ActorPos",tolua_get_CICRActor_CICRActor_ICR_ActorPos,tolua_set_CICRActor_CICRActor_ICR_ActorPos);
 tolua_variable(tolua_S,"ICR_ActorId",tolua_get_CICRActor_CICRActor_ICR_ActorId,tolua_set_CICRActor_CICRActor_ICR_ActorId);
 tolua_variable(tolua_S,"ICR_ActorName",tolua_get_CICRActor_CICRActor_ICR_ActorName,tolua_set_CICRActor_CICRActor_ICR_ActorName);
 tolua_function(tolua_S,"new",tolua_ObjetosExportados_CICRActor_new00);
 tolua_function(tolua_S,"new",tolua_ObjetosExportados_CICRActor_new01);
 tolua_function(tolua_S,"delete",tolua_ObjetosExportados_CICRActor_delete00);
 tolua_function(tolua_S,"GetName",tolua_ObjetosExportados_CICRActor_GetName00);
 tolua_function(tolua_S,"SetName",tolua_ObjetosExportados_CICRActor_SetName00);
 tolua_function(tolua_S,"SetPos",tolua_ObjetosExportados_CICRActor_SetPos00);
 tolua_function(tolua_S,"GetPos",tolua_ObjetosExportados_CICRActor_GetPos00);
 tolua_function(tolua_S,"Walk",tolua_ObjetosExportados_CICRActor_Walk00);
 tolua_function(tolua_S,"Stop",tolua_ObjetosExportados_CICRActor_Stop00);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"CICRCamera","CICRCamera","",tolua_collect_CICRCamera);
#else
 tolua_cclass(tolua_S,"CICRCamera","CICRCamera","",NULL);
#endif
 tolua_beginmodule(tolua_S,"CICRCamera");
 tolua_variable(tolua_S,"mPos",tolua_get_CICRCamera_CICRCamera_mPos,tolua_set_CICRCamera_CICRCamera_mPos);
 tolua_function(tolua_S,"new",tolua_ObjetosExportados_CICRCamera_new00);
 tolua_function(tolua_S,"new",tolua_ObjetosExportados_CICRCamera_new01);
 tolua_function(tolua_S,"delete",tolua_ObjetosExportados_CICRCamera_delete00);
 tolua_function(tolua_S,"Move",tolua_ObjetosExportados_CICRCamera_Move00);
 tolua_endmodule(tolua_S);
 tolua_function(tolua_S,"ICR_SystemOk",tolua_ObjetosExportados_ICR_SystemOk00);
 tolua_function(tolua_S,"ICR_SystemRunning",tolua_ObjetosExportados_ICR_SystemRunning00);
 tolua_function(tolua_S,"ICR_RegisterKbFunction",tolua_ObjetosExportados_ICR_RegisterKbFunction00);
 tolua_function(tolua_S,"ICR_ShutDown",tolua_ObjetosExportados_ICR_ShutDown00);
 tolua_function(tolua_S,"ICR_HoldPipelines",tolua_ObjetosExportados_ICR_HoldPipelines00);
 tolua_function(tolua_S,"ICR_FreePipelines",tolua_ObjetosExportados_ICR_FreePipelines00);
 tolua_endmodule(tolua_S);
 return 1;
}
/* Open tolua function */
TOLUA_API int tolua_ObjetosExportados_open (lua_State* tolua_S)
{
 lua_pushcfunction(tolua_S, luaopen_ObjetosExportados);
 lua_pushstring(tolua_S, "ObjetosExportados");
 lua_call(tolua_S, 1, 0);
 return 1;
}
