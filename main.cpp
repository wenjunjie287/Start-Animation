#include "mainwindow.h"

#include <QApplication>
#include <QString>
#include <QDir>
#include <QDebug>
#include <QLabel>
#include <QTimer>
#include <QLibraryInfo>
#include <QProcess>

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>

QString PrintProcessNameAndID( DWORD processID )
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    // Get a handle to the process.

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, processID );

    // Get the process name.
    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod),
             &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName,
                               sizeof(szProcessName)/sizeof(TCHAR) );
        }
    }
    // Print the process name and identifier.
    //_tprintf( TEXT("%s  (PID: %u)\n"), szProcessName, processID );
    // Release the handle to the process.
    CloseHandle( hProcess );
    QString qstring = QString::fromWCharArray(szProcessName);
    return qstring;
}
bool checkProcess(QString exeName)
{
    // Get the list of process identifiers.

    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
    {
        return false;
    }
    // Calculate how many process identifiers were returned.
    cProcesses = cbNeeded / sizeof(DWORD);

    // Print the name and process identifier for each process.

    for ( i = 0; i < cProcesses; i++ )
    {
        if(aProcesses[i] != 0  && exeName == PrintProcessNameAndID( aProcesses[i]) )
        {
            return true;
        }
    }
    return false;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int ms=30;
    int width = 500;
    int height = 500;
    QString exeName;

    if(argc<2)
    {
        return 0;
    }
    else if(argc>=4)
    {
        ms=atoi(argv[2]);
        width = atoi(argv[3]);
        height = atoi(argv[4]);
        exeName = QString::fromLocal8Bit(argv[5]);
        if(ms==0)
        {
            ms=30;
        }
    }
    QLabel label;

    QString str=QString::fromUtf8(argv[1]);
    MainWindow w(str,ms,width,height);
    w.show();

    QTimer *t = new QTimer();
    t->start(1000);
    // 获取进程的输出结果
    QObject::connect(t,&QTimer::timeout,[&]()
    {
        if (checkProcess(exeName))
        {
            qDebug() << "Executable is running!";
        }
        else
        {
            a.quit();
            qDebug() << "Executable is not running!";
        }
    }
    );

    return a.exec();
}
