#pragma once
#include "QT_Semes.h"
#include <QtWidgets/QApplication>
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define initHeapMonitor() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QT_Semes w;
    w.show();
    return a.exec();


}
