#include "phoneticchartdialog.h"
#include "ui_phoneticchartdialog.h"
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QScrollArea>

PhoneticChartDialog::PhoneticChartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PhoneticChartDialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // 设置窗口标题
    setWindowTitle(tr("Phonetic Chart"));

    // 初始化音标表
    setupPhoneticCharts();
}

PhoneticChartDialog::~PhoneticChartDialog()
{
    // 直接删除UI，Qt会自动清理所有子控件
    delete ui;
    ui = nullptr;
}


void PhoneticChartDialog::setupPhoneticCharts()
{
    // 在初始化表格前，先清除可能存在的旧数据
    clearAllTables();
    
    setupLatinChart();
    setupCyrillicChart();
    setupGreekChart();
    setupKhmerChart();
    setupSyriacChart();
    setupTibetanChart();
    setupDevanagariChart();
    setupHebrewChart();
    setupRunicChart();
    setupHangulChart();
    setupKanaChart();
    setupZhuyinChart();
    setupArabicChart();
    setupUyghurChart();
    setupPersianChart();
    setupGeorgianChart();
    setupGeezChart();
    setupThaiChart();
    setupArmenianChart();
    setupBengaliChart();
}

void PhoneticChartDialog::clearAllTables()
{
    // 清除所有表格的内容
    QList<QTableWidget*> tables = {
        ui->latinTableWidget, ui->cyrillicTableWidget, ui->greekTableWidget,
        ui->khmerTableWidget, ui->syriacTableWidget, ui->tibetanTableWidget,
        ui->devanagariTableWidget, ui->hebrewTableWidget, ui->runicTableWidget,
        ui->hangulTableWidget, ui->kanaTableWidget, ui->zhuyinTableWidget,
        ui->arabicTableWidget, ui->uyghurTableWidget, ui->persianTableWidget,
        ui->georgianTableWidget, ui->geezTableWidget, ui->thaiTableWidget,
        ui->armenianTableWidget, ui->bengaliTableWidget
    };

    for (QTableWidget* table : tables) {
        if (table) {
            // 先清除所有内容
            table->clearContents();
            // 设置行数为0，这会删除所有QTableWidgetItem对象
            table->setRowCount(0);
        }
    }
}

void PhoneticChartDialog::setupLatinChart()
{
    ui->latinTableWidget->setRowCount(26);

    // 添加拉丁字母和对应的IPA
    QStringList letters = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
                           "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    QStringList ipa = {"/eɪ/", "/biː/", "/siː/", "/diː/", "/iː/", "/ɛf/", "/dʒiː/", "/eɪtʃ/", "/aɪ/", "/dʒeɪ/",
                       "/keɪ/", "/ɛl/", "/ɛm/", "/ɛn/", "/oʊ/", "/piː/", "/kjuː/", "/ɑːr/", "/ɛs/", "/tiː/",
                       "/juː/", "/viː/", "/dʌbəl.juː/", "/ɛks/", "/waɪ/", "/ziː/"};

    for (int i = 0; i < letters.size(); ++i) {
        QTableWidgetItem *letterItem = new QTableWidgetItem(letters[i]);
        QTableWidgetItem *ipaItem = new QTableWidgetItem(ipa[i]);

        // 设置字母项居中对齐
        letterItem->setTextAlignment(Qt::AlignCenter);
        // 设置字体大小
        QFont font = letterItem->font();
        font.setPointSize(16);
        letterItem->setFont(font);

        // 设置表格项为只读
        letterItem->setFlags(letterItem->flags() & ~Qt::ItemIsEditable);
        ipaItem->setFlags(ipaItem->flags() & ~Qt::ItemIsEditable);

        ui->latinTableWidget->setItem(i, 0, letterItem);
        ui->latinTableWidget->setItem(i, 1, ipaItem);
    }

    // 调整列宽
    ui->latinTableWidget->resizeColumnsToContents();
}

void PhoneticChartDialog::setupCyrillicChart()
{
    ui->cyrillicTableWidget->setRowCount(33);

    // 添加西里尔字母和对应的IPA
    QStringList letters = {"А", "Б", "В", "Г", "Д", "Е", "Ё", "Ж", "З", "И", "Й", "К", "Л", "М", "Н",
                           "О", "П", "Р", "С", "Т", "У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь",
                           "Э", "Ю", "Я"};
    QStringList ipa = {"/a/", "/b/", "/v/", "/ɡ/", "/d/", "/je/", "/jo/", "/ʐ/", "/z/", "/i/", "/j/", "/k/", "/l/", "/m/", "/n/",
                       "/o/", "/p/", "/r/", "/s/", "/t/", "/u/", "/f/", "/x/", "/ts/", "/tɕ/", "/ʂ/", "/ɕː/", "/–/",
                       "/ɨ/", "/ʲ/", "/e/", "/ju/", "/ja/"};

    for (int i = 0; i < letters.size(); ++i) {
        QTableWidgetItem *letterItem = new QTableWidgetItem(letters[i]);
        QTableWidgetItem *ipaItem = new QTableWidgetItem(ipa[i]);

        // 设置字母项居中对齐
        letterItem->setTextAlignment(Qt::AlignCenter);
        // 设置字体大小
        QFont font = letterItem->font();
        font.setPointSize(16);
        letterItem->setFont(font);
        letterItem->setFlags(letterItem->flags() & ~Qt::ItemIsEditable);
        ipaItem->setFlags(ipaItem->flags() & ~Qt::ItemIsEditable);
        ui->cyrillicTableWidget->setItem(i, 0, letterItem);
        ui->cyrillicTableWidget->setItem(i, 1, ipaItem);
    }

    // 调整列宽
    ui->cyrillicTableWidget->resizeColumnsToContents();
}

