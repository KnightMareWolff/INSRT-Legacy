/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :Ponto Inicial de execução do aplicativo/jogo
/*Data de Criação     :2013/2014
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "INS_GlobalDef.h"
#include "INS_Launcher.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>

/**************************/
/*Includes da Lua e Tolua */
/**************************/
extern "C" {
#include <../../extools/lua522/lua.h>
#include <../../extools/lua522/lualib.h>
#include <../../extools/lua522/lauxlib.h>
}

#include <../../extools/tolua/tolua.h>

void RecuperaConfigPaths(QString &pathinst,QString &pathworld)
{
    /****************************************************/
    /*ATENÇÃO!                                          */
    /*Caso esta seja a primeira instalação da INS3D     */
    /*em seu ambiente, é necessário alterar o define    */
    /*global INS_PATH_CONFIG para apontar para o        */
    /*arquivo config.xml contendo os Paths de instalação*/
    /*do codigo fonte em sua máquina(INS_Globaldef.h)   */
    /****************************************************/
    QString ArqConfig = INS_PATH_CONFIG;

    QFile file(ArqConfig);

    file.open(QIODevice::ReadOnly);

    QTextStream      out(&file);
    QString config = out.readAll();

    QXmlStreamReader *ConfigStream = new QXmlStreamReader(config);

    while (!ConfigStream->atEnd())
    {
       if(ConfigStream->readNextStartElement())
       {
           if(ConfigStream->name() == "pathinst")
           {
               pathinst = ConfigStream->readElementText();
           }
           if(ConfigStream->name() == "pathworld")
           {
               pathworld = ConfigStream->readElementText();
           }
       }
    }
}

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    QString pathinstalacao;
    QString pathworld;

    //Recupera Paths de aplicação do arquivo config.xml
    RecuperaConfigPaths(pathinstalacao,pathworld);

    QString program = "../../../INSRT/bin/insetup";
    QStringList arguments;

    arguments << "-style" << "fusion";


    QProcess *myProcess = new QProcess();

    myProcess->start(program, arguments);

    //Contexto principal de inicialização do componente de Utilidades
    INSUT* pINSUTPlatInterface=NULL;
    //Inicializa Plataforma de Utilidades
    pINSUTPlatInterface  = new INSUT();
    pINSUTPlatInterface->SetaAppPaths(pathinstalacao,pathworld);

    //Inicializa e Executa Insane Launcher
    CINSLauncher Launcher;
    Launcher.exec();

    //Contexto principal de Inicialização do componente de Sistema
    INSSL* pINSSLPlatInterface=NULL;

    //Cria uma Instancia da Camada De Sistema da INS baseado nos parametros do Launcher
    switch(Launcher.mModoExecucao)
    {
       case 0:
       {
          pINSSLPlatInterface  = new INSSL(ISL_EDITOR_MODE,0);
          if(pINSSLPlatInterface==NULL)
          {
              QMessageBox::information(0, "Insane RT Framework",
                                          "Falha ao Iniciar o Layer de Sistema.");
              exit(0);
          }
          pINSSLPlatInterface->MostraTela(ISL_EDITOR_MODE);
       };break;
       case 1:
       {
          pINSSLPlatInterface  = new INSSL(ISL_RUNTIME_MODE,Launcher.mProjetoRuntime);
          if(pINSSLPlatInterface==NULL)
          {
              QMessageBox::information(0, "Insane RT Framework",
                                          "Falha ao Iniciar o Layer de Sistema.");
              exit(0);
          }
          pINSSLPlatInterface->MostraTela(ISL_RUNTIME_MODE);
       };break;
       case 2:{exit(0);}break;
       //pINSSLPlatInterface = new INSSL(ISL_QQUICK_MODE);
       //pINSSLPlatInterface->MostraTela(ISL_QQUICK_MODE);
    }

    //Executa a aplicação Principal até ser fechada
    return a.exec();
}
