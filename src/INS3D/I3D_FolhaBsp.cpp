/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "I3D_FolhaBsp.h"


CI3DFolhaBsp::CI3DFolhaBsp()
{
    I3D_FaceCount       = 0;
}


CI3DFolhaBsp::~CI3DFolhaBsp()
{

}

bool CI3DFolhaBsp::ConstroiIndicesFaces( CI3DFaceBsp * pListaFaces )
{

    CI3DFaceBsp    *Iterator       = pListaFaces;
    unsigned long   IndiceOriginal = 0;

    I3D_Borda.Limpa();

    while ( Iterator != NULL )
    {
        IndiceOriginal = Iterator->IndiceOriginal;
        try
        {
            if (std::find(I3D_FaceIndices.begin(), I3D_FaceIndices.end(), IndiceOriginal) == I3D_FaceIndices.end())
            {
                if (I3D_FaceIndices.size() >= (I3D_FaceIndices.capacity() - 1))
                {
                    I3D_FaceIndices.reserve( I3D_FaceIndices.size() + BLOCO_MEMORIA_FOLHA);
                }
                I3D_FaceIndices.push_back(IndiceOriginal);
            }
        }
        catch (...)
        {
            I3D_FaceCount = 0;
            I3D_FaceIndices.clear();
            return false;
        }

        I3D_Borda.CalculaBordaMesh( Iterator->Vertices, Iterator->I3D_QtdVertices,sizeof(CI3DVertice),false);

        Iterator = Iterator->Proximo;
    }

    I3D_FaceCount = I3D_FaceIndices.size();

    if (I3D_FaceCount < I3D_FaceIndices.capacity()) I3D_FaceIndices.resize( I3D_FaceCount );

    return true;
}

//-----------------------------------------------------------------------------
// Name : AddPortal ()
// Desc : Adds the specified portal index to this leaf
//-----------------------------------------------------------------------------
bool CI3DFolhaBsp::AdicionaPortal( unsigned long IndicePortal )
{
    try
    {
        // Resize the vector if we need to
        if (PortalIndices.size() >= (PortalIndices.capacity() - 1))
        {
            PortalIndices.reserve( PortalIndices.size() + BLOCO_MEMORIA_FOLHA );
        } // End If

        // Finally add this face index to the list
        PortalIndices.push_back( IndicePortal );

    } // End Try Block

    catch (...)
    {
        // Clean up and bail
        PortalCount = 0;
        PortalIndices.clear();
        return false;
    } // End Catch

    // Increase the portal count
    PortalCount++;

    // Success
    return true;
}

//-----------------------------------------------------------------------------
// Name : AdicionaRefLogica ()
// Desc : Adiciona um indice de Ref Logica na Folha
//-----------------------------------------------------------------------------
bool CI3DFolhaBsp::AdicionaRefLogica( unsigned long IndiceRefLog)
{
    try
    {
        if (RefLogIndices.size() >= (RefLogIndices.capacity() - 1))
        {
            RefLogIndices.reserve( RefLogIndices.size() + BLOCO_MEMORIA_FOLHA );
        }

        for(long pos=0;pos<RefLogIndices.size();pos++)
        {
            if(IndiceRefLog==RefLogIndices[pos])
            {
                return false;
            }
        }
        RefLogIndices.push_back( IndiceRefLog );
    }

    catch (...)
    {
        RefLogCount = 0;
        RefLogIndices.clear();
        return false;
    }

    RefLogCount++;
    return true;
}

//-----------------------------------------------------------------------------
// Name : AdicionaObjDetalhado ()
// Desc : Adiciona um indice de ObjDetalhado na Folha
//-----------------------------------------------------------------------------
bool CI3DFolhaBsp::AdicionaObjDetalhado( unsigned long IndiceObjDet)
{
    try
    {
        if (ObjectIndices.size() >= (ObjectIndices.capacity() - 1))
        {
            ObjectIndices.reserve( ObjectIndices.size() + BLOCO_MEMORIA_FOLHA );
        }

        for(long pos=0;pos<ObjectIndices.size();pos++)
        {
            if(IndiceObjDet==ObjectIndices[pos])
            {
                return false;
            }
        }
        ObjectIndices.push_back( IndiceObjDet );

    }

    catch (...)
    {
        ObjectCount = 0;
        ObjectIndices.clear();
        return false;
    }

    ObjectCount++;

    return true;
}