void PhoneticChartDialog::setupGreekChart()
{
    ui->greekTableWidget->setRowCount(24);

    // 添加希腊字母和对应的IPA
    QStringList letters = {"Α", "Β", "Γ", "Δ", "Ε", "Ζ", "Η", "Θ", "Ι", "Κ", "Λ", "Μ", "Ν",
                           "Ξ", "Ο", "Π", "Ρ", "Σ", "Τ", "Υ", "Φ", "Χ", "Ψ", "Ω"};
    QStringList ipa = {"/a/", "/v/", "/ɣ/", "/ð/", "/e/", "/z/", "/i/", "/θ/", "/i/", "/k/", "/l/", "/m/", "/n/",
                       "/ks/", "/o/", "/p/", "/r/", "/s/", "/t/", "/i/", "/f/", "/x/", "/ps/", "/o/"};

    for (int i = 0; i < letters.size(); ++i) {
        QTableWidgetItem *letterItem = new QTableWidgetItem(letters[i]);
        QTableWidgetItem *ipaItem = new QTableWidgetItem(ipa[i]);

        // 设置字母项居中对齐
        letterItem->setTextAlignment(Qt::AlignCenter);
        // 设置字体大小
        QFont font = letterItem->font();
        font.setPointSize(16);
        letterItem->setFont(font);
        letterItem->setFlags(letterItem->flags() & ~Qt::ItemIsEditable);
        ipaItem->setFlags(ipaItem->flags() & ~Qt::ItemIsEditable);
        ui->greekTableWidget->setItem(i, 0, letterItem);
        ui->greekTableWidget->setItem(i, 1, ipaItem);
    }

    // 调整列宽
    ui->greekTableWidget->resizeColumnsToContents();
}

void PhoneticChartDialog::setupKhmerChart()
{
    ui->khmerTableWidget->setRowCount(33);

    // 添加高棉字母和对应的IPA
    QStringList letters = {"ក", "ខ", "គ", "ឃ", "ង", "ច", "ឆ", "ជ", "ឈ", "ញ", "ដ", "ឋ", "ឌ", "ឍ", "ណ",
                           "ត", "ថ", "ទ", "ធ", "ន", "ប", "ផ", "ព", "ភ", "ម", "យ", "រ", "ល", "វ", "ស",
                           "ហ", "ឡ", "អ"};
    QStringList ipa = {"/kɑ/", "/kʰɑ/", "/kɑ/", "/kʰɑ/", "/ŋɑ/", "/cɑ/", "/cʰɑ/", "/cɑ/", "/cʰɑ/", "/ɲɑ/", "/ɗɑ/",
                       "/tʰɑ/", "/ɗɑ/", "/tʰɑ/", "/ɗɑ/", "/tɑ/", "/tʰɑ/", "/tɑ/", "/tʰɑ/", "/nɑ/", "/bɑ/",
                       "/pʰɑ/", "/bɑ/", "/pʰɑ/", "/mɑ/", "/jɑ/", "/rɑ/", "/lɑ/", "/ʋɑ/", "/sɑ/", "/hɑ/",
                       "/lɑ/", "/ʔɑ/"};

    for (int i = 0; i < letters.size(); ++i) {
        QTableWidgetItem *letterItem = new QTableWidgetItem(letters[i]);
        QTableWidgetItem *ipaItem = new QTableWidgetItem(ipa[i]);

        // 设置字母项居中对齐
        letterItem->setTextAlignment(Qt::AlignCenter);
        // 设置字体大小
        QFont font = letterItem->font();
        font.setPointSize(16);
        letterItem->setFont(font);
        letterItem->setFlags(letterItem->flags() & ~Qt::ItemIsEditable);
        ipaItem->setFlags(ipaItem->flags() & ~Qt::ItemIsEditable);
        ui->khmerTableWidget->setItem(i, 0, letterItem);
        ui->khmerTableWidget->setItem(i, 1, ipaItem);
    }

    // 调整列宽
    ui->khmerTableWidget->resizeColumnsToContents();
}

void PhoneticChartDialog::setupSyriacChart()
{
    ui->syriacTableWidget->setRowCount(22);

    // 添加叙利亚字母和对应的IPA
    QStringList letters = {"ܐ", "ܒ", "ܓ", "ܕ", "ܗ", "ܘ", "ܙ", "ܚ", "ܛ", "ܝ", "ܟ", "ܠ", "ܡ", "ܢ", "ܣ",
                           "ܥ", "ܦ", "ܨ", "ܩ", "ܪ", "ܫ", "ܬ"};
    QStringList ipa = {"/ʔ/", "/b/", "/ɡ/", "/d/", "/h/", "/w/", "/z/", "/ħ/", "/tˤ/", "/j/", "/k/", "/l/", "/m/", "/n/",
                       "/s/", "/ʕ/", "/f/", "/sˤ/", "/q/", "/r/", "/ʃ/", "/t/"};

    for (int i = 0; i < letters.size(); ++i) {
        QTableWidgetItem *letterItem = new QTableWidgetItem(letters[i]);
        QTableWidgetItem *ipaItem = new QTableWidgetItem(ipa[i]);

        // 设置字母项居中对齐
        letterItem->setTextAlignment(Qt::AlignCenter);
        // 设置字体大小
        QFont font = letterItem->font();
        font.setPointSize(16);
        letterItem->setFont(font);
        letterItem->setFlags(letterItem->flags() & ~Qt::ItemIsEditable);
        ipaItem->setFlags(ipaItem->flags() & ~Qt::ItemIsEditable);
        ui->syriacTableWidget->setItem(i, 0, letterItem);
        ui->syriacTableWidget->setItem(i, 1, ipaItem);
    }

    // 调整列宽
    ui->syriacTableWidget->resizeColumnsToContents();
}

