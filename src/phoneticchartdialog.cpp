#include "phoneticchartdialog.h"
#include "ui_phoneticchartdialog.h"
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QFrame>
#include <QFontMetrics>
#include <QSpacerItem>
#include <QTimer>
#include <QProgressBar>
#include <QTimer>
#include <QProgressBar>

PhoneticChartDialog::PhoneticChartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PhoneticChartDialog),
    loadTimer(new QTimer(this)),
    progressBar(nullptr),
    currentAlphabetIndex(0),
    totalAlphabets(11) // 总共要加载的字母表数量
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

        // 初始化加载UI
        initializeLoadingUI();
        
        // 设置定时器，延迟加载音标表
        connect(loadTimer, &QTimer::timeout, this, &PhoneticChartDialog::loadNextAlphabet);
        loadTimer->setSingleShot(false);
        
        // 显示对话框
        show();
        
        // 开始延迟加载
        QTimer::singleShot(100, this, [this]() {
            loadTimer->start(10); // 每10毫秒加载一个字母表
        });
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
    // 停止加载定时器
    if (loadTimer) {
        loadTimer->stop();
    }
    
    if (ui) {
        delete ui;
        ui = nullptr;
    }
}

void PhoneticChartDialog::setupPhoneticChart()
{
    try {
        clearGrid();
        
        // 获取滚动区域的内容widget
        QScrollArea *scrollArea = ui->scrollArea;
        QWidget *container = scrollArea->widget();
        QGridLayout *gridLayout = qobject_cast<QGridLayout*>(container->layout());
        
        if (!gridLayout) {
            qWarning() << "Grid layout not found in scroll area widget";
            return;
        }
        
        // 重置当前索引
        currentAlphabetIndex = 0;
        
        // 初始化加载UI
        initializeLoadingUI();
        
        // 启动定时器开始加载
        loadTimer->start(10); // 每10毫秒加载一个字母表
    } catch (const std::exception& e) {
        qCritical() << "Failed to setup phonetic chart:" << e.what();
    } catch (...) {
        qCritical() << "Unknown error occurred while setting up phonetic chart";
    }
}

