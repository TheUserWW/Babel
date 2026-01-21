#include "LetterConverter.h"
#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>

LetterConverter::LetterConverter(QObject *parent) : QObject(parent)
{
    // 从JSON文件加载映射表
    // 使用相对于可执行文件的路径查找mappings.json
    QString exeDir = QCoreApplication::applicationDirPath();
    QString jsonPath = QDir(exeDir).filePath("mappings.json");
    
    // 如果可执行文件目录中没有找到，尝试在上级目录中查找
    if (!QFile::exists(jsonPath)) {
        QDir parentDir = QDir(exeDir);
        if (parentDir.cdUp()) {
            jsonPath = parentDir.filePath("mappings.json");
        }
    }
    
    if (!loadMappingsFromJson(jsonPath)) {
        qWarning() << "无法从JSON文件加载映射表:" << jsonPath;
        qWarning() << "程序可能无法正常工作";
    }
}



QString LetterConverter::convertText(const QString &text, AlphabetSystem system, ConversionDirection direction)
{
    if (system == Latin) return text;


    // 特殊处理西里尔字母转换
    if (system == Cyrillic) {
        if (direction == LatinToTarget) {
            return convertToCyrillic(text);
        } else {
            return convertFromCyrillic(text);
        }
    }

    // 特殊处理希腊字母转换
    if (system == Greek) {
        if (direction == LatinToTarget) {
            return convertToGreek(text);
        } else {
            return convertFromGreek(text);
        }
    }

    // 特殊处理阿拉伯字母转换
    if (system == Arabic) {
        if (direction == LatinToTarget) {
            return convertToArabic(text);
        } else {
            return convertFromArabic(text);
        }
    }

    // 新增：特殊处理假名转换
    if (system == Kana) {
        if (direction == LatinToTarget) {
            return convertToKana(text);
        } else {
            return convertFromKana(text);
        }
    }

    // 新增：特殊处理天城文转换
    if (system == Devanagari) {
        if (direction == LatinToTarget) {
            return convertToDevanagari(text);
        } else {
            return convertFromDevanagari(text);
        }
    }

    QString intermediateText = text;
    // 如果目标不是拉丁字母且方向是TargetToLatin，先转换为拉丁字母
    if (direction != LatinToTarget) {
        intermediateText = convertText(text, system, LatinToTarget);
    }

    QString result;
    QHash<QString, QString> *currentMap = nullptr; // 修改为QString映射

    if (direction == LatinToTarget) {
        switch(system) {
        case Syriac: currentMap = &latinToSyriac; break;
        case Tibetan: currentMap = &latinToTibetan; break;
        case Devanagari: currentMap = &latinToDevanagari; break;
        case Hebrew: currentMap = &latinToHebrew; break;
        case Runic: currentMap = &latinToRunic; break;
        case Hangul: currentMap = &latinToHangul; break;
        case Zhuyin: currentMap = &latinToZhuyin; break;
        case Arabic: currentMap = &latinToArabic; break;
        case Uyghur: currentMap = &latinToUyghur; break;
        case Persian: currentMap = &latinToPersian; break;
        case Khmer: currentMap = &latinToKhmer; break;
        case Georgian: currentMap = &latinToGeorgian; break;
        case Geez: currentMap = &latinToGeez; break;
        case Thai: currentMap = &latinToThai; break;
        case Armenian: currentMap = &latinToArmenian; break;
        case Bengali: currentMap = &latinToBengali; break; 
        case Kurdish: currentMap = &latinToKurdish; break; 
        case Pashto: currentMap = &latinToPashto; break; 
        case Ottoman: currentMap = &latinToOttoman; break; 
        case Tamil: currentMap = &latinToTamil; break;
        case Telugu: currentMap = &latinToTelugu; break;
        case Kannada: currentMap = &latinToKannada; break;
        case Assamese: currentMap = &latinToAssamese; break;
        case OldUyghur: currentMap = &latinToOldUyghur; break;
        case Manchu: currentMap = &latinToManchu; break;
        case Inuktitut: currentMap = &latinToInuktitut; break;
        case OldTurkic: currentMap = &latinToOldTurkic; break;
        case OldItalic: currentMap = &latinToOldItalic; break;
        case Phoenician: currentMap = &latinToPhoenician; break;
        case Sogdian: currentMap = &latinToSogdian; break;
        case TraditionalHungarian: currentMap = &latinToTraditionalHungarian; break;
        case OldPersian: currentMap = &latinToOldPersian; break;
        case OldSouthArabian: currentMap = &latinToOldSouthArabian; break;
        case OldNorthArabian: currentMap = &latinToOldNorthArabian; break;
        case MeroiticHieroglyphs: currentMap = &latinToMeroiticHieroglyphs; break;
        case MeroiticCursive: currentMap = &latinToMeroiticCursive; break;
        case Samaritan: currentMap = &latinToSamaritan; break;
        case Urdu: currentMap = &latinToUrdu; break;
        case Dhivehi: currentMap = &latinToDhivehi; break;
        case OldDhivehi: currentMap = &latinToOldDhivehi; break;
        default: break;
        }
    } else {
        switch(system) {
        case Cyrillic: currentMap = &cyrillicToLatin; break;
        case Syriac: currentMap = &syriacToLatin; break;
        case Tibetan: currentMap = &tibetanToLatin; break;
        case Devanagari: currentMap = &devanagariToLatin; break;
        case Hebrew: currentMap = &hebrewToLatin; break;
        case Runic: currentMap = &runicToLatin; break;
        case Hangul: currentMap = &hangulToLatin; break;
        case Zhuyin: currentMap = &zhuyinToLatin; break;
        case Arabic: currentMap = &arabicToLatin; break;
        case Uyghur: currentMap = &uyghurToLatin; break;
        case Persian: currentMap = &persianToLatin; break;
        case Khmer: currentMap = &khmerToLatin; break;
        case Georgian: currentMap = &georgianToLatin; break;
        case Geez: currentMap = &geezToLatin; break; 
        case Thai: currentMap = &thaiToLatin; break; 
        case Armenian: currentMap = &armenianToLatin; break; 
        case Bengali: currentMap = &bengaliToLatin; break; 
        case Kurdish: currentMap = &kurdishToLatin; break; 
        case Pashto: currentMap = &pashtoToLatin; break;
        case Ottoman: currentMap = &ottomanToLatin; break;
        case Tamil: currentMap = &tamilToLatin; break;
        case Telugu: currentMap = &teluguToLatin; break; 
        case Kannada: currentMap = &kannadaToLatin; break; 
        case Assamese: currentMap = &assameseToLatin; break; 
        case OldUyghur: currentMap = &oldUyghurToLatin; break;
        case Manchu: currentMap = &manchuToLatin; break;
        case Inuktitut: currentMap = &inuktitutToLatin; break;
        case OldTurkic: currentMap = &oldTurkicToLatin; break; 
        case OldItalic: currentMap = &oldItalicToLatin; break; 
        case Phoenician: currentMap = &phoenicianToLatin; break; 
        case Sogdian: currentMap = &sogdianToLatin; break; 
        case TraditionalHungarian: currentMap = &traditionalHungarianToLatin; break; 
        case OldPersian: currentMap = &oldPersianToLatin; break; //new
        case OldSouthArabian: currentMap = &oldSouthArabianToLatin; break;
        case OldNorthArabian: currentMap = &oldNorthArabianToLatin; break;
        case MeroiticHieroglyphs: currentMap = &meroiticHieroglyphsToLatin; break;
        case MeroiticCursive: currentMap = &meroiticCursiveToLatin; break;
        case Samaritan: currentMap = &samaritanToLatin; break;  // 撒玛利亚字母反向映射
        case Urdu: currentMap = &urduToLatin; break;
        case Dhivehi: currentMap = &dhivehiToLatin; break;
        case OldDhivehi: currentMap = &oldDhivehiToLatin; break;
        default: break;
        }
    }

    if (!currentMap) return text;

    for (int i = 0; i < text.length(); ++i) {
        QChar currentChar = text.at(i);
        QString lookupStr;

        //检查四字组合
        if (i < text.length() - 3) {
            lookupStr = text.mid(i, 4).toUpper();
            if (currentMap->contains(lookupStr)) {
                QString converted = currentMap->value(lookupStr);
                // 保持大小写一致性
                if (text.mid(i, 4).toLower() == lookupStr.toLower()) {
                    result += converted.toLower();
                } else {
                    result += converted;
                }
                i += 3; 
                continue;
            }
        }

        // 检查是否可能是三字组合
        if (i < text.length() - 2) {
            lookupStr = text.mid(i, 3).toUpper();
            if (currentMap->contains(lookupStr)) {
                QString converted = currentMap->value(lookupStr);
                // 保持大小写一致性
                if (text.mid(i, 3).toLower() == lookupStr.toLower()) {
                    result += converted.toLower();
                } else {
                    result += converted;
                }
                i += 2; 
                continue;
            }
        }

        // 检查是否可能是双字符组合（如"Ch"、"Kh"等）
        if (i < text.length() - 1) {
            lookupStr = text.mid(i, 2).toUpper();
            if (currentMap->contains(lookupStr)) {
                QString converted = currentMap->value(lookupStr);
                // 保持大小写一致性
                if (text.mid(i, 2).toLower() == lookupStr.toLower()) {
                    result += converted.toLower();
                } else {
                    result += converted;
                }
                i++; // 跳过下一个字符
                continue;
            }
        }

        // 单字符查找
        lookupStr = currentChar.toUpper();
        if (currentMap->contains(lookupStr)) {
            QString converted = currentMap->value(lookupStr);
            // 保持大小写一致性
            result += currentChar.isLower() ? converted.toLower() : converted;
        } else {
            result += currentChar;
        }
    }

    return result;
}