void PhoneticChartDialog::setupTibetanChart()
{
    ui->tibetanTableWidget->setRowCount(30);

    // 添加藏文字母和对应的IPA
    QStringList letters = {"ཀ", "ཁ", "ག", "ང", "ཅ", "ཆ", "ཇ", "ཉ", "ཏ", "ཐ", "ད", "ན", "པ", "ཕ", "བ",
                           "མ", "ཙ", "ཚ", "ཛ", "ཝ", "ཞ", "ཟ", "འ", "ཡ", "ར", "ལ", "ཤ", "ས", "ཧ", "ཨ"};
    QStringList ipa = {"/k/", "/kʰ/", "/ɡ/", "/ŋ/", "/tɕ/", "/tɕʰ/", "/dʑ/", "/ɲ/", "/t/", "/tʰ/", "/d/", "/n/",
                       "/p/", "/pʰ/", "/b/", "/m/", "/ts/", "/tsʰ/", "/dz/", "/w/", "/ʑ/", "/z/", "/ʔ/", "/j/",
                       "/r/", "/l/", "/ɕ/", "/s/", "/h/", "/ʔ/"};

    for (int i = 0; i < letters.size(); ++i) {
        QTableWidgetItem *letterItem = new QTableWidgetItem(letters[i]);
        QTableWidgetItem *ipaItem = new QTableWidgetItem(ipa[i]);

        // 设置字母项居中对齐
        letterItem->setTextAlignment(Qt::AlignCenter);
        // 设置字体大小
        QFont font = letterItem->font();
        font.setPointSize(16);
        letterItem->setFont(font);
        letterItem->setFlags(letterItem->flags() & ~Qt::ItemIsEditable);
        ipaItem->setFlags(ipaItem->flags() & ~Qt::ItemIsEditable);
        ui->tibetanTableWidget->setItem(i, 0, letterItem);
        ui->tibetanTableWidget->setItem(i, 1, ipaItem);
    }

    // 调整列宽
    ui->tibetanTableWidget->resizeColumnsToContents();
}

void PhoneticChartDialog::setupDevanagariChart()
{
    ui->devanagariTableWidget->setRowCount(36);

    // 添加天城体字母和对应的IPA
    QStringList letters = {"अ", "आ", "इ", "ई", "उ", "ऊ", "ऋ", "ॠ", "ऌ", "ॡ", "ए", "ऐ", "ओ", "औ", "अं", "अः",
                           "क", "ख", "ग", "घ", "ङ", "च", "छ", "ज", "झ", "ञ", "ट", "ठ", "ड", "ढ", "ण",
                           "त", "थ", "द", "ध", "न", "प"};
    QStringList ipa = {"/ə/", "/ɑː/", "/i/", "/iː/", "/u/", "/uː/", "/rɪ/", "/r̩ː/", "/lɪ/", "/l̩ː/", "/eː/",
                       "/əi̯/", "/oː/", "/əu̯/", "/ə̃/", "/əh/", "/k/", "/kʰ/", "/ɡ/", "/ɡʱ/", "/ŋ/", "/tɕ/",
                       "/tɕʰ/", "/dʑ/", "/dʑʱ/", "/ɲ/", "/ʈ/", "/ʈʰ/", "/ɖ/", "/ɖʱ/", "/ɳ/", "/t̪/",
                       "/t̪ʰ/", "/d̪/", "/d̪ʱ/", "/n̪/", "/p/"};

    for (int i = 0; i < letters.size(); ++i) {
        QTableWidgetItem *letterItem = new QTableWidgetItem(letters[i]);
        QTableWidgetItem *ipaItem = new QTableWidgetItem(ipa[i]);

        // 设置字母项居中对齐
        letterItem->setTextAlignment(Qt::AlignCenter);
        // 设置字体大小
        QFont font = letterItem->font();
        font.setPointSize(16);
        letterItem->setFont(font);
        letterItem->setFlags(letterItem->flags() & ~Qt::ItemIsEditable);
        ipaItem->setFlags(ipaItem->flags() & ~Qt::ItemIsEditable);
        ui->devanagariTableWidget->setItem(i, 0, letterItem);
        ui->devanagariTableWidget->setItem(i, 1, ipaItem);
    }

    // 调整列宽
    ui->devanagariTableWidget->resizeColumnsToContents();
}

