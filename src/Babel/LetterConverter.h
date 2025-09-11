#ifndef LETTERCONVERTER_H
#define LETTERCONVERTER_H

#include <QObject>
#include <QHash>
#include <QString>


class LetterConverter : public QObject
{
    Q_OBJECT
public:
    explicit LetterConverter(QObject *parent = nullptr);

    enum AlphabetSystem {
        Latin,      // 拉丁字母
        Cyrillic,   // 西里尔字母
        Greek,      // 希腊字母
        Khmer,      // 高棉文
        Syriac,     // 叙利亚字母
        Tibetan,    // 藏文字母
        Devanagari, // 天城体梵文字母
        Hebrew,     // 希伯来字母
        Runic,      // 卢恩字母
        Hangul,     // 谚文字母
        Kana,       // 假名
        Zhuyin,     // 注音符号
        Arabic,     // 阿拉伯文
        Uyghur,     // 维吾尔文
        Persian,    // 波斯语
        Georgian,   // 格鲁吉亚文
        Geez,       // 吉兹字母
        Thai,       // 泰文
        Armenian,   // 亚美尼亚字母
        Bengali,    // 孟加拉字母
        Kurdish,    // 库尔德文
        Pashto,     // 普什图文
        Ottoman,    // 奥斯曼土耳其文
        Tamil,      // 泰米尔文
        Telugu,     // 泰卢固文
        Kannada,    // 卡纳达文
        Assamese,   // 阿萨姆文
        OldUyghur,  // 回鹘蒙文
        Manchu,     // 满文
        Inuktitut,  // 因纽特文
        OldTurkic,  // 古突厥文
        OldHunnic,  // 古匈奴文
        Phoenician, // 腓尼基文
        Sogdian,    // 粟特文
        TraditionalHungarian, // 传统匈牙利文
    };
    Q_ENUM(AlphabetSystem)

    enum ConversionDirection {
        LatinToTarget,
        TargetToLatin
    };
    Q_ENUM(ConversionDirection)
    QString matchCase(const QString &src, const QString &mapped);
    QString convertFromCyrillic(const QString &text);
    QString convertToCyrillic(const QString &text);
    QString convertToGreek(const QString &text);
    QString convertFromGreek(const QString &text);
    QString convertToArabic(const QString &text);
    QString convertFromArabic(const QString &text);
    QString convertToKana(const QString &text);
    QString convertFromKana(const QString &text);
    QString convertToHebrew(const QString &text);
    QString convertFromHebrew(const QString &text);
    QString convertText(const QString &text, AlphabetSystem system, ConversionDirection direction = LatinToTarget);
    QString convertWithMap(const QString &text, const QHash<QString, QString> &map);  // 修改参数类型为QHash

private:
    void initializeMaps();
    bool isVowel(const QChar &c);
    QString getHebrewVowelSymbol(const QChar &c);

    // 正向映射
    QHash<QString, QString> latinToCyrillic;  // 将QMap替换为QHash
    QHash<QString, QString> latinToGreek;
    QHash<QString, QString> latinToKhmer;
    QHash<QString, QString> latinToSyriac;
    QHash<QString, QString> latinToTibetan;
    QHash<QString, QString> latinToDevanagari;
    QHash<QString, QString> latinToHebrew;
    QHash<QString, QString> latinToRunic;
    QHash<QString, QString> latinToHangul;
    QHash<QString, QString> latinToKana;
    QHash<QString, QString> latinToZhuyin;
    QHash<QString, QString> latinToArabic;
    QHash<QString, QString> latinToUyghur;
    QHash<QString, QString> latinToPersian;
    QHash<QString, QString> latinToGeorgian;
    QHash<QString, QString> latinToGeez;
    QHash<QString, QString> latinToThai;
    QHash<QString, QString> latinToArmenian;
    QHash<QString, QString> latinToBengali;
    QHash<QString, QString> latinToKurdish;
    QHash<QString, QString> latinToPashto;
    QHash<QString, QString> latinToOttoman;
    QHash<QString, QString> latinToTamil;  
    QHash<QString, QString> latinToTelugu; 
    QHash<QString, QString> latinToKannada;
    QHash<QString, QString> latinToAssamese;
    QHash<QString, QString> latinToOldUyghur; //new
    QHash<QString, QString> latinToManchu; //new
    QHash<QString, QString> latinToInuktitut; //new
    QHash<QString, QString> latinToOldTurkic; //new
    QHash<QString, QString> latinToOldHunnic; //new
    QHash<QString, QString> latinToPhoenician; //new
    QHash<QString, QString> latinToSogdian; //new
    QHash<QString, QString> latinToTraditionalHungarian; // 传统匈牙利文

    // 反向映射
    QHash<QString, QString> pashtoToLatin;  // 将QMap替换为QHash
    QHash<QString, QString> cyrillicToLatin;
    QHash<QString, QString> greekToLatin;
    QHash<QString, QString> khmerToLatin;
    QHash<QString, QString> syriacToLatin;
    QHash<QString, QString> tibetanToLatin;
    QHash<QString, QString> devanagariToLatin;
    QHash<QString, QString> hebrewToLatin;
    QHash<QString, QString> runicToLatin;
    QHash<QString, QString> hangulToLatin;
    QHash<QString, QString> kanaToLatin;
    QHash<QString, QString> zhuyinToLatin;
    QHash<QString, QString> arabicToLatin;
    QHash<QString, QString> uyghurToLatin;
    QHash<QString, QString> persianToLatin;
    QHash<QString, QString> georgianToLatin;
    QHash<QString, QString> geezToLatin;
    QHash<QString, QString> thaiToLatin;
    QHash<QString, QString> armenianToLatin;
    QHash<QString, QString> bengaliToLatin;
    QHash<QString, QString> kurdishToLatin;
    QHash<QString, QString> ottomanToLatin;
    QHash<QString, QString> tamilToLatin;
    QHash<QString, QString> teluguToLatin;
    QHash<QString, QString> kannadaToLatin;
    QHash<QString, QString> assameseToLatin;
    QHash<QString, QString> oldUyghurToLatin;
    QHash<QString, QString> manchuToLatin;
    QHash<QString, QString> inuktitutToLatin;
    QHash<QString, QString> oldTurkicToLatin;
    QHash<QString, QString> oldHunnicToLatin;
    QHash<QString, QString> phoenicianToLatin; //new
    QHash<QString, QString> sogdianToLatin; //new
    QHash<QString, QString> traditionalHungarianToLatin; // 传统匈牙利文反向映射
};

#endif // LETTERCONVERTER_H
