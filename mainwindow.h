#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QString;
class QTimer;
class QStringList;
class QMovie;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString str,int ms,int w,int h, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void initWindow();

private:
    Ui::MainWindow *ui;
    QString m_path;
    int m_currindex =0;
    int m_ms=0;
    QTimer *m_timer = nullptr;
    QStringList m_files;
    QMovie *m_move = nullptr;
    QString mCurrentPath;

};
#endif // MAINWINDOW_H
