// phoneticchartdialog.h
#ifndef PHONETICCHARTDIALOG_H
#define PHONETICCHARTDIALOG_H

#include <QDialog>
#include "LetterConverter.h"
#include <QGridLayout>
#include <QCloseEvent>
#include <QProgressBar>

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
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::PhoneticChartDialog *ui;
    LetterConverter converter;
    QTimer *loadTimer;
    QProgressBar *progressBar;
    int currentAlphabetIndex;
    int totalAlphabets;

    void setupPhoneticChart();
    void clearGrid();
    void addAlphabetToGrid(const QString& title, const QStringList& letters, const QStringList& ipa);
    void loadNextAlphabet();
    void initializeLoadingUI();
    void finalizeLoadingUI();
};

#endif // PHONETICCHARTDIALOG_H