// 西里尔字母转换逻辑
QString LetterConverter::convertToCyrillic(const QString &text)
{
    QString result;
    for (int i = 0; i < text.length(); i++) {
        QChar c = text[i];
        QString current = QString(c).toUpper();
        bool isLower = c.isLower();

        // 处理三字符组合
        if (i < text.length() - 2) {
            QString triple = text.mid(i, 3).toUpper();
            if (latinToCyrillic.contains(triple)) {
                QString converted = latinToCyrillic[triple];
                result += isLower ? converted.toLower() : converted;
                i += 2;
                continue;
            }
        }

        // 处理双字符组合
        if (i < text.length() - 1) {
            QString pair = text.mid(i, 2).toUpper();
            if (latinToCyrillic.contains(pair)) {
                QString converted = latinToCyrillic[pair];
                result += isLower ? converted.toLower() : converted;
                i++;
                continue;
            }
        }

        // 处理特殊规则：C 的发音使用贪心算法确定
        if (current == "C") {
            QString cConversion;
            int skipCount = 0;
            
            // 贪心算法：优先匹配最长的有效组合
            // 检查 "ch" 组合（发 "ч" 音）
            if (i < text.length() - 1 && text[i + 1].toUpper() == 'H') {
                // 进一步检查是否是 "chr" 组合（发 "хр" 音）
                if (i < text.length() - 2 && text[i + 2].toUpper() == 'R') {
                    cConversion = isLower ? "хр" : "ХР";
                    skipCount = 2;
                } else {
                    cConversion = isLower ? "ч" : "Ч";
                    skipCount = 1;
                }
            }
            // 检查 "ck" 组合（发 "к" 音）
            else if (i < text.length() - 1 && text[i + 1].toUpper() == 'K') {
                cConversion = isLower ? "к" : "К";
                skipCount = 1;
            }
            // 检查 "cs" 组合（发 "кс" 音）
            else if (i < text.length() - 1 && text[i + 1].toUpper() == 'S') {
                cConversion = isLower ? "кс" : "КС";
                skipCount = 1;
            }
            // 检查 "cz" 组合（发 "ч" 音）
            else if (i < text.length() - 1 && text[i + 1].toUpper() == 'Z') {
                cConversion = isLower ? "ч" : "Ч";
                skipCount = 1;
            }
            // 检查 "ci" 组合（发 "ц" 音）
            else if (i < text.length() - 1 && text[i + 1].toUpper() == 'I') {
                cConversion = isLower ? "ц" : "Ц";
                skipCount = 1;
            }
            // 检查 "ce" 组合（发 "с" 音）
            else if (i < text.length() - 1 && text[i + 1].toUpper() == 'E') {
                cConversion = isLower ? "с" : "С";
                skipCount = 1;
            }
            // 检查 "cy" 组合（发 "с" 音）
            else if (i < text.length() - 1 && text[i + 1].toUpper() == 'Y') {
                cConversion = isLower ? "с" : "С";
                skipCount = 1;
            }
            // 检查 "ca" 组合（发 "к" 音）
            else if (i < text.length() - 1 && text[i + 1].toUpper() == 'A') {
                cConversion = isLower ? "к" : "К";
                skipCount = 1;
            }
            // 检查 "co" 组合（发 "к" 音）
            else if (i < text.length() - 1 && text[i + 1].toUpper() == 'O') {
                cConversion = isLower ? "к" : "К";
                skipCount = 1;
            }
            // 检查 "cu" 组合（发 "к" 音）
            else if (i < text.length() - 1 && text[i + 1].toUpper() == 'U') {
                cConversion = isLower ? "к" : "К";
                skipCount = 1;
            }
            // 检查 "c" 在词尾（发 "к" 音）
            else if (i == text.length() - 1) {
                cConversion = isLower ? "к" : "К";
            }
            // 默认情况：C 发 "к" 音
            else {
                cConversion = isLower ? "к" : "К";
            }
            
            result += cConversion;
            i += skipCount; // 跳过已处理的字符
            continue;
        }

        // 处理特殊规则：G 的发音取决于后续元音
        if (current == "G") {
            // 检查是否是 "gh" 组合
            if (i < text.length() - 1 && text[i+1].toUpper() == 'H') {
                result += isLower ? "гх" : "ГХ";
                i++; // 跳过 H
            } else {
                result += isLower ? "г" : "Г"; // 正确：将 G 转换为 г
            }
            continue;
        }

        // 处理特殊规则：X -> КС，但在词首时可能发 "з" 音（某些外来词）
        if (current == "X") {
            if (i == 0) {
                // 词首 X 在外来词中有时发 "з" 音
                result += isLower ? "з" : "З";
            } else {
                result += isLower ? "кс" : "КС";
            }
            continue;
        }

        // 处理软音符号和硬音符号
        if (current == "'") {
            result += QChar(0x044C); // ь
            continue;
        }
        if (current == "`") {
            result += QChar(0x044A); // ъ
            continue;
        }

        // 默认映射
        if (latinToCyrillic.contains(current)) {
            QString converted = latinToCyrillic[current];
            result += isLower ? converted.toLower() : converted;
        } else {
            result += c;
        }
    }
    return result;
}