void PhoneticChartDialog::setupHebrewChart()
{
    ui->hebrewTableWidget->setRowCount(22);

    // 添加希伯来字母和对应的IPA
    QStringList letters = {"א", "ב", "ג", "ד", "ה", "ו", "ז", "ח", "ט", "י", "כ", "ל", "מ", "נ", "ס",
                           "ע", "פ", "צ", "ק", "ר", "ש", "ת"};
    QStringList ipa = {"/ʔ/", "/b, v/", "/ɡ/", "/d/", "/h/", "/v/", "/z/", "/χ, ħ/", "/t/", "/j/", "/k, x/",
                       "/l/", "/m/", "/n/", "/s/", "/ʕ/", "/p, f/", "/ts/", "/k/", "/ʁ/", "/ʃ, s/", "/t/"};

    for (int i = 0; i < letters.size(); ++i) {
        QTableWidgetItem *letterItem = new QTableWidgetItem(letters[i]);
        QTableWidgetItem *ipaItem = new QTableWidgetItem(ipa[i]);

        // 设置字母项居中对齐
        letterItem->setTextAlignment(Qt::AlignCenter);
        // 设置字体大小
        QFont font = letterItem->font();
        font.setPointSize(16);
        letterItem->setFont(font);
        letterItem->setFlags(letterItem->flags() & ~Qt::ItemIsEditable);
        ipaItem->setFlags(ipaItem->flags() & ~Qt::ItemIsEditable);
        ui->hebrewTableWidget->setItem(i, 0, letterItem);
        ui->hebrewTableWidget->setItem(i, 1, ipaItem);
    }

    // 调整列宽
    ui->hebrewTableWidget->resizeColumnsToContents();
}

void PhoneticChartDialog::setupRunicChart()
{
    ui->runicTableWidget->setRowCount(24);

    // 添加卢恩字母和对应的IPA
    QStringList letters = {"ᚠ", "ᚢ", "ᚦ", "ᚨ", "ᚱ", "ᚲ", "ᚷ", "ᚹ", "ᚺ", "ᚾ", "ᛁ", "ᛃ", "ᛇ", "ᛈ", "ᛉ",
                           "ᛊ", "ᛏ", "ᛒ", "ᛖ", "ᛗ", "ᛚ", "ᛜ", "ᛞ", "ᛟ"};
    QStringList ipa = {"/f/", "/u/", "/θ, ð/", "/a/", "/r/", "/k/", "/ɡ/", "/w/", "/h/", "/n/", "/i/", "/j/",
                       "/ei̯/", "/p/", "/z/", "/s/", "/t/", "/b/", "/e/", "/m/", "/l/", "/ŋ/", "/d/", "/o/"};

    for (int i = 0; i < letters.size(); ++i) {
        QTableWidgetItem *letterItem = new QTableWidgetItem(letters[i]);
        QTableWidgetItem *ipaItem = new QTableWidgetItem(ipa[i]);

        // 设置字母项居中对齐
        letterItem->setTextAlignment(Qt::AlignCenter);
        // 设置字体大小
        QFont font = letterItem->font();
        font.setPointSize(16);
        letterItem->setFont(font);
        letterItem->setFlags(letterItem->flags() & ~Qt::ItemIsEditable);
        ipaItem->setFlags(ipaItem->flags() & ~Qt::ItemIsEditable);
        ui->runicTableWidget->setItem(i, 0, letterItem);
        ui->runicTableWidget->setItem(i, 1, ipaItem);
    }

    // 调整列宽
    ui->runicTableWidget->resizeColumnsToContents();
}

void PhoneticChartDialog::setupHangulChart()
{
    ui->hangulTableWidget->setRowCount(24);

    // 添加谚文字母和对应的IPA
    QStringList letters = {"ㄱ", "ㄲ", "ㄴ", "ㄷ", "ㄸ", "ㄹ", "ㅁ", "ㅂ", "ㅃ", "ㅅ", "ㅆ", "ㅇ", "ㅈ", "ㅉ",
                           "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ", "ㅏ", "ㅑ", "ㅓ", "ㅕ", "ㅗ"};
    QStringList ipa = {"/k/", "/k͈/", "/n/", "/t/", "/t͈/", "/l, ɾ/", "/m/", "/p/", "/p͈/", "/s/", "/s͈/",
                       "/ŋ, ʔ/", "/tɕ/", "/tɕ͈/", "/tɕʰ/", "/kʰ/", "/tʰ/", "/pʰ/", "/h/", "/a/", "/ja/",
                       "/ʌ/", "/jʌ/", "/o/"};

    for (int i = 0; i < letters.size(); ++i) {
        QTableWidgetItem *letterItem = new QTableWidgetItem(letters[i]);
        QTableWidgetItem *ipaItem = new QTableWidgetItem(ipa[i]);

        // 设置字母项居中对齐
        letterItem->setTextAlignment(Qt::AlignCenter);
        // 设置字体大小
        QFont font = letterItem->font();
        font.setPointSize(16);
        letterItem->setFont(font);
        letterItem->setFlags(letterItem->flags() & ~Qt::ItemIsEditable);
        ipaItem->setFlags(ipaItem->flags() & ~Qt::ItemIsEditable);
        ui->hangulTableWidget->setItem(i, 0, letterItem);
        ui->hangulTableWidget->setItem(i, 1, ipaItem);
    }

    // 调整列宽
    ui->hangulTableWidget->resizeColumnsToContents();
}

