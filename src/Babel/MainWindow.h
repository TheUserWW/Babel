#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <phoneticchartdialog.h>
#include <QMenuBar>
#include "LetterConverter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onConvertClicked();
    void switchLanguage(const QString &language);
    void retranslateUi();
    void onAboutClicked();
    void onTheUserWWClicked();
    void onPhoneticChartClicked();

private:
    Ui::MainWindow *ui;
    LetterConverter converter;
    PhoneticChartDialog *phoneticChartDialog; // 添加对话框指针成员变量
    void populateAlphabetComboBoxes();
};

#endif // MAINWINDOW_H
