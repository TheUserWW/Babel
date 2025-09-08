#include "MainWindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QSettings>
#include <Windows.h> // 添加Windows头文件
#include <shellapi.h> // 用于ShellExecute





bool isAdmin() {
    BOOL fRet = FALSE;
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof(TOKEN_ELEVATION);
        if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
            fRet = Elevation.TokenIsElevated;
        }
    }
    if (hToken) {
        CloseHandle(hToken);
    }
    return fRet;
}

// 重启应用程序并请求管理员权限
void restartAsAdmin() {
    wchar_t szPath[MAX_PATH];
    if (GetModuleFileNameW(NULL, szPath, ARRAYSIZE(szPath))) {
        SHELLEXECUTEINFOW sei = {
            sizeof(sei),
            SEE_MASK_NOCLOSEPROCESS,
            NULL,
            L"runas",
            szPath,
            NULL,
            NULL,
            SW_SHOW
        };
        ShellExecuteExW(&sei);
    }
}







int main(int argc, char *argv[])
{
    // 检查是否以管理员权限运行
    if (!isAdmin()) {
        // 如果不是管理员权限，重启应用程序
        restartAsAdmin();
        return 0;
    }

    QApplication a(argc, argv);

    // 加载保存的语言设置
    QSettings settings("Babel.ini", QSettings::IniFormat);
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