void PhoneticChartDialog::setupKanaChart()
{
    ui->kanaTableWidget->setRowCount(46);

    // 添加假名字母和对应的IPA
    QStringList letters = {"あ", "い", "う", "え", "お", "か", "き", "く", "け", "こ", "さ", "し", "す", "せ", "そ",
                           "た", "ち", "つ", "て", "と", "な", "に", "ぬ", "ね", "の", "は", "ひ", "ふ", "へ", "ほ",
                           "ま", "み", "む", "め", "も", "や", "ゆ", "よ", "ら", "り", "る", "れ", "ろ", "わ", "を", "ん"};
    QStringList ipa = {"/a/", "/i/", "/ɯᵝ/", "/e/", "/o/", "/ka/", "/kʲi/", "/kɯᵝ/", "/ke/", "/ko/", "/sa/",
                       "/ɕi/", "/sɯᵝ/", "/se/", "/so/", "/ta/", "/tɕi/", "/tsɯᵝ/", "/te/", "/to/", "/na/",
                       "/nʲi/", "/nɯᵝ/", "/ne/", "/no/", "/ha/", "/çi/", "/ɸɯᵝ/", "/he/", "/ho/", "/ma/",
                       "/mʲi/", "/mɯᵝ/", "/me/", "/mo/", "/ja/", "/jɯᵝ/", "/jo/", "/ra/", "/rʲi/", "/rɯᵝ/",
                       "/re/", "/ro/", "/ɰa/", "/ɰo/", "/n/"};

    for (int i = 0; i < letters.size(); ++i) {
        QTableWidgetItem *letterItem = new QTableWidgetItem(letters[i]);
        QTableWidgetItem *ipaItem = new QTableWidgetItem(ipa[i]);

        // 设置字母项居中对齐
        letterItem->setTextAlignment(Qt::AlignCenter);
        // 设置字体大小
        QFont font = letterItem->font();
        font.setPointSize(16);
        letterItem->setFont(font);
        letterItem->setFlags(letterItem->flags() & ~Qt::ItemIsEditable);
        ipaItem->setFlags(ipaItem->flags() & ~Qt::ItemIsEditable);
        ui->kanaTableWidget->setItem(i, 0, letterItem);
        ui->kanaTableWidget->setItem(i, 1, ipaItem);
    }

    // 调整列宽
    ui->kanaTableWidget->resizeColumnsToContents();
}

void PhoneticChartDialog::setupZhuyinChart()
{
    ui->zhuyinTableWidget->setRowCount(37);

    // 添加注音符号和对应的IPA
    QStringList letters = {"ㄅ", "ㄆ", "ㄇ", "ㄈ", "ㄉ", "ㄊ", "ㄋ", "ㄌ", "ㄍ", "ㄎ", "ㄏ", "ㄐ", "ㄑ", "ㄒ", "ㄓ",
                           "ㄔ", "ㄕ", "ㄖ", "ㄗ", "ㄘ", "ㄙ", "ㄚ", "ㄛ", "ㄜ", "ㄝ", "ㄞ", "ㄟ", "ㄠ", "ㄡ", "ㄢ",
                           "ㄣ", "ㄤ", "ㄥ", "ㄦ", "ㄧ", "ㄨ", "ㄩ"};
    QStringList ipa = {"/p/", "/pʰ/", "/m/", "/f/", "/t/", "/tʰ/", "/n/", "/l/", "/k/", "/kʰ/", "/x/", "/tɕ/",
                       "/tɕʰ/", "/ɕ/", "/ʈʂ/", "/ʈʂʰ/", "/ʂ/", "/ʐ/", "/ts/", "/tsʰ/", "/s/", "/a/", "/o/",
                       "/ɤ/", "/ɛ/", "/ai/", "/ei/", "/au/", "/ou/", "/an/", "/ən/", "/aŋ/", "/əŋ/", "/ɚ/", "/i/",
                       "/u/", "/y/"};

    for (int i = 0; i < letters.size(); ++i) {
        QTableWidgetItem *letterItem = new QTableWidgetItem(letters[i]);
        QTableWidgetItem *ipaItem = new QTableWidgetItem(ipa[i]);

        // 设置字母项居中对齐
        letterItem->setTextAlignment(Qt::AlignCenter);
        // 设置字体大小
        QFont font = letterItem->font();
        font.setPointSize(16);
        letterItem->setFont(font);
        letterItem->setFlags(letterItem->flags() & ~Qt::ItemIsEditable);
        ipaItem->setFlags(ipaItem->flags() & ~Qt::ItemIsEditable);
        ui->zhuyinTableWidget->setItem(i, 0, letterItem);
        ui->zhuyinTableWidget->setItem(i, 1, ipaItem);
    }

    // 调整列宽
    ui->zhuyinTableWidget->resizeColumnsToContents();
}

