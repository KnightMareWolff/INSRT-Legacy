TEMPLATE = subdirs

SUBDIRS += \
    extools \
    intools \
    INSMT \
    INSUT \
    INSSH \
    INSIA \
    INSMD \
    INSGL \
    INSCL \
    INS3D \
    INSMA \
    INSGZ \
    INSGO \
    INSSM \
    INSPL \
    INSCR \
    INSSL \
    INSPH \
    INSCG \
    INSVK \
    INS


# where to find the sub projects - give the folders
extools.subdir = extools
intools.subdir = intools
INSMT.subdir   = src/INSMT
INSUT.subdir   = src/INSUT
INSSH.subdir   = src/INSSH
INSIA.subdir   = src/INSIA
INSMD.subdir   = src/INSMD
INSGL.subdir   = src/INSGL
INSCL.subdir   = src/INSCL
INS3D.subdir   = src/INS3D
INSMA.subdir   = src/INSMA
INSGZ.subdir   = src/INSGZ
INSGO.subdir   = src/INSGO
INSSM.subdir   = src/INSSM
INSPL.subdir   = src/INSPL
INSCR.subdir   = src/INSCR
INSSL.subdir   = src/INSSL
INSPH.subdir   = src/INSPH
INSCG.subdir   = src/INSCG
INSVK.subdir   = src/INSVK
INS.subdir     = INS

#seta dependencias obrigatorias
INSUT.depends = extools INSMT
INSSH.depends = INSGL INSUT
INS3D.depends = INSGL INSSH INSMA INSCL INSVK
INSGL.depends = INSMT
INSMD.depends = INSMT
INSCL.depends = INSGL INSUT
INSMA.depends = INSGL INSUT
INSGZ.depends = INS3D
INSGO.depends = INSGZ
INSSM.depends = INS3D INSGZ INSGO
INSPL.depends = INSSM INSCR
INSCR.depends = INSMT INSSM
INSSL.depends = INSPL
INSCG.depends = INSMT
INSVK.depends = INSMT INSUT
INS.depends   = INSSL

