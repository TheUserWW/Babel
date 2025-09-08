#ifndef LETTERCONVERTER_H
#define LETTERCONVERTER_H

#include <QObject>
#include <QMap>
#include <QString>
#include <windows.h>
#include <imm.h>

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
        Ottoman,    // 新增：奥斯曼土耳其文
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
    QString convertText(const QString &text, AlphabetSystem system, ConversionDirection direction = LatinToTarget);
    QString convertWithMap(const QString &text, const QMap<QString, QString> &map);

private:
    void initializeMaps();

    // 正向映射
    QMap<QString, QString> latinToCyrillic;
    QMap<QString, QString> latinToGreek;
    QMap<QString, QString> latinToKhmer;
    QMap<QString, QString> latinToSyriac;
    QMap<QString, QString> latinToTibetan;
    QMap<QString, QString> latinToDevanagari;
    QMap<QString, QString> latinToHebrew;
    QMap<QString, QString> latinToRunic;
    QMap<QString, QString> latinToHangul;
    QMap<QString, QString> latinToKana;
    QMap<QString, QString> latinToZhuyin;
    QMap<QString, QString> latinToArabic;
    QMap<QString, QString> latinToUyghur;
    QMap<QString, QString> latinToPersian;
    QMap<QString, QString> latinToGeorgian;
    QMap<QString, QString> latinToGeez;  // 新增：吉兹字母正向映射
    QMap<QString, QString> latinToThai;  // 新增：泰文正向映射
    QMap<QString, QString> latinToArmenian;  // 新增：亚美尼亚字母正向映射
    QMap<QString, QString> latinToBengali;  // 新增：孟加拉字母正向映射
    QMap<QString, QString> latinToKurdish;  // 新增：库尔德文正向映射
    QMap<QString, QString> latinToPashto;  // 新增：普什图文正向映射
    QMap<QString, QString> latinToOttoman;  // 新增：奥斯曼土耳其文正向映射
    
    // 反向映射
    QMap<QString, QString> pashtoToLatin;
    QMap<QString, QString> cyrillicToLatin;
    QMap<QString, QString> greekToLatin;
    QMap<QString, QString> khmerToLatin;
    QMap<QString, QString> syriacToLatin;
    QMap<QString, QString> tibetanToLatin;
    QMap<QString, QString> devanagariToLatin;
    QMap<QString, QString> hebrewToLatin;
    QMap<QString, QString> runicToLatin;
    QMap<QString, QString> hangulToLatin;
    QMap<QString, QString> kanaToLatin;
    QMap<QString, QString> zhuyinToLatin;
    QMap<QString, QString> arabicToLatin;
    QMap<QString, QString> uyghurToLatin;
    QMap<QString, QString> persianToLatin;
    QMap<QString, QString> georgianToLatin;
    QMap<QString, QString> geezToLatin;  // 新增：吉兹字母反向映射
    QMap<QString, QString> thaiToLatin;  // 新增：泰文反向映射
    QMap<QString, QString> armenianToLatin;  // 新增：亚美尼亚字母反向映射
    QMap<QString, QString> bengaliToLatin;  // 新增：孟加拉字母反向映射
    QMap<QString, QString> kurdishToLatin;  // 新增：库尔德文反向映射
    QMap<QString, QString> ottomanToLatin;
};

#endif // LETTERCONVERTER_H

