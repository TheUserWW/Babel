#include "phoneticchartdialog.h"
#include "ui_phoneticchartdialog.h"
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QFrame>
#include <QFontMetrics>
#include <QSpacerItem>

PhoneticChartDialog::PhoneticChartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PhoneticChartDialog)
{
    try {
        ui->setupUi(this);
        setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
        setWindowTitle(tr("Phonetic Chart"));

        // 使用UI文件中已存在的滚动区域
        QScrollArea *scrollArea = ui->scrollArea;
        
        // 获取滚动区域的内容widget，如果没有则创建一个
        QWidget *container = scrollArea->widget();
        if (!container) {
            container = new QWidget();
            scrollArea->setWidget(container);
        }
        
        // 为容器添加网格布局，如果没有的话
        QGridLayout *gridLayout = qobject_cast<QGridLayout*>(container->layout());
        if (!gridLayout) {
            gridLayout = new QGridLayout(container);
            gridLayout->setSpacing(10);
            gridLayout->setAlignment(Qt::AlignTop);
            container->setLayout(gridLayout);
        }

        // 设置音标表
        setupPhoneticChart();
    } catch (const std::exception& e) {
        qCritical() << "Failed to initialize PhoneticChartDialog:" << e.what();
        if (ui) {
            delete ui;
            ui = nullptr;
        }
        throw;
    } catch (...) {
        qCritical() << "Unknown error occurred while initializing PhoneticChartDialog";
        if (ui) {
            delete ui;
            ui = nullptr;
        }
        throw;
    }
}

PhoneticChartDialog::~PhoneticChartDialog()
{
    if (ui) {
        delete ui;
        ui = nullptr;
    }
}

