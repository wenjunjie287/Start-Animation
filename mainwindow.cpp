#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QTimer>
#include <QDir>
#include <QFileInfo>
#include <QPixmap>
#include <QMovie>
#include <QDesktopWidget>
MainWindow::MainWindow(QString str,int ms,int w,int h,QWidget *parent)
    : QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
    mCurrentPath = QDir::currentPath();

    m_path = str;
    m_ms=ms;
    ui->setupUi(this);
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    ui->label->setScaledContents(true);
    resize(w,h);
    initWindow();

    QDesktopWidget * desktop = QApplication::desktop();
    int curMonitor = desktop->screenNumber (0); // 参数是一个QWidget*
    QRect rect = desktop->screenGeometry(curMonitor);
    move((rect.width()-this->width())/2,(rect.height()-this->height())/2);
    //move((QApplication::desktop()->width()-this->width())/2,(QApplication::desktop()->height()-this->height())/2);
}

MainWindow::~MainWindow()
{
    if(m_move)
    {
        m_move->stop();
        delete  m_move;
    }
    if(m_timer)
    {
        m_timer->stop();
        delete m_timer;
    }
    delete ui;
}

void MainWindow::initWindow()
{
    m_path = mCurrentPath+m_path;
    QFileInfo info(m_path);
    if(info.isDir())
    {//如果传入是一个目录

        ui->label->setText(m_path);
        m_timer = new QTimer(this);
        connect(m_timer,&QTimer::timeout,[this]()
        {
            if(m_currindex == m_files.length())
            {
                m_timer->stop();
                this->close();
            }
            else
            {

                QPixmap pix(m_path + "/" + m_files.at(m_currindex++));
                pix = pix.scaled(ui->label->size(), Qt::KeepAspectRatio);
                ui->label->setPixmap(pix);
            }
        });

        QDir dir(m_path);
        m_files = dir.entryList(QDir::NoDotAndDotDot | QDir::Files);
        if(!m_files.isEmpty())
        {
            QPixmap pix(m_path + "/" + m_files.at(m_currindex++));
            pix = pix.scaled(ui->label->size(), Qt::KeepAspectRatio);
            ui->label->setPixmap(pix);
            m_timer->start(m_ms);
        }
        else
        {
            this->close();
        }
    }
    else if(m_path.endsWith(".gif"))
    {

        m_move = new QMovie(m_path);
        ui->label->setMovie(m_move);
        m_move->start();
    }
    else
    {
        QPixmap pix(m_path);
        pix = pix.scaled(ui->label->size(), Qt::KeepAspectRatio);
        ui->label->setPixmap(pix);
    }

}

