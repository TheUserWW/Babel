#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
    LetterConverter converter;
    void populateAlphabetComboBoxes();
};

#endif // MAINWINDOW_H