void PhoneticChartDialog::setupPhoneticChart()
{
    // 清除网格
    clearGrid();

    // 添加大写拉丁字母
    QStringList latinUpperLetters = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
                                     "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    QStringList latinUpperIPA = {"/eɪ/", "/biː/", "/siː/", "/diː/", "/iː/", "/ɛf/", "/dʒiː/", "/eɪtʃ/", "/aɪ/", "/dʒeɪ/",
                                 "/keɪ/", "/ɛl/", "/ɛm/", "/ɛn/", "/oʊ/", "/piː/", "/kjuː/", "/ɑːr/", "/ɛs/", "/tiː/",
                                 "/juː/", "/viː/", "/dʌbəl.juː/", "/ɛks/", "/waɪ/", "/ziː/"};
    addAlphabetToGrid("Latin (Uppercase)", latinUpperLetters, latinUpperIPA);

    // 添加小写拉丁字母
    QStringList latinLowerLetters = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
                                     "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    QStringList latinLowerIPA = {"/eɪ/", "/biː/", "/siː/", "/diː/", "/iː/", "/ɛf/", "/dʒiː/", "/eɪtʃ/", "/aɪ/", "/dʒeɪ/",
                                 "/keɪ/", "/ɛl/", "/ɛm/", "/ɛn/", "/oʊ/", "/piː/", "/kjuː/", "/ɑːr/", "/ɛs/", "/tiː/",
                                 "/juː/", "/viː/", "/dʌbəl.juː/", "/ɛks/", "/waɪ/", "/ziː/"};
    addAlphabetToGrid("Latin (Lowercase)", latinLowerLetters, latinLowerIPA);

    // 添加带重音符号的拉丁字母
    QStringList latinAccentedLetters = {"Á", "À", "Â", "Ä", "Ã", "Å", "Ā", "Ă", "Ǎ", "Ą",
                                       "É", "È", "Ê", "Ë", "Ē", "Ĕ", "Ė", "Ę", "Ě", "Ẽ",
                                       "Í", "Ì", "Î", "Ï", "Ĩ", "Ī", "Ĭ", "Ǐ", "Į", "İ",
                                       "Ó", "Ò", "Ô", "Ö", "Õ", "Ō", "Ŏ", "Ǒ", "Ǫ", "Ő",
                                       "Ú", "Ù", "Û", "Ü", "Ũ", "Ū", "Ŭ", "Ů", "Ų", "Ű",
                                       "Ý", "Ŷ", "Ÿ", "Ȳ", "Ž", "Ź", "Ż", "Ç", "Ć", "Č",
                                       "á", "à", "â", "ä", "ã", "å", "ā", "ă", "ǎ", "ą",
                                       "é", "è", "ê", "ë", "ē", "ĕ", "ė", "ę", "ě", "ẽ",
                                       "í", "ì", "î", "ï", "ĩ", "ī", "ĭ", "ǐ", "į", "i",
                                       "ó", "ò", "ô", "ö", "õ", "ō", "ŏ", "ǒ", "ǫ", "ő",
                                       "ú", "ù", "û", "ü", "ũ", "ū", "ŭ", "ů", "ų", "ű",
                                       "ý", "ŷ", "ÿ", "ȳ", "ž", "ź", "ż", "ç", "ć", "č"};
    QStringList latinAccentedIPA = {"/ɑː/", "/ɑː/", "/ɑː/", "/ɛː/", "/ɑ̃/", "/ɔː/", "/ɑː/", "/ɑː/", "/ɑː/", "/ɑ̃/",
                                    "/eː/", "/ɛː/", "/ɛː/", "/eː/", "/eː/", "/ɛː/", "/eː/", "/ɛ̃/", "/ɛː/", "/ɛ̃/",
                                    "/iː/", "/iː/", "/iː/", "/iː/", "/ĩ/", "/iː/", "/iː/", "/iː/", "/ĩ/", "/i/",
                                    "/oː/", "/ɔː/", "/oː/", "/øː/", "/õ/", "/oː/", "/ɔː/", "/ɔː/", "/ɔ̃/", "/øː/",
                                    "/uː/", "/uː/", "/uː/", "/yː/", "/ũ/", "/uː/", "/uː/", "/uː/", "/ũ/", "/yː/",
                                    "/iː/", "/iː/", "/iː/", "/iː/", "/ʒ/", "/ʒ/", "/ʒ/", "/tʃ/", "/tʃ/", "/tʃ/",
                                    "/ɑː/", "/ɑː/", "/ɑː/", "/ɛː/", "/ɑ̃/", "/ɔː/", "/ɑː/", "/ɑː/", "/ɑː/", "/ɑ̃/",
                                    "/eː/", "/ɛː/", "/ɛː/", "/eː/", "/eː/", "/ɛː/", "/eː/", "/ɛ̃/", "/ɛː/", "/ɛ̃/",
                                    "/iː/", "/iː/", "/iː/", "/iː/", "/ĩ/", "/iː/", "/iː/", "/iː/", "/ĩ/", "/i/",
                                    "/oː/", "/ɔː/", "/oː/", "/øː/", "/õ/", "/oː/", "/ɔː/", "/ɔː/", "/ɔ̃/", "/øː/",
                                    "/uː/", "/uː/", "/uː/", "/yː/", "/ũ/", "/uː/", "/uː/", "/uː/", "/ũ/", "/yː/",
                                    "/iː/", "/iː/", "/iː/", "/iː/", "/ʒ/", "/ʒ/", "/ʒ/", "/tʃ/", "/tʃ/", "/tʃ/"};
    addAlphabetToGrid("Latin (Accented)", latinAccentedLetters, latinAccentedIPA);

    // 添加拉丁扩展字母
    QStringList latinExtendedLetters = {"Æ", "Œ", "Ð", "Þ", "ß", "Ĳ", "Ŋ", "Ə", "Ɣ", "Ʒ",
                                       "æ", "œ", "ð", "þ", "ĳ", "ŋ", "ə", "ɣ", "ʒ", "ǀ",
                                       "ǁ", "ǂ", "ǃ", "ʼ", "ʔ", "ʕ", "ʢ", "ʡ", "ʖ", "ʗ"};
    QStringList latinExtendedIPA = {"/eɪ/", "/øː/", "/ɛð/", "/θɹ/", "/s/", "/ɛɪ/", "/ŋ/", "/ə/", "/ɣ/", "/ʒ/",
                                    "/aɪ/", "/øː/", "/ð/", "/θ/", "/ɛɪ/", "/ŋ/", "/ə/", "/ɣ/", "/ʒ/", "/ǀ/",
                                    "/ǁ/", "/ǂ/", "/ǃ/", "/ʔ/", "/ʔ/", "/ʕ/", "/ʢ/", "/ʡ/", "/ʖ/", "/ʗ/"};
    addAlphabetToGrid("Latin (Extended)", latinExtendedLetters, latinExtendedIPA);

    // 添加大写西里尔字母
    QStringList cyrillicUpperLetters = {"А", "Б", "В", "Г", "Д", "Е", "Ё", "Ж", "З", "И", "Й", "К", "Л", "М", "Н",
                                        "О", "П", "Р", "С", "Т", "У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь", "Э", "Ю", "Я"};
    QStringList cyrillicUpperIPA = {"/ɑ/", "/b/", "/v/", "/ɡ/", "/d/", "/je/", "/jo/", "/ʐ/", "/z/", "/i/", "/j/", "/k/", "/l/", "/m/", "/n/",
                                    "/o/", "/p/", "/r/", "/s/", "/t/", "/u/", "/f/", "/x/", "/ts/", "/tɕ/", "/ʂ/", "/ɕɕ/", "/ʔ/", "/ɨ/", "/ʔ/", "/e/", "/ju/", "/jɑ/"};
    addAlphabetToGrid("Cyrillic (Uppercase)", cyrillicUpperLetters, cyrillicUpperIPA);

    // 添加小写西里尔字母
    QStringList cyrillicLowerLetters = {"а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и", "й", "к", "л", "м", "н",
                                        "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"};
    QStringList cyrillicLowerIPA = {"/ɑ/", "/b/", "/v/", "/ɡ/", "/d/", "/je/", "/jo/", "/ʐ/", "/z/", "/i/", "/j/", "/k/", "/l/", "/m/", "/n/",
                                    "/o/", "/p/", "/r/", "/s/", "/t/", "/u/", "/f/", "/x/", "/ts/", "/tɕ/", "/ʂ/", "/ɕɕ/", "/ʔ/", "/ɨ/", "/ʔ/", "/e/", "/ju/", "/jɑ/"};
    addAlphabetToGrid("Cyrillic (Lowercase)", cyrillicLowerLetters, cyrillicLowerIPA);

    // 添加西里尔扩展字母
    QStringList cyrillicExtendedLetters = {"Ђ", "Ћ", "Ј", "Љ", "Њ", "Ћ", "Џ", "Ґ", "Ғ", "Қ", "Ң", "Ү", "Ұ", "Һ", "Ӏ",
                                           "ђ", "ћ", "ј", "љ", "њ", "ћ", "џ", "ґ", "ғ", "қ", "ң", "ү", "ұ", "һ", "ӏ"};
    QStringList cyrillicExtendedIPA = {"/dʑ/", "/tɕ/", "/j/", "/lʑ/", "/nʑ/", "/tɕ/", "/dʐ/", "/ɡ/", "/ʁ/", "/q/", "/ŋ/", "/y/", "/u/", "/h/", "/ʔ/",
                                       "/dʑ/", "/tɕ/", "/j/", "/lʑ/", "/nʑ/", "/tɕ/", "/dʐ/", "/ɡ/", "/ʁ/", "/q/", "/ŋ/", "/y/", "/u/", "/h/", "/ʔ/"};
    addAlphabetToGrid("Cyrillic (Extended)", cyrillicExtendedLetters, cyrillicExtendedIPA);


    // 添加大写希腊字母
    QStringList greekUpperLetters = {"Α", "Β", "Γ", "Δ", "Ε", "Ζ", "Η", "Θ", "Ι", "Κ", "Λ", "Μ", "Ν", "Ξ", "Ο", "Π", "Ρ", "Σ", "Τ", "Υ", "Φ", "Χ", "Ψ", "Ω"};
    QStringList greekUpperIPA = {"/a/", "/b/", "/ɡ/", "/d/", "/e/", "/z/", "/iː/", "/θ/", "/i/", "/k/", "/l/", "/m/", "/n/", "/ks/", "/o/", "/p/", "/r/", "/s/", "/t/", "/y/", "/f/", "/x/", "/ps/", "/oː/"};
    addAlphabetToGrid("Greek (Uppercase)", greekUpperLetters, greekUpperIPA);

    // 添加小写希腊字母
    QStringList greekLowerLetters = {"α", "β", "γ", "δ", "ε", "ζ", "η", "θ", "ι", "κ", "λ", "μ", "ν", "ξ", "ο", "π", "ρ", "σ", "τ", "υ", "φ", "χ", "ψ", "ω"};
    QStringList greekLowerIPA = {"/a/", "/b/", "/ɡ/", "/d/", "/e/", "/z/", "/iː/", "/θ/", "/i/", "/k/", "/l/", "/m/", "/n/", "/ks/", "/o/", "/p/", "/r/", "/s/", "/t/", "/y/", "/f/", "/x/", "/ps/", "/oː/"};
    addAlphabetToGrid("Greek (Lowercase)", greekLowerLetters, greekLowerIPA);

    // 添加带重音符号的希腊字母
    QStringList greekAccentedLetters = {"Ά", "Έ", "Ή", "Ί", "Ό", "Ύ", "Ώ", "Ϊ", "Ϋ", "ά", "έ", "ή", "ί", "ό", "ύ", "ώ", "ϊ", "ϋ"};
    QStringList greekAccentedIPA = {"/a/", "/e/", "/iː/", "/i/", "/o/", "/y/", "/oː/", "/i/", "/y/", "/a/", "/e/", "/iː/", "/i/", "/o/", "/y/", "/oː/", "/i/", "/y/"};
    addAlphabetToGrid("Greek (Accented)", greekAccentedLetters, greekAccentedIPA);

    // 添加希腊扩展字母
    QStringList greekExtendedLetters = {"ϐ", "ϑ", "ϒ", "ϕ", "ϖ", "ϰ", "ϱ", "ϲ", "ϴ", "ϵ", "϶", "Ͱ", "ͱ", "Ͳ", "ͳ", "ʹ", "͵", "Ͷ", "ͷ", "͸", "͹", "ͺ", "ͻ", "ͼ", "ͽ", ";", "Ϳ"};
    QStringList greekExtendedIPA = {"/b/", "/θ/", "/y/", "/f/", "/p/", "/k/", "/r/", "/s/", "/θ/", "/e/", "/e/", "/h/", "/h/", "/a/", "/a/", "/ˈ/", "/͵/", "/ʃ/", "/ʃ/", "/ʔ/", "/ʔ/", "/ˈ/", "/c/", "/c/", "/c/", ";", "/ʔ/"};
    addAlphabetToGrid("Greek (Extended)", greekExtendedLetters, greekExtendedIPA);


}