void PhoneticChartDialog::loadNextAlphabet()
{
    try {
        // 获取滚动区域的内容widget
        QScrollArea *scrollArea = ui->scrollArea;
        QWidget *container = scrollArea->widget();
        QGridLayout *gridLayout = qobject_cast<QGridLayout*>(container->layout());
        
        if (!gridLayout) {
            qWarning() << "Grid layout not found in scroll area widget";
            loadTimer->stop();
            return;
        }
        
        // 根据当前索引加载对应的字母表
        switch (currentAlphabetIndex) {
        case 0: {
            // 添加大写拉丁字母
            QStringList latinUpperLetters = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
                                             "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
            QStringList latinUpperIPA = {"/eɪ/", "/biː/", "/siː/", "/diː/", "/iː/", "/ɛf/", "/dʒiː/", "/eɪtʃ/", "/aɪ/", "/dʒeɪ/",
                                         "/keɪ/", "/ɛl/", "/ɛm/", "/ɛn/", "/oʊ/", "/piː/", "/kjuː/", "/ɑːr/", "/ɛs/", "/tiː/",
                                         "/juː/", "/viː/", "/dʌbəl.juː/", "/ɛks/", "/waɪ/", "/ziː/"};
            addAlphabetToGrid("Latin (Uppercase)", latinUpperLetters, latinUpperIPA);
            break;
        }
        case 1: {
            // 添加小写拉丁字母
            QStringList latinLowerLetters = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
                                             "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
            QStringList latinLowerIPA = {"/eɪ/", "/biː/", "/siː/", "/diː/", "/iː/", "/ɛf/", "/dʒiː/", "/eɪtʃ/", "/aɪ/", "/dʒeɪ/",
                                         "/keɪ/", "/ɛl/", "/ɛm/", "/ɛn/", "/oʊ/", "/piː/", "/kjuː/", "/ɑːr/", "/ɛs/", "/tiː/",
                                         "/juː/", "/viː/", "/dʌbəl.juː/", "/ɛks/", "/waɪ/", "/ziː/"};
            addAlphabetToGrid("Latin (Lowercase)", latinLowerLetters, latinLowerIPA);
            break;
        }
        case 2: {
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
            break;
        }
        case 3: {
            // 添加拉丁扩展字母
            QStringList latinExtendedLetters = {"Æ", "Œ", "Ð", "Þ", "ß", "Ĳ", "Ŋ", "Ə", "Ɣ", "Ʒ",
                                               "æ", "œ", "ð", "þ", "ĳ", "ŋ", "ə", "ɣ", "ʒ", "ǀ",
                                               "ǁ", "ǂ", "ǃ", "ʼ", "ʔ", "ʕ", "ʢ", "ʡ", "ʖ", "ʗ"};
            QStringList latinExtendedIPA = {"/eɪ/", "/øː/", "/ɛð/", "/θɹ/", "/s/", "/ɛɪ/", "/ŋ/", "/ə/", "/ɣ/", "/ʒ/",
                                            "/aɪ/", "/øː/", "/ð/", "/θ/", "/ɛɪ/", "/ŋ/", "/ə/", "/ɣ/", "/ʒ/", "/ǀ/",
                                            "/ǁ/", "/ǂ/", "/ǃ/", "/ʔ/", "/ʔ/", "/ʕ/", "/ʢ/", "/ʡ/", "/ʖ/", "/ʗ/"};
            addAlphabetToGrid("Latin (Extended)", latinExtendedLetters, latinExtendedIPA);
            break;
        }
        case 4: {
            // 添加大写西里尔字母
            QStringList cyrillicUpperLetters = {"А", "Б", "В", "Г", "Д", "Е", "Ё", "Ж", "З", "И", "Й", "К", "Л", "М", "Н",
                                                "О", "П", "Р", "С", "Т", "У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь", "Э", "Ю", "Я"};
            QStringList cyrillicUpperIPA = {"/ɑ/", "/b/", "/v/", "/ɡ/", "/d/", "/je/", "/jo/", "/ʐ/", "/z/", "/i/", "/j/", "/k/", "/l/", "/m/", "/n/",
                                            "/o/", "/p/", "/r/", "/s/", "/t/", "/u/", "/f/", "/x/", "/ts/", "/tɕ/", "/ʂ/", "/ɕɕ/", "/ʔ/", "/ɨ/", "/ʔ/", "/e/", "/ju/", "/jɑ/"};
            addAlphabetToGrid("Cyrillic (Uppercase)", cyrillicUpperLetters, cyrillicUpperIPA);
            break;
        }
        case 5: {
            // 添加小写西里尔字母
            QStringList cyrillicLowerLetters = {"а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и", "й", "к", "л", "м", "н",
                                                "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"};
            QStringList cyrillicLowerIPA = {"/ɑ/", "/b/", "/v/", "/ɡ/", "/d/", "/je/", "/jo/", "/ʐ/", "/z/", "/i/", "/j/", "/k/", "/l/", "/m/", "/n/",
                                            "/o/", "/p/", "/r/", "/s/", "/t/", "/u/", "/f/", "/x/", "/ts/", "/tɕ/", "/ʂ/", "/ɕɕ/", "/ʔ/", "/ɨ/", "/ʔ/", "/e/", "/ju/", "/jɑ/"};
            addAlphabetToGrid("Cyrillic (Lowercase)", cyrillicLowerLetters, cyrillicLowerIPA);
            break;
        }
        case 6: {
            // 添加西里尔扩展字母
            QStringList cyrillicExtendedLetters = {"Ђ", "Ћ", "Ј", "Љ", "Њ", "Ћ", "Џ", "Ґ", "Ғ", "Қ", "Ң", "Ү", "Ұ", "Һ", "Ӏ",
                                                   "ђ", "ћ", "ј", "љ", "њ", "ћ", "џ", "ґ", "ғ", "қ", "ң", "ү", "ұ", "һ", "ӏ"};
            QStringList cyrillicExtendedIPA = {"/dʑ/", "/tɕ/", "/j/", "/lʑ/", "/nʑ/", "/tɕ/", "/dʐ/", "/ɡ/", "/ʁ/", "/q/", "/ŋ/", "/y/", "/u/", "/h/", "/ʔ/",
                                               "/dʑ/", "/tɕ/", "/j/", "/lʑ/", "/nʑ/", "/tɕ/", "/dʐ/", "/ɡ/", "/ʁ/", "/q/", "/ŋ/", "/y/", "/u/", "/h/", "/ʔ/"};
            addAlphabetToGrid("Cyrillic (Extended)", cyrillicExtendedLetters, cyrillicExtendedIPA);
            break;
        }
        case 7: {
            // 添加大写希腊字母
            QStringList greekUpperLetters = {"Α", "Β", "Γ", "Δ", "Ε", "Ζ", "Η", "Θ", "Ι", "Κ", "Λ", "Μ", "Ν", "Ξ", "Ο", "Π", "Ρ", "Σ", "Τ", "Υ", "Φ", "Χ", "Ψ", "Ω"};
            QStringList greekUpperIPA = {"/a/", "/b/", "/ɡ/", "/d/", "/e/", "/z/", "/iː/", "/θ/", "/i/", "/k/", "/l/", "/m/", "/n/", "/ks/", "/o/", "/p/", "/r/", "/s/", "/t/", "/y/", "/f/", "/x/", "/ps/", "/oː/"};
            addAlphabetToGrid("Greek (Uppercase)", greekUpperLetters, greekUpperIPA);
            break;
        }
        case 8: {
            // 添加小写希腊字母
            QStringList greekLowerLetters = {"α", "β", "γ", "δ", "ε", "ζ", "η", "θ", "ι", "κ", "λ", "μ", "ν", "ξ", "ο", "π", "ρ", "σ", "τ", "υ", "φ", "χ", "ψ", "ω"};
            QStringList greekLowerIPA = {"/a/", "/b/", "/ɡ/", "/d/", "/e/", "/z/", "/iː/", "/θ/", "/i/", "/k/", "/l/", "/m/", "/n/", "/ks/", "/o/", "/p/", "/r/", "/s/", "/t/", "/y/", "/f/", "/x/", "/ps/", "/oː/"};
            addAlphabetToGrid("Greek (Lowercase)", greekLowerLetters, greekLowerIPA);
            break;
        }
        case 9: {
            // 添加带重音符号的希腊字母
            QStringList greekAccentedLetters = {"Ά", "Έ", "Ή", "Ί", "Ό", "Ύ", "Ώ", "Ϊ", "Ϋ", "ά", "έ", "ή", "ί", "ό", "ύ", "ώ", "ϊ", "ϋ"};
            QStringList greekAccentedIPA = {"/a/", "/e/", "/iː/", "/i/", "/o/", "/y/", "/oː/", "/i/", "/y/", "/a/", "/e/", "/iː/", "/i/", "/o/", "/y/", "/oː/", "/i/", "/y/"};
            addAlphabetToGrid("Greek (Accented)", greekAccentedLetters, greekAccentedIPA);
            break;
        }
        case 10: {
            // 添加希腊扩展字母
            QStringList greekExtendedLetters = {"ϐ", "ϑ", "ϒ", "ϕ", "ϖ", "ϰ", "ϱ", "ϲ", "ϴ", "ϵ", "϶", "Ͱ", "ͱ", "Ͳ", "ͳ", "ʹ", "͵", "Ͷ", "ͷ", "͸", "͹", "ͺ", "ͻ", "ͼ", "ͽ", ";", "Ϳ"};
            QStringList greekExtendedIPA = {"/b/", "/θ/", "/y/", "/f/", "/p/", "/k/", "/r/", "/s/", "/θ/", "/e/", "/e/", "/h/", "/h/", "/a/", "/a/", "/ˈ/", "/͵/", "/ʃ/", "/ʃ/", "/ʔ/", "/ʔ/", "/ˈ/", "/c/", "/c/", "/c/", ";", "/ʔ/"};
            addAlphabetToGrid("Greek (Extended)", greekExtendedLetters, greekExtendedIPA);
            break;
        }
        case 11: {
            // 添加格鲁吉亚字母
            QStringList georgianLetters = {"ა", "ბ", "გ", "დ", "ე", "ვ", "ზ", "თ", "ი", "კ", "ლ", "მ", "ნ", "ო", "პ", "ჟ", "რ", "ს", "ტ", "უ", "ფ", "ქ", "ღ", "ყ", "შ", "ჩ", "ც", "ძ", "წ", "ჭ", "ხ", "ჯ", "ჰ"};
            QStringList georgianIPA = {"/ɑ/", "/b/", "/ɡ/", "/d/", "/ɛ/", "/v/", "/z/", "/tʰ/", "/i/", "/kʼ/", "/l/", "/m/", "/n/", "/ɔ/", "/pʼ/", "/ʒ/", "/r/", "/s/", "/tʼ/", "/u/", "/pʰ/", "/kʰ/", "/ɣ/", "/qʼ/", "/ʃ/", "/tʃʰ/", "/tsʰ/", "/dz/", "/tsʼ/", "/tʃʼ/", "/χ/", "/dʒ/", "/h/"};
            addAlphabetToGrid("Georgian", georgianLetters, georgianIPA);
            break;
        }
        case 12: {
            // 添加亚美尼亚字母
            QStringList armenianLetters = {"Ա", "Բ", "Գ", "Դ", "Ե", "Զ", "Է", "Ը", "Թ", "Ժ", "Ի", "Լ", "Խ", "Ծ", "Կ", "Հ", "Ձ", "Ղ", "Ճ", "Մ", "Յ", "Ն", "Շ", "Ո", "Չ", "Պ", "Ջ", "Ռ", "Ս", "Վ", "Տ", "Ր", "Ց", "Ւ", "Փ", "Ք", "Օ", "Ֆ"};
            QStringList armenianIPA = {"/ɑ/", "/b/", "/ɡ/", "/d/", "/jɛ/", "/z/", "/ɛ/", "/ə/", "/tʰ/", "/ʒ/", "/i/", "/l/", "/χ/", "/ts/", "/k/", "/h/", "/dz/", "/ʁ/", "/tʃ/", "/m/", "/j/", "/n/", "/ʃ/", "/ɔ/", "/tʃʰ/", "/p/", "/dʒ/", "/r/", "/s/", "/v/", "/t/", "/ɾ/", "/tsʰ/", "/w/", "/pʰ/", "/kʰ/", "/o/", "/f/"};
            addAlphabetToGrid("Armenian", armenianLetters, armenianIPA);
            break;
        }
        case 13: {
            // 添加腓尼基字母
            QStringList phoenicianLetters = {"𐤀", "𐤁", "𐤂", "𐤃", "𐤄", "𐤅", "𐤆", "𐤇", "𐤈", "𐤉", "𐤊", "𐤋", "𐤌", "𐤍", "𐤎", "𐤏", "𐤐", "𐤑", "𐤒", "𐤓", "𐤔", "𐤕"};
            QStringList phoenicianIPA = {"/ʔ/", "/b/", "/ɡ/", "/d/", "/h/", "/w/", "/z/", "/ħ/", "/tˤ/", "/j/", "/k/", "/l/", "/m/", "/n/", "/s/", "/ʕ/", "/p/", "/sˤ/", "/q/", "/r/", "/ʃ/", "/t/"};
            addAlphabetToGrid("Phoenician", phoenicianLetters, phoenicianIPA);
            break;
        }
        case 14:{
            // 添加叙利亚字母
            QStringList syriacLetters = {"ܐ", "ܒ", "ܓ", "ܕ", "ܗ", "ܘ", "ܙ", "ܚ", "ܛ", "ܝ", "ܟ", "ܠ", "ܡ", "ܢ", "ܣ", "ܥ", "ܦ", "ܨ", "ܩ", "ܪ", "ܫ", "ܬ"};
            QStringList syriacIPA = {"/ʔ/", "/b/", "/ɡ/", "/d/", "/h/", "/w/", "/z/", "/ħ/", "/tˤ/", "/j/", "/k/", "/l/", "/m/", "/n/", "/s/", "/ʕ/", "/p/", "/sˤ/", "/q/", "/r/", "/ʃ/", "/t/"};
            addAlphabetToGrid("Syriac", syriacLetters, syriacIPA);
            break;
        }
        case 15: {
            // 添加希伯来字母
            QStringList hebrewLetters = {"א", "ב", "ג", "ד", "ה", "ו", "ז", "ח", "ט", "י", "כ", "ל", "מ", "נ", "ס", "ע", "פ", "צ", "ק", "ר", "ש", "ת"};
            QStringList hebrewIPA = {"/ʔ/", "/b/", "/ɡ/", "/d/", "/h/", "/v/", "/z/", "/ħ/", "/t/", "/j/", "/k/", "/l/", "/m/", "/n/", "/s/", "/ʕ/", "/p/", "/ts/", "/k/", "/r/", "/ʃ/", "/t/"};
            addAlphabetToGrid("Hebrew", hebrewLetters, hebrewIPA);
            break;
        }
        case 16: {
            // 添加阿拉伯字母
            QStringList arabicLetters = {"ا", "ب", "ت", "ث", "ج", "ح", "خ", "د", "ذ", "ر", "ز", "س", "ش", "ص", "ض", "ط", "ظ", "ع", "غ", "ف", "ق", "ك", "ل", "م", "ن", "ه", "و", "ي"};
            QStringList arabicIPA = {"/ʔ/", "/b/", "/t/", "/θ/", "/dʒ/", "/ħ/", "/x/", "/d/", "/ð/", "/r/", "/z/", "/s/", "/ʃ/", "/sˤ/", "/dˤ/", "/tˤ/", "/ðˤ/", "/ʕ/", "/ɣ/", "/f/", "/q/", "/k/", "/l/", "/m/", "/n/", "/h/", "/w/", "/j/"};
            addAlphabetToGrid("Arabic", arabicLetters, arabicIPA);
            break;
        }
        case 17: {
            // 添加阿拉伯扩展字母（包括波斯语、乌尔都语等使用的字母）
            QStringList arabicExtendedLetters = {"پ", "چ", "ژ", "گ", "ڤ", "ڭ", "ڨ", "ڪ", "ڧ", "ڭ", "ٻ", "ڀ", "ٺ", "ٿ", "ڃ", "ڄ", "څ", "ݮ", "ݯ", "ݰ", "ݱ", "ݲ", "ݳ", "ݴ"};
            QStringList arabicExtendedIPA = {"/p/", "/tʃ/", "/ʒ/", "/ɡ/", "/v/", "/ŋ/", "/ɡ/", "/k/", "/q/", "/ŋ/", "/ɓ/", "/ɓ/", "/ʈ/", "/ʈ/", "/c/", "/c/", "/c/", "/ɖ/", "/ɖ/", "/ɖ/", "/ɗ/", "/ɗ/", "/ɗ/", "/ɗ/"};
            addAlphabetToGrid("Arabic (Extended)", arabicExtendedLetters, arabicExtendedIPA);
        }

        default:
            // 所有字母表加载完成
            loadTimer->stop();
            finalizeLoadingUI();
            return;
        }
        
        // 更新进度条
        if (progressBar) {
            progressBar->setValue((currentAlphabetIndex + 1) * 100 / totalAlphabets);
        }
        
        // 增加索引
        currentAlphabetIndex++;
        
        // 处理事件循环，确保界面更新
        QCoreApplication::processEvents();
        
    } catch (const std::exception& e) {
        qCritical() << "Failed to load alphabet:" << e.what();
        loadTimer->stop();
    } catch (...) {
        qCritical() << "Unknown error occurred while loading alphabet";
        loadTimer->stop();
    }
}

