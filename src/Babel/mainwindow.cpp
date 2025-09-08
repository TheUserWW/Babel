#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QActionGroup>
#include <QMenu>
#include <QTranslator>
#include <QLocale>
#include <QMenuBar>
#include <QDesktopServices>
#include <QUrl>
#include <QSettings> // 添加QSettings头文件
#include "aboutdialog.h"
#include "phoneticchartdialog.h" // 添加头文件

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    phoneticChartDialog(nullptr) // 初始化对话框指针为nullptr
{
    ui->setupUi(this);

    // 添加语言切换动作组
    QActionGroup *languageGroup = new QActionGroup(this);
    languageGroup->addAction(ui->action);      // 简体中文
    languageGroup->addAction(ui->actionEnglish); // English
    languageGroup->addAction(ui->actionRussian); // Русский
    languageGroup->addAction(ui->actionArabic); // العربية
    languageGroup->addAction(ui->actionSpanish); // Español
    languageGroup->setExclusive(true);

    // 读取保存的语言偏好
    QSettings settings("Babel.ini", QSettings::IniFormat);
    QString language = settings.value("Language", "en_US").toString();

    // 设置默认语言
    if (language == "zh_CN") {
        ui->action->setChecked(true);
        switchLanguage("zh_CN");
    } else if (language == "ru_RU") {
        ui->actionRussian->setChecked(true);
        switchLanguage("ru_RU");
    } else if (language == "ar_SA") {
        ui->actionArabic->setChecked(true);
        switchLanguage("ar_SA");
    } else if (language == "es_ES") {
        ui->actionSpanish->setChecked(true);
        switchLanguage("es_ES");
    } else {
        // 默认英文
        ui->actionEnglish->setChecked(true);
        switchLanguage("en_US");
    }

    // 连接语言切换信号
    connect(ui->action, &QAction::triggered, this, [this]() { switchLanguage("zh_CN"); });
    connect(ui->actionEnglish, &QAction::triggered, this, [this]() { switchLanguage("en_US"); });
    connect(ui->actionRussian, &QAction::triggered, this, [this]() { switchLanguage("ru_RU"); });
    connect(ui->actionArabic, &QAction::triggered, this, [this]() { switchLanguage("ar_SA"); });
    connect(ui->actionSpanish, &QAction::triggered, this, [this]() { switchLanguage("es_ES"); });
    

    // 填充字母系统选择框
    populateAlphabetComboBoxes();

    // 初始化UI文本
    retranslateUi();

    // 连接按钮信号
    connect(ui->convertButton, &QPushButton::clicked, this, &MainWindow::onConvertClicked);
    // 连接关于菜单信号
    connect(ui->actionabout, &QAction::triggered, this, &MainWindow::onAboutClicked);
    // 连接TheUserWW菜单信号
    connect(ui->actionTheUserWW, &QAction::triggered, this, &MainWindow::onTheUserWWClicked);
    // 连接音标表菜单信号
    connect(ui->actionPhoneticChart, &QAction::triggered, this, &MainWindow::onPhoneticChartClicked);
}

void MainWindow::populateAlphabetComboBoxes()
{
    ui->sourceComboBox->clear();
    ui->targetComboBox->clear();

    // 添加所有字母系统选项
    ui->sourceComboBox->addItem(tr("Latin"), LetterConverter::Latin);
    ui->sourceComboBox->addItem(tr("Cyrillic"), LetterConverter::Cyrillic);
    ui->sourceComboBox->addItem(tr("Greek"), LetterConverter::Greek);
    ui->sourceComboBox->addItem(tr("Georgian"), LetterConverter::Georgian); //新增格鲁吉亚文
    ui->sourceComboBox->addItem(tr("Runic"), LetterConverter::Runic);
    ui->sourceComboBox->addItem(tr("Armenian"), LetterConverter::Armenian); // 新增：亚美尼亚字母
    ui->sourceComboBox->addItem(tr("Tibetan"), LetterConverter::Tibetan);
    ui->sourceComboBox->addItem(tr("Devanagari"), LetterConverter::Devanagari);
    ui->sourceComboBox->addItem(tr("Bengali"), LetterConverter::Bengali); // 新增：孟加拉字母
    ui->sourceComboBox->addItem(tr("Thai"), LetterConverter::Thai); // 新增：泰语字母
    ui->sourceComboBox->addItem(tr("Khmer"), LetterConverter::Khmer);
    ui->sourceComboBox->addItem(tr("Syriac"), LetterConverter::Syriac);
    ui->sourceComboBox->addItem(tr("Arabic"), LetterConverter::Arabic);
    ui->sourceComboBox->addItem(tr("Uyghur"), LetterConverter::Uyghur);
    ui->sourceComboBox->addItem(tr("Persian"), LetterConverter::Persian);
    ui->sourceComboBox->addItem(tr("Kurdish"), LetterConverter::Kurdish); // 新增：库尔德文
    ui->sourceComboBox->addItem(tr("Pashto"), LetterConverter::Pashto); // 新增：普什图文
    ui->sourceComboBox->addItem(tr("Ottoman"), LetterConverter::Ottoman); // 新增：奥斯曼文
    ui->sourceComboBox->addItem(tr("Hebrew"), LetterConverter::Hebrew);
    ui->sourceComboBox->addItem(tr("Geez"), LetterConverter::Geez); // 新增：吉兹字母
    ui->sourceComboBox->addItem(tr("Hangul"), LetterConverter::Hangul);
    ui->sourceComboBox->addItem(tr("Kana"), LetterConverter::Kana);
    ui->sourceComboBox->addItem(tr("Zhuyin"), LetterConverter::Zhuyin);



    

    

    // 目标下拉框使用相同选项
    for (int i = 0; i < ui->sourceComboBox->count(); i++) {
        ui->targetComboBox->addItem(
            ui->sourceComboBox->itemText(i),
            ui->sourceComboBox->itemData(i)
            );
    }

    // 设置默认值：从拉丁文转换为西里尔文
    ui->sourceComboBox->setCurrentIndex(0); // Latin
    ui->targetComboBox->setCurrentIndex(1); // Cyrillic
}