void PhoneticChartDialog::clearGrid()
{
    // 直接使用UI文件中的滚动区域
    QScrollArea *scrollArea = ui->scrollArea;
    if (!scrollArea) return;

    QWidget *container = scrollArea->widget();
    if (!container) return;

    QGridLayout *gridLayout = qobject_cast<QGridLayout*>(container->layout());
    if (!gridLayout) return;

    // 清除所有子部件
    QLayoutItem *item;
    while ((item = gridLayout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void PhoneticChartDialog::addAlphabetToGrid(const QString& title, const QStringList& letters, const QStringList& ipa)
{
    // 直接使用UI文件中的滚动区域
    QScrollArea *scrollArea = ui->scrollArea;
    if (!scrollArea) return;

    QWidget *container = scrollArea->widget();
    if (!container) return;

    QGridLayout *gridLayout = qobject_cast<QGridLayout*>(container->layout());
    if (!gridLayout) return;

    // 添加标题
    QLabel *titleLabel = new QLabel(title);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);

    gridLayout->addWidget(titleLabel, gridLayout->rowCount(), 0, 1, -1);

    // 计算每行显示的字母数量
    int lettersPerRow = 8;
    int currentRow = gridLayout->rowCount();

    for (int i = 0; i < letters.size(); ++i) {
        // 创建字母单元格
        QFrame *cell = new QFrame();
        cell->setFrameStyle(QFrame::Box);
        cell->setLineWidth(1);
        cell->setFixedSize(80, 80);

        QVBoxLayout *cellLayout = new QVBoxLayout(cell);
        cellLayout->setContentsMargins(2, 2, 2, 2);
        cellLayout->setSpacing(2);

        // 添加字母（居中）
        QLabel *letterLabel = new QLabel(letters[i]);
        letterLabel->setAlignment(Qt::AlignCenter);
        QFont letterFont = letterLabel->font();
        letterFont.setPointSize(20);
        letterLabel->setFont(letterFont);

        // 添加音标和Unicode（底部）
        QHBoxLayout *bottomLayout = new QHBoxLayout();

        QLabel *ipaLabel = new QLabel(ipa[i]);
        ipaLabel->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
        QFont ipaFont = ipaLabel->font();
        ipaFont.setPointSize(8);
        ipaLabel->setFont(ipaFont);

        // 获取Unicode编码
        QString unicode;
        if (!letters[i].isEmpty()) {
            ushort unicodeValue = letters[i].at(0).unicode();
            unicode = QString("U+%1").arg(unicodeValue, 4, 16, QLatin1Char('0')).toUpper();
        }

        QLabel *unicodeLabel = new QLabel(unicode);
        unicodeLabel->setAlignment(Qt::AlignRight | Qt::AlignBottom);
        QFont unicodeFont = unicodeLabel->font();
        unicodeFont.setPointSize(7);
        unicodeLabel->setFont(unicodeFont);

        bottomLayout->addWidget(ipaLabel);
        bottomLayout->addWidget(unicodeLabel);

        cellLayout->addWidget(letterLabel);
        cellLayout->addLayout(bottomLayout);

        // 添加到网格
        int row = currentRow + (i / lettersPerRow) + 1; // +1 因为标题占了一行
        int col = i % lettersPerRow;
        gridLayout->addWidget(cell, row, col);
    }

    // 更新当前行数
    int rowsNeeded = (letters.size() + lettersPerRow - 1) / lettersPerRow;
    currentRow += rowsNeeded + 2; // +2 因为标题和空行

    // 添加空行分隔不同的字母表
    gridLayout->addItem(new QSpacerItem(10, 20), currentRow, 0);
}

void PhoneticChartDialog::closeEvent(QCloseEvent *event)
{
    event->accept();
    hide();
}
