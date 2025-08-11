#include "MainWindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 加载保存的语言设置
    QSettings settings("Babel.ini", QSettings::IniFormat);
    QString language = settings.value("Language", "en").toString();

    QTranslator translator;
    if (language != "en") {
        translator.load("Babel_" + language + ".qm");
        a.installTranslator(&translator);
    }

    MainWindow w;
    w.show();
    return a.exec();
}