void PhoneticChartDialog::initializeLoadingUI()
{
    // 获取滚动区域的内容widget
    QScrollArea *scrollArea = ui->scrollArea;
    QWidget *container = scrollArea->widget();
    QGridLayout *gridLayout = qobject_cast<QGridLayout*>(container->layout());
    
    if (!gridLayout) {
        return;
    }
    
    // 创建进度条
    if (!progressBar) {
        progressBar = new QProgressBar();
        progressBar->setRange(0, 100);
        progressBar->setValue(0);
        progressBar->setTextVisible(true);
        progressBar->setFormat(tr("Loading phonetic chart... %p%"));
        gridLayout->addWidget(progressBar, 0, 0);
    }
}

void PhoneticChartDialog::finalizeLoadingUI()
{
    // 获取滚动区域的内容widget
    QScrollArea *scrollArea = ui->scrollArea;
    QWidget *container = scrollArea->widget();
    QGridLayout *gridLayout = qobject_cast<QGridLayout*>(container->layout());
    
    if (!gridLayout || !progressBar) {
        return;
    }
    
    // 移除进度条
    gridLayout->removeWidget(progressBar);
    delete progressBar;
    progressBar = nullptr;
    
    // 调整布局
    container->adjustSize();
    scrollArea->updateGeometry();
}

