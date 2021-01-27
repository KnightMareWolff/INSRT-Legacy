TEMPLATE = subdirs

SUBDIRS += \
    lua522 \
    tolua \
    assimp \
    zlib \
    lua531

#seta dependencias obrigatorias
tolua.depends = lua522
assimp.depends = zlib
