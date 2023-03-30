#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include<QDebug>
#include<QTextCharFormat>

#include<tools/version.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_log = CLogger::instance();
    connect(m_log, SIGNAL(fireLog(QString,QColor,CL_DEBUG_LEVEL)),this,SLOT(onLog(QString,QColor,CL_DEBUG_LEVEL)));
    setWindowIcon(QIcon(":/icons/gfx/flcards.xpm"));
    m_log->log(tr("Qt Version :") + QT_VERSION_STR,Qt::blue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

///
/// \brief MainWindow::onLog
/// \param Texte
/// \param pColor
/// \param pLevel
///
/// Redirect Log Text flow to Plain Text Edit on main Window
///
void MainWindow::onLog (const QString& pMessage, QColor pColor, CL_DEBUG_LEVEL)
{
    QTextCharFormat fmt;
    fmt.setForeground(QBrush(pColor));
    ui->pteLogger->mergeCurrentCharFormat(fmt);
    ui->pteLogger->appendPlainText(pMessage);
}