void PhoneticChartDialog::setupArabicChart()
{
    ui->arabicTableWidget->setRowCount(28);

    // 添加阿拉伯字母和对应的IPA
    QStringList letters = {"ا", "ب", "ت", "ث", "ج", "ح", "خ", "د", "ذ", "ر", "ز", "س", "ش", "ص", "ض",
                           "ط", "ظ", "ع", "غ", "ف", "ق", "ك", "ل", "م", "ن", "ه", "و", "ي"};
    QStringList ipa = {"/ʔ/", "/b/", "/t/", "/θ/", "/dʒ/", "/ħ/", "/x/", "/d/", "/ð/", "/r/", "/z/", "/s/",
                       "/ʃ/", "/sˤ/", "/dˤ/", "/tˤ/", "/zˤ/", "/ʕ/", "/ɣ/", "/f/", "/q/", "/k/", "/l/", "/m/",
                       "/n/", "/h/", "/w/", "/j/"};

    for (int i = 0; i < letters.size(); ++i) {
        QTableWidgetItem *letterItem = new QTableWidgetItem(letters[i]);
        QTableWidgetItem *ipaItem = new QTableWidgetItem(ipa[i]);

        // 设置字母项居中对齐
        letterItem->setTextAlignment(Qt::AlignCenter);
        // 设置字体大小
        QFont font = letterItem->font();
        font.setPointSize(16);
        letterItem->setFont(font);
        letterItem->setFlags(letterItem->flags() & ~Qt::ItemIsEditable);
        ipaItem->setFlags(ipaItem->flags() & ~Qt::ItemIsEditable);
        ui->arabicTableWidget->setItem(i, 0, letterItem);
        ui->arabicTableWidget->setItem(i, 1, ipaItem);
    }

    // 调整列宽
    ui->arabicTableWidget->resizeColumnsToContents();
}

void PhoneticChartDialog::setupUyghurChart()
{
    ui->uyghurTableWidget->setRowCount(24);

    // 添加维吾尔文字母和对应的IPA
    QStringList letters = {"ا", "ە", "ب", "پ", "ت", "ج", "چ", "خ", "د", "ر", "ز", "ژ", "س", "ش", "غ",
                           "ف", "ق", "ك", "گ", "ڭ", "ل", "م", "ن", "ھ"};
    QStringList ipa = {"/ɑ/", "/ɛ/", "/b/", "/p/", "/t/", "/dʒ/", "/tʃ/", "/x/", "/d/", "/r/", "/z/", "/ʒ/", "/s/",
                       "/ʃ/", "/ʁ/", "/f/", "/q/", "/k/", "/ɡ/", "/ŋ/", "/l/", "/m/", "/n/", "/h/"};

    for (int i = 0; i < letters.size(); ++i) {
        QTableWidgetItem *letterItem = new QTableWidgetItem(letters[i]);
        QTableWidgetItem *ipaItem = new QTableWidgetItem(ipa[i]);

        // 设置字母项居中对齐
        letterItem->setTextAlignment(Qt::AlignCenter);
        // 设置字体大小
        QFont font = letterItem->font();
        font.setPointSize(16);
        letterItem->setFont(font);
        letterItem->setFlags(letterItem->flags() & ~Qt::ItemIsEditable);
        ipaItem->setFlags(ipaItem->flags() & ~Qt::ItemIsEditable);
        ui->uyghurTableWidget->setItem(i, 0, letterItem);
        ui->uyghurTableWidget->setItem(i, 1, ipaItem);
    }

    // 调整列宽
    ui->uyghurTableWidget->resizeColumnsToContents();
}

void PhoneticChartDialog::setupPersianChart()
{
    ui->persianTableWidget->setRowCount(32);

    // 添加波斯语字母和对应的IPA
    QStringList letters = {"ا", "ب", "پ", "ت", "ث", "ج", "چ", "ح", "خ", "د", "ذ", "ر", "ز", "ژ", "س",
                           "ش", "ص", "ض", "ط", "ظ", "ع", "غ", "ف", "ق", "ک", "گ", "ل", "م", "ن", "و",
                           "ه", "ی"};
    QStringList ipa = {"/ɒː, ʔ/", "/b/", "/p/", "/t/", "/s/", "/dʒ/", "/tʃ/", "/h/", "/x/", "/d/", "/z/",
                       "/r/", "/z/", "/ʒ/", "/s/", "/ʃ/", "/sˤ/", "/zˤ/", "/tˤ/", "/zˤ/", "/ʔ, ʕ/",
                       "/ɣ/", "/f/", "/ɢ/", "/k/", "/ɡ/", "/l/", "/m/", "/n/", "/v, uː/", "/h, e/",
                       "/j, iː/"};

    for (int i = 0; i < letters.size(); ++i) {
        QTableWidgetItem *letterItem = new QTableWidgetItem(letters[i]);
        QTableWidgetItem *ipaItem = new QTableWidgetItem(ipa[i]);

        // 设置字母项居中对齐
        letterItem->setTextAlignment(Qt::AlignCenter);
        // 设置字体大小
        QFont font = letterItem->font();
        font.setPointSize(16);
        letterItem->setFont(font);
        letterItem->setFlags(letterItem->flags() & ~Qt::ItemIsEditable);
        ipaItem->setFlags(ipaItem->flags() & ~Qt::ItemIsEditable);
        ui->persianTableWidget->setItem(i, 0, letterItem);
        ui->persianTableWidget->setItem(i, 1, ipaItem);
    }

    // 调整列宽
    ui->persianTableWidget->resizeColumnsToContents();
}

