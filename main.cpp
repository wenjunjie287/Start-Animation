#include "mainwindow.h"

#include <QApplication>
#include <QString>
#include <QDir>
#include "Windows.h"
#include <QDebug>
#include <QLibraryInfo>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int ms=30;
    int width = 500;
    int height = 500;

    if(argc<2)
    {
        return 0;
    }
    else if(argc>=4)
    {
        ms=atoi(argv[2]);
        width = atoi(argv[3]);
        height = atoi(argv[4]);
        if(ms==0)
        {
            ms=30;
        }
    }

    QString str=QString::fromUtf8(argv[1]);
    MainWindow w(str,ms,width,height);
    w.show();
    return a.exec();
}