QString LetterConverter::convertFromCyrillic(const QString &text)
{
    QString result;
    for (int i = 0; i < text.length(); i++) {
        QChar c = text[i];
        QString current = QString(c);
        bool isLower = c.isLower();

        // 处理多字符组合
        if (i < text.length() - 1) {
            QString pair = text.mid(i, 2);
            if (cyrillicToLatin.contains(pair)) {
                QString converted = cyrillicToLatin[pair];
                result += isLower ? converted.toLower() : converted;
                i++;
                continue;
            }
        }

        // 默认映射
        if (cyrillicToLatin.contains(current)) {
            QString converted = cyrillicToLatin[current];
            result += isLower ? converted.toLower() : converted;
        } else {
            result += c;
        }
    }
    return result;
}


// 希腊字母转换逻辑
QString LetterConverter::convertToGreek(const QString &text)
{
    QString result;
    for (int i = 0; i < text.length(); i++) {
        QChar c = text[i];
        QString current = QString(c).toUpper();
        bool isLower = c.isLower();

        // 处理多字符组合
        if (i < text.length() - 1) {
            QString pair = text.mid(i, 2).toUpper();
            if (latinToGreek.contains(pair)) {
                QString converted = latinToGreek[pair];
                result += isLower ? converted.toLower() : converted;
                i++;
                continue;
            }
        }

        // 处理特殊组合：带声调的元音
        if (i < text.length() - 1) {
            QString vowelPair = text.mid(i, 2).toUpper();
            if (latinToGreek.contains(vowelPair)) {
                QString converted = latinToGreek[vowelPair];
                result += isLower ? converted.toLower() : converted;
                i++;
                continue;
            }
        }

        // 默认映射
        if (latinToGreek.contains(current)) {
            QString converted = latinToGreek[current];
            result += isLower ? converted.toLower() : converted;
        } else {
            result += c;
        }
    }
    return result;
}