void PhoneticChartDialog::setupGeorgianChart()
{
    ui->georgianTableWidget->setRowCount(33);

    // 添加格鲁吉亚字母和对应的IPA
    QStringList letters = {"ა", "ბ", "გ", "დ", "ე", "ვ", "ზ", "თ", "ი", "კ", "ლ", "მ", "ნ", "ო", "პ",
                           "ჟ", "რ", "ს", "ტ", "უ", "ფ", "ქ", "ღ", "ყ", "შ", "ჩ", "ც", "ძ", "წ", "ჭ",
                           "ხ", "ჯ", "ჰ"};
    QStringList ipa = {"/ɑ/", "/b/", "/ɡ/", "/d/", "/ɛ/", "/v/", "/z/", "/tʰ/", "/i/", "/kʼ/", "/l/", "/m/",
                       "/n/", "/ɔ/", "/pʼ/", "/ʒ/", "/r/", "/s/", "/tʼ/", "/u/", "/pʰ/", "/kʰ/", "/ɣ/", "/qʼ/",
                       "/ʃ/", "/tɕʰ/", "/tsʰ/", "/dz/", "/tsʼ/", "/tɕʼ/", "/x/", "/dʒ/", "/h/"};

    for (int i = 0; i < letters.size(); ++i) {
        QTableWidgetItem *letterItem = new QTableWidgetItem(letters[i]);
        QTableWidgetItem *ipaItem = new QTableWidgetItem(ipa[i]);

        // 设置字母项居中对齐
        letterItem->setTextAlignment(Qt::AlignCenter);
        // 设置字体大小
        QFont font = letterItem->font();
        font.setPointSize(16);
        letterItem->setFont(font);
        letterItem->setFlags(letterItem->flags() & ~Qt::ItemIsEditable);
        ipaItem->setFlags(ipaItem->flags() & ~Qt::ItemIsEditable);
        ui->georgianTableWidget->setItem(i, 0, letterItem);
        ui->georgianTableWidget->setItem(i, 1, ipaItem);
    }

    // 调整列宽
    ui->georgianTableWidget->resizeColumnsToContents();
}

void PhoneticChartDialog::setupGeezChart()
{
    ui->geezTableWidget->setRowCount(26);

    // 添加吉兹字母和对应的IPA
    QStringList letters = {"ሀ", "ለ", "ሐ", "መ", "ሠ", "ረ", "ሰ", "ሸ", "ቀ", "በ", "ተ", "ኀ", "ነ", "አ", "ከ",
                           "ወ", "ዐ", "ዘ", "የ", "ደ", "ገ", "ጠ", "ጰ", "ጸ", "ፀ"};
    QStringList ipa = {"/h/", "/l/", "/ħ/", "/m/", "/s/", "/r/", "/s/", "/ʃ/", "/kʼ/", "/b/", "/t/", "/ħ/", "/n/",
                       "/ʔ/", "/k/", "/w/", "/ʔ/", "/z/", "/j/", "/d/", "/ɡ/", "/tʼ/", "/pʼ/", "/sʼ/", "/tʼ/"};

    for (int i = 0; i < letters.size(); ++i) {
        QTableWidgetItem *letterItem = new QTableWidgetItem(letters[i]);
        QTableWidgetItem *ipaItem = new QTableWidgetItem(ipa[i]);

        // 设置字母项居中对齐
        letterItem->setTextAlignment(Qt::AlignCenter);
        // 设置字体大小
        QFont font = letterItem->font();
        font.setPointSize(16);
        letterItem->setFont(font);
        letterItem->setFlags(letterItem->flags() & ~Qt::ItemIsEditable);
        ipaItem->setFlags(ipaItem->flags() & ~Qt::ItemIsEditable);
        ui->geezTableWidget->setItem(i, 0, letterItem);
        ui->geezTableWidget->setItem(i, 1, ipaItem);
    }

    // 调整列宽
    ui->geezTableWidget->resizeColumnsToContents();
}

void PhoneticChartDialog::setupThaiChart()
{
    ui->thaiTableWidget->setRowCount(44);

    // 添加泰文字母和对应的IPA
    QStringList letters = {"ก", "ข", "ฃ", "ค", "ฅ", "ฆ", "ง", "จ", "ฉ", "ช", "ซ", "ฌ", "ญ", "ฎ", "ฏ",
                           "ฐ", "ฑ", "ฒ", "ณ", "ด", "ต", "ถ", "ท", "ธ", "น", "บ", "ป", "ผ", "ฝ", "พ", "ฟ",
                           "ภ", "ม", "ย", "ร", "ล", "ว", "ศ", "ษ", "ส", "ห", "ฬ", "ฮ"};
    QStringList ipa = {"/k/", "/kʰ/", "/kʰ/", "/kʰ/", "/kʰ/", "/kʰ/", "/ŋ/", "/tɕ/", "/tɕʰ/", "/tɕʰ/", "/s/",
                       "/tɕʰ/", "/j/", "/d/", "/t/", "/tʰ/", "/d/", "/tʰ/", "/n/", "/d/", "/t/", "/tʰ/",
                       "/tʰ/", "/n/", "/b/", "/p/", "/pʰ/", "/f/", "/pʰ/", "/f/", "/pʰ/", "/m/", "/j/",
                       "/r/", "/l/", "/w/", "/s/", "/s/", "/s/", "/h/", "/l/", "/h/"};

    for (int i = 0; i < letters.size(); ++i) {
        QTableWidgetItem *letterItem = new QTableWidgetItem(letters[i]);
        QTableWidgetItem *ipaItem = new QTableWidgetItem(ipa[i]);

        // 设置字母项居中对齐
        letterItem->setTextAlignment(Qt::AlignCenter);
        // 设置字体大小
        QFont font = letterItem->font();
        font.setPointSize(16);
        letterItem->setFont(font);
        letterItem->setFlags(letterItem->flags() & ~Qt::ItemIsEditable);
        ipaItem->setFlags(ipaItem->flags() & ~Qt::ItemIsEditable);
        ui->thaiTableWidget->setItem(i, 0, letterItem);
        ui->thaiTableWidget->setItem(i, 1, ipaItem);
    }

    // 调整列宽
    ui->thaiTableWidget->resizeColumnsToContents();
}

