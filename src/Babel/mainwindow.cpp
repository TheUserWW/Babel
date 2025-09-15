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
#include <QStandardPaths> // 添加QStandardPaths头文件
#include <QDir>
#include "aboutdialog.h"
#include "phoneticchartdialog.h" // 添加头文件
#include <QFontDatabase>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    phoneticChartDialog(nullptr)
{
    ui->setupUi(this);
    
    // 设置支持广泛Unicode字符的字体
    QFont unicodeFont;
    
    // 尝试按优先级设置字体，添加蒙文和满文字体
    QStringList fontFamilies = {
        "Noto Sans Mongolian",  // 蒙文字体
        "Noto Sans Manchu",     // 满文字体
        "Mongolian Baiti",      // 另一种蒙文字体
        "Noto Sans",            // 通用Unicode字体
        "Segoe UI Historic",    // Windows上的备选
        "Wreathe Unicode",      // 另一个广泛Unicode字体
        "Arial Unicode MS",     // 跨平台备选
        "Code2000",            // 另一个Unicode字体
        "FreeSerif"            // Linux上的备选
    };
    
    // 检查系统中可用的字体
    QFontDatabase fontDb;
    bool fontFound = false;
    
    for (const QString &family : fontFamilies) {
        if (fontDb.families().contains(family)) {
            unicodeFont = QFont(family, 10);
            fontFound = true;
            break;
        }
    }
    
    // 如果没有找到专门的Unicode字体，使用系统默认字体
    if (!fontFound) {
        unicodeFont = QFontDatabase::systemFont(QFontDatabase::GeneralFont);
    }
    
    // 应用字体到输入和输出框
    ui->inputEdit->setFont(unicodeFont);
    ui->outputEdit->setFont(unicodeFont);
    
    // 为QTextEdit设置额外的属性以改善蒙文和满文显示
    ui->outputEdit->setAcceptRichText(true);
    ui->outputEdit->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    
    // 尝试设置文本方向（可能需要根据蒙文和满文的特性调整）
    ui->outputEdit->setLayoutDirection(Qt::LeftToRight);
    
    // 添加语言切换动作组
    QActionGroup *languageGroup = new QActionGroup(this);
    languageGroup->addAction(ui->action);      // 简体中文
    languageGroup->addAction(ui->actionEnglish); // English
    languageGroup->addAction(ui->actionRussian); // Русский
    languageGroup->addAction(ui->actionArabic); // العربية
    languageGroup->addAction(ui->actionSpanish); // Español
    languageGroup->setExclusive(true);

    // 读取保存的语言偏好
    QString configPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QDir().mkpath(configPath);
    QString iniFilePath = configPath + "/Babel.ini";
    QSettings settings(iniFilePath, QSettings::IniFormat);
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
    ui->sourceComboBox->addItem(tr("OldItalic"), LetterConverter::OldItalic);
    ui->sourceComboBox->addItem(tr("Georgian"), LetterConverter::Georgian);
    ui->sourceComboBox->addItem(tr("Runic"), LetterConverter::Runic);
    ui->sourceComboBox->addItem(tr("Trad Hungarian"),LetterConverter::TraditionalHungarian);
    ui->sourceComboBox->addItem(tr("Armenian"), LetterConverter::Armenian); 
    ui->sourceComboBox->addItem(tr("Tibetan"), LetterConverter::Tibetan);
    ui->sourceComboBox->addItem(tr("Devanagari"), LetterConverter::Devanagari);
    ui->sourceComboBox->addItem(tr("Bengali"), LetterConverter::Bengali);
    ui->sourceComboBox->addItem(tr("Assamese"), LetterConverter::Assamese);
    ui->sourceComboBox->addItem(tr("Tamil"), LetterConverter::Tamil);
    ui->sourceComboBox->addItem(tr("Telugu"), LetterConverter::Telugu);
    ui->sourceComboBox->addItem(tr("Kannada"), LetterConverter::Kannada);
    ui->sourceComboBox->addItem(tr("Thai"), LetterConverter::Thai);
    ui->sourceComboBox->addItem(tr("Khmer"), LetterConverter::Khmer);
    ui->sourceComboBox->addItem(tr("Phoenician"), LetterConverter::Phoenician);
    ui->sourceComboBox->addItem(tr("OldSouthArabian"), LetterConverter::OldSouthArabian);
    ui->sourceComboBox->addItem(tr("OldNorthArabian"), LetterConverter::OldNorthArabian);
    ui->sourceComboBox->addItem(tr("MeroiticHieroglyphs"), LetterConverter::MeroiticHieroglyphs);
    ui->sourceComboBox->addItem(tr("Syriac"), LetterConverter::Syriac);
    ui->sourceComboBox->addItem(tr("Arabic"), LetterConverter::Arabic);
    ui->sourceComboBox->addItem(tr("Full Arabic"), LetterConverter::FullArabic);
    ui->sourceComboBox->addItem(tr("Uyghur"), LetterConverter::Uyghur);
    ui->sourceComboBox->addItem(tr("Persian"), LetterConverter::Persian);
    ui->sourceComboBox->addItem(tr("Kurdish"), LetterConverter::Kurdish); 
    ui->sourceComboBox->addItem(tr("Pashto"), LetterConverter::Pashto); 
    ui->sourceComboBox->addItem(tr("Ottoman"), LetterConverter::Ottoman); 
    ui->sourceComboBox->addItem(tr("Hebrew"), LetterConverter::Hebrew);
    ui->sourceComboBox->addItem(tr("Geez"), LetterConverter::Geez); 
    ui->sourceComboBox->addItem(tr("OldTurkic"), LetterConverter::OldTurkic);
    ui->sourceComboBox->addItem(tr("OldUyghur"), LetterConverter::OldUyghur);
    ui->sourceComboBox->addItem(tr("Sogdian"), LetterConverter::Sogdian);
    ui->sourceComboBox->addItem(tr("Hangul"), LetterConverter::Hangul);
    ui->sourceComboBox->addItem(tr("Kana"), LetterConverter::Kana);
    ui->sourceComboBox->addItem(tr("Zhuyin"), LetterConverter::Zhuyin);
    ui->sourceComboBox->addItem(tr("Manchu"), LetterConverter::Manchu);
    ui->sourceComboBox->addItem(tr("Inuktitut"), LetterConverter::Inuktitut);
    ui->sourceComboBox->addItem(tr("OldPersian"), LetterConverter::OldPersian);
    



    

    

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
    QString configPath = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QDir().mkpath(configPath);
    QString iniFilePath = configPath + "/Babel.ini";
    QSettings settings(iniFilePath, QSettings::IniFormat);
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
        
        // 对于蒙文、满文、传统匈牙利文、粟特文和麦罗埃文圣书体，尝试使用HTML格式以获得更好的显示效果
        if (target == LetterConverter::Manchu) {
            // 满文使用专门字体
            QString htmlText = "<div style='font-family: \"Noto Sans Manchu\", \"Mongolian Baiti\", \"Noto Sans Mongolian\", \"Segoe UI Historic\", \"Arial Unicode MS\", \"Code2000\", sans-serif;'>" + convertedText + "</div>";
            ui->outputEdit->setHtml(htmlText);
        } else if (target == LetterConverter::OldUyghur) {
            // 蒙文使用专门字体
            QString htmlText = "<div style='font-family: \"Noto Sans Mongolian\", \"Mongolian Baiti\", \"Segoe UI Historic\", \"Arial Unicode MS\", \"Code2000\", sans-serif;'>" + convertedText + "</div>";
            ui->outputEdit->setHtml(htmlText);
        } else if (target == LetterConverter::TraditionalHungarian || target == LetterConverter::Sogdian) {
            // 传统匈牙利文和粟特文使用原有字体
            QString htmlText = "<div style='font-family: \"Noto Sans Old Hungarian\", \"Segoe UI Historic\", \"Arial Unicode MS\", \"Code2000\", \"Noto Sans Sogdian\", sans-serif;'>" + convertedText + "</div>";
            ui->outputEdit->setHtml(htmlText);
        } else if (target == LetterConverter::MeroiticHieroglyphs) {
            // 麦罗埃文圣书体使用专门字体
            QString htmlText = "<div style='font-family: \"Noto Sans Meroitic\", \"Segoe UI Historic\", \"Arial Unicode MS\", \"Code2000\", \"FreeSerif\", sans-serif; font-size: 16pt;'>" + convertedText + "</div>";
            ui->outputEdit->setHtml(htmlText);
        } else if(target == LetterConverter::Sogdian)
        {
            QString htmlText = "<div style='font-family: \"Noto Sans Sogdian\", \"Segoe UI Historic\", \"Arial Unicode MS\", \"Code2000\", sans-serif;'>" + convertedText + "</div>";
            ui->outputEdit->setHtml(htmlText);
        }
        else {
            ui->outputEdit->setPlainText(convertedText);
        }
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
        
        // 对于蒙文、满文、传统匈牙利文、粟特文和麦罗埃文圣书体，尝试使用HTML格式以获得更好的显示效果
        if (target == LetterConverter::Manchu) {
            // 满文使用专门字体
            QString htmlText = "<div style='font-family: \"Noto Sans Manchu\", \"Mongolian Baiti\", \"Noto Sans Mongolian\", \"Segoe UI Historic\", \"Arial Unicode MS\", \"Code2000\", sans-serif;'>" + convertedText + "</div>";
            ui->outputEdit->setHtml(htmlText);
        } else if (target == LetterConverter::OldUyghur) {
            // 蒙文使用专门字体
            QString htmlText = "<div style='font-family: \"Noto Sans Mongolian\", \"Mongolian Baiti\", \"Segoe UI Historic\", \"Arial Unicode MS\", \"Code2000\", sans-serif;'>" + convertedText + "</div>";
            ui->outputEdit->setHtml(htmlText);
        } else if (target == LetterConverter::TraditionalHungarian || target == LetterConverter::Sogdian) {
            // 传统匈牙利文和粟特文使用原有字体
            QString htmlText = "<div style='font-family: \"Noto Sans Old Hungarian\", \"Segoe UI Historic\", \"Arial Unicode MS\", \"Code2000\", \"Noto Sans Sogdian\", sans-serif;'>" + convertedText + "</div>";
            ui->outputEdit->setHtml(htmlText);
        } else if (target == LetterConverter::MeroiticHieroglyphs) {
            // 麦罗埃文圣书体使用专门字体
            QString htmlText = "<div style='font-family: \"Noto Sans Meroitic\", \"Segoe UI Historic\", \"Arial Unicode MS\", \"Code2000\", \"FreeSerif\", sans-serif; font-size: 16pt;'>" + convertedText + "</div>";
            ui->outputEdit->setHtml(htmlText);
        } else {
            ui->outputEdit->setPlainText(convertedText);
        }
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

    try {
        // 创建新的对话框
        phoneticChartDialog = new PhoneticChartDialog(this);
        // 设置对话框在关闭时隐藏而不是删除
        phoneticChartDialog->setAttribute(Qt::WA_DeleteOnClose, false);
        // 显示对话框
        phoneticChartDialog->show();
    } catch (const std::exception& e) {
        // 如果创建对话框时发生异常，显示错误信息
        qCritical() << "Failed to create PhoneticChartDialog:" << e.what();
        // 确保指针为空，避免后续操作出错
        phoneticChartDialog = nullptr;
    } catch (...) {
        // 捕获其他未知异常
        qCritical() << "Unknown error occurred while creating PhoneticChartDialog";
        // 确保指针为空，避免后续操作出错
        phoneticChartDialog = nullptr;
    }
}

void MainWindow::onTheUserWWClicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/TheUserWW"));
}
