#ifndef LETTERCONVERTER_H
#define LETTERCONVERTER_H

#include <QObject>
#include <QMap>
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
        Persian     // 波斯语
    };
    Q_ENUM(AlphabetSystem)

    enum ConversionDirection {
        LatinToTarget,
        TargetToLatin
    };
    Q_ENUM(ConversionDirection)

    QString convertText(const QString &text, AlphabetSystem system, ConversionDirection direction = LatinToTarget);

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

    // 反向映射
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
};

#endif // LETTERCONVERTER_H
