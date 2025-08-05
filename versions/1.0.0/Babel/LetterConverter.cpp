#include "LetterConverter.h"

LetterConverter::LetterConverter(QObject *parent) : QObject(parent)
{
    initializeMaps();
}

void LetterConverter::initializeMaps()
{
    // 基本拉丁字母映射（按字母表顺序）
    latinToCyrillic["A"] = QString(QChar(0x0410)); // А
    latinToCyrillic["B"] = QString(QChar(0x0411)); // Б
    latinToCyrillic["C"] = QString(QChar(0x0426)); // Ц
    latinToCyrillic["D"] = QString(QChar(0x0414)); // Д
    latinToCyrillic["E"] = QString(QChar(0x0415)); // Е
    latinToCyrillic["F"] = QString(QChar(0x0424)); // Ф
    latinToCyrillic["G"] = QString(QChar(0x0413)); // Г
    latinToCyrillic["H"] = QString(QChar(0x0425)); // Х
    latinToCyrillic["I"] = QString(QChar(0x0418)); // И
    latinToCyrillic["J"] = QString(QChar(0x0419)); // Й
    latinToCyrillic["K"] = QString(QChar(0x041A)); // К
    latinToCyrillic["L"] = QString(QChar(0x041B)); // Л
    latinToCyrillic["M"] = QString(QChar(0x041C)); // М
    latinToCyrillic["N"] = QString(QChar(0x041D)); // Н
    latinToCyrillic["O"] = QString(QChar(0x041E)); // О
    latinToCyrillic["P"] = QString(QChar(0x041F)); // П
    latinToCyrillic["Q"] = QString(QChar(0x041A)) + QString(QChar(0x0421)); // КС
    latinToCyrillic["R"] = QString(QChar(0x0420)); // Р
    latinToCyrillic["S"] = QString(QChar(0x0421)); // С
    latinToCyrillic["Sh"] = QString(QChar(0x0428)); // Ш
    latinToCyrillic["Sch"] = QString(QChar(0x0429)); // Щ
    latinToCyrillic["T"] = QString(QChar(0x0422)); // Т
    latinToCyrillic["U"] = QString(QChar(0x0423)); // У
    latinToCyrillic["V"] = QString(QChar(0x0412)); // В
    latinToCyrillic["W"] = QString(QChar(0x0412)); // В (W在俄语中通常用В表示)
    latinToCyrillic["X"] = QString(QChar(0x0425)); // Х
    latinToCyrillic["Y"] = QString(QChar(0x042B)); // Ы
    latinToCyrillic["Z"] = QString(QChar(0x0417)); // З
    latinToCyrillic["Yo"] = QString(QChar(0x0401)); // Ё
    latinToCyrillic["Yu"] = QString(QChar(0x042E)); // Ю
    latinToCyrillic["Ya"] = QString(QChar(0x042F)); // Я
    latinToCyrillic["Ä"] = QString(QChar(0x0410)) + QString(QChar(0x0308)); // Ӓ
    latinToCyrillic["Ö"] = QString(QChar(0x041E)) + QString(QChar(0x0308)); // Ö
    latinToCyrillic["Ü"] = QString(QChar(0x0423)) + QString(QChar(0x0308)); // Ӱ
    latinToCyrillic["ß"] = QString(QChar(0x0421)) + QString(QChar(0x0421)); // СС
    latinToCyrillic["Ch"] = QString(QChar(0x0427)); // Ч
    latinToCyrillic["Kh"] = QString(QChar(0x0425)); // Х
    latinToCyrillic["Zh"] = QString(QChar(0x0416)); // Ж


    // 拉丁字母到希腊字母的映射 (改进版)
    latinToGreek["A"] = QString(QChar(0x0391)); // Α
    latinToGreek["B"] = QString(QChar(0x0392)); // Β
    latinToGreek["G"] = QString(QChar(0x0393)); // Γ
    latinToGreek["D"] = QString(QChar(0x0394)); // Δ
    latinToGreek["E"] = QString(QChar(0x0395)); // Ε
    latinToGreek["Z"] = QString(QChar(0x0396)); // Ζ
    latinToGreek["H"] = QString(QChar(0x0397)); // Η
    latinToGreek["Th"] = QString(QChar(0x0398)); // Θ (添加Th映射为Theta)
    latinToGreek["I"] = QString(QChar(0x0399)); // Ι
    latinToGreek["J"] = QString(QChar(0x03B9)); // ι (使用小写Iota表示J)
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
    latinToGreek["Y"] = QString(QChar(0x03A8)); // Ψ
    latinToGreek["W"] = QString(QChar(0x03A9)); // Ω
    latinToGreek["V"] = QString(QChar(0x03BD)); // ν (使用小写Nu表示V)
    latinToGreek["Zh"] = QString(QChar(0x0396)) + QString(QChar(0x03B9)); // Ζι (zh的希腊模拟音)
    latinToGreek["Ch"] = QString(QChar(0x03C7)); // χ (ch的希腊模拟音)
    latinToGreek["Sh"] = QString(QChar(0x03C3)) + QString(QChar(0x03B9)); // σι (sh的希腊模拟音)
    latinToGreek["Ae"] = QString(QChar(0x03AC)); // ά
    latinToGreek["Ee"] = QString(QChar(0x03AD)); // έ
    latinToGreek["Ie"] = QString(QChar(0x03AF)); // ί
    latinToGreek["Oe"] = QString(QChar(0x03CC)); // ό
    latinToGreek["Ue"] = QString(QChar(0x03CD)); // ύ
    latinToGreek["He"] = QString(QChar(0x03AE)); // ή
    latinToGreek["Wie"] = QString(QChar(0x03CE)); // ώ


    // 拉丁字母到叙利亚字母的映射
    latinToSyriac["A"] = QString(QChar(0x0710)); // ܐ
    latinToSyriac["B"] = QString(QChar(0x0712)); // ܒ
    latinToSyriac["C"] = QString(QChar(0x072D)); // ܭ (使用Taw的变体表示C)
    latinToSyriac["D"] = QString(QChar(0x0715)); // ܕ
    latinToSyriac["E"] = QString(QChar(0x0725)); // ܥ
    latinToSyriac["F"] = QString(QChar(0x0726)); // ܦ (使用Pe表示F)
    latinToSyriac["G"] = QString(QChar(0x0713)); // ܓ
    latinToSyriac["H"] = QString(QChar(0x071A)); // ܚ (保留最后出现的映射)
    latinToSyriac["I"] = QString(QChar(0x071D)); // ܝ
    latinToSyriac["J"] = QString(QChar(0x071F)); // ܟ (使用Kaph表示J)
    latinToSyriac["K"] = QString(QChar(0x071F)); // ܟ
    latinToSyriac["L"] = QString(QChar(0x0720)); // ܠ
    latinToSyriac["M"] = QString(QChar(0x0721)); // ܡ
    latinToSyriac["N"] = QString(QChar(0x0722)); // ܢ
    latinToSyriac["O"] = QString(QChar(0x0718)); // ܘ (使用Waw表示O)
    latinToSyriac["P"] = QString(QChar(0x0726)); // ܦ
    latinToSyriac["Q"] = QString(QChar(0x0729)); // ܩ
    latinToSyriac["R"] = QString(QChar(0x072A)); // ܪ
    latinToSyriac["S"] = QString(QChar(0x072B)); // ܫ (保留最后出现的映射)
    latinToSyriac["T"] = QString(QChar(0x072C)); // ܬ (保留最后出现的映射)
    latinToSyriac["U"] = QString(QChar(0x0718)); // ܘ (使用Waw表示U)
    latinToSyriac["V"] = QString(QChar(0x0712)); // ܒ (使用Beth表示V)
    latinToSyriac["W"] = QString(QChar(0x0718)); // ܘ
    latinToSyriac["X"] = QString(QChar(0x0713)); // ܓ (使用Gimel表示X)
    latinToSyriac["Y"] = QString(QChar(0x071D)); // ܝ (保留最后出现的映射)
    latinToSyriac["Z"] = QString(QChar(0x0719)); // ܙ
    latinToSyriac["Tt"] = QString(QChar(0x071B)); // ܛ (添加双字符组合映射)
    latinToSyriac["Sh"] = QString(QChar(0x072B)); // ܫ (添加双字符组合映射)

    // 拉丁字母到藏文字母的映射
    latinToTibetan["A"] = QString(QChar(0x0F40)); // ཀ
    latinToTibetan["B"] = QString(QChar(0x0F56)); // པ
    latinToTibetan["C"] = QString(QChar(0x0F62)); // ག
    latinToTibetan["D"] = QString(QChar(0x0F51)); // ད
    latinToTibetan["E"] = QString(QChar(0x0F7A)); // ེ
    latinToTibetan["F"] = QString(QChar(0x0F54)); // ན
    latinToTibetan["G"] = QString(QChar(0x0F42)); // ག
    latinToTibetan["H"] = QString(QChar(0x0F64)); // ང
    latinToTibetan["J"] = QString(QChar(0x0F9D)); // ྜྷ
    latinToTibetan["K"] = QString(QChar(0x0F40)); // ཀ
    latinToTibetan["L"] = QString(QChar(0x0F63)); // གྷ
    latinToTibetan["M"] = QString(QChar(0x0F58)); // མ
    latinToTibetan["N"] = QString(QChar(0x0F53)); // ཎ
    latinToTibetan["O"] = QString(QChar(0x0F7C)); // ོ
    latinToTibetan["P"] = QString(QChar(0x0F55)); // ཕ
    latinToTibetan["Q"] = QString(QChar(0x0F67)); // ཧ
    latinToTibetan["R"] = QString(QChar(0x0F66)); // ཤ
    latinToTibetan["S"] = QString(QChar(0x0F66)); // ཤ
    latinToTibetan["T"] = QString(QChar(0x0F4F)); // ཏ
    latinToTibetan["U"] = QString(QChar(0x0F74)); // ུ
    latinToTibetan["V"] = QString(QChar(0x0F5D)); // ཝ
    latinToTibetan["W"] = QString(QChar(0x0F5D)); // ཝ
    latinToTibetan["X"] = QString(QChar(0x0F61)); // ཁ
    latinToTibetan["Y"] = QString(QChar(0x0F71)); // ཱ
    latinToTibetan["Z"] = QString(QChar(0x0F5A)); // ཚ

    // 拉丁字母到天城体梵文字母的映射
    // 拉丁字母到天城体梵文字母的映射
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


    // 拉丁字母到阿拉伯字母的映射
    latinToArabic["A"] = QString(QChar(0x0627)); // ا
    latinToArabic["B"] = QString(QChar(0x0628)); // ب
    latinToArabic["C"] = QString(QChar(0x0642)); // ق (更准确的C发音)
    latinToArabic["Ç"] = QString(QChar(0x0634)); // ش (对应法语/阿尔巴尼亚语中的Ç)
    latinToArabic["D"] = QString(QChar(0x062F)); // د
    latinToArabic["E"] = QString(QChar(0x0639)); // ع
    latinToArabic["F"] = QString(QChar(0x0641)); // ف
    latinToArabic["G"] = QString(QChar(0x063A)); // غ
    latinToArabic["H"] = QString(QChar(0x062D)); // ح
    latinToArabic["Ḥ"] = QString(QChar(0x0621)); // ء (喉音H)
    latinToArabic["I"] = QString(QChar(0x064A)); // ي
    latinToArabic["J"] = QString(QChar(0x062C)); // ج
    latinToArabic["K"] = QString(QChar(0x0643)); // ك
    latinToArabic["L"] = QString(QChar(0x0644)); // ل
    latinToArabic["M"] = QString(QChar(0x0645)); // م
    latinToArabic["N"] = QString(QChar(0x0646)); // ن
    latinToArabic["O"] = QString(QChar(0x0648)); // و
    latinToArabic["P"] = QString(QChar(0x067E)); // پ (用于表示P音)
    latinToArabic["Q"] = QString(QChar(0x0642)); // ق
    latinToArabic["R"] = QString(QChar(0x0631)); // ر
    latinToArabic["S"] = QString(QChar(0x0633)); // س
    latinToArabic["Š"] = QString(QChar(0x0634)); // ش (对应Š)
    latinToArabic["T"] = QString(QChar(0x062A)); // ت
    latinToArabic["Ṭ"] = QString(QChar(0x0637)); // ط ( emphatic T)
    latinToArabic["U"] = QString(QChar(0x0648)); // و
    latinToArabic["V"] = QString(QChar(0x06A4)); // ڤ (用于表示V音)
    latinToArabic["W"] = QString(QChar(0x0648)); // و
    latinToArabic["X"] = QString(QChar(0x062E)); // خ
    latinToArabic["Y"] = QString(QChar(0x064A)); // ي
    latinToArabic["Z"] = QString(QChar(0x0632)); // ز
    latinToArabic["Ž"] = QString(QChar(0x0636)); // ض (对应Ž)
    latinToArabic["Sh"] = QString(QChar(0x0634)); // ش
    latinToArabic["Th"] = QString(QChar(0x062B)); // ث
    latinToArabic["Dh"] = QString(QChar(0x0630)); // ذ
    latinToArabic["Kh"] = QString(QChar(0x062E)); // خ
    latinToArabic["Gh"] = QString(QChar(0x063A)); // غ
    latinToArabic["Aa"] = QString(QChar(0x0622)); // آ (长音A)
    latinToArabic["Ee"] = QString(QChar(0x0635)); // ص (长音E)
    latinToArabic["Oo"] = QString(QChar(0x0623)); // أ (长音O


    // 拉丁字母到波斯语的映射
    // 波斯语使用阿拉伯字母表，但有一些额外的字母和发音
    latinToPersian["A"] = QString(QChar(0x0639)); //  ع (保留最后出现的映射)
    latinToPersian["B"] = QString(QChar(0x0628)); //  ب
    latinToPersian["C"] = QString(QChar(0x0633)); //  س (参考阿拉伯语映射)
    latinToPersian["D"] = QString(QChar(0x0636)); //  ض (保留最后出现的映射)
    latinToPersian["E"] = QString(QChar(0x0639)); //  ع (参考阿拉伯语映射)
    latinToPersian["F"] = QString(QChar(0x0641)); //  ف
    latinToPersian["G"] = QString(QChar(0x06AF)); //  گ
    latinToPersian["H"] = QString(QChar(0x0647)); //  ه (保留最后出现的映射)
    latinToPersian["I"] = QString(QChar(0x064A)); //  ی (参考阿拉伯语映射)
    latinToPersian["J"] = QString(QChar(0x062C)); //  ج
    latinToPersian["K"] = QString(QChar(0x0643)); //  ك
    latinToPersian["L"] = QString(QChar(0x0644)); //  ل (参考阿拉伯语映射)
    latinToPersian["M"] = QString(QChar(0x0645)); //  م
    latinToPersian["N"] = QString(QChar(0x0646)); //  ن (参考阿拉伯语映射)
    latinToPersian["O"] = QString(QChar(0x0648)); //  و (参考阿拉伯语映射)
    latinToPersian["P"] = QString(QChar(0x067E)); //  پ
    latinToPersian["Q"] = QString(QChar(0x0642)); //  ق (参考阿拉伯语映射)
    latinToPersian["R"] = QString(QChar(0x0631)); //  ر
    latinToPersian["S"] = QString(QChar(0x0635)); //  ص (保留最后出现的映射)
    latinToPersian["T"] = QString(QChar(0x0637)); //  ط (保留最后出现的映射)
    latinToPersian["U"] = QString(QChar(0x0648)); //  و (参考阿拉伯语映射)
    latinToPersian["V"] = QString(QChar(0x0648)); //  و
    latinToPersian["W"] = QString(QChar(0x0648)); //  و (参考阿拉伯语映射)
    latinToPersian["X"] = QString(QChar(0x062E)); //  خ (参考阿拉伯语映射)
    latinToPersian["Y"] = QString(QChar(0x064A)); //  ی
    latinToPersian["Z"] = QString(QChar(0x0638)); //  ظ (保留最后出现的映射)
    latinToPersian["Ch"] = QString(QChar(0x0686)); //  چ
    latinToPersian["Dh"] = QString(QChar(0x062F)); //  د (对应英语dh发音)
    latinToPersian["Gh"] = QString(QChar(0x063A)); //  غ
    latinToPersian["Kh"] = QString(QChar(0x062E)); //  خ
    latinToPersian["Sh"] = QString(QChar(0x0634)); //  ش
    latinToPersian["Th"] = QString(QChar(0x062A)); //  ت (对应英语th发音)
    latinToPersian["Zh"] = QString(QChar(0x0698)); //  ژ


    // 拉丁字母到希伯来字母的映射
    // 拉丁字母到希伯来字母的映射（基于SBL转写系统）
    latinToHebrew["A"] = QString(QChar(0x05D0)); // א
    latinToHebrew["B"] = QString(QChar(0x05D1)); // ב
    latinToHebrew["C"] = QString(QChar(0x05E6)); // צ
    latinToHebrew["D"] = QString(QChar(0x05D3)); // ד
    latinToHebrew["E"] = QString(QChar(0x05D0)) + QString(QChar(0x05B5)); // אֶ (e音)
    latinToHebrew["F"] = QString(QChar(0x05E4)); // פ
    latinToHebrew["G"] = QString(QChar(0x05D2)); // ג
    latinToHebrew["H"] = QString(QChar(0x05D4)); // ה
    latinToHebrew["I"] = QString(QChar(0x05D9)); // י (表示i音)
    latinToHebrew["J"] = QString(QChar(0x05D9)); // י (表示j音)
    latinToHebrew["K"] = QString(QChar(0x05DB)); // כ
    latinToHebrew["L"] = QString(QChar(0x05DC)); // ל
    latinToHebrew["M"] = QString(QChar(0x05DE)); // מ
    latinToHebrew["N"] = QString(QChar(0x05E0)); // נ
    latinToHebrew["O"] = QString(QChar(0x05D5)) + QString(QChar(0x05B9)); // וֹ (o音)
    latinToHebrew["P"] = QString(QChar(0x05E4)); // פ
    latinToHebrew["Q"] = QString(QChar(0x05E7)); // ק
    latinToHebrew["R"] = QString(QChar(0x05E8)); // ר
    latinToHebrew["S"] = QString(QChar(0x05E1)); // ס
    latinToHebrew["T"] = QString(QChar(0x05D8)); // ט
    latinToHebrew["U"] = QString(QChar(0x05D5)) + QString(QChar(0x05BC)); // וּ (u音)
    latinToHebrew["V"] = QString(QChar(0x05D5)); // ו
    latinToHebrew["W"] = QString(QChar(0x05D5)); // ו
    latinToHebrew["X"] = QString(QChar(0x05E6)) + QString(QChar(0x05E1)); // צס (近似x音)
    latinToHebrew["Y"] = QString(QChar(0x05D9)); // י
    latinToHebrew["Z"] = QString(QChar(0x05D6)); // ז
    latinToHebrew["Ch"] = QString(QChar(0x05D7)); // ח
    latinToHebrew["Sh"] = QString(QChar(0x05E9)); // ש
    latinToHebrew["Ts"] = QString(QChar(0x05E6)); // צ
    latinToHebrew["Ayin"] = QString(QChar(0x05E2)); // ע

    // 拉丁字母到卢恩字母的映射
    latinToRunic["A"] = QString(QChar(0x16A8)); // ᚨ
    latinToRunic["B"] = QString(QChar(0x16D2)); // ᚲ
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
    latinToRunic["Q"] = QString(QChar(0x16B2)); // ᚲ (使用K代替)
    latinToRunic["R"] = QString(QChar(0x16B1)); // ᚱ
    latinToRunic["S"] = QString(QChar(0x16CB)); // ᛋ
    latinToRunic["T"] = QString(QChar(0x16CF)); // ᛏ
    latinToRunic["U"] = QString(QChar(0x16A2)); // ᚢ
    latinToRunic["V"] = QString(QChar(0x16A0)); // ᚠ (使用F代替)
    latinToRunic["W"] = QString(QChar(0x16B9)); // ᚹ
    latinToRunic["X"] = QString(QChar(0x16C9)); // ᛉ
    latinToRunic["Y"] = QString(QChar(0x16A3)); // ᚣ
    latinToRunic["Z"] = QString(QChar(0x16CE)); // ᛉ


    // 拉丁字母到高棉文的映射
    latinToKhmer["A"] = QString(QChar(0x1791)); // អ
    latinToKhmer["B"] = QString(QChar(0x1793)); // ប
    latinToKhmer["C"] = QString(QChar(0x1786)); // ឆ (修正，之前与H重复)
    latinToKhmer["D"] = QString(QChar(0x1794)); // ដ
    latinToKhmer["E"] = QString(QChar(0x1791)) + QString(QChar(0x17B6)); // អេ (改为组合字符)
    latinToKhmer["F"] = QString(QChar(0x17A0)) + QString(QChar(0x17C1)); // ហ្វ (改为组合字符)
    latinToKhmer["G"] = QString(QChar(0x1797)); // ក
    latinToKhmer["H"] = QString(QChar(0x17A0)); // ហ
    latinToKhmer["I"] = QString(QChar(0x1791)) + QString(QChar(0x17B7)); // អិ (改为组合字符)
    latinToKhmer["J"] = QString(QChar(0x1787)); // ជ (修正，之前是ឣ)
    latinToKhmer["K"] = QString(QChar(0x1796)); // ខ (修正，之前与G重复)
    latinToKhmer["L"] = QString(QChar(0x17A1)); // ឡ (修正，之前是វ)
    latinToKhmer["M"] = QString(QChar(0x17A2)); // ម (修正，之前是គ)
    latinToKhmer["N"] = QString(QChar(0x1799)); // ន (修正，之前是យ)
    latinToKhmer["O"] = QString(QChar(0x1791)) + QString(QChar(0x17B8)); // អូ (改为组合字符)
    latinToKhmer["P"] = QString(QChar(0x179F)); // ស (保持，但F已修改)
    latinToKhmer["Q"] = QString(QChar(0x1798)); // ឃ (新增映射)
    latinToKhmer["R"] = QString(QChar(0x179A)); // រ (修正，之前是ម)
    latinToKhmer["S"] = QString(QChar(0x17A4)); // ឤ (保持)
    latinToKhmer["T"] = QString(QChar(0x1795)); // ឌ (保持)
    latinToKhmer["U"] = QString(QChar(0x1791)) + QString(QChar(0x17B9)); // អុ (改为组合字符)
    latinToKhmer["V"] = QString(QChar(0x179C)); // វ (修正，之前是ឦ)
    latinToKhmer["W"] = QString(QChar(0x179C)); // វ (与V相同)
    latinToKhmer["X"] = QString(QChar(0x17A5)); // ឥ (修正，之前是ឨ)
    latinToKhmer["Y"] = QString(QChar(0x179D)); // យ (修正，之前是ឩ)
    latinToKhmer["Z"] = QString(QChar(0x179B)); // ល (修正，之前是ឪ)

    // 拉丁字母到谚文字母的映射
    latinToHangul["A"] = QString(QChar(0xAC00)); // 가
    latinToHangul["B"] = QString(QChar(0xBC14)); // 바
    latinToHangul["C"] = QString(QChar(0xCE58)); // 치
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

    // 拉丁字母到假名的映射
    latinToKana["A"] = QString(QChar(0x30A2)); // ア
    latinToKana["B"] = QString(QChar(0x30D0)); // バ
    latinToKana["C"] = QString(QChar(0x30B7)); // シ
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
    latinToKana["X"] = QString(QChar(0x30B7)); // シ
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

    QString intermediateText = text;
    // 如果目标不是拉丁字母且方向是TargetToLatin，先转换为拉丁字母
    if (direction != LatinToTarget) {
        intermediateText = convertText(text, system, LatinToTarget);
    }

    QString result;
    QMap<QString, QString> *currentMap = nullptr; // 修改为QString映射

    if (direction == LatinToTarget) {
        switch(system) {
        case Cyrillic: currentMap = &latinToCyrillic; break;
        case Greek: currentMap = &latinToGreek; break;
        case Syriac: currentMap = &latinToSyriac; break;
        case Tibetan: currentMap = &latinToTibetan; break;
        case Devanagari: currentMap = &latinToDevanagari; break;
        case Hebrew: currentMap = &latinToHebrew; break;
        case Runic: currentMap = &latinToRunic; break;
        case Hangul: currentMap = &latinToHangul; break;
        case Kana: currentMap = &latinToKana; break;
        case Zhuyin: currentMap = &latinToZhuyin; break;
        case Arabic: currentMap = &latinToArabic; break;
        case Uyghur: currentMap = &latinToUyghur; break;
        case Persian: currentMap = &latinToPersian; break;
        case Khmer: currentMap = &latinToKhmer; break;
        default: break;
        }
    } else {
        switch(system) {
        case Cyrillic: currentMap = &cyrillicToLatin; break;
        case Greek: currentMap = &greekToLatin; break;
        case Syriac: currentMap = &syriacToLatin; break;
        case Tibetan: currentMap = &tibetanToLatin; break;
        case Devanagari: currentMap = &devanagariToLatin; break;
        case Hebrew: currentMap = &hebrewToLatin; break;
        case Runic: currentMap = &runicToLatin; break;
        case Hangul: currentMap = &hangulToLatin; break;
        case Kana: currentMap = &kanaToLatin; break;
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

        // 检查是否可能是多字符组合（如"Ch"、"Kh"等）
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
