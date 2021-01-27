#ifndef IVK_GLOBALDEF_H
#define IVK_GLOBALDEF_H

#include <QtGlobal>

#include "../INSMT/INSMT.h"
#include "../INSUT/INSUT.h"

//Mapeia Rotinas Nativas Para Windows
#ifdef Q_OS_WIN
   #include <Windows.h>
   #include <wingdi.h>
   #include <vulkan.h>
   #include <vk_platform.h>
   #include <QtPlatformHeaders/QWGLNativeContext>
#endif

using namespace std;


#endif // IVK_GLOBALDEF_H
