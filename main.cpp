/*
 * @Copyright(c) 2021-2021 *** All Rights Reserved
 * @version: 1.1
 * @Author: Guo Zhc, guozc09@163.com
 * @Created: 2021-09-30 15:00
 */
#include "shutdownmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShutdownMainWindow w;
    w.show();
    return a.exec();
}
