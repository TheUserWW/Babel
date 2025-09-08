#ifndef PHONETICCHARTDIALOG_H
#define PHONETICCHARTDIALOG_H

#include <QDialog>
#include "LetterConverter.h"
#include <QTabWidget>
#include <QCloseEvent> // 添加QCloseEvent头文件

namespace Ui {
class PhoneticChartDialog;
}

class PhoneticChartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PhoneticChartDialog(QWidget *parent = nullptr);
    ~PhoneticChartDialog();

protected:
    // 重写closeEvent函数，实现隐藏而不是删除对话框
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::PhoneticChartDialog *ui;
    LetterConverter converter;

    void setupPhoneticCharts();
    void clearAllTables();
    void setupLatinChart();
    void setupCyrillicChart();
    void setupGreekChart();
    void setupKhmerChart();
    void setupSyriacChart();
    void setupTibetanChart();
    void setupDevanagariChart();
    void setupHebrewChart();
    void setupRunicChart();
    void setupHangulChart();
    void setupKanaChart();
    void setupZhuyinChart();
    void setupArabicChart();
    void setupUyghurChart();
    void setupPersianChart();
    void setupGeorgianChart();
    void setupGeezChart();
    void setupThaiChart();
    void setupArmenianChart();
    void setupBengaliChart();
};

#endif // PHONETICCHARTDIALOG_H
