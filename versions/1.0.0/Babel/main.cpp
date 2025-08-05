#include "MainWindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 可以在这里添加全局翻译初始化代码
    // 但我们已经在MainWindow中实现了动态切换

    MainWindow w;
    w.show();
    return a.exec();
}
