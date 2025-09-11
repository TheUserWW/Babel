#include "MainWindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QSettings>
#include <QStandardPaths>
#include <QDir>



int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    // 加载保存的语言设置
    QString configPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QDir().mkpath(configPath);
    QString iniFilePath = configPath + "/Babel.ini";
    QSettings settings(iniFilePath, QSettings::IniFormat);
    QString language = settings.value("Language", "en").toString();

    QTranslator translator;
    if (language != "en") {
        if (translator.load("Babel_" + language + ".qm", qApp->applicationDirPath())) {
            a.installTranslator(&translator);
        } else {
            qWarning() << "Failed to load translation file for language:" << language;
        }
    }

    MainWindow w;
    w.show();
    return a.exec();
}
