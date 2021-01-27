#ifndef CIPLEDITORMAINWINDOW_H
#define CIPLEDITORMAINWINDOW_H

#include "IPL_GlobalDef.h"
#include "IPL_EditorTabWidget.h"
#include <QMainWindow>

class CIPLEditorMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    CIPLEditorMainWindow();

    /**************************************************************/
    /*Rotinas para Criação da estrutura principal de Menus e Telas*/
    /**************************************************************/
    void        CriaAcoes      ();
    void        CriaMenus      ();
    void        CriaBarras     ();
    void        CriaBarraStatus();
    void        CriaDocking    ();
    /**************************************************************/
    /*Rotinas de apoio para linkagem Front-End com Back-End       */
    /**************************************************************/
    void        atribuiCenario          (CISMCenario *pScn );
    QGLContext* PegaContexto            (                  );
private:
    //Instancia Barra de Menu
    QMenuBar *mBarraMenu  ;
    QMenu    *mMenuArquivo;
    QMenu    *mMenuEditar ;
    QMenu    *mMenuSobre  ;
    QAction  *addNew      ;

    QToolBar *mToolBarArquivo;
    QToolBar *mToolBarEditar;

    QAction *mAcaoNovo;
    QAction *mAcaoAbrir;
    QAction *mAcaoSalvar;
    QAction *mAcaoSalvarComo;
    QAction *mAcaoSair;
    QAction *mAcaoCortar;
    QAction *mAcaoCopiar;
    QAction *mAcaoColar;
    QAction *mAcaoSobre;

    CIPLEditorTabWidget    *tabFerramentas;

};

#endif // CIPLMAINWINDOW_H