QString LetterConverter::convertFromGreek(const QString &text)
{
    // 使用反向映射表进行转换
    return convertWithMap(text, greekToLatin);
}

// 阿拉伯字母转换逻辑
QString LetterConverter::convertToArabic(const QString &text)
{
    QString result;
    int i = 0;
    int n = text.length();

    while (i < n) {
        bool matched = false;

        // 按长度递减尝试匹配（6字符 -> 5字符 -> ... -> 1字符）
        for (int len = 6; len >= 1; len--) {
            if (i + len > n) continue;

            QString segment = text.mid(i, len);
            QString key = segment.toLower();  // 统一使用小写作为键

            // 检查映射
            if (latinToArabic.contains(key)) {
                QString converted = latinToArabic[key];
                result += converted;
                i += len;
                matched = true;
                break;
            }
        }

        if (matched) continue;

        // 处理特殊规则
        QChar currentChar = text[i];
        QString currentUpper = QString(currentChar).toUpper();

        // 处理喉音标记
        if (currentUpper == "H" && i > 0) {
            QChar prevChar = text[i-1];
            QString prevUpper = QString(prevChar).toUpper();
            if (prevUpper == "A" || prevUpper == "U" || prevUpper == "I") {
                result += QChar(0x0621); // ء
                i++;
                continue;
            }
        }

        // 处理 Q 的特殊情况
        if (currentUpper == "Q" && i + 1 < n) {
            QChar nextChar = text[i+1];
            QString nextUpper = QString(nextChar).toUpper();
            if (nextUpper == "I") {
                result += currentChar.isLower() ?
                         QString(QChar(0x0643)).toLower() :
                         QString(QChar(0x0643));
                i += 2;  // 跳过 Q 和 I
                continue;
            }
        }

        // 处理 X 的特殊情况
        if (currentUpper == "X") {
            if (i + 2 < n &&
                (text[i+1] == 'i' || text[i+1] == 'I') &&
                (text[i+2] == 'n' || text[i+2] == 'N')) {
                result += QChar(0x0634); // ش
                i += 3;  // 跳过 X, i, n
            } else {
                result += QChar(0x0632); // ز
                i++;
            }
            continue;
        }

        // 处理 E 的特殊情况
        if (currentUpper == "E") {
            if (i == 0) {
                result += QChar(0x0625); // إ
            } else {
                result += QChar(0x064A); // ي
            }
            i++;
            continue;
        }

        // 默认映射
        if (latinToArabic.contains(currentUpper)) {
            result += latinToArabic[currentUpper];
        } else {
            result += currentChar;
        }

        i++;
    }

    return result;
}