void MainWindow::retranslateUi()
{
    // 更新标签文本
    ui->label->setText(tr("Enter text:"));
    ui->label_2->setText(tr("Convert from:"));
    ui->label_3->setText(tr("Result:"));
    ui->label_4->setText(tr("to"));
    ui->convertButton->setText(tr("Convert"));

    ui->menuLanguage_2->setTitle(tr("Language"));

    // 重新填充下拉框以更新翻译
    populateAlphabetComboBoxes();
}

void MainWindow::switchLanguage(const QString &language)
{
    static QTranslator translator;
    // 移除之前的翻译器
    qApp->removeTranslator(&translator);

    // 根据语言加载对应的翻译文件
    if (language == "zh_CN") {
        translator.load("Babel_zh_CN.qm", qApp->applicationDirPath());
        QLocale::setDefault(QLocale(QLocale::Chinese, QLocale::China));
    } else if (language == "ru_RU") {
        translator.load("Babel_ru_RU.qm", qApp->applicationDirPath());
        QLocale::setDefault(QLocale(QLocale::Russian, QLocale::Russia));
    } 
    else if (language == "ar_SA") { // 添加阿拉伯语支持
        translator.load("Babel_ar_SA.qm", qApp->applicationDirPath());
        QLocale::setDefault(QLocale(QLocale::Arabic, QLocale::SaudiArabia));
    } else if (language == "es_ES") { // 添加西班牙语支持
        translator.load("Babel_es_ES.qm", qApp->applicationDirPath());
        QLocale::setDefault(QLocale(QLocale::Spanish, QLocale::Spain));
    } else {
        translator.load("Babel_en_US.qm", qApp->applicationDirPath());
        QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
    }

    // 保存语言设置到配置文件
    QSettings settings("Babel.ini", QSettings::IniFormat);
    settings.setValue("Language", language);
    settings.sync(); // 确保立即写入文件

    // 安装新的翻译器
    qApp->installTranslator(&translator);

    // 更新UI
    ui->retranslateUi(this);
    populateAlphabetComboBoxes();
}

void MainWindow::onConvertClicked()
{
    QString inputText = ui->inputEdit->toPlainText();

    // 获取源系统和目标系统
    LetterConverter::AlphabetSystem source = static_cast<LetterConverter::AlphabetSystem>(
        ui->sourceComboBox->currentData().toInt());

    LetterConverter::AlphabetSystem target = static_cast<LetterConverter::AlphabetSystem>(
        ui->targetComboBox->currentData().toInt());

    // 如果源和目标相同，直接返回输入文本
    if (source == target) {
        ui->outputEdit->setPlainText(inputText);
        return;
    }

    // 拉丁文到目标系统
    if (source == LetterConverter::Latin) {
        QString convertedText = converter.convertText(inputText, target);
        ui->outputEdit->setPlainText(convertedText);
    }
    // 目标系统到拉丁文
    else if (target == LetterConverter::Latin) {
        QString convertedText = converter.convertText(inputText, source, LetterConverter::TargetToLatin);
        ui->outputEdit->setPlainText(convertedText);
    }
    // 非拉丁系统之间转换：先转换为拉丁文，再转换为目标系统
    else {
        QString intermediate = converter.convertText(inputText, source, LetterConverter::TargetToLatin);
        QString convertedText = converter.convertText(intermediate, target);
        ui->outputEdit->setPlainText(convertedText);
    }
}

MainWindow::~MainWindow()
{
    // 确保在删除UI之前，先删除对话框
    if (phoneticChartDialog) {
        delete phoneticChartDialog;
        phoneticChartDialog = nullptr;
    }
    delete ui;
}

void MainWindow::onAboutClicked()
{
    AboutDialog aboutDialog(this);
    aboutDialog.exec();
}

void MainWindow::onPhoneticChartClicked()
{
    // 如果对话框已经存在且有效，直接显示它
    if (phoneticChartDialog) {
        phoneticChartDialog->show();
        phoneticChartDialog->raise();
        phoneticChartDialog->activateWindow();
        return;
    }

    // 创建新的对话框
    phoneticChartDialog = new PhoneticChartDialog(this);
    // 设置对话框在关闭时隐藏而不是删除
    phoneticChartDialog->setAttribute(Qt::WA_DeleteOnClose, false);
    // 显示对话框
    phoneticChartDialog->show();
}

void MainWindow::onTheUserWWClicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/TheUserWW"));
}