void PhoneticChartDialog::setupArmenianChart()
{
    ui->armenianTableWidget->setRowCount(38);

    // 添加亚美尼亚字母和对应的IPA
    QStringList letters = {"Ա", "Բ", "Գ", "Դ", "Ե", "Զ", "Է", "Ը", "Թ", "Ժ", "Ի", "Լ", "Խ", "Ծ", "Կ",
                           "Հ", "Ձ", "Ղ", "Ճ", "Մ", "Յ", "Ն", "Շ", "Ո", "Չ", "Պ", "Ջ", "Ռ", "Ս", "Վ", "Տ",
                           "Ր", "Ց", "Ւ", "Փ", "Ք", "Օ", "Ֆ"};
    QStringList ipa = {"/ɑ/", "/b/", "/ɡ/", "/d/", "/ɛ/", "/z/", "/ɛ/", "/ə/", "/tʰ/", "/ʒ/", "/i/", "/l/",
                       "/χ/", "/dz/", "/k/", "/h/", "/dz/", "/ʁ/", "/tʃʰ/", "/m/", "/j/", "/n/", "/ʃ/",
                       "/v/", "/tʃʰ/", "/p/", "/dʒ/", "/ɺ/", "/s/", "/v/", "/t/", "/r/", "/tsʰ/", "/w/",
                       "/pʰ/", "/kʰ/", "/o/", "/f/"};

    for (int i = 0; i < letters.size(); ++i) {
        QTableWidgetItem *letterItem = new QTableWidgetItem(letters[i]);
        QTableWidgetItem *ipaItem = new QTableWidgetItem(ipa[i]);

        // 设置字母项居中对齐
        letterItem->setTextAlignment(Qt::AlignCenter);
        // 设置字体大小
        QFont font = letterItem->font();
        font.setPointSize(16);
        letterItem->setFont(font);
        letterItem->setFlags(letterItem->flags() & ~Qt::ItemIsEditable);
        ipaItem->setFlags(ipaItem->flags() & ~Qt::ItemIsEditable);
        ui->armenianTableWidget->setItem(i, 0, letterItem);
        ui->armenianTableWidget->setItem(i, 1, ipaItem);
    }

    // 调整列宽
    ui->armenianTableWidget->resizeColumnsToContents();
}

void PhoneticChartDialog::setupBengaliChart()
{
    ui->bengaliTableWidget->setRowCount(39);

    // 添加孟加拉字母和对应的IPA
    QStringList letters = {"অ", "আ", "ই", "ঈ", "উ", "ঊ", "ঋ", "এ", "ঐ", "ও", "ঔ", "ক", "খ", "গ", "ঘ", "ঙ",
                           "চ", "ছ", "জ", "ঝ", "ঞ", "ট", "ঠ", "ড", "ঢ", "ণ", "ত", "থ", "দ", "ধ", "ন", "প",
                           "ফ", "ব", "ভ", "ম", "য", "র", "ল", "শ", "ষ", "স", "হ"};
    QStringList ipa = {"/ɔ/", "/a/", "/i/", "/i/", "/u/", "/u/", "/ri/", "/e/", "/oi/", "/o/", "/ou/", "/kɔ/",
                       "/kʰɔ/", "/ɡɔ/", "/ɡʱɔ/", "/ŋɔ/", "/tɕɔ/", "/tɕʰɔ/", "/dʑɔ/", "/dʑʱɔ/", "/ɲɔ/",
                       "/ʈɔ/", "/ʈʰɔ/", "/ɖɔ/", "/ɖʱɔ/", "/ɳɔ/", "/t̪ɔ/", "/t̪ʰɔ/", "/d̪ɔ/", "/d̪ʱɔ/", "/n̪ɔ/",
                       "/pɔ/", "/fɔ/", "/bɔ/", "/bʱɔ/", "/mɔ/", "/dʑɔ/", "/rɔ/", "/lɔ/", "/ɕɔ/", "/ʂɔ/",
                       "/sɔ/", "/hɔ/"};

    for (int i = 0; i < letters.size(); ++i) {
        QTableWidgetItem *letterItem = new QTableWidgetItem(letters[i]);
        QTableWidgetItem *ipaItem = new QTableWidgetItem(ipa[i]);

        // 设置字母项居中对齐
        letterItem->setTextAlignment(Qt::AlignCenter);
        // 设置字体大小
        QFont font = letterItem->font();
        font.setPointSize(16);
        letterItem->setFont(font);
        letterItem->setFlags(letterItem->flags() & ~Qt::ItemIsEditable);
        ipaItem->setFlags(ipaItem->flags() & ~Qt::ItemIsEditable);
        ui->bengaliTableWidget->setItem(i, 0, letterItem);
        ui->bengaliTableWidget->setItem(i, 1, ipaItem);
    }

    // 调整列宽
    ui->bengaliTableWidget->resizeColumnsToContents();
}

void PhoneticChartDialog::closeEvent(QCloseEvent *event)
{
    // 接受关闭事件，但只是隐藏对话框而不是删除它
    event->accept();
    hide(); // 隐藏对话框
}