QString LetterConverter::convertFromArabic(const QString &text){
    // 使用反向映射表进行转换
    return convertWithMap(text, arabicToLatin);
}

// 假名转换逻辑
QString LetterConverter::convertToKana(const QString &text)
{
    QString result;
    for (int i = 0; i < text.length(); i++) {
        QChar c = text[i];
        QString current = QString(c).toUpper();
        bool isLower = c.isLower();

        // 处理拗音 (如 kya, shu, cho)
        if (i < text.length() - 2) {
            QString tri = text.mid(i, 3).toLower();
            if (tri == "kya") { result += isLower ? "きゃ" : "キャ"; i += 2; continue; }
            if (tri == "kyu") { result += isLower ? "きゅ" : "キュ"; i += 2; continue; }
            if (tri == "kyo") { result += isLower ? "きょ" : "キョ"; i += 2; continue; }
            if (tri == "sha") { result += isLower ? "しゃ" : "シャ"; i += 2; continue; }
            if (tri == "shu") { result += isLower ? "しゅ" : "シュ"; i += 2; continue; }
            if (tri == "sho") { result += isLower ? "しょ" : "ショ"; i += 2; continue; }
            if (tri == "cha") { result += isLower ? "ちゃ" : "チャ"; i += 2; continue; }
            if (tri == "chu") { result += isLower ? "ちゅ" : "チュ"; i += 2; continue; }
            if (tri == "cho") { result += isLower ? "ちょ" : "チョ"; i += 2; continue; }
        }

        // 处理长音
        if (i > 0 && (c == 'u' || c == 'U') &&
            (text[i-1] == 'o' || text[i-1] == 'O')) {
            result += isLower ? "う" : "ウ";
            continue;
        }

        // 处理促音 (小写 つ)
        if (c == 't' && i < text.length() - 1 && text[i+1] == text[i+1]) {
            result += isLower ? "っ" : "ッ";
            continue;
        }

        // 处理单辅音 + 元音组合
        if (i < text.length() - 1) {
            QChar next = text[i+1];
            QString syllable = current + QString(next).toUpper();
            if (syllable == "KA") { result += isLower ? "か" : "カ"; i++; continue; }
            if (syllable == "KI") { result += isLower ? "き" : "キ"; i++; continue; }
            // ... 其他音节组合
        }

        // 默认映射
        if (latinToKana.contains(current)) {
            QString converted = latinToKana[current];
            result += isLower ? converted.toLower() : converted;
        } else {
            result += c;
        }
    }
    return result;
}

QString LetterConverter::convertFromKana(const QString &text)
{
    // 使用反向映射表进行转换
    return convertWithMap(text, kanaToLatin);
}