void PhoneticChartDialog::clearGrid()
{
    try {
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
    } catch (const std::exception& e) {
        qCritical() << "Failed to clear grid:" << e.what();
    } catch (...) {
        qCritical() << "Unknown error occurred while clearing grid";
    }
}

void PhoneticChartDialog::addAlphabetToGrid(const QString& title, const QStringList& letters, const QStringList& ipa)
{
    try {
        // 直接使用UI文件中的滚动区域
        QScrollArea *scrollArea = ui->scrollArea;
        if (!scrollArea) {
            qWarning() << "Scroll area not found in UI";
            return;
        }

        QWidget *container = scrollArea->widget();
        if (!container) {
            qWarning() << "Container widget not found in scroll area";
            return;
        }

        QGridLayout *gridLayout = qobject_cast<QGridLayout*>(container->layout());
        if (!gridLayout) {
            qWarning() << "Grid layout not found in container";
            return;
        }

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

        // 处理事件循环，防止界面卡顿
        QCoreApplication::processEvents();

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

            // 每添加10个字母处理一次事件循环，防止界面卡顿
            if (i % 10 == 0) {
                QCoreApplication::processEvents();
            }
        }

        // 更新当前行数
        int rowsNeeded = (letters.size() + lettersPerRow - 1) / lettersPerRow;
        currentRow += rowsNeeded + 2; // +2 因为标题和空行

        // 添加空行分隔不同的字母表
        gridLayout->addItem(new QSpacerItem(10, 20), currentRow, 0);
    } catch (const std::exception& e) {
        qCritical() << "Failed to add alphabet to grid:" << e.what();
    } catch (...) {
        qCritical() << "Unknown error occurred while adding alphabet to grid";
    }
}

void PhoneticChartDialog::closeEvent(QCloseEvent *event)
{
    event->accept();
    hide();
}
