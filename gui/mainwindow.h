#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "tools/clogger.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    CLogger*        m_log;

private slots:
    void    onLog(const QString& pMessage,QColor pColor, CL_DEBUG_LEVEL pLevel);
};
#endif // MAINWINDOW_H