// 天城文转换逻辑
QString LetterConverter::convertToDevanagari(const QString &text)
{
    QString result;
    int i = 0;
    int n = text.length();

    while (i < n) {
        bool matched = false;

        // 按长度递减尝试匹配（4字符 -> 3字符 -> 2字符 -> 1字符）
        for (int len = 4; len >= 1; len--) {
            if (i + len > n) continue;

            QString segment = text.mid(i, len);
            QString key = segment.toLower();  // 统一使用小写作为键

            // 检查映射
            if (latinToDevanagari.contains(key)) {
                QString converted = latinToDevanagari[key];
                
                // 处理大小写一致性
                if (segment.toLower() == key) {
                    result += converted;
                } else {
                    // 对于大写字母，尝试保持适当的大小写格式
                    if (segment.length() == 1 && segment[0].isUpper()) {
                        // 单字符大写：保持原样
                        result += converted;
                    } else {
                        // 多字符组合：使用原格式
                        result += converted;
                    }
                }
                i += len;
                matched = true;
                break;
            }
        }

        if (matched) continue;

        // 处理特殊的天城文元音副标规则
        QChar currentChar = text[i];
        QString currentUpper = QString(currentChar).toUpper();

        // 处理元音副标：当辅音后面跟着元音时，需要组合成带副标的字符
        if (i > 0 && isVowel(currentChar)) {
            QChar prevChar = text[i-1];
            QString prevUpper = QString(prevChar).toUpper();
            
            // 检查前一个字符是否是辅音
            if (!isVowel(prevChar) && latinToDevanagari.contains(prevUpper)) {
                // 获取辅音的基础形式
                QString baseConsonant = latinToDevanagari[prevUpper];
                
                // 根据当前元音添加相应的副标
                if (currentUpper == "A") {
                    // 默认辅音已经包含a音，不需要额外处理
                    result += baseConsonant;
                } else if (currentUpper == "I" || currentUpper == "Í" || currentUpper == "Ī") {
                    // i音副标：在辅音后添加ि
                    result += baseConsonant + QString(QChar(0x093F));
                } else if (currentUpper == "U" || currentUpper == "Ú" || currentUpper == "Ū") {
                    // u音副标：在辅音后添加ु
                    result += baseConsonant + QString(QChar(0x0941));
                } else if (currentUpper == "E" || currentUpper == "É" || currentUpper == "Ē") {
                    // e音副标：在辅音后添加े
                    result += baseConsonant + QString(QChar(0x0947));
                } else if (currentUpper == "O" || currentUpper == "Ó" || currentUpper == "Ō") {
                    // o音副标：在辅音后添加ो
                    result += baseConsonant + QString(QChar(0x094B));
                } else {
                    // 其他元音：使用基础映射
                    result += latinToDevanagari.contains(currentUpper) ? 
                             latinToDevanagari[currentUpper] : QString(currentChar);
                }
                i++;
                continue;
            }
        }

        // 默认处理：使用基础映射
        QString lookupKey = currentUpper;
        if (!latinToDevanagari.contains(lookupKey)) {
            // 如果大写形式不存在，尝试小写形式
            lookupKey = QString(currentChar).toLower();
        }
        
        if (latinToDevanagari.contains(lookupKey)) {
            result += latinToDevanagari[lookupKey];
        } else {
            result += currentChar;
        }
        i++;
    }

    return result;
}

QString LetterConverter::convertFromDevanagari(const QString &text)
{
    // 使用反向映射表进行转换
    return convertWithMap(text, devanagariToLatin);
}


// 修改convertWithMap函数，将QMap替换为QHash
QString LetterConverter::convertWithMap(const QString &text, const QHash<QString, QString> &map)
{
    QString result;
    int i = 0;
    const int length = text.length();

    while (i < length) {
        bool found = false;

        //尝试4字组合
        if (i < text.length() - 3) {
            QString fourChars = text.mid(i, 4);
            if (map.contains(fourChars)) {
                result += map.value(fourChars);
                i += 4;
                found = true;
            }
        }

        // 尝试匹配3个字符
        if (i + 2 < length) {
            QString threeChars = text.mid(i, 3);
            if (map.contains(threeChars)) {
                result += map.value(threeChars);
                i += 3;
                found = true;
            }
        }

        // 尝试匹配2个字符
        if (!found && i + 1 < length) {
            QString twoChars = text.mid(i, 2);
            if (map.contains(twoChars)) {
                result += map.value(twoChars);
                i += 2;
                found = true;
            }
        }

        // 尝试匹配1个字符
        if (!found) {
            QString oneChar = text.mid(i, 1);
            if (map.contains(oneChar)) {
                result += map.value(oneChar);
            } else {
                // 如果没有找到映射，保留原字符
                result += oneChar;
            }
            i += 1;
        }
    }

    return result;
}


// 辅助函数：检查字符是否是元音
bool LetterConverter::isVowel(const QChar &c)
{
    QString upper = QString(c).toUpper();
    return (upper == "A" || upper == "E" || upper == "I" || upper == "O" || upper == "U" ||
            upper == "Á" || upper == "É" || upper == "Í" || upper == "Ó" || upper == "Ú");
}

// 辅助函数：获取希伯来文元音符号
QString LetterConverter::getHebrewVowelSymbol(const QChar &c)
{
    QString upper = QString(c).toUpper();

    // 基本元音映射
    if (upper == "A") return QString(QChar(0x05B7));  // Patach (אַ)
    if (upper == "E") return QString(QChar(0x05B5));  // Segol (אֶ)
    if (upper == "I") return QString(QChar(0x05B9));  // Hiriq (אִ)
    if (upper == "O") return QString(QChar(0x05B9));  // Kamatz (אָ)
    if (upper == "U") return QString(QChar(0x05BB));  // Kubutz (אֻ)

    // 带重音的元音
    if (upper == "Á") return QString(QChar(0x05B8));  // Qamatz Qatan (אָ)
    if (upper == "É") return QString(QChar(0x05B4));  // Hataf Segol (אֱ)
    if (upper == "Í") return QString(QChar(0x05B6));  // Tzeirei (אֵ)
    if (upper == "Ó") return QString(QChar(0x05C7));  // Qamatz Gadol (אֹ)
    if (upper == "Ú") return QString(QChar(0x05B7));  // Shuruk (אוּ)

    return "";
}

