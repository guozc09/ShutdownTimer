#include "shutdownmainwindow.h"
#include "ui_shutdownmainwindow.h"
#include <QDebug>
#include <QProcess>
#include <QString>

ShutdownMainWindow::ShutdownMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ShutdownMainWindow),
      mHour(0.0), mSecond(0)
{
    ui->setupUi(this);
    mMsgBox.reset(new QMessageBox);
    this->setWindowTitle(tr("定时关机"));
}

ShutdownMainWindow::~ShutdownMainWindow()
{
    delete ui;
    mMsgBox.clear();
}

void ShutdownMainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "Event is" << event->key();
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        on_buttonBox_accepted();
    }
}

void ShutdownMainWindow::on_buttonBox_accepted()
{
    if (mHour <= 0.0 || mHour >= 24.0) {
        QString &&noteMsg = QString(tr("小宝贝你输入的关机时间 %1 小时是非法的哟~，请重新输入吧！")).arg(mHour);
        qDebug() << noteMsg;
        mMsgBox->setText(noteMsg);
        mMsgBox->show();
        return;
    }
    QString &&msgContext = QString(tr("小宝贝我们 %1 小时后要关机咯~")).arg(mHour);
    qDebug() << msgContext;
    mMsgBox->setText(msgContext);
    mMsgBox->show();

    QProcess shutdownProcess;
    shutdownProcess.start("cmd", QStringList()<< "/c" << "shutdown -a");
    shutdownProcess.waitForStarted();
    shutdownProcess.waitForFinished();
    qDebug()<<QString::fromLocal8Bit(shutdownProcess.readAllStandardOutput());
    shutdownProcess.start("cmd", QStringList()<< "/c" << "shutdown -s -t " + QString::number(mSecond, 10));
    shutdownProcess.waitForStarted();
    shutdownProcess.waitForFinished();
    qDebug()<<QString::fromLocal8Bit(shutdownProcess.readAllStandardOutput());
    this->close();
}


void ShutdownMainWindow::on_buttonBox_rejected()
{
    QString &&msgContext = QString(tr("小宝贝我已经为你取消关机咯~"));
    qDebug() << msgContext;
    mMsgBox->setText(msgContext);
    mMsgBox->show();
    QProcess shutdownProcess;
    shutdownProcess.start("cmd", QStringList()<< "/c" << "shutdown -a");
    shutdownProcess.waitForStarted();
    shutdownProcess.waitForFinished();
    qDebug()<<QString::fromLocal8Bit(shutdownProcess.readAllStandardOutput());
    this->close();
}


void ShutdownMainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    qDebug() << "刚刚设置的是：" << arg1 << "小时";
    if (arg1 <= 0.0 || arg1 >= 24.0) {
        qDebug() << "错误的输入信息";
        return;
    }
    mHour = arg1;
    mSecond = static_cast<int>(arg1 * 3600);
}

