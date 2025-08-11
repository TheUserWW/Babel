#include "LetterConverter.h"

LetterConverter::LetterConverter(QObject *parent) : QObject(parent)
{
    initializeMaps();
}

void LetterConverter::initializeMaps()
{

    // -------------------------
    // 拉丁字母到西里尔字母 (Cyrillic) - 改进与保留
    // -------------------------
    latinToCyrillic["SCH"] = QString(QChar(0x0429)); // Щ
    latinToCyrillic["SH"]  = QString(QChar(0x0428)); // Ш
    latinToCyrillic["CH"]  = QString(QChar(0x0427)); // Ч
    latinToCyrillic["KH"]  = QString(QChar(0x0425)); // Х
    latinToCyrillic["ZH"]  = QString(QChar(0x0416)); // Ж
    latinToCyrillic["TSH"] = QString(QChar(0x0422)) + QString(QChar(0x0428)); // ТШ (示例组合)
    latinToCyrillic["TS"] = QString(QChar(0x0426)); // Ц
    latinToCyrillic["DZ"] = QString(QChar(0x0436)) + QString(QChar(0x043A)); // ДЗ
    latinToCyrillic["DZH"] = QString(QChar(0x0414)) + QString(QChar(0x0416)); // ДЖ
    latinToCyrillic["NJ"] = QString(QChar(0x041D)) + QString(QChar(0x0436)); // Њ
    latinToCyrillic["LJ"] = QString(QChar(0x041B)) + QString(QChar(0x0436)); // Љ

    // 单字符（多数保留原表，但 C/G/X 会在 convertText 中依据后续元音调整）
    latinToCyrillic["A"] = QString(QChar(0x0410)); // А
    latinToCyrillic["B"] = QString(QChar(0x0411)); // Б
    // 注意：C 的映射由 convertText 的发音规则决定（К / С）
    latinToCyrillic["D"] = QString(QChar(0x0414)); // Д
    latinToCyrillic["E"] = QString(QChar(0x0415)); // Е
    latinToCyrillic["F"] = QString(QChar(0x0424)); // Ф
    latinToCyrillic["G"] = QString(QChar(0x0413)); // Г (软音处理在convertText)
    latinToCyrillic["H"] = QString(QChar(0x0425)); // Х
    latinToCyrillic["I"] = QString(QChar(0x0418)); // И
    latinToCyrillic["J"] = QString(QChar(0x0419)); // Й
    latinToCyrillic["K"] = QString(QChar(0x041A)); // К
    latinToCyrillic["L"] = QString(QChar(0x041B)); // Л
    latinToCyrillic["M"] = QString(QChar(0x041C)); // М
    latinToCyrillic["N"] = QString(QChar(0x041D)); // Н
    latinToCyrillic["O"] = QString(QChar(0x041E)); // О
    latinToCyrillic["P"] = QString(QChar(0x041F)); // П
    latinToCyrillic["Q"] = QString(QChar(0x041A)) + QString(QChar(0x0421)); // КС (近似)
    latinToCyrillic["R"] = QString(QChar(0x0420)); // Р
    latinToCyrillic["S"] = QString(QChar(0x0421)); // С
    latinToCyrillic["T"] = QString(QChar(0x0422)); // Т
    latinToCyrillic["U"] = QString(QChar(0x0423)); // У
    latinToCyrillic["V"] = QString(QChar(0x0412)); // В
    latinToCyrillic["W"] = QString(QChar(0x0412)); // В (W 常映射为 В)
    // X 在 convertText 中将被映射为 "КС" 以更接近读音
    latinToCyrillic["Y"] = QString(QChar(0x042B)); // Ы
    latinToCyrillic["Z"] = QString(QChar(0x0417)); // З
    latinToCyrillic["Yo"] = QString(QChar(0x0401)); // Ё
    latinToCyrillic["YU"] = QString(QChar(0x042E)); // Ю
    latinToCyrillic["YA"] = QString(QChar(0x042F)); // Я

    // 带音调/变音字符（尽量用组合字符）
    latinToCyrillic["ā"] = QString(QChar(0x0410)) + QString(QChar(0x0304)); // А̄
    latinToCyrillic["ē"] = QString(QChar(0x0415)) + QString(QChar(0x0304)); // Е̄
    latinToCyrillic["ī"] = QString(QChar(0x0418)) + QString(QChar(0x0304)); // Ӣ
    latinToCyrillic["ō"] = QString(QChar(0x041E)) + QString(QChar(0x0304)); // О̄
    latinToCyrillic["ū"] = QString(QChar(0x0423)) + QString(QChar(0x0304)); // Ӯ
    latinToCyrillic["á"] = QString(QChar(0x0410)) + QString(QChar(0x0301)); // А́
    latinToCyrillic["é"] = QString(QChar(0x0415)) + QString(QChar(0x0301)); // Е́
    latinToCyrillic["í"] = QString(QChar(0x0418)) + QString(QChar(0x0301)); // И́
    latinToCyrillic["ó"] = QString(QChar(0x041E)) + QString(QChar(0x0301)); // О́
    latinToCyrillic["ú"] = QString(QChar(0x0423)) + QString(QChar(0x0301)); // У́
    latinToCyrillic["ǎ"] = QString(QChar(0x0410)) + QString(QChar(0x030C)); // А̌
    latinToCyrillic["ě"] = QString(QChar(0x0415)) + QString(QChar(0x030C)); // Е̌
    latinToCyrillic["ǐ"] = QString(QChar(0x0418)) + QString(QChar(0x030C)); // И̌
    latinToCyrillic["ǒ"] = QString(QChar(0x041E)) + QString(QChar(0x030C)); // О̌
    latinToCyrillic["ǔ"] = QString(QChar(0x0423)) + QString(QChar(0x030C)); // У̌
    latinToCyrillic["à"] = QString(QChar(0x0410)) + QString(QChar(0x0300)); // À
    latinToCyrillic["è"] = QString(QChar(0x0415)) + QString(QChar(0x0300)); // È
    latinToCyrillic["ì"] = QString(QChar(0x0418)) + QString(QChar(0x0300)); // Ì
    latinToCyrillic["ò"] = QString(QChar(0x041E)) + QString(QChar(0x0300)); // Ò
    latinToCyrillic["ù"] = QString(QChar(0x0423)) + QString(QChar(0x0300)); // Ù
    latinToCyrillic["Ä"] = QString(QChar(0x0410)) + QString(QChar(0x0308)); // Ӓ (近似)
    latinToCyrillic["Ö"] = QString(QChar(0x041E)) + QString(QChar(0x0308)); // Ӧ
    latinToCyrillic["Ü"] = QString(QChar(0x0423)) + QString(QChar(0x0308)); // Ӱ
    latinToCyrillic["ß"] = QString(QChar(0x0421)) + QString(QChar(0x0421)); // СС (近似)

    // -------------------------
    // 拉丁字母到希腊字母的映射 (改进版)
    // -------------------------
    latinToGreek["A"] = QString(QChar(0x0391)); // Α
    latinToGreek["B"] = QString(QChar(0x0392)); // Β
    latinToGreek["G"] = QString(QChar(0x0393)); // Γ
    latinToGreek["D"] = QString(QChar(0x0394)); // Δ
    latinToGreek["E"] = QString(QChar(0x0395)); // Ε
    latinToGreek["Z"] = QString(QChar(0x0396)); // Ζ
    latinToGreek["H"] = QString(QChar(0x0397)); // Η
    latinToGreek["TH"] = QString(QChar(0x0398)); // Θ
    latinToGreek["I"] = QString(QChar(0x0399)); // Ι
    latinToGreek["J"] = QString(QChar(0x03B9)); // ι (使用小写 iota 表示 j)
    latinToGreek["K"] = QString(QChar(0x039A)); // Κ
    latinToGreek["L"] = QString(QChar(0x039B)); // Λ
    latinToGreek["M"] = QString(QChar(0x039C)); // Μ
    latinToGreek["N"] = QString(QChar(0x039D)); // Ν
    latinToGreek["X"] = QString(QChar(0x039E)); // Ξ
    latinToGreek["O"] = QString(QChar(0x039F)); // Ο
    latinToGreek["P"] = QString(QChar(0x03A0)); // Π
    latinToGreek["R"] = QString(QChar(0x03A1)); // Ρ
    latinToGreek["S"] = QString(QChar(0x03A3)); // Σ
    latinToGreek["T"] = QString(QChar(0x03A4)); // Τ
    latinToGreek["U"] = QString(QChar(0x03A5)); // Υ
    latinToGreek["F"] = QString(QChar(0x03A6)); // Φ
    latinToGreek["C"] = QString(QChar(0x03A7)); // Χ
    // 将 V 映射为 Β（大写 Beta），更贴近外来语音译
    latinToGreek["V"] = QString(QChar(0x0392)); // Β
    latinToGreek["W"] = QString(QChar(0x03A9)); // Ω
    // 对多字符组合做近似音处理
    latinToGreek["ZH"] = QString(QChar(0x0396)) + QString(QChar(0x03B9)); // Ζι (近似)
    latinToGreek["CH"] = QString(QChar(0x03C7)); // χ (小写 chi)
    latinToGreek["SH"] = QString(QChar(0x03C3)) + QString(QChar(0x03B9)); // σι (近似)

    // 带声调的组合（希腊文带音符）
    latinToGreek["AE"] = QString(QChar(0x03AC)); // ά
    latinToGreek["EE"] = QString(QChar(0x03AD)); // έ
    latinToGreek["IE"] = QString(QChar(0x03AF)); // ί
    latinToGreek["OE"] = QString(QChar(0x03CC)); // ό
    latinToGreek["UE"] = QString(QChar(0x03CD)); // ύ
    latinToGreek["HE"] = QString(QChar(0x03AE)); // ή
    latinToGreek["WIE"] = QString(QChar(0x03CE)); // ώ

    // -------------------------
    // 拉丁字母到叙利亚字母的映射
    // -------------------------
    latinToSyriac["A"] = QString(QChar(0x0710)); // ܐ
    latinToSyriac["B"] = QString(QChar(0x0712)); // ܒ
    latinToSyriac["C"] = QString(QChar(0x072D)); // ܭ (近似)
    latinToSyriac["D"] = QString(QChar(0x0715)); // ܕ
    latinToSyriac["E"] = QString(QChar(0x0725)); // ܥ
    latinToSyriac["F"] = QString(QChar(0x0726)); // ܦ
    latinToSyriac["G"] = QString(QChar(0x0713)); // ܓ
    latinToSyriac["H"] = QString(QChar(0x071A)); // ܚ
    latinToSyriac["I"] = QString(QChar(0x071D)); // ܝ
    latinToSyriac["J"] = QString(QChar(0x071F)); // ܟ (近似)
    latinToSyriac["K"] = QString(QChar(0x071F)); // ܟ
    latinToSyriac["L"] = QString(QChar(0x0720)); // ܠ
    latinToSyriac["M"] = QString(QChar(0x0721)); // ܡ
    latinToSyriac["N"] = QString(QChar(0x0722)); // ܢ
    latinToSyriac["O"] = QString(QChar(0x0718)); // ܘ (Waw 用于 O/U 表示)
    latinToSyriac["P"] = QString(QChar(0x0726)); // ܦ
    latinToSyriac["Q"] = QString(QChar(0x0729)); // ܩ
    latinToSyriac["R"] = QString(QChar(0x072A)); // ܪ
    latinToSyriac["S"] = QString(QChar(0x072B)); // ܫ
    latinToSyriac["T"] = QString(QChar(0x072C)); // ܬ
    latinToSyriac["U"] = QString(QChar(0x0718)); // ܘ
    latinToSyriac["V"] = QString(QChar(0x0712)); // ܒ (近似)
    latinToSyriac["W"] = QString(QChar(0x0718)); // ܘ
    latinToSyriac["X"] = QString(QChar(0x0713)); // ܓ (近似)
    latinToSyriac["Y"] = QString(QChar(0x071D)); // ܝ
    latinToSyriac["Z"] = QString(QChar(0x0719)); // ܙ
    latinToSyriac["TT"] = QString(QChar(0x071B)); // ܛ
    latinToSyriac["SH"] = QString(QChar(0x072B)); // ܫ

    // -------------------------
    // 拉丁字母到藏文字母 (Tibetan) - 注意：很多为近似映射
    // -------------------------
    latinToTibetan["A"] = QString(QChar(0x0F40)); // ཀ
    latinToTibetan["B"] = QString(QChar(0x0F56)); // པ
    latinToTibetan["C"] = QString(QChar(0x0F62)); // ག (近似)
    latinToTibetan["D"] = QString(QChar(0x0F51)); // ད
    latinToTibetan["E"] = QString(QChar(0x0F7A)); // ེ
    latinToTibetan["F"] = QString(QChar(0x0F54)); // ན (近似)
    latinToTibetan["G"] = QString(QChar(0x0F42)); // ག
    latinToTibetan["H"] = QString(QChar(0x0F64)); // ང (近似)
    latinToTibetan["I"] = QString(QChar(0x0F72)); // ི
    latinToTibetan["J"] = QString(QChar(0x0F9D)); // ྜྷ
    latinToTibetan["K"] = QString(QChar(0x0F40)); // ཀ
    latinToTibetan["L"] = QString(QChar(0x0F63)); // གྷ (近似)
    latinToTibetan["M"] = QString(QChar(0x0F58)); // མ
    latinToTibetan["N"] = QString(QChar(0x0F53)); // ཎ
    latinToTibetan["O"] = QString(QChar(0x0F7C)); // ོ
    latinToTibetan["P"] = QString(QChar(0x0F55)); // ཕ
    latinToTibetan["Q"] = QString(QChar(0x0F67)); // ཧ
    latinToTibetan["R"] = QString(QChar(0x0F5F)); // ཟ (修改：原为0x0F66)
    latinToTibetan["S"] = QString(QChar(0x0F66)); // ཤ
    latinToTibetan["T"] = QString(QChar(0x0F4F)); // ཏ
    latinToTibetan["U"] = QString(QChar(0x0F74)); // ུ
    latinToTibetan["V"] = QString(QChar(0x0F6B)); // ཫ (修改：原为0x0F5D)
    latinToTibetan["W"] = QString(QChar(0x0F5D)); // ཝ
    latinToTibetan["X"] = QString(QChar(0x0F61)); // ཁ
    latinToTibetan["Y"] = QString(QChar(0x0F71)); // ཱ
    latinToTibetan["Z"] = QString(QChar(0x0F5A)); // ཚ

    // -------------------------
    // 拉丁字母到天城体（Devanagari）
    // -------------------------
    latinToDevanagari["A"] = QString(QChar(0x0905)); // अ
    latinToDevanagari["B"] = QString(QChar(0x092C)); // ब
    latinToDevanagari["C"] = QString(QChar(0x091A)); // च
    latinToDevanagari["D"] = QString(QChar(0x0926)); // द
    latinToDevanagari["E"] = QString(QChar(0x0908)); // ई
    latinToDevanagari["F"] = QString(QChar(0x092B)); // फ
    latinToDevanagari["G"] = QString(QChar(0x0917)); // ग
    latinToDevanagari["H"] = QString(QChar(0x0939)); // ह
    latinToDevanagari["I"] = QString(QChar(0x0907)); // इ
    latinToDevanagari["J"] = QString(QChar(0x091C)); // ज
    latinToDevanagari["K"] = QString(QChar(0x0915)); // क
    latinToDevanagari["L"] = QString(QChar(0x0932)); // ल
    latinToDevanagari["M"] = QString(QChar(0x092E)); // म
    latinToDevanagari["N"] = QString(QChar(0x0928)); // न
    latinToDevanagari["O"] = QString(QChar(0x0913)); // ओ
    latinToDevanagari["P"] = QString(QChar(0x092A)); // प
    latinToDevanagari["Q"] = QString(QChar(0x0915)) + QString(QChar(0x094D)) + QString(QChar(0x0935)); // क्व
    latinToDevanagari["R"] = QString(QChar(0x0930)); // र
    latinToDevanagari["S"] = QString(QChar(0x0938)); // स
    latinToDevanagari["T"] = QString(QChar(0x0924)); // त
    latinToDevanagari["U"] = QString(QChar(0x0909)); // उ
    latinToDevanagari["V"] = QString(QChar(0x0935)); // व
    latinToDevanagari["W"] = QString(QChar(0x0935)) + QString(QChar(0x094D)) + QString(QChar(0x0939)); // व्ह
    latinToDevanagari["X"] = QString(QChar(0x0915)) + QString(QChar(0x094D)) + QString(QChar(0x0937)); // क्ष
    latinToDevanagari["Y"] = QString(QChar(0x092F)); // य
    latinToDevanagari["Z"] = QString(QChar(0x091D)); // झ
    latinToDevanagari[".n"] = QString(QChar(0x0902)); // अनुस्वार (anusvara)
    latinToDevanagari[".h"] = QString(QChar(0x0903)); // विसर्ग (visarga)
    latinToDevanagari["_"] = QString(QChar(0x094D)); // विराम (virama)

    // -------------------------
    // 拉丁字母到阿拉伯字母（Arabic）
    // （此处仅为初始化，部分发音优化将在 convertText 中补充）
    // -------------------------
    latinToArabic["A"] = QString(QChar(0x0627)); // ا
    latinToArabic["B"] = QString(QChar(0x0628)); // ب
    // C: 视语言环境而定，默认用 ق 表示 /q/ 或 /k/ 近似
    latinToArabic["C"] = QString(QChar(0x0642)); // ق
    latinToArabic["Ç"] = QString(QChar(0x0634)); // ش (法语/阿尔巴尼亚Ç)
    latinToArabic["D"] = QString(QChar(0x062F)); // د
    // E：外来词处理在 convertText 中更精细化
    latinToArabic["E"] = QString(QChar(0x0639)); // ع (占位，convertText 可替换为 إ/ي 等)
    latinToArabic["F"] = QString(QChar(0x0641)); // ف
    latinToArabic["G"] = QString(QChar(0x063A)); // غ (也可用 گ/ج 视方言)
    latinToArabic["H"] = QString(QChar(0x062D)); // ح
    latinToArabic["Ḥ"] = QString(QChar(0x0621)); // ء (喉音标记)
    latinToArabic["I"] = QString(QChar(0x064A)); // ي
    latinToArabic["J"] = QString(QChar(0x062C)); // ج
    latinToArabic["K"] = QString(QChar(0x0643)); // ك
    latinToArabic["L"] = QString(QChar(0x0644)); // ل
    latinToArabic["M"] = QString(QChar(0x0645)); // م
    latinToArabic["N"] = QString(QChar(0x0646)); // ن
    latinToArabic["O"] = QString(QChar(0x0648)); // و
    latinToArabic["P"] = QString(QChar(0x067E)); // پ (波斯/借词)
    latinToArabic["Q"] = QString(QChar(0x0642)); // ق
    latinToArabic["R"] = QString(QChar(0x0631)); // ر
    latinToArabic["S"] = QString(QChar(0x0633)); // س
    latinToArabic["Š"] = QString(QChar(0x0634)); // ش (Š)
    latinToArabic["T"] = QString(QChar(0x062A)); // ت
    latinToArabic["Ṭ"] = QString(QChar(0x0637)); // ط (重音 t)
    latinToArabic["U"] = QString(QChar(0x0648)); // و
    latinToArabic["V"] = QString(QChar(0x06A4)); // ڤ (用于表示 V)
    latinToArabic["W"] = QString(QChar(0x0648)); // و
    latinToArabic["X"] = QString(QChar(0x062E)); // خ
    latinToArabic["Y"] = QString(QChar(0x064A)); // ي
    latinToArabic["Z"] = QString(QChar(0x0632)); // ز
    latinToArabic["Ž"] = QString(QChar(0x0636)); // ض (近似)

    // 双字母/组合（阿拉伯）
    latinToArabic["SH"] = QString(QChar(0x0634)); // ش
    latinToArabic["TH"] = QString(QChar(0x062B)); // ث
    latinToArabic["DH"] = QString(QChar(0x0630)); // ذ
    latinToArabic["KH"] = QString(QChar(0x062E)); // خ
    latinToArabic["GH"] = QString(QChar(0x063A)); // غ
    latinToArabic["AA"] = QString(QChar(0x0622)); // آ (长音 A)
    latinToArabic["EE"] = QString(QChar(0x0635)); // ص (占位)
    latinToArabic["XI"] = QString(QChar(0x062E)) + QString(QChar(0x064A)); // خي (示例)
    latinToArabic["ZH"] = QString(QChar(0x0698)); // ژ (zh)
    latinToArabic["OO"] = QString(QChar(0x0623)); // أ (近似长 O)

    // -------------------------
    // 拉丁字母到波斯语 (Persian) - 基于阿拉伯表并调整
    // -------------------------
    latinToPersian["A"] = QString(QChar(0x0627)); // ا
    latinToPersian["B"] = QString(QChar(0x0628)); // ب
    latinToPersian["C"] = QString(QChar(0x0633)); // س (近似)
    latinToPersian["D"] = QString(QChar(0x062F)); // د
    latinToPersian["E"] = QString(QChar(0x0627)); // ا (近似处理)
    latinToPersian["F"] = QString(QChar(0x0641)); // ف
    latinToPersian["G"] = QString(QChar(0x06AF)); // گ
    latinToPersian["H"] = QString(QChar(0x0647)); // ه
    latinToPersian["I"] = QString(QChar(0x064A)); // ی
    latinToPersian["J"] = QString(QChar(0x062C)); // ج
    latinToPersian["K"] = QString(QChar(0x0643)); // ك
    latinToPersian["L"] = QString(QChar(0x0644)); // ل
    latinToPersian["M"] = QString(QChar(0x0645)); // م
    latinToPersian["N"] = QString(QChar(0x0646)); // ن
    latinToPersian["O"] = QString(QChar(0x0648)); // و
    latinToPersian["P"] = QString(QChar(0x067E)); // پ
    latinToPersian["Q"] = QString(QChar(0x0642)); // ق
    latinToPersian["R"] = QString(QChar(0x0631)); // ر
    latinToPersian["S"] = QString(QChar(0x0633)); // س
    latinToPersian["T"] = QString(QChar(0x062A)); // ت
    latinToPersian["U"] = QString(QChar(0x0648)); // و
    latinToPersian["V"] = QString(QChar(0x0648)); // و (近似)
    latinToPersian["W"] = QString(QChar(0x0648)); // و
    latinToPersian["X"] = QString(QChar(0x062E)); // خ
    latinToPersian["Y"] = QString(QChar(0x064A)); // ی
    latinToPersian["Z"] = QString(QChar(0x0632)); // ز
    latinToPersian["CH"] = QString(QChar(0x0686)); // چ
    latinToPersian["GH"] = QString(QChar(0x063A)); // غ
    latinToPersian["KH"] = QString(QChar(0x062E)); // خ
    latinToPersian["SH"] = QString(QChar(0x0634)); // ش
    latinToPersian["ZH"] = QString(QChar(0x0698)); // ژ

    // -------------------------
    // 拉丁字母到希伯来字母 (Hebrew) — 基于 SBL / 常见转写
    // -------------------------
    latinToHebrew["A"] = QString(QChar(0x05D0)); // א
    latinToHebrew["B"] = QString(QChar(0x05D1)); // ב
    latinToHebrew["C"] = QString(QChar(0x05E6)); // צ (近似)
    latinToHebrew["D"] = QString(QChar(0x05D3)); // ד
    latinToHebrew["E"] = QString(QChar(0x05D0)) + QString(QChar(0x05B5)); // אֶ (e 音)
    latinToHebrew["F"] = QString(QChar(0x05E4)); // פ
    latinToHebrew["G"] = QString(QChar(0x05D2)); // ג
    latinToHebrew["H"] = QString(QChar(0x05D4)); // ה
    latinToHebrew["I"] = QString(QChar(0x05D9)); // י
    latinToHebrew["J"] = QString(QChar(0x05D9)); // י (近似)
    latinToHebrew["K"] = QString(QChar(0x05DB)); // כ
    latinToHebrew["L"] = QString(QChar(0x05DC)); // ל
    latinToHebrew["M"] = QString(QChar(0x05DE)); // מ
    latinToHebrew["N"] = QString(QChar(0x05E0)); // נ
    latinToHebrew["O"] = QString(QChar(0x05D5)) + QString(QChar(0x05B9)); // וֹ (o 音)
    latinToHebrew["P"] = QString(QChar(0x05E4)); // פ
    latinToHebrew["Q"] = QString(QChar(0x05E7)); // ק
    latinToHebrew["R"] = QString(QChar(0x05E8)); // ר
    latinToHebrew["S"] = QString(QChar(0x05E1)); // ס
    latinToHebrew["T"] = QString(QChar(0x05D8)); // ט
    latinToHebrew["U"] = QString(QChar(0x05D5)) + QString(QChar(0x05BC)); // וּ (u 音)
    latinToHebrew["V"] = QString(QChar(0x05D5)); // ו
    latinToHebrew["W"] = QString(QChar(0x05D5)); // ו
    latinToHebrew["X"] = QString(QChar(0x05E6)) + QString(QChar(0x05E1)); // צס (近似 x)
    latinToHebrew["Y"] = QString(QChar(0x05D9)); // י
    latinToHebrew["Z"] = QString(QChar(0x05D6)); // ז
    latinToHebrew["CH"] = QString(QChar(0x05D7)); // ח
    latinToHebrew["SH"] = QString(QChar(0x05E9)); // ש
    latinToHebrew["TH"] = QString(QChar(0x05E6)); // צ (近似)
    latinToHebrew["AYIN"] = QString(QChar(0x05E2)); // ע

    // -------------------------
    // 拉丁字母到卢恩字母 (Runic) - 近似
    // -------------------------
    latinToRunic["A"] = QString(QChar(0x16A8)); // ᚨ
    latinToRunic["B"] = QString(QChar(0x16D2)); // ᚲ (近似)
    latinToRunic["C"] = QString(QChar(0x16CB)); // ᛋ
    latinToRunic["D"] = QString(QChar(0x16DE)); // ᛞ
    latinToRunic["E"] = QString(QChar(0x16D6)); // ᛖ
    latinToRunic["F"] = QString(QChar(0x16A0)); // ᚠ
    latinToRunic["G"] = QString(QChar(0x16B7)); // ᚷ
    latinToRunic["H"] = QString(QChar(0x16BA)); // ᚺ
    latinToRunic["I"] = QString(QChar(0x16C1)); // ᛁ
    latinToRunic["J"] = QString(QChar(0x16C4)); // ᛜ
    latinToRunic["K"] = QString(QChar(0x16B2)); // ᚲ
    latinToRunic["L"] = QString(QChar(0x16DA)); // ᛚ
    latinToRunic["M"] = QString(QChar(0x16D7)); // ᛗ
    latinToRunic["N"] = QString(QChar(0x16BE)); // ᚾ
    latinToRunic["O"] = QString(QChar(0x16DF)); // ᛟ
    latinToRunic["P"] = QString(QChar(0x16C8)); // ᛈ
    latinToRunic["Q"] = QString(QChar(0x16B2)); // ᚲ (K 代替)
    latinToRunic["R"] = QString(QChar(0x16B1)); // ᚱ
    latinToRunic["S"] = QString(QChar(0x16CB)); // ᛋ
    latinToRunic["T"] = QString(QChar(0x16CF)); // ᛏ
    latinToRunic["U"] = QString(QChar(0x16A2)); // ᚢ
    latinToRunic["V"] = QString(QChar(0x16A0)); // ᚠ (F 代替)
    latinToRunic["W"] = QString(QChar(0x16B9)); // ᚹ
    latinToRunic["X"] = QString(QChar(0x16C9)); // ᛉ
    latinToRunic["Y"] = QString(QChar(0x16A3)); // ᚣ
    latinToRunic["Z"] = QString(QChar(0x16CE)); // ᛉ

    // -------------------------
    // 拉丁字母到高棉文 (Khmer)
    // -------------------------
    latinToKhmer["A"] = QString(QChar(0x1791)); // អ
    latinToKhmer["B"] = QString(QChar(0x1793)); // ប
    latinToKhmer["C"] = QString(QChar(0x1786)); // ឆ
    latinToKhmer["D"] = QString(QChar(0x1794)); // ដ
    latinToKhmer["E"] = QString(QChar(0x1791)) + QString(QChar(0x17B6)); // អេ
    latinToKhmer["F"] = QString(QChar(0x17A0)) + QString(QChar(0x17C1)); // ហ្វ
    latinToKhmer["G"] = QString(QChar(0x1797)); // ក
    latinToKhmer["H"] = QString(QChar(0x17A0)); // ហ
    latinToKhmer["I"] = QString(QChar(0x1791)) + QString(QChar(0x17B7)); // អិ
    latinToKhmer["J"] = QString(QChar(0x1787)); // ជ
    latinToKhmer["K"] = QString(QChar(0x1796)); // ខ
    latinToKhmer["L"] = QString(QChar(0x17A1)); // ឡ
    latinToKhmer["M"] = QString(QChar(0x17A2)); // ម
    latinToKhmer["N"] = QString(QChar(0x1799)); // ន
    latinToKhmer["O"] = QString(QChar(0x1791)) + QString(QChar(0x17B8)); // អូ
    latinToKhmer["P"] = QString(QChar(0x17A6)); // ព
    latinToKhmer["PH"] = QString(QChar(0x17A7)); // ភ
    latinToKhmer["Q"] = QString(QChar(0x1798)); // ឃ
    latinToKhmer["R"] = QString(QChar(0x179A)); // រ
    latinToKhmer["S"] = QString(QChar(0x17A4)); // ស
    latinToKhmer["T"] = QString(QChar(0x1795)); // ឌ
    latinToKhmer["TH"] = QString(QChar(0x179F)); // ឯ
    latinToKhmer["U"] = QString(QChar(0x1791)) + QString(QChar(0x17B9)); // អុ
    latinToKhmer["V"] = QString(QChar(0x179C)); // វ
    latinToKhmer["W"] = QString(QChar(0x179C)); // វ
    latinToKhmer["X"] = QString(QChar(0x17A5)); // ឥ
    latinToKhmer["Y"] = QString(QChar(0x179D)); // យ
    latinToKhmer["Z"] = QString(QChar(0x179B)); // ល
    
    // 添加双辅音组合
    latinToKhmer["KH"] = QString(QChar(0x1796)); // ខ
    latinToKhmer["GH"] = QString(QChar(0x1798)); // ឃ
    latinToKhmer["CH"] = QString(QChar(0x1786)); // ឆ
    latinToKhmer["JH"] = QString(QChar(0x1787)); // ជ
    latinToKhmer["TH"] = QString(QChar(0x179F)); // ឯ
    latinToKhmer["DH"] = QString(QChar(0x17A8)); // ឨ
    latinToKhmer["PH"] = QString(QChar(0x17A7)); // ភ
    latinToKhmer["BH"] = QString(QChar(0x17A9)); // ឩ
    
    // 添加带元音符号的组合
    latinToKhmer["AA"] = QString(QChar(0x1791)) + QString(QChar(0x17B0)); // អា
    latinToKhmer["AE"] = QString(QChar(0x1791)) + QString(QChar(0x17B6)); // អេ
    latinToKhmer["AI"] = QString(QChar(0x1791)) + QString(QChar(0x17B1)); // អៃ
    latinToKhmer["AO"] = QString(QChar(0x1791)) + QString(QChar(0x17B2)); // អោ
    latinToKhmer["AU"] = QString(QChar(0x1791)) + QString(QChar(0x17B3)); // អៅ

    // -------------------------
    // 拉丁字母到韩文(谚文 Hangul) 映射（取常见音节首）
    // -------------------------
    latinToHangul["A"] = QString(QChar(0xAC00)); // 가
    latinToHangul["B"] = QString(QChar(0xBC14)); // 바
    latinToHangul["C"] = QString(QChar(0xCE58)); // 치 (近似)
    latinToHangul["D"] = QString(QChar(0xB2E4)); // 다
    latinToHangul["E"] = QString(QChar(0xC5D0)); // 에
    latinToHangul["F"] = QString(QChar(0xD504)); // 프
    latinToHangul["G"] = QString(QChar(0xAE00)); // 거
    latinToHangul["H"] = QString(QChar(0xD558)); // 하
    latinToHangul["I"] = QString(QChar(0xC774)); // 이
    latinToHangul["J"] = QString(QChar(0xC790)); // 자
    latinToHangul["K"] = QString(QChar(0xCE74)); // 카
    latinToHangul["L"] = QString(QChar(0xB77C)); // 라
    latinToHangul["M"] = QString(QChar(0xB9C8)); // 마
    latinToHangul["N"] = QString(QChar(0xB098)); // 나
    latinToHangul["O"] = QString(QChar(0xC624)); // 오
    latinToHangul["P"] = QString(QChar(0xD30C)); // 파
    latinToHangul["Q"] = QString(QChar(0xCEE4)); // 커
    latinToHangul["R"] = QString(QChar(0xB85C)); // 로
    latinToHangul["S"] = QString(QChar(0xC2A4)); // 스
    latinToHangul["T"] = QString(QChar(0xD2B8)); // 트
    latinToHangul["U"] = QString(QChar(0xC6B0)); // 우
    latinToHangul["V"] = QString(QChar(0xBE44)); // 비
    latinToHangul["W"] = QString(QChar(0xC6CC)); // 워
    latinToHangul["X"] = QString(QChar(0xC2DD)); // 식
    latinToHangul["Y"] = QString(QChar(0xC5F0)); // 유
    latinToHangul["Z"] = QString(QChar(0xC9C0)); // 지

    // -------------------------
    // 假名 (Kana) 映射 — 以片假名为主，注意：日语映射常依赖前后元音，convertText 中会细化
    // -------------------------
    latinToKana["A"] = QString(QChar(0x30A2)); // ア
    latinToKana["B"] = QString(QChar(0x30D0)); // バ
    latinToKana["C"] = QString(QChar(0x30B7)); // シ (默认)
    latinToKana["D"] = QString(QChar(0x30C0)); // ダ
    latinToKana["E"] = QString(QChar(0x30A8)); // エ
    latinToKana["F"] = QString(QChar(0x30D5)); // フ
    latinToKana["G"] = QString(QChar(0x30AE)); // ギ
    latinToKana["H"] = QString(QChar(0x30CF)); // ハ
    latinToKana["I"] = QString(QChar(0x30A4)); // イ
    latinToKana["J"] = QString(QChar(0x30B8)); // ジ
    latinToKana["K"] = QString(QChar(0x30AB)); // カ
    latinToKana["L"] = QString(QChar(0x30EB)); // ル
    latinToKana["M"] = QString(QChar(0x30DE)); // マ
    latinToKana["N"] = QString(QChar(0x30CA)); // ナ
    latinToKana["O"] = QString(QChar(0x30AA)); // オ
    latinToKana["P"] = QString(QChar(0x30D1)); // パ
    latinToKana["Q"] = QString(QChar(0x30AF)); // ク
    latinToKana["R"] = QString(QChar(0x30E9)); // ラ
    latinToKana["S"] = QString(QChar(0x30B5)); // サ
    latinToKana["T"] = QString(QChar(0x30BF)); // タ
    latinToKana["U"] = QString(QChar(0x30A6)); // ウ
    latinToKana["V"] = QString(QChar(0x30F4)); // ヴ
    latinToKana["W"] = QString(QChar(0x30EF)); // ワ
    latinToKana["X"] = QString(QChar(0x30B7)); // シ (近似)
    latinToKana["Y"] = QString(QChar(0x30E4)); // ヤ
    latinToKana["Z"] = QString(QChar(0x30BA)); // ズ






    // 拉丁字母到注音符号的映射
    latinToZhuyin["A"] = QString(QChar(0x3105)); // ㄅ
    latinToZhuyin["B"] = QString(QChar(0x3106)); // ㄆ
    latinToZhuyin["C"] = QString(QChar(0x3107)); // ㄇ
    latinToZhuyin["D"] = QString(QChar(0x3108)); // ㄈ
    latinToZhuyin["E"] = QString(QChar(0x3109)); // ㄉ
    latinToZhuyin["F"] = QString(QChar(0x310A)); // ㄊ
    latinToZhuyin["G"] = QString(QChar(0x310B)); // ㄋ
    latinToZhuyin["H"] = QString(QChar(0x310C)); // ㄌ
    latinToZhuyin["I"] = QString(QChar(0x310D)); // ㄍ
    latinToZhuyin["J"] = QString(QChar(0x310E)); // ㄎ
    latinToZhuyin["K"] = QString(QChar(0x310F)); // ㄏ
    latinToZhuyin["L"] = QString(QChar(0x3110)); // ㄐ
    latinToZhuyin["M"] = QString(QChar(0x3111)); // ㄑ
    latinToZhuyin["N"] = QString(QChar(0x3112)); // ㄒ
    latinToZhuyin["O"] = QString(QChar(0x3113)); // ㄓ
    latinToZhuyin["P"] = QString(QChar(0x3114)); // ㄔ
    latinToZhuyin["Q"] = QString(QChar(0x3115)); // ㄕ
    latinToZhuyin["R"] = QString(QChar(0x3116)); // ㄖ
    latinToZhuyin["S"] = QString(QChar(0x3117)); // ㄗ
    latinToZhuyin["T"] = QString(QChar(0x3118)); // ㄘ
    latinToZhuyin["U"] = QString(QChar(0x3119)); // ㄙ
    latinToZhuyin["V"] = QString(QChar(0x311A)); // ㄚ
    latinToZhuyin["W"] = QString(QChar(0x311B)); // ㄛ
    latinToZhuyin["X"] = QString(QChar(0x311C)); // ㄜ
    latinToZhuyin["Y"] = QString(QChar(0x311D)); // ㄝ
    latinToZhuyin["Z"] = QString(QChar(0x311E)); // ㄞ

    // 维吾尔语映射表
    latinToUyghur["A"] = QString(QChar(0x0627)); // ا
    latinToUyghur["B"] = QString(QChar(0x0628)); // ب
    latinToUyghur["C"] = QString(QChar(0x0686)); // چ
    latinToUyghur["D"] = QString(QChar(0x062F)); // د
    latinToUyghur["E"] = QString(QChar(0x06D5)); // ە
    latinToUyghur["F"] = QString(QChar(0x0641)); // ف
    latinToUyghur["G"] = QString(QChar(0x06AF)); // گ
    latinToUyghur["H"] = QString(QChar(0x0647)); // ه
    latinToUyghur["I"] = QString(QChar(0x0649)); // ى
    latinToUyghur["J"] = QString(QChar(0x062C)); // ج
    latinToUyghur["K"] = QString(QChar(0x0643)); // ك
    latinToUyghur["L"] = QString(QChar(0x0644)); // ل
    latinToUyghur["M"] = QString(QChar(0x0645)); // م
    latinToUyghur["N"] = QString(QChar(0x0646)); // ن
    latinToUyghur["O"] = QString(QChar(0x0648)); // و
    latinToUyghur["P"] = QString(QChar(0x067E)); // پ
    latinToUyghur["Q"] = QString(QChar(0x0642)); // ق
    latinToUyghur["R"] = QString(QChar(0x0631)); // ر
    latinToUyghur["S"] = QString(QChar(0x0633)); // س
    latinToUyghur["T"] = QString(QChar(0x062A)); // ت
    latinToUyghur["U"] = QString(QChar(0x06C7)); // ۇ
    latinToUyghur["V"] = QString(QChar(0x06CB)); // ۋ
    latinToUyghur["W"] = QString(QChar(0x06C6)); // ۆ
    latinToUyghur["X"] = QString(QChar(0x062E)); // خ
    latinToUyghur["Y"] = QString(QChar(0x064A)); // ي
    latinToUyghur["Z"] = QString(QChar(0x0632)); // ز

    // 创建反向映射
    auto createReverseMap = [](const QMap<QString, QString>& forwardMap, QMap<QString, QString>& reverseMap) {
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
    createReverseMap(latinToUyghur, uyghurToLatin);
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

    QString intermediateText = text;
    // 如果目标不是拉丁字母且方向是TargetToLatin，先转换为拉丁字母
    if (direction != LatinToTarget) {
        intermediateText = convertText(text, system, LatinToTarget);
    }

    QString result;
    QMap<QString, QString> *currentMap = nullptr; // 修改为QString映射

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
        default: break;
        }
    } else {
        switch(system) {
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
        default: break;
        }
    }

    if (!currentMap) return text;

    for (int i = 0; i < text.length(); ++i) {
        QChar currentChar = text.at(i);
        QString lookupStr;

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
                i += 2; // 跳过接下来的两个字符
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

        // 处理特殊规则：C 的发音取决于后续元音
        if (current == "C" && i < text.length() - 1) {
            QChar nextChar = text[i + 1].toLower();
            // 修复QChar与字符比较的错误，使用unicode值
            if (nextChar == 'a' || nextChar == 'e' || nextChar == 'i' || nextChar == 'o' || nextChar == 'u' || nextChar == 'y' ||
                nextChar.unicode() == 0x00EB || // ë
                nextChar.unicode() == 0x00FC || // ü
                nextChar.unicode() == 0x00EF) { // ï
                result += isLower ? "с" : "С";
            } else {
                // 在词尾时，C 通常发 "к" 音
                if (i == text.length() - 1) {
                    result += isLower ? "к" : "К";
                } else {
                    // 检查是否是 "ch" 组合的一部分
                    if (i < text.length() - 1 && text[i + 1].toUpper() == 'H') {
                        result += isLower ? "ч" : "Ч";
                        i++;
                    } else {
                        result += isLower ? "к" : "К";
                    }
                }
            }
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
    for (int i = 0; i < text.length(); i++) {
        QChar c = text[i];
        QString current = QString(c).toUpper();
        bool isLower = c.isLower();

        // 处理多字符组合
        if (i < text.length() - 1) {
            QString pair = text.mid(i, 2).toUpper();
            if (latinToArabic.contains(pair)) {
                QString converted = latinToArabic[pair];
                result += converted;
                i++;
                continue;
            }
        }

        // 处理特殊字符：喉音标记
        if (current == "H" && i > 0 && (text[i-1] == 'a' || text[i-1] == 'A' ||
                                        text[i-1] == 'u' || text[i-1] == 'U' ||
                                        text[i-1] == 'i' || text[i-1] == 'I')) {
            result += QChar(0x0621); // ء
            continue;
        }

        // 处理特殊规则：E 在词首和词中不同
        if (current == "E") {
            if (i == 0) {
                result += QChar(0x0625); // إ
            } else {
                result += QChar(0x064A); // ي
            }
            continue;
        }

        // 默认映射
        if (latinToArabic.contains(current)) {
            QString converted = latinToArabic[current];
            result += converted;
        } else {
            result += c;
        }
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


QString LetterConverter::convertWithMap(const QString &text, const QMap<QString, QString> &map)
{
    QString result;
    for (int i = 0; i < text.length(); ++i) {
        QChar currentChar = text.at(i);
        QString lookupStr;
        bool found = false;

        // 检查3字符组合
        if (i < text.length() - 2) {
            lookupStr = text.mid(i, 3);
            if (map.contains(lookupStr)) {
                result += map.value(lookupStr);
                i += 2;
                found = true;
                continue;
            }
        }

        // 检查2字符组合
        if (!found && i < text.length() - 1) {
            lookupStr = text.mid(i, 2);
            if (map.contains(lookupStr)) {
                result += map.value(lookupStr);
                i++;
                found = true;
                continue;
            }
        }

        // 单字符查找
        if (!found) {
            lookupStr = QString(currentChar);
            if (map.contains(lookupStr)) {
                result += map.value(lookupStr);
            } else {
                result += currentChar;
            }
        }
    }
    return result;
}