// 从JSON文件加载映射表
bool LetterConverter::loadMappingsFromJson(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "无法打开映射表文件:" << filePath;
        return false;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
    
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON解析错误:" << parseError.errorString();
        return false;
    }

    if (!jsonDoc.isObject()) {
        qWarning() << "JSON文件格式错误：根元素不是对象";
        return false;
    }

    QJsonObject rootObject = jsonDoc.object();
    
    // 检查是否存在mappings对象
    if (!rootObject.contains("mappings") || !rootObject["mappings"].isObject()) {
        qWarning() << "JSON文件中未找到mappings对象";
        return false;
    }
    
    QJsonObject mappingsObject = rootObject["mappings"].toObject();
    
    // 加载所有映射表
    loadMappingFromJsonObject(mappingsObject, "latinToCyrillic", latinToCyrillic);
    loadMappingFromJsonObject(mappingsObject, "latinToGreek", latinToGreek);
    loadMappingFromJsonObject(mappingsObject, "latinToKhmer", latinToKhmer);
    loadMappingFromJsonObject(mappingsObject, "latinToSyriac", latinToSyriac);
    loadMappingFromJsonObject(mappingsObject, "latinToTibetan", latinToTibetan);
    loadMappingFromJsonObject(mappingsObject, "latinToDevanagari", latinToDevanagari);
    loadMappingFromJsonObject(mappingsObject, "latinToHebrew", latinToHebrew);
    loadMappingFromJsonObject(mappingsObject, "latinToRunic", latinToRunic);
    loadMappingFromJsonObject(mappingsObject, "latinToHangul", latinToHangul);
    loadMappingFromJsonObject(mappingsObject, "latinToKana", latinToKana);
    loadMappingFromJsonObject(mappingsObject, "latinToZhuyin", latinToZhuyin);
    loadMappingFromJsonObject(mappingsObject, "latinToArabic", latinToArabic);
    loadMappingFromJsonObject(mappingsObject, "latinToUyghur", latinToUyghur);
    loadMappingFromJsonObject(mappingsObject, "latinToPersian", latinToPersian);
    loadMappingFromJsonObject(mappingsObject, "latinToOldPersian", latinToOldPersian);
    loadMappingFromJsonObject(mappingsObject, "latinToSamaritan", latinToSamaritan);
    loadMappingFromJsonObject(mappingsObject, "latinToGeorgian", latinToGeorgian);
    loadMappingFromJsonObject(mappingsObject, "latinToGeez", latinToGeez);
    loadMappingFromJsonObject(mappingsObject, "latinToThai", latinToThai);
    loadMappingFromJsonObject(mappingsObject, "latinToArmenian", latinToArmenian);
    loadMappingFromJsonObject(mappingsObject, "latinToBengali", latinToBengali);
    loadMappingFromJsonObject(mappingsObject, "latinToKurdish", latinToKurdish);
    loadMappingFromJsonObject(mappingsObject, "latinToPashto", latinToPashto);
    loadMappingFromJsonObject(mappingsObject, "latinToOttoman", latinToOttoman);
    loadMappingFromJsonObject(mappingsObject, "latinToTamil", latinToTamil);
    loadMappingFromJsonObject(mappingsObject, "latinToTelugu", latinToTelugu);
    loadMappingFromJsonObject(mappingsObject, "latinToKannada", latinToKannada);
    loadMappingFromJsonObject(mappingsObject, "latinToAssamese", latinToAssamese);
    loadMappingFromJsonObject(mappingsObject, "latinToOldUyghur", latinToOldUyghur);
    loadMappingFromJsonObject(mappingsObject, "latinToManchu", latinToManchu);
    loadMappingFromJsonObject(mappingsObject, "latinToInuktitut", latinToInuktitut);
    loadMappingFromJsonObject(mappingsObject, "latinToOldTurkic", latinToOldTurkic);
    loadMappingFromJsonObject(mappingsObject, "latinToPhoenician", latinToPhoenician);
    loadMappingFromJsonObject(mappingsObject, "latinToSogdian", latinToSogdian);
    loadMappingFromJsonObject(mappingsObject, "latinToTraditionalHungarian", latinToTraditionalHungarian);
    loadMappingFromJsonObject(mappingsObject, "latinToOldItalic", latinToOldItalic);
    loadMappingFromJsonObject(mappingsObject, "latinToOldSouthArabian", latinToOldSouthArabian);
    loadMappingFromJsonObject(mappingsObject, "latinToOldNorthArabian", latinToOldNorthArabian);
    loadMappingFromJsonObject(mappingsObject, "latinToMeroiticHieroglyphs", latinToMeroiticHieroglyphs);
    loadMappingFromJsonObject(mappingsObject, "latinToMeroiticCursive", latinToMeroiticCursive);
    loadMappingFromJsonObject(mappingsObject, "latinToUrdu", latinToUrdu);
    loadMappingFromJsonObject(mappingsObject, "latinToDhivehi", latinToDhivehi);
    loadMappingFromJsonObject(mappingsObject, "latinToOldDhivehi", latinToOldDhivehi);

    // 创建反向映射
    auto createReverseMap = [](const QHash<QString, QString>& forwardMap, QHash<QString, QString>& reverseMap) {
        for (auto it = forwardMap.begin(); it != forwardMap.end(); ++it) {
            if (!reverseMap.contains(it.value())) {
                reverseMap.insert(it.value(), it.key());
            }
        }
    };

    createReverseMap(latinToCyrillic, cyrillicToLatin);
    createReverseMap(latinToGreek, greekToLatin);
    createReverseMap(latinToSyriac, syriacToLatin);
    createReverseMap(latinToTibetan, tibetanToLatin);
    createReverseMap(latinToDevanagari, devanagariToLatin);
    createReverseMap(latinToKhmer, khmerToLatin);
    createReverseMap(latinToHebrew, hebrewToLatin);
    createReverseMap(latinToRunic, runicToLatin);
    createReverseMap(latinToHangul, hangulToLatin);
    createReverseMap(latinToKana, kanaToLatin);
    createReverseMap(latinToZhuyin, zhuyinToLatin);
    createReverseMap(latinToArabic, arabicToLatin);
    createReverseMap(latinToUyghur, uyghurToLatin);
    createReverseMap(latinToPersian, persianToLatin);
    createReverseMap(latinToKhmer, khmerToLatin);
    createReverseMap(latinToHebrew, hebrewToLatin);
    createReverseMap(latinToGeorgian, georgianToLatin);
    createReverseMap(latinToGeez, geezToLatin);
    createReverseMap(latinToThai, thaiToLatin);
    createReverseMap(latinToArmenian, armenianToLatin);
    createReverseMap(latinToBengali, bengaliToLatin);
    createReverseMap(latinToKurdish, kurdishToLatin);
    createReverseMap(latinToPashto, pashtoToLatin);
    createReverseMap(latinToOttoman, ottomanToLatin);
    createReverseMap(latinToTamil, tamilToLatin);
    createReverseMap(latinToTelugu, teluguToLatin);
    createReverseMap(latinToKannada, kannadaToLatin);
    createReverseMap(latinToAssamese, assameseToLatin);
    createReverseMap(latinToOldUyghur, oldUyghurToLatin);
    createReverseMap(latinToOldPersian, oldPersianToLatin);
    createReverseMap(latinToOldTurkic, oldTurkicToLatin);
    createReverseMap(latinToManchu, manchuToLatin);
    createReverseMap(latinToInuktitut, inuktitutToLatin);
    createReverseMap(latinToOldItalic, oldItalicToLatin);
    createReverseMap(latinToPhoenician, phoenicianToLatin);
    createReverseMap(latinToSogdian, sogdianToLatin);
    createReverseMap(latinToTraditionalHungarian, traditionalHungarianToLatin);
    createReverseMap(latinToOldSouthArabian, oldSouthArabianToLatin);
    createReverseMap(latinToOldNorthArabian, oldNorthArabianToLatin);
    createReverseMap(latinToOldPersian, oldPersianToLatin);
    createReverseMap(latinToMeroiticCursive, meroiticCursiveToLatin);
    createReverseMap(latinToUrdu, urduToLatin);
    createReverseMap(latinToDhivehi, dhivehiToLatin);
    createReverseMap(latinToOldDhivehi, oldDhivehiToLatin);

    qDebug() << "成功从JSON文件加载映射表:" << filePath;
    return true;
}

// 从JSON对象加载单个映射表
void LetterConverter::loadMappingFromJsonObject(const QJsonObject &jsonObject, const QString &mapName, QHash<QString, QString> &targetMap)
{
    if (jsonObject.contains(mapName) && jsonObject[mapName].isObject()) {
        QJsonObject mapObject = jsonObject[mapName].toObject();
        targetMap.clear();
        
        for (auto it = mapObject.begin(); it != mapObject.end(); ++it) {
            QString key = it.key();
            QString value = it.value().toString();
            targetMap.insert(key, value);
        }
        
        qDebug() << "加载映射表:" << mapName << "包含" << targetMap.size() << "个条目";
    } else {
        qWarning() << "JSON文件中未找到映射表:" << mapName;
    }
}
