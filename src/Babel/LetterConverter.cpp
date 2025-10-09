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
    latinToCyrillic["ß"] = QString(QChar(0x0421)) + QString(QChar(0x0421)); // СС (近似)

    // 小写拉丁字母到西里尔字母的映射
    latinToCyrillic["a"] = QString(QChar(0x0430)); // а
    latinToCyrillic["b"] = QString(QChar(0x0431)); // б
    latinToCyrillic["c"] = QString(QChar(0x0441)); // с (注意：C的映射由convertText的发音规则决定)
    latinToCyrillic["d"] = QString(QChar(0x0434)); // д
    latinToCyrillic["e"] = QString(QChar(0x0435)); // е
    latinToCyrillic["f"] = QString(QChar(0x0444)); // ф
    latinToCyrillic["g"] = QString(QChar(0x0433)); // г (软音处理在convertText)
    latinToCyrillic["h"] = QString(QChar(0x0445)); // х
    latinToCyrillic["i"] = QString(QChar(0x0438)); // и
    latinToCyrillic["j"] = QString(QChar(0x0439)); // й
    latinToCyrillic["k"] = QString(QChar(0x043A)); // к
    latinToCyrillic["l"] = QString(QChar(0x043B)); // л
    latinToCyrillic["m"] = QString(QChar(0x043C)); // м
    latinToCyrillic["n"] = QString(QChar(0x043D)); // н
    latinToCyrillic["o"] = QString(QChar(0x043E)); // о
    latinToCyrillic["p"] = QString(QChar(0x043F)); // п
    latinToCyrillic["q"] = QString(QChar(0x043A)) + QString(QChar(0x0441)); // кс (近似)
    latinToCyrillic["r"] = QString(QChar(0x0440)); // р
    latinToCyrillic["s"] = QString(QChar(0x0441)); // с
    latinToCyrillic["t"] = QString(QChar(0x0442)); // т
    latinToCyrillic["u"] = QString(QChar(0x0443)); // у
    latinToCyrillic["v"] = QString(QChar(0x0432)); // в
    latinToCyrillic["w"] = QString(QChar(0x0432)); // в (W 常映射为 в)
    latinToCyrillic["x"] = QString(QChar(0x043A)) + QString(QChar(0x0441)); // кс (在convertText中处理)
    latinToCyrillic["y"] = QString(QChar(0x044B)); // ы
    latinToCyrillic["z"] = QString(QChar(0x0437)); // з
    latinToCyrillic["yo"] = QString(QChar(0x0451)); // ё
    latinToCyrillic["yu"] = QString(QChar(0x044E)); // ю
    latinToCyrillic["ya"] = QString(QChar(0x044F)); // я
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
    // 常见外来后缀/多音节（用户要求）
    latinToCyrillic["TION"] = QString("ЦИОН"); // tion -> ЦИОН
    latinToCyrillic["SION"] = QString("СИОН"); // sion -> СИОН
    latinToCyrillic["ING"] = QString("ИНГ"); // ing -> ИНГ
    latinToCyrillic["ANG"] = QString("АНГ"); // ang -> АНГ
    latinToCyrillic["ONG"] = QString("ОНГ"); // ong -> ОНГ
    latinToCyrillic["ION"] = QString("ИОН"); // ion -> ИОН
    latinToCyrillic["sch"] = QString(QChar(0x0449)); // щ
    latinToCyrillic["sh"]  = QString(QChar(0x0448)); // ш
    latinToCyrillic["ch"]  = QString(QChar(0x0447)); // ч
    latinToCyrillic["kh"]  = QString(QChar(0x0445)); // х
    latinToCyrillic["zh"]  = QString(QChar(0x0436)); // ж
    latinToCyrillic["tsh"] = QString(QChar(0x0442)) + QString(QChar(0x0448)); // тш (示例组合)
    latinToCyrillic["ts"] = QString(QChar(0x0446)); // ц
    latinToCyrillic["dz"] = QString(QChar(0x0436)) + QString(QChar(0x043A)); // дз
    latinToCyrillic["dzh"] = QString(QChar(0x0434)) + QString(QChar(0x0436)); // дж
    latinToCyrillic["nj"] = QString(QChar(0x043D)) + QString(QChar(0x0436)); // њ
    latinToCyrillic["lj"] = QString(QChar(0x043B)) + QString(QChar(0x0436)); // љ



    // -----------------------------------------------------------------
    // 拉丁字母到希腊字母的映射 (改进版)
    // -----------------------------------------------------------------
    latinToGreek["A"] = QString(QChar(0x0391)); // Α
    latinToGreek["B"] = QString(QChar(0x0392)); // Β
    latinToGreek["C"] = QString(QChar(0x03A7)); // Χ
    latinToGreek["D"] = QString(QChar(0x0394)); // Δ
    latinToGreek["E"] = QString(QChar(0x0395)); // Ε
    latinToGreek["F"] = QString(QChar(0x03A6)); // Φ
    latinToGreek["G"] = QString(QChar(0x0393)); // Γ
    latinToGreek["H"] = QString(QChar(0x0397)); // Η
    latinToGreek["I"] = QString(QChar(0x0399)); // Ι
    latinToGreek["J"] = QString(QChar(0x03B9)); // ι (使用小写 iota 表示 j)
    latinToGreek["K"] = QString(QChar(0x039A)); // Κ
    latinToGreek["L"] = QString(QChar(0x039B)); // Λ
    latinToGreek["M"] = QString(QChar(0x039C)); // Μ
    latinToGreek["N"] = QString(QChar(0x039D)); //
    latinToGreek["O"] = QString(QChar(0x039F)); // Ο
    latinToGreek["P"] = QString(QChar(0x03A0)); // Π
    latinToGreek["Q"] = QString(QChar(0x0398)); // Θ (使用Theta表示Q)
    latinToGreek["R"] = QString(QChar(0x03A1)); // Ρ
    latinToGreek["S"] = QString(QChar(0x03A3)); // Σ
    latinToGreek["T"] = QString(QChar(0x03A4)); // Τ
    latinToGreek["U"] = QString(QChar(0x03A5)); // Υ
    latinToGreek["V"] = QString(QChar(0x0392)); // Β
    latinToGreek["W"] = QString(QChar(0x03A9)); // Ω
    latinToGreek["X"] = QString(QChar(0x039E)); // Ξ
    latinToGreek["Y"] = QString(QChar(0x03A5)); // Υ (使用Upsilon表示Y)
    latinToGreek["Z"] = QString(QChar(0x0396)); // Ζ
    latinToGreek["ZH"] = QString(QChar(0x0396)) + QString(QChar(0x03B9)); // Ζι (近似)
    latinToGreek["CH"] = QString(QChar(0x03C7)); // χ (小写 chi)
    latinToGreek["SH"] = QString(QChar(0x03C3)) + QString(QChar(0x03B9)); // σι (近似)
    latinToGreek["TH"] = QString(QChar(0x0398)); // Θ
    latinToGreek["AE"] = QString(QChar(0x03AC)); // ά
    latinToGreek["EE"] = QString(QChar(0x03AD)); // έ
    latinToGreek["IE"] = QString(QChar(0x03AF)); // ί
    latinToGreek["OE"] = QString(QChar(0x03CC)); // ό
    latinToGreek["UE"] = QString(QChar(0x03CD)); // ύ
    latinToGreek["HE"] = QString(QChar(0x03AE)); // ή
    latinToGreek["WIE"] = QString(QChar(0x03CE)); // ώ
    latinToGreek["a"] = QString(QChar(0x03B1)); // α
    latinToGreek["b"] = QString(QChar(0x03B2)); // β
    latinToGreek["g"] = QString(QChar(0x03B3)); // γ
    latinToGreek["d"] = QString(QChar(0x03B4)); // δ
    latinToGreek["e"] = QString(QChar(0x03B5)); // ε
    latinToGreek["z"] = QString(QChar(0x03B6)); // ζ
    latinToGreek["h"] = QString(QChar(0x03B7)); // η
    latinToGreek["th"] = QString(QChar(0x03B8)); // θ
    latinToGreek["i"] = QString(QChar(0x03B9)); // ι
    latinToGreek["k"] = QString(QChar(0x03BA)); // κ
    latinToGreek["l"] = QString(QChar(0x03BB)); // λ
    latinToGreek["m"] = QString(QChar(0x03BC)); // μ
    latinToGreek["n"] = QString(QChar(0x03BD)); // ν
    latinToGreek["x"] = QString(QChar(0x03BE)); // ξ
    latinToGreek["o"] = QString(QChar(0x03BF)); // ο
    latinToGreek["p"] = QString(QChar(0x03C0)); // π
    latinToGreek["r"] = QString(QChar(0x03C1)); // ρ
    latinToGreek["s"] = QString(QChar(0x03C3)); // σ
    latinToGreek["t"] = QString(QChar(0x03C4)); // τ
    latinToGreek["u"] = QString(QChar(0x03C5)); // υ
    latinToGreek["f"] = QString(QChar(0x03C6)); // φ
    latinToGreek["c"] = QString(QChar(0x03C7)); // χ
    latinToGreek["v"] = QString(QChar(0x03C2)); // ς (词尾sigma)
    latinToGreek["w"] = QString(QChar(0x03C9)); // ω
    latinToGreek["ae"] = QString(QChar(0x03AC)); // ά
    latinToGreek["ee"] = QString(QChar(0x03AD)); // έ
    latinToGreek["ie"] = QString(QChar(0x03AF)); // ί
    latinToGreek["oe"] = QString(QChar(0x03CC)); // ό
    latinToGreek["ue"] = QString(QChar(0x03CD)); // ύ
    latinToGreek["he"] = QString(QChar(0x03AE)); // ή
    latinToGreek["wie"] = QString(QChar(0x03CE)); // ώ
    latinToGreek["zh"] = QString(QChar(0x03B6)) + QString(QChar(0x03B9)); // ζι (近似)
    latinToGreek["ch"] = QString(QChar(0x03C7)); // χ
    latinToGreek["sh"] = QString(QChar(0x03C3)) + QString(QChar(0x03B9)); // σι (近似)
    latinToGreek["ā"] = QString(QChar(0x03B1)) + QString(QChar(0x0304)); // ᾱ (第一声)
    latinToGreek["á"] = QString(QChar(0x03AC)); // ά (第二声)
    latinToGreek["ǎ"] = QString(QChar(0x03B1)) + QString(QChar(0x030C)); // α̌ (第三声)
    latinToGreek["à"] = QString(QChar(0x03B1)) + QString(QChar(0x0300)); // ὰ (第四声)
    latinToGreek["a"] = QString(QChar(0x03B1)); // α (轻声)
    latinToGreek["ē"] = QString(QChar(0x03B5)) + QString(QChar(0x0304)); // ε̄ (第一声)
    latinToGreek["é"] = QString(QChar(0x03AD)); // έ (第二声)
    latinToGreek["ě"] = QString(QChar(0x03B5)) + QString(QChar(0x030C)); // ε̌ (第三声)
    latinToGreek["è"] = QString(QChar(0x03B5)) + QString(QChar(0x0300)); // ὲ (第四声)
    latinToGreek["e"] = QString(QChar(0x03B5)); // ε (轻声)
    latinToGreek["ī"] = QString(QChar(0x03B9)) + QString(QChar(0x0304)); // ῑ (第一声)
    latinToGreek["í"] = QString(QChar(0x03AF)); // ί (第二声)
    latinToGreek["ǐ"] = QString(QChar(0x03B9)) + QString(QChar(0x030C)); // ι̌ (第三声)
    latinToGreek["ì"] = QString(QChar(0x03B9)) + QString(QChar(0x0300)); // ὶ (第四声)
    latinToGreek["i"] = QString(QChar(0x03B9)); // ι (轻声)
    latinToGreek["ō"] = QString(QChar(0x03BF)) + QString(QChar(0x0304)); // ο̄ (第一声)
    latinToGreek["ó"] = QString(QChar(0x03CC)); // ό (第二声)
    latinToGreek["ǒ"] = QString(QChar(0x03BF)) + QString(QChar(0x030C)); // ο̌ (第三声)
    latinToGreek["ò"] = QString(QChar(0x03BF)) + QString(QChar(0x0300)); // ὸ (第四声)
    latinToGreek["o"] = QString(QChar(0x03BF)); // ο (轻声)
    latinToGreek["ū"] = QString(QChar(0x03C5)) + QString(QChar(0x0304)); // ῡ (第一声)
    latinToGreek["ú"] = QString(QChar(0x03CD)); // ύ (第二声)
    latinToGreek["ǔ"] = QString(QChar(0x03C5)) + QString(QChar(0x030C)); // υ̌ (第三声)
    latinToGreek["ù"] = QString(QChar(0x03C5)) + QString(QChar(0x0300)); // ὺ (第四声)
    latinToGreek["u"] = QString(QChar(0x03C5)); // υ (轻声)
    latinToGreek["ǖ"] = QString(QChar(0x03CB)) + QString(QChar(0x0304)); // ϋ̄ (第一声)
    latinToGreek["ǘ"] = QString(QChar(0x03CB)) + QString(QChar(0x0301)); // ΰ (第二声)
    latinToGreek["ǚ"] = QString(QChar(0x03CB)) + QString(QChar(0x030C)); // ϋ̌ (第三声)
    latinToGreek["ǜ"] = QString(QChar(0x03CB)) + QString(QChar(0x0300)); // ῢ (第四声)
    latinToGreek["ü"] = QString(QChar(0x03CB)); // ϋ (轻声)
    latinToGreek["Ā"] = QString(QChar(0x0391)) + QString(QChar(0x0304)); // Ᾱ (第一声)
    latinToGreek["Á"] = QString(QChar(0x0386)); // Ά (第二声)
    latinToGreek["Ǎ"] = QString(QChar(0x0391)) + QString(QChar(0x030C)); // Α̌ (第三声)
    latinToGreek["À"] = QString(QChar(0x0391)) + QString(QChar(0x0300)); // Ὰ (第四声)
    latinToGreek["Ē"] = QString(QChar(0x0395)) + QString(QChar(0x0304)); // Ε̄ (第一声)
    latinToGreek["É"] = QString(QChar(0x0388)); // Έ (第二声)
    latinToGreek["Ě"] = QString(QChar(0x0395)) + QString(QChar(0x030C)); // Ε̌ (第三声)
    latinToGreek["È"] = QString(QChar(0x0395)) + QString(QChar(0x0300)); // Ὲ (第四声)
    latinToGreek["Ī"] = QString(QChar(0x0399)) + QString(QChar(0x0304)); // Ῑ (第一声)
    latinToGreek["Í"] = QString(QChar(0x038A)); // Ί (第二声)
    latinToGreek["Ǐ"] = QString(QChar(0x0399)) + QString(QChar(0x030C)); // Ι̌ (第三声)
    latinToGreek["Ì"] = QString(QChar(0x0399)) + QString(QChar(0x0300)); // Ὶ (第四声)
    latinToGreek["Ō"] = QString(QChar(0x039F)) + QString(QChar(0x0304)); // Ο̄ (第一声)
    latinToGreek["Ó"] = QString(QChar(0x038C)); // Ό (第二声)
    latinToGreek["Ǒ"] = QString(QChar(0x039F)) + QString(QChar(0x030C)); // Ο̌ (第三声)
    latinToGreek["Ò"] = QString(QChar(0x039F)) + QString(QChar(0x0300)); // Ὸ (第四声)
    latinToGreek["Ū"] = QString(QChar(0x03A5)) + QString(QChar(0x0304)); // Ῡ (第一声)
    latinToGreek["Ú"] = QString(QChar(0x038E)); // Ύ (第二声)
    latinToGreek["Ǔ"] = QString(QChar(0x03A5)) + QString(QChar(0x030C)); // Υ̌ (第三声)
    latinToGreek["Ù"] = QString(QChar(0x03A5)) + QString(QChar(0x0300)); // Ὺ (第四声)
    latinToGreek["ã"] = QString(QChar(0x03B1)) + QString(QChar(0x0303)); // α̃
    latinToGreek["ẽ"] = QString(QChar(0x03B5)) + QString(QChar(0x0303)); // ε̃
    latinToGreek["ĩ"] = QString(QChar(0x03B9)) + QString(QChar(0x0303)); // ι̃
    latinToGreek["õ"] = QString(QChar(0x03BF)) + QString(QChar(0x0303)); // ο̃
    latinToGreek["ũ"] = QString(QChar(0x03C5)) + QString(QChar(0x0303)); // υ̃
    latinToGreek["Ã"] = QString(QChar(0x0391)) + QString(QChar(0x0303)); // Α̃
    latinToGreek["Ẽ"] = QString(QChar(0x0395)) + QString(QChar(0x0303)); // Ε̃
    latinToGreek["Ĩ"] = QString(QChar(0x0399)) + QString(QChar(0x0303)); // Ι̃
    latinToGreek["Õ"] = QString(QChar(0x039F)) + QString(QChar(0x0303)); // Ο̃
    latinToGreek["Ũ"] = QString(QChar(0x03A5)) + QString(QChar(0x0303)); // Υ̃
    latinToGreek["ä"] = QString(QChar(0x03B0)); // ϊ (近似)
    latinToGreek["ë"] = QString(QChar(0x03B5)) + QString(QChar(0x0308)); // ε̈
    latinToGreek["ï"] = QString(QChar(0x03CA)); // ϊ
    latinToGreek["ö"] = QString(QChar(0x03CC)); // ό (近似)
    latinToGreek["ü"] = QString(QChar(0x03CB)); // ϋ
    latinToGreek["ÿ"] = QString(QChar(0x03CB)) + QString(QChar(0x0301)); // ΰ
    latinToGreek["Ä"] = QString(QChar(0x03AA)); // Ϊ
    latinToGreek["Ë"] = QString(QChar(0x0395)) + QString(QChar(0x0308)); // Ε̈
    latinToGreek["Ï"] = QString(QChar(0x03AA)); // Ϊ
    latinToGreek["Ö"] = QString(QChar(0x038C)); // Ό (近似)
    latinToGreek["Ü"] = QString(QChar(0x03AB)); // Ϋ
    latinToGreek["Ÿ"] = QString(QChar(0x03AB)) + QString(QChar(0x0301)); // Ϋ́
    latinToGreek["â"] = QString(QChar(0x03B1)) + QString(QChar(0x0302)); // α̂
    latinToGreek["ê"] = QString(QChar(0x03B5)) + QString(QChar(0x0302)); // ε̂
    latinToGreek["î"] = QString(QChar(0x03B9)) + QString(QChar(0x0302)); // ι̂
    latinToGreek["ô"] = QString(QChar(0x03BF)) + QString(QChar(0x0302)); // ο̂
    latinToGreek["û"] = QString(QChar(0x03C5)) + QString(QChar(0x0302)); // υ̂
    latinToGreek["Â"] = QString(QChar(0x0391)) + QString(QChar(0x0302)); // Α̂
    latinToGreek["Ê"] = QString(QChar(0x0395)) + QString(QChar(0x0302)); // Ε̂
    latinToGreek["Î"] = QString(QChar(0x0399)) + QString(QChar(0x0302)); // Ι̂
    latinToGreek["Ô"] = QString(QChar(0x039F)) + QString(QChar(0x0302)); // Ο̂
    latinToGreek["Û"] = QString(QChar(0x03A5)) + QString(QChar(0x0302)); // Υ̂
    latinToGreek["ç"] = QString(QChar(0x03B8)); // θ (近似)
    latinToGreek["ñ"] = QString(QChar(0x03B7)) + QString(QChar(0x0303)); // η̃ (近似)
    latinToGreek["Ç"] = QString(QChar(0x0398)); // Θ (近似)
    latinToGreek["Ñ"] = QString(QChar(0x0397)) + QString(QChar(0x0303)); // Η̃ (近似)
    latinToGreek["āi"] = QString(QChar(0x03B1)) + QString(QChar(0x0304)) + QString(QChar(0x03B9)); // ᾱι
    latinToGreek["ái"] = QString(QChar(0x03AC)) + QString(QChar(0x03B9)); // άι
    latinToGreek["ǎi"] = QString(QChar(0x03B1)) + QString(QChar(0x030C)) + QString(QChar(0x03B9)); // α̌ι
    latinToGreek["ài"] = QString(QChar(0x03B1)) + QString(QChar(0x0300)) + QString(QChar(0x03B9)); // ὰι
    latinToGreek["āo"] = QString(QChar(0x03B1)) + QString(QChar(0x0304)) + QString(QChar(0x03BF)); // ᾱο
    latinToGreek["áo"] = QString(QChar(0x03AC)) + QString(QChar(0x03BF)); // άο
    latinToGreek["ǎo"] = QString(QChar(0x03B1)) + QString(QChar(0x030C)) + QString(QChar(0x03BF)); // α̌ο
    latinToGreek["ào"] = QString(QChar(0x03B1)) + QString(QChar(0x0300)) + QString(QChar(0x03BF)); // ὰο
    latinToGreek["ēi"] = QString(QChar(0x03B5)) + QString(QChar(0x0304)) + QString(QChar(0x03B9)); // ε̄ι
    latinToGreek["éi"] = QString(QChar(0x03AD)) + QString(QChar(0x03B9)); // ει
    latinToGreek["ěi"] = QString(QChar(0x03B5)) + QString(QChar(0x030C)) + QString(QChar(0x03B9)); // ε̌ι
    latinToGreek["èi"] = QString(QChar(0x03B5)) + QString(QChar(0x0300)) + QString(QChar(0x03B9)); // ὲι
    latinToGreek["ōu"] = QString(QChar(0x03BF)) + QString(QChar(0x0304)) + QString(QChar(0x03C5)); // ο̄υ
    latinToGreek["óu"] = QString(QChar(0x03CC)) + QString(QChar(0x03C5)); // ου
    latinToGreek["ǒu"] = QString(QChar(0x03BF)) + QString(QChar(0x030C)) + QString(QChar(0x03C5)); // ο̌υ
    latinToGreek["òu"] = QString(QChar(0x03BF)) + QString(QChar(0x0300)) + QString(QChar(0x03C5)); // ὸυ


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



    // ---------------------------------------------------------------------------
      // 拉丁字母到麦罗埃文草书体 (Meroitic Cursive)
      // ---------------------------------------------------------------------------
      // 基本元音
      latinToMeroiticCursive["A"] = QString("𐦠"); // a
      latinToMeroiticCursive["E"] = QString("𐦡"); // e
      latinToMeroiticCursive["I"] = QString("𐦢"); // i
      latinToMeroiticCursive["O"] = QString("𐦣"); // o
      latinToMeroiticCursive["U"] = QString("𐦤"); // u

      // 基本辅音
      latinToMeroiticCursive["B"] = QString("𐦥"); // b
      latinToMeroiticCursive["C"] = QString("𐦤"); // c
      latinToMeroiticCursive["D"] = QString("𐦦"); // d
      latinToMeroiticCursive["F"] = QString("𐦧"); // f
      latinToMeroiticCursive["G"] = QString("𐦨"); // g
      latinToMeroiticCursive["H"] = QString("𐦩"); // h
      latinToMeroiticCursive["J"] = QString("𐦪"); // j
      latinToMeroiticCursive["K"] = QString("𐦫"); // k
      latinToMeroiticCursive["L"] = QString("𐦬"); // l
      latinToMeroiticCursive["M"] = QString("𐦭"); // m
      latinToMeroiticCursive["N"] = QString("𐦮"); // n
      latinToMeroiticCursive["P"] = QString("𐦯"); // p
      latinToMeroiticCursive["Q"] = QString("𐦰"); // q
      latinToMeroiticCursive["R"] = QString("𐦱"); // r
      latinToMeroiticCursive["S"] = QString("𐦲"); // s
      latinToMeroiticCursive["T"] = QString("𐦳"); // t
      latinToMeroiticCursive["V"] = QString("𐦴"); // v
      latinToMeroiticCursive["W"] = QString("𐦵"); // w
      latinToMeroiticCursive["X"] = QString("𐦼"); // x
      latinToMeroiticCursive["Y"] = QString("𐦶"); // y
      latinToMeroiticCursive["Z"] = QString("𐦷"); // z

      // 常见辅音组合
      latinToMeroiticCursive["SH"] = QString("𐦸"); // sh
      latinToMeroiticCursive["KH"] = QString("𐦹"); // kh
      latinToMeroiticCursive["TH"] = QString("𐦺"); // th
      latinToMeroiticCursive["NH"] = QString("𐦻"); // nh


    // -------------------------
    // 完善的叙利亚字母映射表（大写字母 + 大写多音节）
    // 适配汉语拼音（含 ü 和四声调）
    // -------------------------

    // 辅音
    latinToSyriac["B"] = QString(QChar(0x0712));  // ܒ
    latinToSyriac["C"] = QString(QChar(0x072D));  // ܭ
    latinToSyriac["D"] = QString(QChar(0x0715));  // ܕ
    latinToSyriac["F"] = QString(QChar(0x0726));  // ܦ
    latinToSyriac["G"] = QString(QChar(0x0713));  // ܓ
    latinToSyriac["H"] = QString(QChar(0x071A));  // ܚ
    latinToSyriac["J"] = QString(QChar(0x0723));  // ܣ (近似 J)
    latinToSyriac["K"] = QString(QChar(0x071F));  // ܟ
    latinToSyriac["L"] = QString(QChar(0x0720));  // ܠ
    latinToSyriac["M"] = QString(QChar(0x0721));  // ܡ
    latinToSyriac["N"] = QString(QChar(0x0722));  // ܢ
    latinToSyriac["P"] = QString(QChar(0x0726));  // ܦ
    latinToSyriac["Q"] = QString(QChar(0x0729));  // ܩ
    latinToSyriac["R"] = QString(QChar(0x072A));  // ܪ
    latinToSyriac["S"] = QString(QChar(0x0723));  // ܣ
    latinToSyriac["T"] = QString(QChar(0x072C));  // ܬ
    latinToSyriac["V"] = QString(QChar(0x0712));  // ܒ (浊化)
    latinToSyriac["W"] = QString(QChar(0x0718));  // ܘ
    latinToSyriac["X"] = QString(QChar(0x0713));  // ܓ (近似 /x/)
    latinToSyriac["Y"] = QString(QChar(0x071D));  // ܝ
    latinToSyriac["Z"] = QString(QChar(0x0719));  // ܙ

    // 多音节组合（大写）
    latinToSyriac["SH"] = QString(QChar(0x072B)); // ܫ
    latinToSyriac["CH"] = QString(QChar(0x072B)); // ܫ (近似汉语 ch)
    latinToSyriac["ZH"] = QString(QChar(0x072E)); // ܮ
    latinToSyriac["TH"] = QString(QChar(0x071B)); // ܛ
    latinToSyriac["KH"] = QString(QChar(0x071C)); // ܜ
    latinToSyriac["GH"] = QString(QChar(0x0714)); // ܔ
    latinToSyriac["TS"] = QString(QChar(0x072F)); // ܯ
    latinToSyriac["DZ"] = QString(QChar(0x0716)); // ܖ

    // 基本元音（无调号，大写键）
    latinToSyriac["A"] = QString(QChar(0x0740));  // ܀
    latinToSyriac["E"] = QString(QChar(0x0741));  // ܁
    latinToSyriac["I"] = QString(QChar(0x0742));  // ܂
    latinToSyriac["O"] = QString(QChar(0x0743));  // ܃
    latinToSyriac["U"] = QString(QChar(0x0744));  // ܄
    latinToSyriac["Ü"] = QString(QChar(0x0759));  // ܙ (ü)





    // --------------------------------------------------------------------
    // 拉丁字母到古南阿拉伯字母映射表
    // -------------------------------------------------------------------
    // 单字母映射（基础映射）
    latinToOldSouthArabian["A"] = QString("𐩠"); // 𐩠
    latinToOldSouthArabian["B"] = QString("𐩡"); // 𐩡
    latinToOldSouthArabian["C"] = QString("𐩢"); // 𐩢
    latinToOldSouthArabian["D"] = QString("𐩣"); // 𐩣
    latinToOldSouthArabian["E"] = QString("𐩤"); // 𐩤
    latinToOldSouthArabian["F"] = QString("𐩥"); // 𐩥
    latinToOldSouthArabian["G"] = QString("𐩦"); // 𐩦
    latinToOldSouthArabian["H"] = QString("𐩧"); // 𐩧
    latinToOldSouthArabian["I"] = QString("𐩨"); // 𐩨
    latinToOldSouthArabian["J"] = QString("𐩩"); // 𐩩
    latinToOldSouthArabian["K"] = QString("𐩪"); // 𐩪
    latinToOldSouthArabian["L"] = QString("𐩫"); // 𐩫
    latinToOldSouthArabian["M"] = QString("𐩬"); // 𐩬
    latinToOldSouthArabian["N"] = QString("𐩭"); // 𐩭
    latinToOldSouthArabian["O"] = QString("𐩮"); // 𐩮
    latinToOldSouthArabian["P"] = QString("𐩯"); // 𐩯
    latinToOldSouthArabian["Q"] = QString("𐩰"); // 𐩰
    latinToOldSouthArabian["R"] = QString("𐩱"); // 𐩱
    latinToOldSouthArabian["S"] = QString("𐩲"); // 𐩲
    latinToOldSouthArabian["T"] = QString("𐩳"); // 𐩳
    latinToOldSouthArabian["U"] = QString("𐩴"); // 𐩴
    latinToOldSouthArabian["V"] = QString("𐩵"); // 𐩵
    latinToOldSouthArabian["W"] = QString("𐩶"); // 𐩶
    latinToOldSouthArabian["X"] = QString("𐩷"); // 𐩷
    latinToOldSouthArabian["Y"] = QString("𐩸"); // 𐩸
    latinToOldSouthArabian["Z"] = QString("𐩹"); // 𐩹

    // -------------------------
    // 拉丁字母到古北阿拉伯字母映射表
    // -------------------------
    // 单字母映射（基础映射）
    latinToOldNorthArabian["A"] = QString("𐪀"); // 𐪀
    latinToOldNorthArabian["B"] = QString("𐪁"); // 𐪁
    latinToOldNorthArabian["C"] = QString("𐪂"); // 𐪂
    latinToOldNorthArabian["D"] = QString("𐪃"); // 𐪃
    latinToOldNorthArabian["E"] = QString("𐪄"); // 𐪄
    latinToOldNorthArabian["F"] = QString("𐪅"); // 𐪅
    latinToOldNorthArabian["G"] = QString("𐪆"); // 𐪆
    latinToOldNorthArabian["H"] = QString("𐪇"); // 𐪇
    latinToOldNorthArabian["I"] = QString("𐪈"); // 𐪈
    latinToOldNorthArabian["J"] = QString("𐪉"); // 𐪉
    latinToOldNorthArabian["K"] = QString("𐪊"); // 𐪊
    latinToOldNorthArabian["L"] = QString("𐪋"); // 𐪋
    latinToOldNorthArabian["M"] = QString("𐪌"); // 𐪌
    latinToOldNorthArabian["N"] = QString("𐪍"); // 𐪍
    latinToOldNorthArabian["O"] = QString("𐪎"); // 𐪎
    latinToOldNorthArabian["P"] = QString("𐪏"); // 𐪏
    latinToOldNorthArabian["Q"] = QString("𐪐"); // 𐪐
    latinToOldNorthArabian["R"] = QString("𐪑"); // 𐪑
    latinToOldNorthArabian["S"] = QString("𐪒"); // 𐪒
    latinToOldNorthArabian["T"] = QString("𐪓"); // 𐪓
    latinToOldNorthArabian["U"] = QString("𐪔"); // 𐪔
    latinToOldNorthArabian["V"] = QString("𐪕"); // 𐪕
    latinToOldNorthArabian["W"] = QString("𐪖"); // 𐪖
    latinToOldNorthArabian["X"] = QString("𐪗"); // 𐪗
    latinToOldNorthArabian["Y"] = QString("𐪘"); // 𐪘
    latinToOldNorthArabian["Z"] = QString("𐪙"); // 𐪙

    // -------------------------------------------------------------------
    // 拉丁字母到阿拉伯字母（标准阿拉伯语）
    // 注意：部分发音优化将在 convertText 中根据上下文补充
    // -------------------------------------------------------------------

    // 基本拉丁字母 - 优化发音准确性
    latinToArabic["A"] = QString(QChar(0x0627)); // ا (Alif) - 长音a
    latinToArabic["B"] = QString(QChar(0x0628)); // ب (Ba)
    latinToArabic["C"] = QString(QChar(0x0633)); // س (Sin) - 更常见发/s/音
    latinToArabic["D"] = QString(QChar(0x062F)); // د (Dal)
    latinToArabic["E"] = QString(QChar(0x064A)); // ي (Ya) - 作为元音e
    latinToArabic["F"] = QString(QChar(0x0641)); // ف (Fa)
    latinToArabic["G"] = QString(QChar(0x062C)); // ج (Jim) - 埃及方言中发/g/
    latinToArabic["H"] = QString(QChar(0x0647)); // ه (Ha)
    latinToArabic["I"] = QString(QChar(0x064A)); // ي (Ya) - 作为元音i
    latinToArabic["J"] = QString(QChar(0x062C)); // ج (Jim)
    latinToArabic["K"] = QString(QChar(0x0643)); // ك (Kaf)
    latinToArabic["L"] = QString(QChar(0x0644)); // ل (Lam)
    latinToArabic["M"] = QString(QChar(0x0645)); // م (Mim)
    latinToArabic["N"] = QString(QChar(0x0646)); // ن (Nun)
    latinToArabic["O"] = QString(QChar(0x0648)); // و (Waw) - 作为元音o
    latinToArabic["P"] = QString(QChar(0x0628)); // ب (Ba) - 阿拉伯语无/p/，用ب加三点ﭖ在某些方言中
    latinToArabic["Q"] = QString(QChar(0x0642)); // ق (Qaf)
    latinToArabic["R"] = QString(QChar(0x0631)); // ر (Ra)
    latinToArabic["S"] = QString(QChar(0x0633)); // س (Sin)
    latinToArabic["T"] = QString(QChar(0x062A)); // ت (Ta)
    latinToArabic["U"] = QString(QChar(0x0648)); // و (Waw) - 作为元音u
    latinToArabic["V"] = QString(QChar(0x0641)); // ف (Fa) - 阿拉伯语无/v/
    latinToArabic["W"] = QString(QChar(0x0648)); // و (Waw)
    latinToArabic["X"] = QString(QChar(0x0643)) + QString(QChar(0x0633)); // كس
    latinToArabic["Y"] = QString(QChar(0x064A)); // ي (Ya)
    latinToArabic["Z"] = QString(QChar(0x0632)); // ز (Zay)
    // 重要双字母组合 - 优化优先级和准确性
    latinToArabic["SH"] = QString(QChar(0x0634)); // ش (Shin)
    latinToArabic["CH"] = QString(QChar(0x0634)); // ش (Shin) - /tʃ/近似ش
    latinToArabic["TH"] = QString(QChar(0x062B)); // ث (Tha) - 清音/θ/
    latinToArabic["DH"] = QString(QChar(0x0630)); // ذ (Dhal) - 浊音/ð/
    latinToArabic["KH"] = QString(QChar(0x062E)); // خ (Kha)
    latinToArabic["GH"] = QString(QChar(0x063A)); // غ (Ghayn)
    latinToArabic["AA"] = QString(QChar(0x0622)); // آ (Alif with madda) - 长音A

    // 英语常见辅音组合优化
    latinToArabic["PH"] = QString(QChar(0x0641)); // ف (Fa) - ph = f
    latinToArabic["QU"] = QString(QChar(0x0643)) + QString(QChar(0x0648)); // كو
    latinToArabic["WH"] = QString(QChar(0x0648)) + QString(QChar(0x0647)); // وه

    // 德语特殊字符优化
    latinToArabic["Ä"] = QString(QChar(0x0627)) + QString(QChar(0x064E)); // اَ
    latinToArabic["Ö"] = QString(QChar(0x0648)) + QString(QChar(0x064E)); // وَ
    latinToArabic["Ü"] = QString(QChar(0x0648)) + QString(QChar(0x0652)); // وْ
    latinToArabic["ß"] = QString(QChar(0x0633)); // س

    // 法语特殊字符优化
    latinToArabic["É"] = QString(QChar(0x064A)) + QString(QChar(0x064E)); // يَ
    latinToArabic["È"] = QString(QChar(0x064A)) + QString(QChar(0x064F)); // يُ
    latinToArabic["Ê"] = QString(QChar(0x064A)) + QString(QChar(0x0304)); // ي̄
    latinToArabic["Ç"] = QString(QChar(0x0633)); // س

    // 汉语拼音优化 - 重点处理声母和韵母
    // 声母
    latinToArabic["ZH"] = QString(QChar(0x062C)) + QString(QChar(0x0651)); // جّ (强调的Jim)
    latinToArabic["CH"] = QString(QChar(0x062A)) + QString(QChar(0x0634)); // تش (组合表示ch)
    latinToArabic["SH"] = QString(QChar(0x0634)); // ش

    // 韵母优化
    latinToArabic["ANG"] = QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x063A)); // انغ
    latinToArabic["ENG"] = QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x063A)); // انغ
    latinToArabic["ING"] = QString(QChar(0x064A)) + QString(QChar(0x0646)) + QString(QChar(0x063A)); // ينغ
    latinToArabic["ONG"] = QString(QChar(0x0648)) + QString(QChar(0x0646)) + QString(QChar(0x063A)); // ونغ

    // 英语后缀优化
    latinToArabic["TION"] = QString(QChar(0x0634)) + QString(QChar(0x0646)); // شن (更准确表示/ʃən/)
    latinToArabic["SION"] = QString(QChar(0x062C)) + QString(QChar(0x0646)); // جن (表示/ʒən/)
    latinToArabic["MENT"] = QString(QChar(0x0645)) + QString(QChar(0x0646)) + QString(QChar(0x062A)); // منت



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
    latinToPersian["GH"] = QString(QChar(0x063A)); // غ
    latinToPersian["KH"] = QString(QChar(0x062E)); // خ

    // 第一声（阴平）
    latinToPersian["Ā"] = QString(QChar(0x0627)); // ا (长音表示)
    latinToPersian["Ē"] = QString(QChar(0x06CC)); // ی
    latinToPersian["Ī"] = QString(QChar(0x06CC)); // ی
    latinToPersian["Ō"] = QString(QChar(0x0648)); // و
    latinToPersian["Ū"] = QString(QChar(0x0648)); // و
    latinToPersian["Ǖ"] = QString(QChar(0x06CC)) + QString(QChar(0x0648)); // یو (ü)

    // 第二声（阳平）
    latinToPersian["Á"] = QString(QChar(0x0627)); // ا
    latinToPersian["É"] = QString(QChar(0x06CC)); // ی
    latinToPersian["Í"] = QString(QChar(0x06CC)); // ی
    latinToPersian["Ó"] = QString(QChar(0x0648)); // و
    latinToPersian["Ú"] = QString(QChar(0x0648)); // و
    latinToPersian["Ǘ"] = QString(QChar(0x06CC)) + QString(QChar(0x0648)); // یو (ü)

    // 第三声（上声）
    latinToPersian["Ǎ"] = QString(QChar(0x0627)); // ا
    latinToPersian["Ě"] = QString(QChar(0x06CC)); // ی
    latinToPersian["Ǐ"] = QString(QChar(0x06CC)); // ی
    latinToPersian["Ǒ"] = QString(QChar(0x0648)); // و
    latinToPersian["Ǔ"] = QString(QChar(0x0648)); // و
    latinToPersian["Ǚ"] = QString(QChar(0x06CC)) + QString(QChar(0x0648)); // یو (ü)

    // 第四声（去声）
    latinToPersian["À"] = QString(QChar(0x0627)); // ا
    latinToPersian["È"] = QString(QChar(0x06CC)); // ی
    latinToPersian["Ì"] = QString(QChar(0x06CC)); // ی
    latinToPersian["Ò"] = QString(QChar(0x0648)); // و
    latinToPersian["Ù"] = QString(QChar(0x0648)); //和
    latinToPersian["Ǜ"] = QString(QChar(0x06CC)) + QString(QChar(0x0648)); // یو (ü)

    // ================= 新增多音节映射 =================
    // 英语常见辅音组合
    latinToPersian["TH"] = QString(QChar(0x062B)); // ث (英语 th)
    latinToPersian["PH"] = QString(QChar(0x0641)); // ف (英语 ph)
    latinToPersian["QU"] = QString(QChar(0x0642)) + QString(QChar(0x0648)); // قو (英语 qu)
    latinToPersian["NG"] = QString(QChar(0x0646)) + QString(QChar(0x06AF)); // نگ (英语 ng)
    latinToPersian["TR"] = QString(QChar(0x062A)) + QString(QChar(0x0631)); // تر (英语 tr)
    latinToPersian["DR"] = QString(QChar(0x062F)) + QString(QChar(0x0631)); // در (英语 dr)
    latinToPersian["BR"] = QString(QChar(0x0628)) + QString(QChar(0x0631)); // بر (英语 br)
    latinToPersian["CR"] = QString(QChar(0x0643)) + QString(QChar(0x0631)); // کر (英语 cr)
    latinToPersian["FR"] = QString(QChar(0x0641)) + QString(QChar(0x0631)); // فر (英语 fr)
    latinToPersian["GR"] = QString(QChar(0x06AF)) + QString(QChar(0x0631)); // گر (英语 gr)
    latinToPersian["PR"] = QString(QChar(0x067E)) + QString(QChar(0x0631)); // پر (英语 pr)
    latinToPersian["ST"] = QString(QChar(0x0633)) + QString(QChar(0x062A)); // ست (英语 st)
    latinToPersian["SP"] = QString(QChar(0x0633)) + QString(QChar(0x067E)); // سپ (英语 sp)
    latinToPersian["SK"] = QString(QChar(0x0633)) + QString(QChar(0x0643)); // سک (英语 sk)
    latinToPersian["SL"] = QString(QChar(0x0633)) + QString(QChar(0x0644)); // سل (英语 sl)
    latinToPersian["SM"] = QString(QChar(0x0633)) + QString(QChar(0x0645)); // سم (英语 sm)
    latinToPersian["SN"] = QString(QChar(0x0633)) + QString(QChar(0x0646)); // سن (英语 sn)
    latinToPersian["SW"] = QString(QChar(0x0633)) + QString(QChar(0x0648)); // سو (英语 sw)
    latinToPersian["TW"] = QString(QChar(0x062A)) + QString(QChar(0x0648)); // تو (英语 tw)
    latinToPersian["WH"] = QString(QChar(0x0648)) + QString(QChar(0x0647)); // وه (英语 wh)

    // 英语常见元音组合
    latinToPersian["AI"] = QString(QChar(0x0627)) + QString(QChar(0x06CC)); // ای (英语 ai)
    latinToPersian["AY"] = QString(QChar(0x0627)) + QString(QChar(0x06CC)); // ای (英语 ay)
    latinToPersian["EA"] = QString(QChar(0x06CC)) + QString(QChar(0x0627)); // یا (英语 ea)
    latinToPersian["EE"] = QString(QChar(0x06CC)); // ی (英语 ee)
    latinToPersian["EI"] = QString(QChar(0x0627)) + QString(QChar(0x06CC)); // ای (英语 ei)
    latinToPersian["EY"] = QString(QChar(0x0627)) + QString(QChar(0x06CC)); // ای (英语 ey)
    latinToPersian["IE"] = QString(QChar(0x0627)) + QString(QChar(0x06CC)); // ای (英语 ie)
    latinToPersian["OA"] = QString(QChar(0x0648)) + QString(QChar(0x0627)); // وا (英语 oa)
    latinToPersian["OE"] = QString(QChar(0x0648)) + QString(QChar(0x06CC)); // وی (英语 oe)
    latinToPersian["OI"] = QString(QChar(0x0648)) + QString(QChar(0x06CC)); // وی (英语 oi)
    latinToPersian["OO"] = QString(QChar(0x0648)); // و (英语 oo)
    latinToPersian["OU"] = QString(QChar(0x0627)) + QString(QChar(0x0648)); // او (英语 ou)
    latinToPersian["OW"] = QString(QChar(0x0627)) + QString(QChar(0x0648)); // او (英语 ow)
    latinToPersian["UE"] = QString(QChar(0x0648)); // و (英语 ue)
    latinToPersian["UI"] = QString(QChar(0x0648)) + QString(QChar(0x06CC)); // وی (英语 ui)
    latinToPersian["UY"] = QString(QChar(0x0648)) + QString(QChar(0x06CC)); // وی (英语 uy)

    // 汉语拼音特有组合
    latinToPersian["AN"] = QString(QChar(0x0627)) + QString(QChar(0x0646)); // ان (拼音 an)
    latinToPersian["EN"] = QString(QChar(0x0627)) + QString(QChar(0x0646)); // ان (拼音 en)
    latinToPersian["IN"] = QString(QChar(0x06CC)) + QString(QChar(0x0646)); // ین (拼音 in)
    latinToPersian["UN"] = QString(QChar(0x0648)) + QString(QChar(0x0646)); // ون (拼音 un)
    latinToPersian["ANG"] = QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // انگ (拼音 ang)
    latinToPersian["ENG"] = QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // انگ (拼音 eng)
    latinToPersian["ING"] = QString(QChar(0x06CC)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // ینگ (拼音 ing)
    latinToPersian["ONG"] = QString(QChar(0x0648)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // ونگ (拼音 ong)
    latinToPersian["ER"] = QString(QChar(0x0627)) + QString(QChar(0x0631)); // ار (拼音 er)
    latinToPersian["IA"] = QString(QChar(0x06CC)) + QString(QChar(0x0627)); // یا (拼音 ia)
    latinToPersian["IAN"] = QString(QChar(0x06CC)) + QString(QChar(0x0627)) + QString(QChar(0x0646)); // یان (拼音 ian)
    latinToPersian["IANG"] = QString(QChar(0x06CC)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // یانگ (拼音 iang)
    latinToPersian["IAO"] = QString(QChar(0x06CC)) + QString(QChar(0x0627)) + QString(QChar(0x0648)); // یاو (拼音 iao)
    latinToPersian["IE"] = QString(QChar(0x06CC)) + QString(QChar(0x0627)); // یا (拼音 ie)
    latinToPersian["IONG"] = QString(QChar(0x06CC)) + QString(QChar(0x0648)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // یونگ (拼音 iong)
    latinToPersian["IU"] = QString(QChar(0x06CC)) + QString(QChar(0x0648)); // یو (拼音 iu)
    latinToPersian["UA"] = QString(QChar(0x0648)) + QString(QChar(0x0627)); // وا (拼音 ua)
    latinToPersian["UAI"] = QString(QChar(0x0648)) + QString(QChar(0x0627)) + QString(QChar(0x06CC)); // وای (拼音 uai)
    latinToPersian["UAN"] = QString(QChar(0x0648)) + QString(QChar(0x0627)) + QString(QChar(0x0646)); // وان (拼音 uan)
    latinToPersian["UANG"] = QString(QChar(0x0648)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // وانگ (拼音 uang)
    latinToPersian["UE"] = QString(QChar(0x0648)) + QString(QChar(0x0627)); // وا (拼音 ue)
    latinToPersian["UI"] = QString(QChar(0x0648)) + QString(QChar(0x06CC)); // وی (拼音 ui)
    latinToPersian["UO"] = QString(QChar(0x0648)) + QString(QChar(0x0648)); // وو (拼音 uo)
    latinToPersian["Ü"] = QString(QChar(0x06CC)) + QString(QChar(0x0648)); // یو (拼音 ü)
    latinToPersian["ÜE"] = QString(QChar(0x06CC)) + QString(QChar(0x0648)) + QString(QChar(0x0627)); // یوا (拼音 üe)

    // 汉语拼音声母组合
    latinToPersian["ZH"] = QString(QChar(0x0698)); // ژ (拼音 zh)
    latinToPersian["CH"] = QString(QChar(0x0686)); // چ (拼音 ch)
    latinToPersian["SH"] = QString(QChar(0x0634)); // ش (拼音 sh)
    latinToPersian["ZHI"] = QString(QChar(0x0698)); // ژ (拼音 zhi)
    latinToPersian["CHI"] = QString(QChar(0x0686)); // چ (拼音 chi)
    latinToPersian["SHI"] = QString(QChar(0x0634)); // ش (拼音 shi)
    latinToPersian["RI"] = QString(QChar(0x0631)); // ر (拼音 ri)
    latinToPersian["ZI"] = QString(QChar(0x0632)); // ز (拼音 zi)
    latinToPersian["CI"] = QString(QChar(0x062A)) + QString(QChar(0x0633)); // تس (拼音 ci，更准确)
    latinToPersian["SI"] = QString(QChar(0x0633)); // س (拼音 si)

    // 三音节组合
    latinToPersian["SCH"] = QString(QChar(0x0634)); // ش (德语 sch)
    latinToPersian["STR"] = QString(QChar(0x0633)) + QString(QChar(0x062A)) + QString(QChar(0x0631)); // ستر (英语 str)
    latinToPersian["SPR"] = QString(QChar(0x0633)) + QString(QChar(0x067E)) + QString(QChar(0x0631)); // سپر (英语 spr)
    latinToPersian["THR"] = QString(QChar(0x062B)) + QString(QChar(0x0631)); // ثر (英语 thr)
    latinToPersian["SHR"] = QString(QChar(0x0634)) + QString(QChar(0x0631)); // شر (英语 shr)
    latinToPersian["CHR"] = QString(QChar(0x0686)) + QString(QChar(0x0631)); // چر (英语 chr)
    latinToPersian["PHL"] = QString(QChar(0x0641)) + QString(QChar(0x0644)); // فل (英语 phl)
    latinToPersian["PSY"] = QString(QChar(0x0633)) + QString(QChar(0x06CC)); // سی (英语 psy)


    latinToPersian["STRA"] = QString(QChar(0x0633)) + QString(QChar(0x062A)) + QString(QChar(0x0631)) + QString(QChar(0x0627)); // سترا (英语 stra)
    latinToPersian["STRE"] = QString(QChar(0x0633)) + QString(QChar(0x062A)) + QString(QChar(0x0631)) + QString(QChar(0x06CC)); // ستری (英语 stre)
    latinToPersian["STRI"] = QString(QChar(0x0633)) + QString(QChar(0x062A)) + QString(QChar(0x0631)) + QString(QChar(0x06CC)); // ستری (英语 stri)
    latinToPersian["STRO"] = QString(QChar(0x0633)) + QString(QChar(0x062A)) + QString(QChar(0x0631)) + QString(QChar(0x0648)); // سترو (英语 stro)
    latinToPersian["STRU"] = QString(QChar(0x0633)) + QString(QChar(0x062A)) + QString(QChar(0x0631)) + QString(QChar(0x0648)); // سترو (英语 stru)
    latinToPersian["SPRA"] = QString(QChar(0x0633)) + QString(QChar(0x067E)) + QString(QChar(0x0631)) + QString(QChar(0x0627)); // سپرا (英语 spra)
    latinToPersian["SPRE"] = QString(QChar(0x0633)) + QString(QChar(0x067E)) + QString(QChar(0x0631)) + QString(QChar(0x06CC)); // سپری (英语 spre)
    latinToPersian["SPRI"] = QString(QChar(0x0633)) + QString(QChar(0x067E)) + QString(QChar(0x0631)) + QString(QChar(0x06CC)); // سپری (英语 spri)
    latinToPersian["SPRO"] = QString(QChar(0x0633)) + QString(QChar(0x067E)) + QString(QChar(0x0631)) + QString(QChar(0x0648)); // سپرو (英语 spro)
    latinToPersian["SPRU"] = QString(QChar(0x0633)) + QString(QChar(0x067E)) + QString(QChar(0x0631)) + QString(QChar(0x0648)); // سپرو (英语 spru)
    latinToPersian["THRA"] = QString(QChar(0x062B)) + QString(QChar(0x0631)) + QString(QChar(0x0627)); // ثرا (英语 thra)
    latinToPersian["THRE"] = QString(QChar(0x062B)) + QString(QChar(0x0631)) + QString(QChar(0x06CC)); // ثری (英语 thre)
    latinToPersian["THRI"] = QString(QChar(0x062B)) + QString(QChar(0x0631)) + QString(QChar(0x06CC)); // ثری (英语 thri)
    latinToPersian["THRO"] = QString(QChar(0x062B)) + QString(QChar(0x0631)) + QString(QChar(0x0648)); // ثرو (英语 thro)
    latinToPersian["THRU"] = QString(QChar(0x062B)) + QString(QChar(0x0631)) + QString(QChar(0x0648)); // ثرو (英语 thru)
    latinToPersian["SHRA"] = QString(QChar(0x0634)) + QString(QChar(0x0631)) + QString(QChar(0x0627)); // شرا (英语 shra)
    latinToPersian["SHRE"] = QString(QChar(0x0634)) + QString(QChar(0x0631)) + QString(QChar(0x06CC)); // شری (英语 shre)
    latinToPersian["SHRI"] = QString(QChar(0x0634)) + QString(QChar(0x0631)) + QString(QChar(0x06CC)); // شری (英语 shri)
    latinToPersian["SHRO"] = QString(QChar(0x0634)) + QString(QChar(0x0631)) + QString(QChar(0x0648)); // شرو (英语 shro)
    latinToPersian["SHRU"] = QString(QChar(0x0634)) + QString(QChar(0x0631)) + QString(QChar(0x0648)); // شرو (英语 shru)
    latinToPersian["CHRA"] = QString(QChar(0x0686)) + QString(QChar(0x0631)) + QString(QChar(0x0627)); // چرا (英语 chra)
    latinToPersian["CHRE"] = QString(QChar(0x0686)) + QString(QChar(0x0631)) + QString(QChar(0x06CC)); // چری (英语 chre)
    latinToPersian["CHRI"] = QString(QChar(0x0686)) + QString(QChar(0x0631)) + QString(QChar(0x06CC)); // چری (英语 chri)
    latinToPersian["CHRO"] = QString(QChar(0x0686)) + QString(QChar(0x0631)) + QString(QChar(0x0648)); // چرو (英语 chro)
    latinToPersian["CHRU"] = QString(QChar(0x0686)) + QString(QChar(0x0631)) + QString(QChar(0x0648)); // چرو (英语 chru)

    latinToPersian["ZHANG"] = QString(QChar(0x0698)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // ژانگ (拼音 zhang)
    latinToPersian["CHANG"] = QString(QChar(0x0686)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // چانگ (拼音 chang)
    latinToPersian["SHANG"] = QString(QChar(0x0634)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // شانگ (拼音 shang)
    latinToPersian["RANG"] = QString(QChar(0x0631)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // رانگ (拼音 rang)
    latinToPersian["ZANG"] = QString(QChar(0x0632)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // زانگ (拼音 zang)
    latinToPersian["CANG"] = QString(QChar(0x0633)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // سانگ (拼音 cang)
    latinToPersian["SANG"] = QString(QChar(0x0633)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // سانگ (拼音 sang)
    latinToPersian["BANG"] = QString(QChar(0x0628)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // بانگ (拼音 bang)
    latinToPersian["PANG"] = QString(QChar(0x067E)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // پانگ (拼音 pang)
    latinToPersian["MANG"] = QString(QChar(0x0645)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // مانگ (拼音 mang)
    latinToPersian["FANG"] = QString(QChar(0x0641)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // فانگ (拼音 fang)
    latinToPersian["DANG"] = QString(QChar(0x062F)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // دانگ (拼音 dang)
    latinToPersian["TANG"] = QString(QChar(0x062A)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // تانگ (拼音 tang)
    latinToPersian["NANG"] = QString(QChar(0x0646)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // نانگ (拼音 nang)
    latinToPersian["LANG"] = QString(QChar(0x0644)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // لانگ (拼音 lang)
    latinToPersian["GANG"] = QString(QChar(0x06AF)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // گانگ (拼音 gang)
    latinToPersian["KANG"] = QString(QChar(0x0643)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // کانگ (拼音 kang)
    latinToPersian["HANG"] = QString(QChar(0x0647)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // هانگ (拼音 hang)
    latinToPersian["JANG"] = QString(QChar(0x062C)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // جانگ (拼音 jang)
    latinToPersian["QANG"] = QString(QChar(0x0642)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // قانگ (拼音 qang)
    latinToPersian["XANG"] = QString(QChar(0x062E)) + QString(QChar(0x0627)) + QString(QChar(0x0646)) + QString(QChar(0x06AF)); // خانگ (拼音 xang)




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

    // 撒玛利亚字母映射
     latinToSamaritan["SH"] = QString(QChar(0x0812)); // ࠒ
     latinToSamaritan["A"] = QString(QChar(0x0800)); // ࠀ
     latinToSamaritan["B"] = QString(QChar(0x0801)); // ࠁ
     latinToSamaritan["C"] = QString(QChar(0x0818)); // ࠘ (使用CH的映射)
     latinToSamaritan["D"] = QString(QChar(0x0803)); // ࠃ
     latinToSamaritan["E"] = QString(QChar(0x080E)); // ࠎ
     latinToSamaritan["F"] = QString(QChar(0x0815)); // ࠕ
     latinToSamaritan["G"] = QString(QChar(0x0802)); // ࠂ
     latinToSamaritan["H"] = QString(QChar(0x0804)); // ࠄ
     latinToSamaritan["I"] = QString(QChar(0x0819)); // ࠙
     latinToSamaritan["J"] = QString(QChar(0x0807)); // ࠇ
     latinToSamaritan["K"] = QString(QChar(0x0809)); // ࠉ
     latinToSamaritan["L"] = QString(QChar(0x080A)); // ࠊ
     latinToSamaritan["M"] = QString(QChar(0x080B)); // ࠋ
     latinToSamaritan["N"] = QString(QChar(0x080C)); // ࠌ
     latinToSamaritan["O"] = QString(QChar(0x0816)); // ࠖ
     latinToSamaritan["P"] = QString(QChar(0x080F)); // ࠏ
     latinToSamaritan["Q"] = QString(QChar(0x0810)); // ࠐ
     latinToSamaritan["R"] = QString(QChar(0x0811)); // ࠑ
     latinToSamaritan["S"] = QString(QChar(0x080D)); // ࠍ
     latinToSamaritan["T"] = QString(QChar(0x0813)); // ࠓ
     latinToSamaritan["U"] = QString(QChar(0x0817)); // ࠗ
     latinToSamaritan["V"] = QString(QChar(0x0814)); // ࠔ
     latinToSamaritan["W"] = QString(QChar(0x0805)); // ࠅ
     latinToSamaritan["X"] = QString(QChar(0x081F)); // ࠟ (使用ZH的映射)
     latinToSamaritan["Y"] = QString(QChar(0x0808)); // ࠈ
     latinToSamaritan["Z"] = QString(QChar(0x0806)); // ࠆ
     latinToSamaritan["CH"] = QString(QChar(0x0818)); // ࠘
     latinToSamaritan["TS"] = QString(QChar(0x081A)); // ࠚ
     latinToSamaritan["TH"] = QString(QChar(0x081B)); // ࠛ
     latinToSamaritan["DH"] = QString(QChar(0x081C)); // ࠜ
     latinToSamaritan["BH"] = QString(QChar(0x081D)); // ࠝ
     latinToSamaritan["KH"] = QString(QChar(0x081E)); // ࠞ
     latinToSamaritan["ZH"] = QString(QChar(0x081F)); // ࠟ
     latinToSamaritan["GH"] = QString(QChar(0x0820)); // ࠠ
     latinToSamaritan["TSH"] = QString(QChar(0x0821)); // ࠡ
     latinToSamaritan["DZH"] = QString(QChar(0x0822)); // ࠢ
     latinToSamaritan["FV"] = QString(QChar(0x0823)); // ࠣ
     latinToSamaritan["AY"] = QString(QChar(0x0824)); // ࠤ
     latinToSamaritan["EY"] = QString(QChar(0x0825)); // ࠥ
     latinToSamaritan["AO"] = QString(QChar(0x0826)); // ࠦ
     latinToSamaritan["OY"] = QString(QChar(0x0827)); // ࠧ
     latinToSamaritan["IY"] = QString(QChar(0x0828)); // ࠨ
     latinToSamaritan["UW"] = QString(QChar(0x0829)); // ࠩ
     latinToSamaritan["BW"] = QString(QChar(0x082A)); // ࠪ
     latinToSamaritan["GW"] = QString(QChar(0x082B)); // ࠫ
     latinToSamaritan["HW"] = QString(QChar(0x082C)); // ࠬ
     latinToSamaritan["ZW"] = QString(QChar(0x082D)); // ࠭
     latinToSamaritan["LW"] = QString(QChar(0x082E)); // ࠮
     latinToSamaritan["MW"] = QString(QChar(0x082F)); // ࠯
     latinToSamaritan["NW"] = QString(QChar(0x0830)); // ࠰
     latinToSamaritan["SW"] = QString(QChar(0x0831)); // ࠱
     latinToSamaritan["PW"] = QString(QChar(0x0832)); // ࠲
     latinToSamaritan["RW"] = QString(QChar(0x0833)); // ࠳
     latinToSamaritan["SHW"] = QString(QChar(0x0834)); // ࠴
     latinToSamaritan["TW"] = QString(QChar(0x0835)); // ࠵
     latinToSamaritan["VW"] = QString(QChar(0x0836)); // ࠶
     latinToSamaritan["FW"] = QString(QChar(0x0837)); // ࠷
     latinToSamaritan["OW"] = QString(QChar(0x0838)); // ࠸
     latinToSamaritan["UW"] = QString(QChar(0x0839)); // ࠹
     latinToSamaritan["CHW"] = QString(QChar(0x083A)); // ࠺
     latinToSamaritan["IW"] = QString(QChar(0x083B)); // ࠻
     latinToSamaritan["TSW"] = QString(QChar(0x083C)); // ࠼
     latinToSamaritan["THW"] = QString(QChar(0x083D)); // ࠽
     latinToSamaritan["DHW"] = QString(QChar(0x083E)); // ࠾
     latinToSamaritan["BHW"] = QString(QChar(0x083F)); // ࠿


    //--------------------------------------------------
    // 库尔德文字母映射（基于拉丁字母转写）
    //--------------------------------------------------
    latinToKurdish["A"] = QString(QChar(0x0627)); // ا
    latinToKurdish["B"] = QString(QChar(0x0628)); // ب
    latinToKurdish["C"] = QString(QChar(0x0686)); // چ
    latinToKurdish["D"] = QString(QChar(0x062F)); // د
    latinToKurdish["E"] = QString(QChar(0x06D5)); // ە
    latinToKurdish["F"] = QString(QChar(0x0641)); // ف
    latinToKurdish["G"] = QString(QChar(0x06AF)); // گ
    latinToKurdish["H"] = QString(QChar(0x0647)); // ه
    latinToKurdish["I"] = QString(QChar(0x064A)); // ی
    latinToKurdish["J"] = QString(QChar(0x0698)); // ژ
    latinToKurdish["K"] = QString(QChar(0x0643)); // ک
    latinToKurdish["L"] = QString(QChar(0x0644)); // ل
    latinToKurdish["M"] = QString(QChar(0x0645)); // م
    latinToKurdish["N"] = QString(QChar(0x0646)); // ن
    latinToKurdish["O"] = QString(QChar(0x0648)); // و
    latinToKurdish["P"] = QString(QChar(0x067E)); // پ
    latinToKurdish["Q"] = QString(QChar(0x0642)); // ق
    latinToKurdish["R"] = QString(QChar(0x0631)); // ر
    latinToKurdish["S"] = QString(QChar(0x0633)); // س
    latinToKurdish["T"] = QString(QChar(0x062A)); // ت
    latinToKurdish["U"] = QString(QChar(0x0648)); // و
    latinToKurdish["V"] = QString(QChar(0x06A4)); // ڤ
    latinToKurdish["W"] = QString(QChar(0x0648)); // و
    latinToKurdish["X"] = QString(QChar(0x062E)); // خ
    latinToKurdish["Y"] = QString(QChar(0x064A)); // ی
    latinToKurdish["Z"] = QString(QChar(0x0632)); // ز

    //--------------------------------------------------
    //普什图语映射
    //--------------------------------------------------
    latinToPashto["A"] = QString(QChar(0x0627)); // ا
    latinToPashto["B"] = QString(QChar(0x0628)); // ب
    latinToPashto["C"] = QString(QChar(0x0686)); // چ
    latinToPashto["D"] = QString(QChar(0x062F)); // د
    latinToPashto["E"] = QString(QChar(0x0639)); // ع
    latinToPashto["F"] = QString(QChar(0x0641)); // ف
    latinToPashto["G"] = QString(QChar(0x063A)); // غ
    latinToPashto["H"] = QString(QChar(0x062D)); // ح
    latinToPashto["I"] = QString(QChar(0x064A)); // ی
    latinToPashto["J"] = QString(QChar(0x062C)); // ج
    latinToPashto["K"] = QString(QChar(0x06A9)); // ک
    latinToPashto["L"] = QString(QChar(0x0644)); // ل
    latinToPashto["M"] = QString(QChar(0x0645)); // م
    latinToPashto["N"] = QString(QChar(0x0646)); // ن
    latinToPashto["O"] = QString(QChar(0x0648)); // و
    latinToPashto["P"] = QString(QChar(0x067E)); // پ
    latinToPashto["Q"] = QString(QChar(0x0642)); // ق
    latinToPashto["R"] = QString(QChar(0x0631)); // ر
    latinToPashto["S"] = QString(QChar(0x0633)); // س
    latinToPashto["T"] = QString(QChar(0x062A)); // ت
    latinToPashto["U"] = QString(QChar(0x0626)); // ئ
    latinToPashto["V"] = QString(QChar(0x06A4)); // ڤ
    latinToPashto["W"] = QString(QChar(0x0648)); // و
    latinToPashto["X"] = QString(QChar(0x062E)); // خ
    latinToPashto["Y"] = QString(QChar(0x06CC)); // ی
    latinToPashto["Z"] = QString(QChar(0x0632)); // ز
    latinToPashto["KH"] = QString(QChar(0x062E)); // خ
    latinToPashto["SH"] = QString(QChar(0x0634)); // ش
    latinToPashto["CH"] = QString(QChar(0x0686)); // چ
    latinToPashto["GH"] = QString(QChar(0x063A)); // غ
    latinToPashto["ZH"] = QString(QChar(0x0698)); // ژ
    latinToPashto["TS"] = QString(QChar(0x0681)); // ځ
    latinToPashto["DZ"] = QString(QChar(0x0682)); // ڂ
    latinToPashto["NG"] = QString(QChar(0x06BC)); // ڼ
    latinToPashto["AI"] = QString(QChar(0x06CC)); // ی
    latinToPashto["AY"] = QString(QChar(0x06CC)); // ی
    latinToPashto["EI"] = QString(QChar(0x06CC)); // ی
    latinToPashto["EY"] = QString(QChar(0x06CC)); // ی
    latinToPashto["OI"] = QString(QChar(0x06CC)); // ی
    latinToPashto["OY"] = QString(QChar(0x06CC)); // ی
    latinToPashto["UI"] = QString(QChar(0x06CC)); // ی
    latinToPashto["UY"] = QString(QChar(0x06CC)); // ی

    // 三音节组合
    latinToPashto["TSH"] = QString(QChar(0x0681)); // ځ
    latinToPashto["DZH"] = QString(QChar(0x0682)); // ڂ
    latinToPashto["NGH"] = QString(QChar(0x06BC)); // ڼ




    // 奥斯曼土耳其文映射表（基于阿拉伯文，但有一些特殊字符）
    latinToOttoman["A"] = QString(QChar(0x0627)); // ا
    latinToOttoman["B"] = QString(QChar(0x0628)); // ب
    latinToOttoman["C"] = QString(QChar(0x062C)); // ج
    latinToOttoman["Ç"] = QString(QChar(0x0686)); // چ
    latinToOttoman["D"] = QString(QChar(0x062F)); // د
    latinToOttoman["E"] = QString(QChar(0x0627)); // ا（近似）
    latinToOttoman["F"] = QString(QChar(0x0641)); // ف
    latinToOttoman["G"] = QString(QChar(0x063A)); // غ
    latinToOttoman["Ğ"] = QString(QChar(0x063A)); // غ
    latinToOttoman["H"] = QString(QChar(0x062D)); // ح
    latinToOttoman["I"] = QString(QChar(0x064A)); // ي
    latinToOttoman["İ"] = QString(QChar(0x064A)); // ي
    latinToOttoman["J"] = QString(QChar(0x0698)); // ژ
    latinToOttoman["K"] = QString(QChar(0x0643)); // ك
    latinToOttoman["L"] = QString(QChar(0x0644)); // ل
    latinToOttoman["M"] = QString(QChar(0x0645)); // م
    latinToOttoman["N"] = QString(QChar(0x0646)); // ن
    latinToOttoman["O"] = QString(QChar(0x0648)); // و
    latinToOttoman["Ö"] = QString(QChar(0x0648)); // و（近似）
    latinToOttoman["P"] = QString(QChar(0x067E)); // پ
    latinToOttoman["Q"] = QString(QChar(0x0642)); // ق
    latinToOttoman["R"] = QString(QChar(0x0631)); // ر
    latinToOttoman["S"] = QString(QChar(0x0633)); // س
    latinToOttoman["Ş"] = QString(QChar(0x0634)); // ش
    latinToOttoman["T"] = QString(QChar(0x062A)); // ت
    latinToOttoman["U"] = QString(QChar(0x0648)); // و
    latinToOttoman["Ü"] = QString(QChar(0x0648)); // و（近似）
    latinToOttoman["V"] = QString(QChar(0x0648)); // و（近似）
    latinToOttoman["W"] = QString(QChar(0x0648)); // و
    latinToOttoman["X"] = QString(QChar(0x062E)); // خ
    latinToOttoman["Y"] = QString(QChar(0x064A)); // ي
    latinToOttoman["Z"] = QString(QChar(0x0632)); // ز

    // 双字母组合
    latinToOttoman["CH"] = QString(QChar(0x0686)); // چ
    latinToOttoman["SH"] = QString(QChar(0x0634)); // ش
    latinToOttoman["GH"] = QString(QChar(0x063A)); // غ

    // ---------------------------------------------------------------------------
    // 优化的拉丁字母到吉兹字母 (Ge'ez) 映射 - 基于语音相似性
    // ---------------------------------------------------------------------------

    // 基本单字母映射
    latinToGeez["A"] = QString(QChar(0x12A0)); // አ - 更接近阿姆哈拉语中的喉塞音
    latinToGeez["B"] = QString(QChar(0x1260)); // በ - 浊双唇塞音
    latinToGeez["C"] = QString(QChar(0x1328)); // ጨ - 接近"ts"音
    latinToGeez["D"] = QString(QChar(0x12F0)); // ደ - 浊齿龈塞音
    latinToGeez["E"] = QString(QChar(0x12A4)); // ኤ - 元音e
    latinToGeez["F"] = QString(QChar(0x1348)); // ፈ - 唇齿擦音
    latinToGeez["G"] = QString(QChar(0x1308)); // ገ - 浊软腭塞音
    latinToGeez["H"] = QString(QChar(0x1200)); // ሀ - 声门擦音
    latinToGeez["I"] = QString(QChar(0x12AD)); // ክ - 元音i
    latinToGeez["J"] = QString(QChar(0x130B)); // ጋ - 接近英语j音
    latinToGeez["K"] = QString(QChar(0x12A8)); // ከ - 清软腭塞音
    latinToGeez["L"] = QString(QChar(0x1208)); // ለ - 齿龈边音
    latinToGeez["M"] = QString(QChar(0x1218)); // መ - 双唇鼻音
    latinToGeez["N"] = QString(QChar(0x1290)); // ነ - 齿龈鼻音
    latinToGeez["O"] = QString(QChar(0x12ED)); // ይ - 元音o
    latinToGeez["P"] = QString(QChar(0x1338)); // ጸ - 清双唇塞音
    latinToGeez["Q"] = QString(QChar(0x1240)); // ቀ - 小舌音
    latinToGeez["R"] = QString(QChar(0x1228)); // ሬ - 齿龈颤音
    latinToGeez["S"] = QString(QChar(0x1230)); // ሰ - 清齿龈擦音
    latinToGeez["T"] = QString(QChar(0x1270)); // ተ - 清齿龈塞音
    latinToGeez["U"] = QString(QChar(0x12C0)); // ዀ - 带u元音的基本形式
    latinToGeez["V"] = QString(QChar(0x126C)); // ቬ - 唇齿擦音
    latinToGeez["W"] = QString(QChar(0x12C8)); // ወ - 双唇近音
    latinToGeez["X"] = QString(QChar(0x12E0)); // ዠ - 软腭擦音
    latinToGeez["Y"] = QString(QChar(0x12E8)); // የ - 硬腭近音
    latinToGeez["Z"] = QString(QChar(0x12D8)); // ዘ - 浊齿龈擦音

    // 优化的双字母组合 - 基于实际发音
    latinToGeez["CH"] = QString(QChar(0x1328)); // ጨ - 更接近英语ch音
    latinToGeez["SH"] = QString(QChar(0x1238)); // ሸ - 清后齿龈擦音
    latinToGeez["KH"] = QString(QChar(0x1218)); // መ - 软腭擦音
    latinToGeez["PH"] = QString(QChar(0x1348)); // ፈ - 保持为f音
    latinToGeez["TH"] = QString(QChar(0x1330)); // ጰ - 齿间擦音
    latinToGeez["TS"] = QString(QChar(0x1320)); // ጠ - 齿龈塞擦音
    latinToGeez["DH"] = QString(QChar(0x12F0)); // ደ - 浊齿间擦音近似
    latinToGeez["NY"] = QString(QChar(0x1294)); // ኔ - 硬腭鼻音
    latinToGeez["NG"] = QString(QChar(0x1298)); // ኘ - 软腭鼻音
    latinToGeez["GW"] = QString(QChar(0x130F)); // ጏ - 圆唇软腭塞音

    // 额外的常见组合
    latinToGeez["GY"] = QString(QChar(0x130D)); // ግ - 硬腭化g
    latinToGeez["KY"] = QString(QChar(0x12AE)); // ኮ - 硬腭化k


    // ---------------------------------------------------------------------------
    // 拉丁字母到古突厥文 (Old Turkic, Orkhon runes) - 优化版
    // ---------------------------------------------------------------------------

    // 单字母
    latinToOldTurkic["A"] = QString("𐰀"); // A
    latinToOldTurkic["B"] = QString("𐰉"); // B
    latinToOldTurkic["C"] = QString("𐰲"); // C (Č/CH)
    latinToOldTurkic["D"] = QString("𐰓"); // D
    latinToOldTurkic["E"] = QString("𐰁"); // E
    latinToOldTurkic["F"] = QString("𐰽") + QString("𐰯"); // F ≈ S+P
    latinToOldTurkic["G"] = QString("𐰍"); // G (后元音)
    latinToOldTurkic["H"] = QString("𐰴"); // H ≈ Q
    latinToOldTurkic["I"] = QString("𐰃"); // I (后元音)
    latinToOldTurkic["Ï"] = QString("𐰋"); // Ï (前元音)
    latinToOldTurkic["J"] = QString("𐰶"); // J (Ž)
    latinToOldTurkic["K"] = QString("𐰚"); // K
    latinToOldTurkic["L"] = QString("𐰠"); // L
    latinToOldTurkic["M"] = QString("𐰢"); // M
    latinToOldTurkic["N"] = QString("𐰣"); // N
    latinToOldTurkic["O"] = QString("𐰆"); // O
    latinToOldTurkic["Ö"] = QString("𐰇"); // Ö
    latinToOldTurkic["P"] = QString("𐰯"); // P
    latinToOldTurkic["Q"] = QString("𐰴"); // Q
    latinToOldTurkic["R"] = QString("𐰺"); // R
    latinToOldTurkic["S"] = QString("𐰽"); // S
    latinToOldTurkic["T"] = QString("𐱃"); // T
    latinToOldTurkic["U"] = QString("𐰆"); // U (后元音)
    latinToOldTurkic["Ü"] = QString("𐰊"); // Ü (前元音)
    latinToOldTurkic["V"] = QString("𐰉") + QString("𐰋"); // V ≈ U+Ï
    latinToOldTurkic["W"] = QString("𐰉"); // W ≈ U
    latinToOldTurkic["X"] = QString("𐰚") + QString("𐰽"); // X ≈ K+S
    latinToOldTurkic["Y"] = QString("𐰖"); // Y
    latinToOldTurkic["Z"] = QString("𐰞"); // Z
    latinToOldTurkic["CH"] = QString("𐰲"); // CH
    latinToOldTurkic["SH"] = QString("𐱁"); // SH
    latinToOldTurkic["TH"] = QString("𐱃") + QString("𐰴"); // T+H
    latinToOldTurkic["PH"] = QString("𐰯") + QString("𐰴"); // P+H
    latinToOldTurkic["GH"] = QString("𐰍") + QString("𐰴"); // G+H
    latinToOldTurkic["NG"] = QString("𐰤"); // NG
    latinToOldTurkic["OO"] = QString("𐰆") + QString("𐰆"); // 长 O
    latinToOldTurkic["EE"] = QString("𐰋") + QString("𐰋"); // 长 Ï
    latinToOldTurkic["OU"] = QString("𐰆") + QString("𐰉"); // OU
    latinToOldTurkic["AI"] = QString("𐰀") + QString("𐰖"); // AI
    latinToOldTurkic["EI"] = QString("𐰁") + QString("𐰖"); // EI
    latinToOldTurkic["OI"] = QString("𐰆") + QString("𐰖"); // OI
    latinToOldTurkic["AU"] = QString("𐰀") + QString("𐰉"); // AU
    latinToOldTurkic["ZH"] = QString("𐰶"); // ZH
    latinToOldTurkic["AO"] = QString("𐰀") + QString("𐰆"); // AO
    latinToOldTurkic["UI"] = QString("𐰉") + QString("𐰖"); // UI
    latinToOldTurkic["UE"] = QString("𐰊") + QString("𐰁"); // UE (ÜE)
    latinToOldTurkic["IA"] = QString("𐰋") + QString("𐰀"); // IA
    latinToOldTurkic["IE"] = QString("𐰋") + QString("𐰁"); // IE
    latinToOldTurkic["IO"] = QString("𐰋") + QString("𐰆"); // IO
    latinToOldTurkic["IU"] = QString("𐰋") + QString("𐰉"); // IU
    latinToOldTurkic["EA"] = QString("𐰁") + QString("𐰀"); // EA
    latinToOldTurkic["EO"] = QString("𐰁") + QString("𐰆"); // EO
    latinToOldTurkic["EU"] = QString("𐰁") + QString("𐰉"); // EU
    latinToOldTurkic["ANG"] = QString("𐰀") + QString("𐰤"); // ANG
    latinToOldTurkic["ENG"] = QString("𐰁") + QString("𐰤"); // ENG
    latinToOldTurkic["ONG"] = QString("𐰆") + QString("𐰤"); // ONG
    latinToOldTurkic["ING"] = QString("𐰋") + QString("𐰤"); // ING
    latinToOldTurkic["SCH"] = QString("𐱁") + QString("𐰲"); // SCH
    latinToOldTurkic["TSH"] = QString("𐱃") + QString("𐱁"); // TSH
    latinToOldTurkic["TCH"] = QString("𐱃") + QString("𐰲"); // TCH
    latinToOldTurkic["STR"] = QString("𐰽") + QString("𐱃") + QString("𐰺"); // STR
    latinToOldTurkic["ION"] = QString("𐰋") + QString("𐰆") + QString("𐰣"); // ION
    latinToOldTurkic["TIO"] = QString("𐱃") + QString("𐰋") + QString("𐰆"); // TIO
    latinToOldTurkic["NGE"] = QString("𐰤") + QString("𐰍") + QString("𐰁"); // NGE
    latinToOldTurkic["QUE"] = QString("𐰴") + QString("𐰉") + QString("𐰁"); // QUE
    latinToOldTurkic["GUE"] = QString("𐰍") + QString("𐰉") + QString("𐰁"); // GUE




    // ---------------------------------------------------------------------------
    // 拉丁字母到腓尼基文 (Phoenician)
    // ---------------------------------------------------------------------------
    latinToPhoenician["A"] = QString("𐤀"); // 𐤀
    latinToPhoenician["B"] = QString("𐤁"); // 𐤁
    latinToPhoenician["C"] = QString("𐤂"); // 𐤂
    latinToPhoenician["D"] = QString("𐤃"); // 𐤃
    latinToPhoenician["E"] = QString("𐤄"); // 𐤄
    latinToPhoenician["F"] = QString("𐤅"); // 𐤅
    latinToPhoenician["G"] = QString("𐤆"); // 𐤆
    latinToPhoenician["H"] = QString("𐤇"); // 𐤇
    latinToPhoenician["I"] = QString("𐤉"); // 𐤉
    latinToPhoenician["J"] = QString("𐤉"); // 𐤉 (与I相同)
    latinToPhoenician["K"] = QString("𐤊"); // 𐤊
    latinToPhoenician["L"] = QString("𐤋"); // 𐤋
    latinToPhoenician["M"] = QString("𐤌"); // 𐤌
    latinToPhoenician["N"] = QString("𐤍"); // 𐤍
    latinToPhoenician["O"] = QString("𐤏"); // 𐤏
    latinToPhoenician["P"] = QString("𐤐"); // 𐤐
    latinToPhoenician["Q"] = QString("𐤒"); // 𐤒
    latinToPhoenician["R"] = QString("𐤓"); // 𐤓
    latinToPhoenician["S"] = QString("𐤔"); // 𐤔
    latinToPhoenician["T"] = QString("𐤕"); // 𐤕
    latinToPhoenician["U"] = QString("𐤅"); // 𐤅 (与F相同)
    latinToPhoenician["V"] = QString("𐤅"); // 𐤅 (与F相同)
    latinToPhoenician["W"] = QString("𐤅"); // 𐤅 (与F相同)
    latinToPhoenician["X"] = QString("𐤎"); // 𐤎
    latinToPhoenician["Y"] = QString("𐤉"); // 𐤉 (与I相同)
    latinToPhoenician["Z"] = QString("𐤆"); // 𐤆 (与G相同)


    // 其他多音节/组合映射
    latinToPhoenician["AI"] = QString("𐤀") + QString("𐤉"); // A + I
    latinToPhoenician["AU"] = QString("𐤀") + QString("𐤅"); // A + U
    latinToPhoenician["OI"] = QString("𐤏") + QString("𐤉"); // O + I
    latinToPhoenician["OU"] = QString("𐤏") + QString("𐤅"); // O + U
    latinToPhoenician["EI"] = QString("𐤄") + QString("𐤉"); // E + I
    latinToPhoenician["IU"] = QString("𐤉") + QString("𐤅"); // I + U


    // ---------------------------------------------------------------------------
    // 拉丁字母到传统匈牙利文 (Old Hungarian / Székely Rovás) 映射
    // ---------------------------------------------------------------------------
    latinToTraditionalHungarian["A"]  = QString("𐲀"); // U+10C80
    latinToTraditionalHungarian["B"]  = QString("𐲁"); // U+10C81
    latinToTraditionalHungarian["C"]  = QString("𐲂"); // U+10C82
    latinToTraditionalHungarian["CS"] = QString("𐲃"); // U+10C83
    latinToTraditionalHungarian["D"]  = QString("𐲄"); // U+10C84
    latinToTraditionalHungarian["E"]  = QString("𐲅"); // U+10C85
    latinToTraditionalHungarian["É"]  = QString("𐲆"); // U+10C86
    latinToTraditionalHungarian["F"]  = QString("𐲇"); // U+10C87
    latinToTraditionalHungarian["G"]  = QString("𐲈"); // U+10C88
    latinToTraditionalHungarian["GY"] = QString("𐲉"); // U+10C89
    latinToTraditionalHungarian["H"]  = QString("𐲊"); // U+10C8A
    latinToTraditionalHungarian["I"]  = QString("𐲋"); // U+10C8B
    latinToTraditionalHungarian["Í"]  = QString("𐲌"); // U+10C8C
    latinToTraditionalHungarian["J"]  = QString("𐲍"); // U+10C8D
    latinToTraditionalHungarian["K"]  = QString("𐲎"); // U+10C8E
    latinToTraditionalHungarian["L"]  = QString("𐲏"); // U+10C8F
    latinToTraditionalHungarian["LY"] = QString("𐲐"); // U+10C90
    latinToTraditionalHungarian["M"]  = QString("𐲑"); // U+10C91
    latinToTraditionalHungarian["N"]  = QString("𐲒"); // U+10C92
    latinToTraditionalHungarian["NY"] = QString("𐲓"); // U+10C93
    latinToTraditionalHungarian["O"]  = QString("𐲔"); // U+10C94
    latinToTraditionalHungarian["Ó"]  = QString("𐲕"); // U+10C95
    latinToTraditionalHungarian["Ö"]  = QString("𐲖"); // U+10C96
    latinToTraditionalHungarian["Ő"]  = QString("𐲗"); // U+10C97
    latinToTraditionalHungarian["P"]  = QString("𐲘"); // U+10C98
    latinToTraditionalHungarian["Q"]  = QString("𐲙"); // U+10C99 （Q 并非原始匈牙利字母，用 G+U 代替，保留扩展符号）
    latinToTraditionalHungarian["R"]  = QString("𐲚"); // U+10C9A
    latinToTraditionalHungarian["S"]  = QString("𐲛"); // U+10C9B
    latinToTraditionalHungarian["SZ"] = QString("𐲜"); // U+10C9C
    latinToTraditionalHungarian["T"]  = QString("𐲝"); // U+10C9D
    latinToTraditionalHungarian["TY"] = QString("𐲞"); // U+10C9E
    latinToTraditionalHungarian["U"]  = QString("𐲟"); // U+10C9F
    latinToTraditionalHungarian["Ú"]  = QString("𐲠"); // U+10CA0
    latinToTraditionalHungarian["Ü"]  = QString("𐲡"); // U+10CA1
    latinToTraditionalHungarian["Ű"]  = QString("𐲢"); // U+10CA2
    latinToTraditionalHungarian["V"]  = QString("𐲣"); // U+10CA3
    latinToTraditionalHungarian["W"]  = QString("𐲤"); // U+10CA4 （非原生字母，通常写作 V+V）
    latinToTraditionalHungarian["X"]  = QString("𐲥"); // U+10CA5 （非原生字母，通常写作 K+S）
    latinToTraditionalHungarian["Y"]  = QString("𐲦"); // U+10CA6 （多用于外来词）
    latinToTraditionalHungarian["Z"]  = QString("𐲧"); // U+10CA7
    latinToTraditionalHungarian["ZS"] = QString("𐲨"); // U+10CA8



    // -------------------------
    // 麦罗埃文圣书体 (Meroitic Hieroglyphs)
    // -------------------------
    // 基本元音
    latinToMeroiticHieroglyphs["A"] = QString("𐦀"); // a
    latinToMeroiticHieroglyphs["E"] = QString("𐦁"); // e
    latinToMeroiticHieroglyphs["I"] = QString("𐦂"); // i
    latinToMeroiticHieroglyphs["O"] = QString("𐦃"); // o
    latinToMeroiticHieroglyphs["U"] = QString("𐦄"); // u

    // 基本辅音
    latinToMeroiticHieroglyphs["B"] = QString("𐦅"); // b
    latinToMeroiticHieroglyphs["D"] = QString("𐦆"); // d
    latinToMeroiticHieroglyphs["F"] = QString("𐦇"); // f
    latinToMeroiticHieroglyphs["G"] = QString("𐦈"); // g
    latinToMeroiticHieroglyphs["H"] = QString("𐦉"); // h
    latinToMeroiticHieroglyphs["J"] = QString("𐦊"); // j
    latinToMeroiticHieroglyphs["K"] = QString("𐦋"); // k
    latinToMeroiticHieroglyphs["L"] = QString("𐦌"); // l
    latinToMeroiticHieroglyphs["M"] = QString("𐦍"); // m
    latinToMeroiticHieroglyphs["N"] = QString("𐦎"); // n
    latinToMeroiticHieroglyphs["P"] = QString("𐦏"); // p
    latinToMeroiticHieroglyphs["Q"] = QString("𐦐"); // q
    latinToMeroiticHieroglyphs["R"] = QString("𐦑"); // r
    latinToMeroiticHieroglyphs["S"] = QString("𐦒"); // s
    latinToMeroiticHieroglyphs["T"] = QString("𐦓"); // t
    latinToMeroiticHieroglyphs["V"] = QString("𐦔"); // v
    latinToMeroiticHieroglyphs["W"] = QString("𐦕"); // w
    latinToMeroiticHieroglyphs["Y"] = QString("𐦖"); // y
    latinToMeroiticHieroglyphs["Z"] = QString("𐦗"); // z

    // 常见辅音组合
    latinToMeroiticHieroglyphs["SH"] = QString("𐦘"); // sh
    latinToMeroiticHieroglyphs["KH"] = QString("𐦙"); // kh
    latinToMeroiticHieroglyphs["TH"] = QString("𐦚"); // th
    latinToMeroiticHieroglyphs["NH"] = QString("𐦛"); // nh



    // ---------------------------------------------------------------------------
    // 拉丁字母到粟特文 (Sogdian)
    // ---------------------------------------------------------------------------
    latinToSogdian["A"] = QString("𐼀"); // 𐼀
    latinToSogdian["B"] = QString("𐼁"); // 𐼁
    latinToSogdian["C"] = QString("𐼂"); // 𐼂
    latinToSogdian["D"] = QString("𐼃"); // 𐼃
    latinToSogdian["E"] = QString("𐼄"); // 𐼄
    latinToSogdian["F"] = QString("𐼅"); // 𐼅
    latinToSogdian["G"] = QString("𐼆"); // 𐼆
    latinToSogdian["H"] = QString("𐼇"); // 𐼇
    latinToSogdian["I"] = QString("𐼈"); // 𐼈
    latinToSogdian["J"] = QString("𐼉"); // 𐼉
    latinToSogdian["K"] = QString("𐼊"); // 𐼊
    latinToSogdian["L"] = QString("𐼋"); // 𐼋
    latinToSogdian["M"] = QString("𐼌"); // 𐼌
    latinToSogdian["N"] = QString("𐼍"); // 𐼍
    latinToSogdian["O"] = QString("𐼎"); // 𐼎
    latinToSogdian["P"] = QString("𐼏"); // 𐼏
    latinToSogdian["Q"] = QString("𐼐"); // 𐼐
    latinToSogdian["R"] = QString("𐼑"); // 𐼑
    latinToSogdian["S"] = QString("𐼒"); // 𐼒
    latinToSogdian["T"] = QString("𐼓"); // 𐼓
    latinToSogdian["U"] = QString("𐼔"); // 𐼔
    latinToSogdian["V"] = QString("𐼕"); // 𐼕
    latinToSogdian["W"] = QString("𐼖"); // 𐼖
    latinToSogdian["X"] = QString("𐼗"); // 𐼗
    latinToSogdian["Y"] = QString("𐼘"); // 𐼘
    latinToSogdian["Z"] = QString("𐼙"); // 𐼙
    latinToSogdian["a"] = QString("𐼀"); // 𐼀
    latinToSogdian["b"] = QString("𐼁"); // 𐼁
    latinToSogdian["c"] = QString("𐼂"); // 𐼂
    latinToSogdian["d"] = QString("𐼃"); // 𐼃
    latinToSogdian["e"] = QString("𐼄"); // 𐼄
    latinToSogdian["f"] = QString("𐼅"); // 𐼅
    latinToSogdian["g"] = QString("𐼆"); // 𐼆
    latinToSogdian["h"] = QString("𐼇"); // 𐼇
    latinToSogdian["i"] = QString("𐼈"); // 𐼈
    latinToSogdian["j"] = QString("𐼉"); // 𐼉
    latinToSogdian["k"] = QString("𐼊"); // 𐼊
    latinToSogdian["l"] = QString("𐼋"); // 𐼋
    latinToSogdian["m"] = QString("𐼌"); // 𐼌
    latinToSogdian["n"] = QString("𐼍"); // 𐼍
    latinToSogdian["o"] = QString("𐼎"); // 𐼎
    latinToSogdian["p"] = QString("𐼏"); // 𐼏
    latinToSogdian["q"] = QString("𐼐"); // 𐼐
    latinToSogdian["r"] = QString("𐼑"); // 𐼑
    latinToSogdian["s"] = QString("𐼒"); // 𐼒
    latinToSogdian["t"] = QString("𐼓"); // 𐼓
    latinToSogdian["u"] = QString("𐼔"); // 𐼔
    latinToSogdian["v"] = QString("𐼕"); // 𐼕
    latinToSogdian["w"] = QString("𐼖"); // 𐼖
    latinToSogdian["x"] = QString("𐼗"); // 𐼗
    latinToSogdian["y"] = QString("𐼘"); // 𐼘
    latinToSogdian["z"] = QString("𐼙"); // 𐼙

    // 其他多音节/组合映射
    latinToSogdian["AI"] = QString("𐼀") + QString("𐼘"); // A + Y
    latinToSogdian["AU"] = QString("𐼀") + QString("𐼔"); // A + U
    latinToSogdian["OI"] = QString("𐼎") + QString("𐼘"); // O + Y
    latinToSogdian["OU"] = QString("𐼎") + QString("𐼔"); // O + U
    latinToSogdian["EI"] = QString("𐼄") + QString("𐼘"); // E + Y
    latinToSogdian["IU"] = QString("𐼈") + QString("𐼔"); // I + U













    // -------------------------
    // 拉丁字母到藏文字母映射表（含中英文多音节支持）
    // -------------------------
    // 单字母映射（基础映射）
    latinToTibetan["A"] = QString(QChar(0x0F68)); // ཨ
    latinToTibetan["B"] = QString(QChar(0x0F56)); // པ
    latinToTibetan["C"] = QString(QChar(0x0F45)); // ཅ
    latinToTibetan["D"] = QString(QChar(0x0F51)); // ད
    latinToTibetan["E"] = QString(QChar(0x0F7A)); // ེ
    latinToTibetan["F"] = QString(QChar(0x0F0B)); // ་（音节分隔符）
    latinToTibetan["G"] = QString(QChar(0x0F42)); // ག
    latinToTibetan["H"] = QString(QChar(0x0F67)); // ཧ
    latinToTibetan["I"] = QString(QChar(0x0F72)); // ི
    latinToTibetan["J"] = QString(QChar(0x0F9D)); // ྜ
    latinToTibetan["K"] = QString(QChar(0x0F40)); // ཀ
    latinToTibetan["L"] = QString(QChar(0x0F63)); // ླ
    latinToTibetan["M"] = QString(QChar(0x0F58)); // མ
    latinToTibetan["N"] = QString(QChar(0x0F53)); // ཎ
    latinToTibetan["O"] = QString(QChar(0x0F7C)); // ོ
    latinToTibetan["P"] = QString(QChar(0x0F55)); // ཕ
    latinToTibetan["Q"] = QString(QChar(0x0F6F)); // ཨྲ
    latinToTibetan["R"] = QString(QChar(0x0F62)); // ྲ
    latinToTibetan["S"] = QString(QChar(0x0F66)); // ཤ
    latinToTibetan["T"] = QString(QChar(0x0F4F)); // ཏ
    latinToTibetan["U"] = QString(QChar(0x0F74)); // ུ
    latinToTibetan["V"] = QString(QChar(0x0F5D)); // ཝ
    latinToTibetan["W"] = QString(QChar(0x0F5D)); // ཝ
    latinToTibetan["X"] = QString(QChar(0x0F61)); // ཁ
    latinToTibetan["Y"] = QString(QChar(0x0F71)); // ཱ
    latinToTibetan["Z"] = QString(QChar(0x0F5A)); // ཚ
    // ================= 中文常见音节组合 =================
    // 声母组合（中文拼音声母）
    latinToTibetan["ZH"] = QString(QChar(0x0F5C)); // ཞ (zh)
    latinToTibetan["CH"] = QString(QChar(0x0F46)); // ཆ (ch)
    latinToTibetan["SH"] = QString(QChar(0x0F64)); // ཤ (sh)
    latinToTibetan["QU"] = QString(QChar(0x0F46)) + QString(QChar(0x0F74)); // ཆུ (qu)

    // 韵母组合（中文拼音韵母）
    latinToTibetan["ANG"] = QString(QChar(0x0F68)) + QString(QChar(0x0F44)); // ཨང (ang)
    latinToTibetan["ENG"] = QString(QChar(0x0F7A)) + QString(QChar(0x0F44)); // ེང (eng)
    latinToTibetan["ING"] = QString(QChar(0x0F72)) + QString(QChar(0x0F44)); // ིང (ing)
    latinToTibetan["ONG"] = QString(QChar(0x0F7C)) + QString(QChar(0x0F44)); // ོང (ong)
    latinToTibetan["IAN"] = QString(QChar(0x0F72)) + QString(QChar(0x0F68)) + QString(QChar(0x0F53)); // ིཨན (ian)
    latinToTibetan["UAN"] = QString(QChar(0x0F74)) + QString(QChar(0x0F68)) + QString(QChar(0x0F53)); // ུཨན (uan)
    latinToTibetan["IAO"] = QString(QChar(0x0F72)) + QString(QChar(0x0F68)) + QString(QChar(0x0F7C)); // ིཨོ (iao)
    latinToTibetan["UI"] = QString(QChar(0x0F74)) + QString(QChar(0x0F72)); // ིུ (ui)
    latinToTibetan["IU"] = QString(QChar(0x0F72)) + QString(QChar(0x0F74)); // ིུ (iu)
    latinToTibetan["EI"] = QString(QChar(0x0F7A)) + QString(QChar(0x0F72)); // ེི (ei)
    latinToTibetan["AI"] = QString(QChar(0x0F72)) + QString(QChar(0x0F68)); // ཨི (ai)
    latinToTibetan["AO"] = QString(QChar(0x0F68)) + QString(QChar(0x0F7C)); // ཨོ (ao)
    latinToTibetan["OU"] = QString(QChar(0x0F7C)) + QString(QChar(0x0F74)); // ོུ (ou)
    latinToTibetan["ER"] = QString(QChar(0x0F7A)) + QString(QChar(0x0F62)); // ེར (er)

    // 整体认读音节
    latinToTibetan["ZHI"] = QString(QChar(0x0F5C)); // ཞ (zhi)
    latinToTibetan["CHI"] = QString(QChar(0x0F46)); // ཆ (chi)
    latinToTibetan["SHI"] = QString(QChar(0x0F64)); // ཤ (shi)
    latinToTibetan["RI"] = QString(QChar(0x0F62)); // ར (ri)
    latinToTibetan["ZI"] = QString(QChar(0x0F5B)); // ཛ (zi)
    latinToTibetan["CI"] = QString(QChar(0x0F45)); // ཅ (ci)
    latinToTibetan["SI"] = QString(QChar(0x0F66)); // ཤ (si)
    latinToTibetan["YI"] = QString(QChar(0x0F71)); // ཱ (yi)
    latinToTibetan["WU"] = QString(QChar(0x0F5D)); // ཝ (wu)
    latinToTibetan["YU"] = QString(QChar(0x0F74)); // ུ (yu)
    latinToTibetan["YE"] = QString(QChar(0x0F71)) + QString(QChar(0x0F7A)); // ཱེ (ye)
    latinToTibetan["YUE"] = QString(QChar(0x0F74)) + QString(QChar(0x0F7A)); // ེུ (yue)
    latinToTibetan["YUAN"] = QString(QChar(0x0F74)) + QString(QChar(0x0F68)) + QString(QChar(0x0F53)); // ུཨན (yuan)
    latinToTibetan["YIN"] = QString(QChar(0x0F72)) + QString(QChar(0x0F53)); // ིན (yin)
    latinToTibetan["YUN"] = QString(QChar(0x0F74)) + QString(QChar(0x0F53)); // ུན (yun)
    latinToTibetan["YING"] = QString(QChar(0x0F72)) + QString(QChar(0x0F44)); // ིང (ying)

    // 常见中文姓氏和词汇
    latinToTibetan["ZHANG"] = QString(QChar(0x0F5C)) + QString(QChar(0x0F68)) + QString(QChar(0x0F44)); // ཞང (zhang)
    latinToTibetan["WANG"] = QString(QChar(0x0F5D)) + QString(QChar(0x0F68)) + QString(QChar(0x0F44)); // ཝང (wang)
    latinToTibetan["LI"] = QString(QChar(0x0F63)) + QString(QChar(0x0F72)); // ལི (li)
    latinToTibetan["ZHAO"] = QString(QChar(0x0F5C)) + QString(QChar(0x0F68)) + QString(QChar(0x0F7C)); // ཞོ (zhao)
    latinToTibetan["QIAN"] = QString(QChar(0x0F46)) + QString(QChar(0x0F72)) + QString(QChar(0x0F68)) + QString(QChar(0x0F53)); // ཆིཨན (qian)
    latinToTibetan["SUN"] = QString(QChar(0x0F66)) + QString(QChar(0x0F74)) + QString(QChar(0x0F53)); // ཤུན (sun)
    latinToTibetan["MA"] = QString(QChar(0x0F58)) + QString(QChar(0x0F68)); // མ (ma)
    // ================= 英文常见组合 =================
    // 双字母组合映射
    latinToTibetan["TH"] = QString(QChar(0x0F50)); // ཐ
    latinToTibetan["PH"] = QString(QChar(0x0F55)); // ཕ
    latinToTibetan["GH"] = QString(QChar(0x0F43)); // གྷ
    latinToTibetan["NG"] = QString(QChar(0x0F44)); // ང
    latinToTibetan["NY"] = QString(QChar(0x0F49)); // ཉ
    latinToTibetan["TR"] = QString(QChar(0x0F51)) + QString(QChar(0x0F62)); // དྲ
    latinToTibetan["DR"] = QString(QChar(0x0F52)); // དྲ
    latinToTibetan["TS"] = QString(QChar(0x0F59)); // ཙ
    latinToTibetan["DZ"] = QString(QChar(0x0F5B)); // ཛ
    latinToTibetan["KH"] = QString(QChar(0x0F41)); // ཁ

    // 三字母组合映射
    latinToTibetan["TSH"] = QString(QChar(0x0F5A)); // ཚ
    latinToTibetan["DZH"] = QString(QChar(0x0F5E)); // ཟྷ
    latinToTibetan["NGA"] = QString(QChar(0x0F44)); // ང
    latinToTibetan["TRI"] = QString(QChar(0x0F51)) + QString(QChar(0x0F62)); // དྲི
    latinToTibetan["DRI"] = QString(QChar(0x0F52)) + QString(QChar(0x0F72)); // དྲི

    // 常见英文发音组合
    latinToTibetan["ION"] = QString(QChar(0x0F72)) + QString(QChar(0x0F53)); // ིོན
    latinToTibetan["TION"] = QString(QChar(0x0F4F)) + QString(QChar(0x0F72)) + QString(QChar(0x0F53)); // ཏིོན

    // 元音组合
    latinToTibetan["AU"] = QString(QChar(0x0F74)) + QString(QChar(0x0F68)); // ཨུ

    // ================= 特殊字符 =================
    latinToTibetan["'"] = QString(QChar(0x0F0B)); // 音节分隔符（ཀ་）
    latinToTibetan["-"] = QString(QChar(0x0F0B)); // 音节分隔符
    latinToTibetan[" "] = QString(QChar(0x0F0B)); // 空格也转换为音节分隔符



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
    latinToDevanagari["ā"] = QString(QChar(0x0906)); // आ
    latinToDevanagari["ē"] = QString(QChar(0x0908)); // ई
    latinToDevanagari["ī"] = QString(QChar(0x0908)); // ई
    latinToDevanagari["ō"] = QString(QChar(0x0913)); // ओ
    latinToDevanagari["ū"] = QString(QChar(0x090A)); // ऊ
    latinToDevanagari["á"] = QString(QChar(0x0906)) + QString(QChar(0x0901)); // आं
    latinToDevanagari["é"] = QString(QChar(0x0908)) + QString(QChar(0x0901)); // ईं
    latinToDevanagari["í"] = QString(QChar(0x0908)) + QString(QChar(0x0901)); // ईं
    latinToDevanagari["ó"] = QString(QChar(0x0913)) + QString(QChar(0x0901)); // ओं
    latinToDevanagari["ú"] = QString(QChar(0x090A)) + QString(QChar(0x0901)); // ऊं
    latinToDevanagari["ǎ"] = QString(QChar(0x0905)) + QString(QChar(0x094D)) + QString(QChar(0x0905)); // अअ
    latinToDevanagari["ě"] = QString(QChar(0x0907)) + QString(QChar(0x094D)) + QString(QChar(0x0907)); // इइ
    latinToDevanagari["ǐ"] = QString(QChar(0x0907)) + QString(QChar(0x094D)) + QString(QChar(0x0907)); // इइ
    latinToDevanagari["ǒ"] = QString(QChar(0x0913)) + QString(QChar(0x094D)) + QString(QChar(0x0913)); // ओओ
    latinToDevanagari["ǔ"] = QString(QChar(0x0909)) + QString(QChar(0x094D)) + QString(QChar(0x0909)); // उउ
    latinToDevanagari["à"] = QString(QChar(0x0905)) + QString(QChar(0x094D)); // अ्
    latinToDevanagari["è"] = QString(QChar(0x0907)) + QString(QChar(0x094D)); // इ्
    latinToDevanagari["ì"] = QString(QChar(0x0907)) + QString(QChar(0x094D)); // इ्
    latinToDevanagari["ò"] = QString(QChar(0x0913)) + QString(QChar(0x094D)); // ओ्
    latinToDevanagari["ù"] = QString(QChar(0x0909)) + QString(QChar(0x094D)); // उ्
    latinToDevanagari["ù"] = QString(QChar(0x0909)) + QString(QChar(0x094D)); // उ्
    // 法语特殊字符
    latinToDevanagari["ç"] = QString(QChar(0x091A)); // च (法语ç)
    latinToDevanagari["Ç"] = QString(QChar(0x091A)); // च (法语Ç)
    latinToDevanagari["œ"] = QString(QChar(0x0913)); // ओ (法语œ)
    latinToDevanagari["Œ"] = QString(QChar(0x0913)); // ओ (法语Œ)
    // 德语特殊字符
    latinToDevanagari["ß"] = QString(QChar(0x0938)) + QString(QChar(0x094D)) + QString(QChar(0x0938)); // स्स (德语ß)
    latinToDevanagari["ä"] = QString(QChar(0x0906)); // आ (德语ä)
    latinToDevanagari["Ä"] = QString(QChar(0x0906)); // आ (德语Ä)
    latinToDevanagari["ö"] = QString(QChar(0x0913)); // ओ (德语ö)
    latinToDevanagari["Ö"] = QString(QChar(0x0913)); // ओ (德语Ö)
    latinToDevanagari["ü"] = QString(QChar(0x0909)); // उ (德语ü)
    latinToDevanagari["Ü"] = QString(QChar(0x0909)); // उ (德语Ü)
    // 西班牙语特殊字符
    latinToDevanagari["ñ"] = QString(QChar(0x091E)); // ञ (西班牙语ñ)
    latinToDevanagari["Ñ"] = QString(QChar(0x091E)); // ञ (西班牙语Ñ)
    latinToDevanagari["¿"] = QString(QChar(0x003F)); // ? (西班牙语¿)
    latinToDevanagari["¡"] = QString(QChar(0x0021)); // ! (西班牙语¡)
    // 葡萄牙语特殊字符
    latinToDevanagari["ã"] = QString(QChar(0x0906)) + QString(QChar(0x0901)); // आं (葡萄牙语ã)
    latinToDevanagari["Ã"] = QString(QChar(0x0906)) + QString(QChar(0x0901)); // आं (葡萄牙语Ã)
    latinToDevanagari["õ"] = QString(QChar(0x0913)) + QString(QChar(0x0901)); // ओं (葡萄牙语õ)
    latinToDevanagari["Õ"] = QString(QChar(0x0913)) + QString(QChar(0x0901)); // ओं (葡萄牙语Õ)
    // 北欧语言特殊字符
    latinToDevanagari["å"] = QString(QChar(0x0906)); // आ (北欧å)
    latinToDevanagari["Å"] = QString(QChar(0x0906)); // आ (北欧Å)
    latinToDevanagari["æ"] = QString(QChar(0x0906)); // आ (北欧æ)
    latinToDevanagari["Æ"] = QString(QChar(0x0906)); // आ (北欧Æ)
    latinToDevanagari["ø"] = QString(QChar(0x0913)); // ओ (北欧ø)
    latinToDevanagari["Ø"] = QString(QChar(0x0913)); // ओ (北欧Ø)
    // 东欧语言特殊字符
    latinToDevanagari["č"] = QString(QChar(0x091A)); // च (捷克č)
    latinToDevanagari["Č"] = QString(QChar(0x091A)); // च (捷克Č)
    latinToDevanagari["š"] = QString(QChar(0x0938)); // स (捷克š)
    latinToDevanagari["Š"] = QString(QChar(0x0938)); // स (捷克Š)
    latinToDevanagari["ž"] = QString(QChar(0x091D)); // झ (捷克ž)
    latinToDevanagari["Ž"] = QString(QChar(0x091D)); // झ (捷克Ž)
    latinToDevanagari["ć"] = QString(QChar(0x091A)); // च (波兰ć)
    latinToDevanagari["Ć"] = QString(QChar(0x091A)); // च (波兰Ć)
    latinToDevanagari["ń"] = QString(QChar(0x0928)); // न (波兰ń)
    latinToDevanagari["Ń"] = QString(QChar(0x0928)); // न (波兰Ń)
    latinToDevanagari["ś"] = QString(QChar(0x0938)); // स (波兰ś)
    latinToDevanagari["Ś"] = QString(QChar(0x0938)); // स (波兰Ś)
    latinToDevanagari["ź"] = QString(QChar(0x091D)); // झ (波兰ź)
    latinToDevanagari["Ź"] = QString(QChar(0x091D)); // झ (波兰Ź)
    latinToDevanagari["ż"] = QString(QChar(0x091D)); // झ (波兰ż)
    latinToDevanagari["Ż"] = QString(QChar(0x091D)); // झ (波兰Ż)
    // 土耳其语特殊字符
    latinToDevanagari["ğ"] = QString(QChar(0x0917)); // ग (土耳其ğ)
    latinToDevanagari["Ğ"] = QString(QChar(0x0917)); // ग (土耳其Ğ)
    latinToDevanagari["ı"] = QString(QChar(0x0907)); // इ (土耳其ı)
    latinToDevanagari["İ"] = QString(QChar(0x0907)); // इ (土耳其İ)
    latinToDevanagari["ş"] = QString(QChar(0x0938)); // स (土耳其ş)
    latinToDevanagari["Ş"] = QString(QChar(0x0938)); // स (土耳其Ş)


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



    // -------------------------
    // 拉丁字母到格鲁吉亚文 (Georgian) - Mkhedruli 字母表
    // -------------------------

    // 基本单字母映射 - 基于语音相似性
    latinToGeorgian["A"] = QString(QChar(0x10D0)); // ა
    latinToGeorgian["B"] = QString(QChar(0x10D1)); // ბ
    latinToGeorgian["C"] = QString(QChar(0x10E1)); // ს (清齿龈擦音，更接近英语c)
    latinToGeorgian["D"] = QString(QChar(0x10D3)); // დ
    latinToGeorgian["E"] = QString(QChar(0x10D4)); // ე
    latinToGeorgian["F"] = QString(QChar(0x10E4)); // შ (更接近f音，虽然不完美)
    latinToGeorgian["G"] = QString(QChar(0x10D2)); // გ
    latinToGeorgian["H"] = QString(QChar(0x10F0)); // ჰ (声门擦音)
    latinToGeorgian["I"] = QString(QChar(0x10D8)); // ი
    latinToGeorgian["J"] = QString(QChar(0x10EF)); // ჯ (浊塞擦音)
    latinToGeorgian["K"] = QString(QChar(0x10D9)); // კ
    latinToGeorgian["L"] = QString(QChar(0x10DA)); // ლ
    latinToGeorgian["M"] = QString(QChar(0x10DB)); // მ
    latinToGeorgian["N"] = QString(QChar(0x10DC)); // ნ
    latinToGeorgian["O"] = QString(QChar(0x10DD)); // ო
    latinToGeorgian["P"] = QString(QChar(0x10DE)); // პ
    latinToGeorgian["Q"] = QString(QChar(0x10E7)); // ძ (小舌音近似)
    latinToGeorgian["R"] = QString(QChar(0x10E0)); // რ
    latinToGeorgian["S"] = QString(QChar(0x10E1)); // ს
    latinToGeorgian["T"] = QString(QChar(0x10D7)); // თ
    latinToGeorgian["U"] = QString(QChar(0x10E3)); // უ (正确的u音)
    latinToGeorgian["V"] = QString(QChar(0x10D5)); // ვ
    latinToGeorgian["W"] = QString(QChar(0x10D5)); // ვ (用v近似，格鲁吉亚语无w音)
    latinToGeorgian["X"] = QString(QChar(0x10EE)); // ხ (清软腭擦音)
    latinToGeorgian["Y"] = QString(QChar(0x10D8)); // ი (用i近似，或使用ჲ)
    latinToGeorgian["Z"] = QString(QChar(0x10D6)); // ზ

    // 优化的双字母组合 - 基于实际发音
    latinToGeorgian["CH"] = QString(QChar(0x10E9)); // ჩ
    latinToGeorgian["TS"] = QString(QChar(0x10EC)); // ც
    latinToGeorgian["DZ"] = QString(QChar(0x10EB)); // ძ
    latinToGeorgian["KH"] = QString(QChar(0x10EE)); // ხ
    latinToGeorgian["SH"] = QString(QChar(0x10E8)); // შ
    latinToGeorgian["GH"] = QString(QChar(0x10E6)); // ღ
    latinToGeorgian["PH"] = QString(QChar(0x10E4)); // შ (f音近似)
    latinToGeorgian["TH"] = QString(QChar(0x10E2)); // წ
    latinToGeorgian["JH"] = QString(QChar(0x10EF)); // ჯ
    latinToGeorgian["ZH"] = QString(QChar(0x10DF)); // ჟ

    // 三字母组合
    latinToGeorgian["TCH"] = QString(QChar(0x10E9)); // ჩ
    latinToGeorgian["TSK"] = QString(QChar(0x10EC)); // ც
    latinToGeorgian["DZH"] = QString(QChar(0x10EB)); // ძ



    // -------------------------
    // 拉丁字母到泰文 (Thai) 映射
    // -------------------------
    latinToThai["A"] = QString(QChar(0x0E01)); // ก
    latinToThai["B"] = QString(QChar(0x0E1A)); // บ
    latinToThai["C"] = QString(QChar(0x0E08)); // จ
    latinToThai["D"] = QString(QChar(0x0E14)); // ด
    latinToThai["E"] = QString(QChar(0x0E40)); // เ
    latinToThai["F"] = QString(QChar(0x0E1F)); // ฟ
    latinToThai["G"] = QString(QChar(0x0E01)); // ก
    latinToThai["H"] = QString(QChar(0x0E2E)); // ห
    latinToThai["I"] = QString(QChar(0x0E34)); // ิ
    latinToThai["J"] = QString(QChar(0x0E08)); // จ
    latinToThai["K"] = QString(QChar(0x0E01)); // ก
    latinToThai["L"] = QString(QChar(0x0E25)); // ล
    latinToThai["M"] = QString(QChar(0x0E21)); // ม
    latinToThai["N"] = QString(QChar(0x0E19)); // น
    latinToThai["O"] = QString(QChar(0x0E42)); // โ
    latinToThai["P"] = QString(QChar(0x0E1B)); // ป
    latinToThai["Q"] = QString(QChar(0x0E04)); // ค
    latinToThai["R"] = QString(QChar(0x0E23)); // ร
    latinToThai["S"] = QString(QChar(0x0E2A)); // ส
    latinToThai["T"] = QString(QChar(0x0E15)); // ต
    latinToThai["U"] = QString(QChar(0x0E38)); // ุ
    latinToThai["V"] = QString(QChar(0x0E27)); // ว
    latinToThai["W"] = QString(QChar(0x0E27)); // ว
    latinToThai["X"] = QString(QChar(0x0E2A)); // ส
    latinToThai["Y"] = QString(QChar(0x0E22)); // ย
    latinToThai["Z"] = QString(QChar(0x0E0B)); // ซ

    // 泰文双字母组合
    latinToThai["CH"] = QString(QChar(0x0E08)); // จ
    latinToThai["KH"] = QString(QChar(0x0E04)); // ค
    latinToThai["PH"] = QString(QChar(0x0E1C)); // ผ
    latinToThai["TH"] = QString(QChar(0x0E10)); // ฐ
    latinToThai["NG"] = QString(QChar(0x0E07)); // ง
    latinToThai["NY"] = QString(QChar(0x0E0D)); // ญ
    latinToThai["TR"] = QString(QChar(0x0E10)); // ฐ

    // 泰文元音组合
    latinToThai["AA"] = QString(QChar(0x0E32)); // า
    latinToThai["AE"] = QString(QChar(0x0E41)); // แ
    latinToThai["AI"] = QString(QChar(0x0E44)); // ไ
    latinToThai["AO"] = QString(QChar(0x0E2D)); // อ
    latinToThai["II"] = QString(QChar(0x0E35)); // ี
    latinToThai["UE"] = QString(QChar(0x0E37)); // ึ
    latinToThai["UU"] = QString(QChar(0x0E39)); // ู
    latinToThai["OO"] = QString(QChar(0x0E42)); // โ
    latinToThai["EE"] = QString(QChar(0x0E40)); // เ


    // -------------------------
    // 拉丁字母到亚美尼亚字母 (Armenian) 映射
    // -------------------------
    latinToArmenian["A"] = QString(QChar(0x0531)); // Ա
    latinToArmenian["B"] = QString(QChar(0x0532)); // Բ
    latinToArmenian["C"] = QString(QChar(0x0533)); // Գ
    latinToArmenian["D"] = QString(QChar(0x0534)); // Դ
    latinToArmenian["E"] = QString(QChar(0x0535)); // Ե
    latinToArmenian["F"] = QString(QChar(0x0556)); // Ֆ
    latinToArmenian["G"] = QString(QChar(0x0547)); // Է
    latinToArmenian["H"] = QString(QChar(0x0540)); // Հ
    latinToArmenian["I"] = QString(QChar(0x053B)); // Ի
    latinToArmenian["J"] = QString(QChar(0x0541)); // Ձ
    latinToArmenian["K"] = QString(QChar(0x053F)); // Կ
    latinToArmenian["L"] = QString(QChar(0x0544)); // Լ
    latinToArmenian["M"] = QString(QChar(0x0545)); // Խ
    latinToArmenian["N"] = QString(QChar(0x0546)); // Ծ
    latinToArmenian["O"] = QString(QChar(0x0555)); // Օ
    latinToArmenian["P"] = QString(QChar(0x054A)); // Պ
    latinToArmenian["Q"] = QString(QChar(0x0552)); // Ւ
    latinToArmenian["R"] = QString(QChar(0x054C)); // Ռ
    latinToArmenian["S"] = QString(QChar(0x054D)); // Ս
    latinToArmenian["T"] = QString(QChar(0x054F)); // Վ
    latinToArmenian["U"] = QString(QChar(0x0558)); // Ո
    latinToArmenian["V"] = QString(QChar(0x054E)); // Վ
    latinToArmenian["W"] = QString(QChar(0x0552)); // Ւ
    latinToArmenian["X"] = QString(QChar(0x054D)) + QString(QChar(0x0540)); // ՍՀ
    latinToArmenian["Y"] = QString(QChar(0x0557)); // Տ
    latinToArmenian["Z"] = QString(QChar(0x0536)); // Զ

    // 亚美尼亚字母双字母组合
    latinToArmenian["CH"] = QString(QChar(0x0549)); // Չ
    latinToArmenian["GH"] = QString(QChar(0x0542)); // Բ
    latinToArmenian["JH"] = QString(QChar(0x0541)); // Ձ
    latinToArmenian["KH"] = QString(QChar(0x055D)); // Ս
    latinToArmenian["PH"] = QString(QChar(0x0556)); // Ֆ
    latinToArmenian["SH"] = QString(QChar(0x0547)); // Շ
    latinToArmenian["TH"] = QString(QChar(0x054A)); // Պ
    latinToArmenian["TS"] = QString(QChar(0x0543)); // Ծ
    latinToArmenian["DZ"] = QString(QChar(0x0545)) + QString(QChar(0x0536)); // ԽԶ
    latinToArmenian["GH"] = QString(QChar(0x0542)); // Բ
    latinToArmenian["YH"] = QString(QChar(0x0557)); // Տ
    latinToArmenian["ZH"] = QString(QChar(0x055A)); // Ժ

    // -------------------------
    // 拉丁字母到孟加拉字母 (Bengali) 映射
    // -------------------------
    latinToBengali["A"] = QString(QChar(0x0985)); // অ
    latinToBengali["B"] = QString(QChar(0x09AC)); // ব
    latinToBengali["C"] = QString(QChar(0x099A)); // চ
    latinToBengali["D"] = QString(QChar(0x09A1)); // ড
    latinToBengali["E"] = QString(QChar(0x098F)); // এ
    latinToBengali["F"] = QString(QChar(0x09AB)); // ফ
    latinToBengali["G"] = QString(QChar(0x0997)); // গ
    latinToBengali["H"] = QString(QChar(0x09B9)); // হ
    latinToBengali["I"] = QString(QChar(0x0987)); // ই
    latinToBengali["J"] = QString(QChar(0x099C)); // জ
    latinToBengali["K"] = QString(QChar(0x0995)); // ক
    latinToBengali["L"] = QString(QChar(0x09B2)); // ল
    latinToBengali["M"] = QString(QChar(0x09AE)); // ম
    latinToBengali["N"] = QString(QChar(0x09A8)); // ন
    latinToBengali["O"] = QString(QChar(0x0993)); // ও
    latinToBengali["P"] = QString(QChar(0x09AA)); // প
    latinToBengali["Q"] = QString(QChar(0x0995)) + QString(QChar(0x09CD)) + QString(QChar(0x09AC)); // ক্ব
    latinToBengali["R"] = QString(QChar(0x09B0)); // র
    latinToBengali["S"] = QString(QChar(0x09B8)); // স
    latinToBengali["T"] = QString(QChar(0x099F)); // ট
    latinToBengali["U"] = QString(QChar(0x0989)); // উ
    latinToBengali["V"] = QString(QChar(0x09AD)); // ভ
    latinToBengali["W"] = QString(QChar(0x09AD)) + QString(QChar(0x09CD)) + QString(QChar(0x09AC)); // ভ্ব
    latinToBengali["X"] = QString(QChar(0x0995)) + QString(QChar(0x09CD)) + QString(QChar(0x09B7)); // ক্ষ
    latinToBengali["Y"] = QString(QChar(0x09AF)); // য
    latinToBengali["Z"] = QString(QChar(0x099D)); // ঝ

    // 孟加拉字母双字母组合
    latinToBengali["CH"] = QString(QChar(0x099A)); // চ
    latinToBengali["GH"] = QString(QChar(0x0998)); // ঘ
    latinToBengali["JH"] = QString(QChar(0x099D)); // ঝ
    latinToBengali["KH"] = QString(QChar(0x0996)); // খ
    latinToBengali["PH"] = QString(QChar(0x09AB)); // ফ
    latinToBengali["SH"] = QString(QChar(0x09B7)); // ষ
    latinToBengali["TH"] = QString(QChar(0x09A5)); // ঢ
    latinToBengali["DH"] = QString(QChar(0x09A7)); // ধ
    latinToBengali["BH"] = QString(QChar(0x09AD)); // ভ
    latinToBengali["NG"] = QString(QChar(0x0999)); // ঙ
    latinToBengali["NY"] = QString(QChar(0x099E)); // ঞ

    // 孟加拉字母元音组合
    latinToBengali["AA"] = QString(QChar(0x0986)); // আ
    latinToBengali["AI"] = QString(QChar(0x0990)); // ঐ
    latinToBengali["AU"] = QString(QChar(0x0994)); // ঔ
    latinToBengali["II"] = QString(QChar(0x0988)); // ঈ
    latinToBengali["UU"] = QString(QChar(0x098A)); // ঊ


    //泰米尔文
    latinToTamil["A"] = QString(QChar(0x0B85)); // அ
    latinToTamil["B"] = QString(QChar(0x0BAC)); // ப
    latinToTamil["C"] = QString(QChar(0x0B9A)); // ச
    latinToTamil["D"] = QString(QChar(0x0B9F)); // ட
    latinToTamil["E"] = QString(QChar(0x0B8E)); // எ
    latinToTamil["F"] = QString(QChar(0x0B83)); // ஃ (近似)
    latinToTamil["G"] = QString(QChar(0x0B95)); // க
    latinToTamil["H"] = QString(QChar(0x0BB9)); // ஹ
    latinToTamil["I"] = QString(QChar(0x0B87)); // இ
    latinToTamil["J"] = QString(QChar(0x0B9C)); // ஜ
    latinToTamil["K"] = QString(QChar(0x0B95)); // க
    latinToTamil["L"] = QString(QChar(0x0BB2)); // ல
    latinToTamil["M"] = QString(QChar(0x0BAE)); // ம
    latinToTamil["N"] = QString(QChar(0x0BA9)); // ன
    latinToTamil["O"] = QString(QChar(0x0B92)); // ஒ
    latinToTamil["P"] = QString(QChar(0x0BAA)); // ப
    latinToTamil["Q"] = QString(QChar(0x0B95)); // க (近似)
    latinToTamil["R"] = QString(QChar(0x0BB0)); // ர
    latinToTamil["S"] = QString(QChar(0x0BB8)); // ஸ
    latinToTamil["T"] = QString(QChar(0x0B9F)); // ட
    latinToTamil["U"] = QString(QChar(0x0B89)); // உ
    latinToTamil["V"] = QString(QChar(0x0BB5)); // வ
    latinToTamil["W"] = QString(QChar(0x0BB5)); // வ (近似)
    latinToTamil["X"] = QString(QChar(0x0B95)); // க (近似)
    latinToTamil["Y"] = QString(QChar(0x0BAF)); // ய
    latinToTamil["Z"] = QString(QChar(0x0B9C)); // ஜ (近似)

    // 泰米尔文双字母组合
    latinToTamil["CH"] = QString(QChar(0x0B9A)); // ச
    latinToTamil["SH"] = QString(QChar(0x0BB7)); // ஷ
    latinToTamil["TH"] = QString(QChar(0x0BA4)); // த
    latinToTamil["NG"] = QString(QChar(0x0B99)); // ங
    latinToTamil["NY"] = QString(QChar(0x0B9E)); // ஞ
    latinToTamil["AA"] = QString(QChar(0x0B86)); // ஆ
    latinToTamil["EE"] = QString(QChar(0x0B88)); // ஈ
    latinToTamil["OO"] = QString(QChar(0x0B8A)); // ஊ
    latinToTamil["AU"] = QString(QChar(0x0B94)); // ஔ
    latinToTamil["ZH"] = QString(QChar(0x0BB4)); // ழ
    latinToTamil["LH"] = QString(QChar(0x0BB3)); // ள
    latinToTamil["RR"] = QString(QChar(0x0BB1)); // ற
    latinToTamil["NN"] = QString(QChar(0x0BA8)); // ந

    // 泰卢固文映射表
    latinToTelugu["A"] = QString(QChar(0x0C05)); // అ
    latinToTelugu["B"] = QString(QChar(0x0C2C)); // బ
    latinToTelugu["C"] = QString(QChar(0x0C1A)); // చ
    latinToTelugu["D"] = QString(QChar(0x0C21)); // డ
    latinToTelugu["E"] = QString(QChar(0x0C0E)); // ఎ
    latinToTelugu["F"] = QString(QChar(0x0C03)); // ః (近似)
    latinToTelugu["G"] = QString(QChar(0x0C17)); // గ
    latinToTelugu["H"] = QString(QChar(0x0C39)); // హ
    latinToTelugu["I"] = QString(QChar(0x0C07)); // ఇ
    latinToTelugu["J"] = QString(QChar(0x0C1C)); // జ
    latinToTelugu["K"] = QString(QChar(0x0C15)); // క
    latinToTelugu["L"] = QString(QChar(0x0C32)); // ల
    latinToTelugu["M"] = QString(QChar(0x0C2E)); // మ
    latinToTelugu["N"] = QString(QChar(0x0C28)); // న
    latinToTelugu["O"] = QString(QChar(0x0C12)); // ఒ
    latinToTelugu["P"] = QString(QChar(0x0C2A)); // ప
    latinToTelugu["Q"] = QString(QChar(0x0C15)); // క (近似)
    latinToTelugu["R"] = QString(QChar(0x0C30)); // ర
    latinToTelugu["S"] = QString(QChar(0x0C38)); // స
    latinToTelugu["T"] = QString(QChar(0x0C1F)); // ట
    latinToTelugu["U"] = QString(QChar(0x0C09)); // ఉ
    latinToTelugu["V"] = QString(QChar(0x0C35)); // వ
    latinToTelugu["W"] = QString(QChar(0x0C35)); // వ (近似)
    latinToTelugu["X"] = QString(QChar(0x0C15)); // క (近似)
    latinToTelugu["Y"] = QString(QChar(0x0C2F)); // య
    latinToTelugu["Z"] = QString(QChar(0x0C1C)); // జ (近似)
    latinToTelugu["CH"] = QString(QChar(0x0C1A)); // చ
    latinToTelugu["SH"] = QString(QChar(0x0C37)); // ష
    latinToTelugu["TH"] = QString(QChar(0x0C24)); // త
    latinToTelugu["NG"] = QString(QChar(0x0C19)); // ఙ
    latinToTelugu["NY"] = QString(QChar(0x0C1E)); // ఞ
    latinToTelugu["AA"] = QString(QChar(0x0C06)); // ఆ
    latinToTelugu["EE"] = QString(QChar(0x0C08)); // ఈ
    latinToTelugu["OO"] = QString(QChar(0x0C0A)); // ఊ
    latinToTelugu["AU"] = QString(QChar(0x0C14)); // ఔ
    latinToTelugu["PH"] = QString(QChar(0x0C2B)); // ఫ
    latinToTelugu["KH"] = QString(QChar(0x0C16)); // ఖ
    latinToTelugu["GH"] = QString(QChar(0x0C18)); // ఘ
    latinToTelugu["DH"] = QString(QChar(0x0C22)); // ఢ
    latinToTelugu["BH"] = QString(QChar(0x0C2D)); // భ
    latinToTelugu["TS"] = QString(QChar(0x0C1B)); // ఛ
    latinToTelugu["RR"] = QString(QChar(0x0C31)); // ఱ
    latinToTelugu["LL"] = QString(QChar(0x0C33)); // ళ
    latinToTelugu["NN"] = QString(QChar(0x0C23)); // ణ
    latinToTelugu["SHH"] = QString(QChar(0x0C36)); // శ


    // 卡纳达文映射表
    latinToKannada["A"] = QString(QChar(0x0C85)); // ಅ
    latinToKannada["B"] = QString(QChar(0x0CAC)); // ಬ
    latinToKannada["C"] = QString(QChar(0x0C9A)); // ಚ
    latinToKannada["D"] = QString(QChar(0x0CA1)); // ಡ
    latinToKannada["E"] = QString(QChar(0x0C8E)); // ಎ
    latinToKannada["F"] = QString(QChar(0x0C83)); // ಃ (近似)
    latinToKannada["G"] = QString(QChar(0x0C97)); // ಗ
    latinToKannada["H"] = QString(QChar(0x0CB9)); // ಹ
    latinToKannada["I"] = QString(QChar(0x0C87)); // ಇ
    latinToKannada["J"] = QString(QChar(0x0C9C)); // ಜ
    latinToKannada["K"] = QString(QChar(0x0C95)); // ಕ
    latinToKannada["L"] = QString(QChar(0x0CB2)); // ಲ
    latinToKannada["M"] = QString(QChar(0x0CAE)); // ಮ
    latinToKannada["N"] = QString(QChar(0x0CA8)); // ನ
    latinToKannada["O"] = QString(QChar(0x0C92)); // ಒ
    latinToKannada["P"] = QString(QChar(0x0CAA)); // ಪ
    latinToKannada["Q"] = QString(QChar(0x0C95)); // ಕ (近似)
    latinToKannada["R"] = QString(QChar(0x0CB0)); // ರ
    latinToKannada["S"] = QString(QChar(0x0CB8)); // ಸ
    latinToKannada["T"] = QString(QChar(0x0C9F)); // ಟ
    latinToKannada["U"] = QString(QChar(0x0C89)); // ಉ
    latinToKannada["V"] = QString(QChar(0x0CB5)); // ವ
    latinToKannada["W"] = QString(QChar(0x0CB5)); // ವ (近似)
    latinToKannada["X"] = QString(QChar(0x0C95)); // ಕ (近似)
    latinToKannada["Y"] = QString(QChar(0x0CAF)); // ಯ
    latinToKannada["Z"] = QString(QChar(0x0C9C)); // ಜ (近似)
    latinToKannada["CH"] = QString(QChar(0x0C9A)); // ಚ
    latinToKannada["SH"] = QString(QChar(0x0CB7)); // ಷ
    latinToKannada["TH"] = QString(QChar(0x0CA4)); // ತ
    latinToKannada["NG"] = QString(QChar(0x0C99)); // ಙ
    latinToKannada["NY"] = QString(QChar(0x0C9E)); // ಞ
    latinToKannada["AA"] = QString(QChar(0x0C86)); // ಆ
    latinToKannada["EE"] = QString(QChar(0x0C88)); // ಈ
    latinToKannada["OO"] = QString(QChar(0x0C8A)); // ಊ
    latinToKannada["AU"] = QString(QChar(0x0C94)); // ಔ
    latinToKannada["PH"] = QString(QChar(0x0CAB)); // ಫ
    latinToKannada["KH"] = QString(QChar(0x0C96)); // ಖ
    latinToKannada["GH"] = QString(QChar(0x0C98)); // ಘ
    latinToKannada["DH"] = QString(QChar(0x0CA2)); // ಢ
    latinToKannada["BH"] = QString(QChar(0x0CAD)); // ಭ
    latinToKannada["TS"] = QString(QChar(0x0C9B)); // ಛ
    latinToKannada["RR"] = QString(QChar(0x0CB1)); // ಱ
    latinToKannada["LL"] = QString(QChar(0x0CB3)); // ಳ
    latinToKannada["NN"] = QString(QChar(0x0CA3)); // ಣ
    latinToKannada["SHH"] = QString(QChar(0x0CB6)); // ಶ
    
    

    // 阿萨姆文映射表
    latinToAssamese["A"] = QString(QChar(0x0905)); // অ
    latinToAssamese["B"] = QString(QChar(0x09AC)); // ব
    latinToAssamese["C"] = QString(QChar(0x099A)); // চ
    latinToAssamese["D"] = QString(QChar(0x09A1)); // ড
    latinToAssamese["E"] = QString(QChar(0x098F)); // এ
    latinToAssamese["F"] = QString(QChar(0x0983)); // ঃ (近似)
    latinToAssamese["G"] = QString(QChar(0x0997)); // গ
    latinToAssamese["H"] = QString(QChar(0x0939)); // হ
    latinToAssamese["I"] = QString(QChar(0x0987)); // ই
    latinToAssamese["J"] = QString(QChar(0x099C)); // জ
    latinToAssamese["K"] = QString(QChar(0x0995)); // ক
    latinToAssamese["L"] = QString(QChar(0x09B2)); // ল
    latinToAssamese["M"] = QString(QChar(0x09AE)); // ম
    latinToAssamese["N"] = QString(QChar(0x09A8)); // ন
    latinToAssamese["O"] = QString(QChar(0x0993)); // ও
    latinToAssamese["P"] = QString(QChar(0x09AA)); // প
    latinToAssamese["Q"] = QString(QChar(0x0995)); // ক (近似)
    latinToAssamese["R"] = QString(QChar(0x09B0)); // র
    latinToAssamese["S"] = QString(QChar(0x09B8)); // স
    latinToAssamese["T"] = QString(QChar(0x099F)); // ট
    latinToAssamese["U"] = QString(QChar(0x0989)); // উ
    latinToAssamese["V"] = QString(QChar(0x09AD)); // ব
    latinToAssamese["W"] = QString(QChar(0x09AD)); // ব (近似)
    latinToAssamese["X"] = QString(QChar(0x0995)); // ক (近似)
    latinToAssamese["Y"] = QString(QChar(0x09AF)); // য
    latinToAssamese["Z"] = QString(QChar(0x099C)); // জ (近似)
    latinToAssamese["CH"] = QString(QChar(0x099A)); // চ
    latinToAssamese["SH"] = QString(QChar(0x09B7)); // ষ
    latinToAssamese["TH"] = QString(QChar(0x09A4)); // ত
    latinToAssamese["NG"] = QString(QChar(0x0999)); // ঙ
    latinToAssamese["NY"] = QString(QChar(0x099E)); // ঞ
    latinToAssamese["AA"] = QString(QChar(0x0986)); // আ
    latinToAssamese["EE"] = QString(QChar(0x0988)); // ঈ
    latinToAssamese["OO"] = QString(QChar(0x098A)); // ঊ
    latinToAssamese["AU"] = QString(QChar(0x0994)); // ঔ
    latinToAssamese["PH"] = QString(QChar(0x09AB)); // ফ
    latinToAssamese["KH"] = QString(QChar(0x0996)); // খ
    latinToAssamese["GH"] = QString(QChar(0x0998)); // ঘ
    latinToAssamese["DH"] = QString(QChar(0x09A2)); // ঢ
    latinToAssamese["BH"] = QString(QChar(0x09AD)); // ভ
    latinToAssamese["TS"] = QString(QChar(0x099B)); // ছ
    latinToAssamese["NN"] = QString(QChar(0x09A3)); // ণ
    latinToAssamese["SHH"] = QString(QChar(0x09B6)); // শ
    
    //-------------------------------------
    //回鹘蒙文
    //-------------------------------------
    latinToOldUyghur["A"] = QString(QChar(0x1820)); // ᠠ
    latinToOldUyghur["B"] = QString(QChar(0x182A)); // ᠪ
    latinToOldUyghur["C"] = QString(QChar(0x1834)); // ᠴ
    latinToOldUyghur["D"] = QString(QChar(0x1833)); // ᠳ
    latinToOldUyghur["E"] = QString(QChar(0x1868)); // ᡨ
    latinToOldUyghur["F"] = QString(QChar(0x1876)); // ᡶ
    latinToOldUyghur["G"] = QString(QChar(0x1860)); // ᡠ
    latinToOldUyghur["H"] = QString(QChar(0x1865)); // ᡥ
    latinToOldUyghur["I"] = QString(QChar(0x1822)); // ᠢ
    latinToOldUyghur["J"] = QString(QChar(0x1835)); // ᠵ
    latinToOldUyghur["K"] = QString(QChar(0x182F)); // ᠯ
    latinToOldUyghur["L"] = QString(QChar(0x182F)); // ᠯ
    latinToOldUyghur["M"] = QString(QChar(0x182E)); // ᠮ
    latinToOldUyghur["N"] = QString(QChar(0x1828)); // ᠨ
    latinToOldUyghur["O"] = QString(QChar(0x1823)); // ᠣ
    latinToOldUyghur["P"] = QString(QChar(0x1866)); // ᡦ
    latinToOldUyghur["Q"] = QString(QChar(0x184C)); // ᡌ
    latinToOldUyghur["R"] = QString(QChar(0x1837)); // ᠷ
    latinToOldUyghur["S"] = QString(QChar(0x1830)); // ᠰ
    latinToOldUyghur["T"] = QString(QChar(0x1831)); // ᠱ
    latinToOldUyghur["U"] = QString(QChar(0x1864)); // ᡤ
    latinToOldUyghur["V"] = QString(QChar(0x1861)); // ᡡ
    latinToOldUyghur["W"] = QString(QChar(0x186D)); // ᡭ
    latinToOldUyghur["X"] = QString(QChar(0x184D)); // ᡍ
    latinToOldUyghur["Y"] = QString(QChar(0x1836)); // ᠶ
    latinToOldUyghur["Z"] = QString(QChar(0x1839)); // ᠹ
    latinToOldUyghur["CH"] = QString(QChar(0x1834)); // ᠴ
    latinToOldUyghur["SH"] = QString(QChar(0x1830)); // ᠰ
    latinToOldUyghur["ZH"] = QString(QChar(0x1839)); // ᠹ
    latinToOldUyghur["KH"] = QString(QChar(0x184D)); // ᡍ
    latinToOldUyghur["GH"] = QString(QChar(0x1860)); // ᡠ
    latinToOldUyghur["NG"] = QString(QChar(0x1828)); // ᠨ
    latinToOldUyghur["TS"] = QString(QChar(0x1831)); // ᠱ
    latinToOldUyghur["DZ"] = QString(QChar(0x1833)); // ᠳ
    latinToOldUyghur["AA"] = QString(QChar(0x1820)); // ᠠ
    latinToOldUyghur["EE"] = QString(QChar(0x1868)); // ᡨ
    latinToOldUyghur["II"] = QString(QChar(0x1822)); // ᠢ
    latinToOldUyghur["OO"] = QString(QChar(0x1823)); // ᠣ
    latinToOldUyghur["UU"] = QString(QChar(0x1864)); // ᡤ


    //-------------------------------------
    // 满文映射表
    //-------------------------------------
    latinToManchu["A"] = QString(QChar(0x1820)); // ᠠ
    latinToManchu["B"] = QString(QChar(0x182A)); // ᠪ
    latinToManchu["C"] = QString(QChar(0x1834)); // ᠴ
    latinToManchu["D"] = QString(QChar(0x1833)); // ᠳ
    latinToManchu["E"] = QString(QChar(0x1868)); // ᡨ
    latinToManchu["F"] = QString(QChar(0x1876)); // ᡶ
    latinToManchu["G"] = QString(QChar(0x1860)); // ᡠ
    latinToManchu["H"] = QString(QChar(0x1865)); // ᡥ
    latinToManchu["I"] = QString(QChar(0x1822)); // ᠢ
    latinToManchu["J"] = QString(QChar(0x1835)); // ᠵ
    latinToManchu["K"] = QString(QChar(0x1874)); // ᡴ
    latinToManchu["L"] = QString(QChar(0x182F)); // ᠯ
    latinToManchu["M"] = QString(QChar(0x182E)); // ᠮ
    latinToManchu["N"] = QString(QChar(0x1828)); // ᠨ
    latinToManchu["O"] = QString(QChar(0x1823)); // ᠣ
    latinToManchu["P"] = QString(QChar(0x1866)); // ᡦ
    latinToManchu["Q"] = QString(QChar(0x184C)); // ᡌ
    latinToManchu["R"] = QString(QChar(0x1837)); // ᠷ
    latinToManchu["S"] = QString(QChar(0x1830)); // ᠰ
    latinToManchu["T"] = QString(QChar(0x1867)); // ᡧ
    latinToManchu["U"] = QString(QChar(0x1864)); // ᡤ
    latinToManchu["V"] = QString(QChar(0x1861)); // ᡡ
    latinToManchu["W"] = QString(QChar(0x186D)); // ᡭ
    latinToManchu["X"] = QString(QChar(0x184D)); // ᡍ
    latinToManchu["Y"] = QString(QChar(0x1836)); // ᠶ
    latinToManchu["Z"] = QString(QChar(0x1839)); // ᠹ

    // 多音节组合
    latinToManchu["CH"] = QString(QChar(0x1834)); // ᠴ
    latinToManchu["SH"] = QString(QChar(0x1830)); // ᠰ
    latinToManchu["ZH"] = QString(QChar(0x1839)); // ᠹ
    latinToManchu["KH"] = QString(QChar(0x184D)); // ᡍ
    latinToManchu["GH"] = QString(QChar(0x1860)); // ᡠ
    latinToManchu["NG"] = QString(QChar(0x1828)); // ᠨ
    latinToManchu["TS"] = QString(QChar(0x1831)); // ᠱ
    latinToManchu["DZ"] = QString(QChar(0x1833)); // ᠳ
    latinToManchu["AA"] = QString(QChar(0x1820)); // ᠠ
    latinToManchu["EE"] = QString(QChar(0x1868)); // ᡨ
    latinToManchu["II"] = QString(QChar(0x1822)); // ᠢ
    latinToManchu["OO"] = QString(QChar(0x1823)); // ᠣ
    latinToManchu["UU"] = QString(QChar(0x1864)); // ᡤ

    //-------------------------------------
    // 因纽特文映射表 (加拿大原住民音节文字)
    //-------------------------------------
    latinToInuktitut["A"] = QString(QChar(0x1401)); // ᐁ
    latinToInuktitut["B"] = QString(QChar(0x148B)); // ᒋ
    latinToInuktitut["C"] = QString(QChar(0x14C2)); // ᓂ
    latinToInuktitut["D"] = QString(QChar(0x1470)); // ᑰ
    latinToInuktitut["E"] = QString(QChar(0x1402)); // ᐂ
    latinToInuktitut["F"] = QString(QChar(0x14D0)); // ᓐ
    latinToInuktitut["G"] = QString(QChar(0x14D1)); // ᓑ
    latinToInuktitut["H"] = QString(QChar(0x14D2)); // ᓒ
    latinToInuktitut["I"] = QString(QChar(0x1403)); // ᐃ
    latinToInuktitut["J"] = QString(QChar(0x14D3)); // ᓓ
    latinToInuktitut["K"] = QString(QChar(0x14A7)); // ᒧ
    latinToInuktitut["L"] = QString(QChar(0x14D4)); // ᓔ
    latinToInuktitut["M"] = QString(QChar(0x14D5)); // ᓕ
    latinToInuktitut["N"] = QString(QChar(0x14D6)); // ᓖ
    latinToInuktitut["O"] = QString(QChar(0x1404)); // ᐄ
    latinToInuktitut["P"] = QString(QChar(0x14D7)); // ᓗ
    latinToInuktitut["Q"] = QString(QChar(0x14D8)); // ᓘ
    latinToInuktitut["R"] = QString(QChar(0x14D9)); // ᓙ
    latinToInuktitut["S"] = QString(QChar(0x14DA)); // ᓚ
    latinToInuktitut["T"] = QString(QChar(0x14DB)); // ᓛ
    latinToInuktitut["U"] = QString(QChar(0x1405)); // ᐅ
    latinToInuktitut["V"] = QString(QChar(0x14DC)); // ᓜ
    latinToInuktitut["W"] = QString(QChar(0x14DD)); // ᓝ
    latinToInuktitut["X"] = QString(QChar(0x14DE)); // ᓞ
    latinToInuktitut["Y"] = QString(QChar(0x14DF)); // ᓟ
    latinToInuktitut["Z"] = QString(QChar(0x14E0)); // ᓠ

    // 多音节组合
    latinToInuktitut["CH"] = QString(QChar(0x14C2)); // ᓂ
    latinToInuktitut["SH"] = QString(QChar(0x14DA)); // ᓚ
    latinToInuktitut["TH"] = QString(QChar(0x14DB)); // ᓛ
    latinToInuktitut["NG"] = QString(QChar(0x14D6)); // ᓖ
    latinToInuktitut["AA"] = QString(QChar(0x1401)); // ᐁ
    latinToInuktitut["EE"] = QString(QChar(0x1402)); // ᐂ
    latinToInuktitut["II"] = QString(QChar(0x1403)); // ᐃ
    latinToInuktitut["OO"] = QString(QChar(0x1404)); // ᐄ
    latinToInuktitut["UU"] = QString(QChar(0x1405)); // ᐅ







    // -------------------------
    // 拉丁字母到古意大利文 (Old Italic)
    // -------------------------
    latinToOldItalic["A"] = QString("𐌀"); // 𐌀
    latinToOldItalic["B"] = QString("𐌁"); // 𐌁
    latinToOldItalic["C"] = QString("𐌂"); // 𐌂
    latinToOldItalic["D"] = QString("𐌃"); // 𐌃
    latinToOldItalic["E"] = QString("𐌄"); // 𐌄
    latinToOldItalic["F"] = QString("𐌅"); // 𐌅
    latinToOldItalic["G"] = QString("𐌆"); // 𐌆
    latinToOldItalic["H"] = QString("𐌇"); // 𐌇
    latinToOldItalic["I"] = QString("𐌈"); // 𐌈
    latinToOldItalic["J"] = QString("𐌉"); // 𐌉
    latinToOldItalic["K"] = QString("𐌊"); // 𐌊
    latinToOldItalic["L"] = QString("𐌋"); // 𐌋
    latinToOldItalic["M"] = QString("𐌌"); // 𐌌
    latinToOldItalic["N"] = QString("𐌍"); // 𐌍
    latinToOldItalic["O"] = QString("𐌎"); // 𐌎
    latinToOldItalic["P"] = QString("𐌏"); // 𐌏
    latinToOldItalic["Q"] = QString("𐌐"); // 𐌐
    latinToOldItalic["R"] = QString("𐌑"); // 𐌑
    latinToOldItalic["S"] = QString("𐌒"); // 𐌒
    latinToOldItalic["T"] = QString("𐌓"); // 𐌓
    latinToOldItalic["U"] = QString("𐌔"); // 𐌔
    latinToOldItalic["V"] = QString("𐌕"); // 𐌕
    latinToOldItalic["W"] = QString("𐌖"); // 𐌖
    latinToOldItalic["X"] = QString("𐌗"); // 𐌗
    latinToOldItalic["Y"] = QString("𐌘"); // 𐌘
    latinToOldItalic["Z"] = QString("𐌙"); // 𐌙





    // ----------------------------------------------------
    // 拉丁字母到古波斯文 (Old Persian) - 修正和优化的音译表
    // ----------------------------------------------------
    // 说明:
    // 1. 此表旨在提供一个从拉丁字母到古波斯楔形文字的音译近似。
    // 2. 古波斯文是音节文字，大多数字符代表"辅音+元音a"，而非单个辅音。
    // 4. 移除了大量重复、冲突和不准确的映射，并对拼音和英文的常见组合进行了整合与简化。
    // 5. 目标是建立一个更一致、更准确的转写系统。

    // -------------------------
    // 1. 基本字母 (Basic Alphabet)
    // -------------------------
    // 元音 (Vowels)
    latinToOldPersian["A"] = QString("𐎠"); // a
    latinToOldPersian["I"] = QString("𐎡"); // i
    latinToOldPersian["U"] = QString("𐎢"); // u
    latinToOldPersian["E"] = QString("𐎡"); // e (用 i 近似)
    latinToOldPersian["O"] = QString("𐎠𐎢"); // o (用双元音 au 近似)
    latinToOldPersian["Y"] = QString("𐎹"); // y (作为辅音 ya)

    // 辅音 (Consonants)
    latinToOldPersian["B"] = QString("𐎲"); // b
    latinToOldPersian["C"] = QString("𐎣"); // c (发 /k/ 音)
    latinToOldPersian["D"] = QString("𐎭"); // d
    latinToOldPersian["F"] = QString("𐎳"); // f
    latinToOldPersian["G"] = QString("𐎥"); // g
    latinToOldPersian["H"] = QString("𐏃"); // h
    latinToOldPersian["J"] = QString("𐎪"); // j
    latinToOldPersian["K"] = QString("𐎣"); // k
    latinToOldPersian["L"] = QString("𐎫"); // 𐎫 (l)
    latinToOldPersian["M"] = QString("𐎶"); // m
    latinToOldPersian["N"] = QString("𐎴"); // n
    latinToOldPersian["P"] = QString("𐎱"); // p
    latinToOldPersian["Q"] = QString("𐎣"); // q (发 /k/ 音)
    latinToOldPersian["R"] = QString("𐎼"); // r
    latinToOldPersian["S"] = QString("𐎿"); // s
    latinToOldPersian["T"] = QString("𐎫"); // t
    latinToOldPersian["V"] = QString("𐎺"); // v
    latinToOldPersian["W"] = QString("𐎺"); // w (用 v 近似)
    latinToOldPersian["X"] = QString("𐎣𐎿"); // x (用 ks 组合近似)
    latinToOldPersian["Z"] = QString("𐏀"); // z

    // -------------------------
    // 2. 字母组合 (Digraphs & Combinations)
    // -------------------------
    // 辅音组合 (Consonant Digraphs)
    latinToOldPersian["SH"] = QString("𐏁"); // ša
    latinToOldPersian["CH"] = QString("𐏂"); // ça
    latinToOldPersian["TH"] = QString("𐎰"); // θa
    latinToOldPersian["KH"] = QString("𐎧"); // xša
    latinToOldPersian["GH"] = QString("𐎥𐏃"); // g-h
    latinToOldPersian["PH"] = QString("𐎳"); // f (等同于 F)
    latinToOldPersian["QU"] = QString("𐎤"); // ku
    latinToOldPersian["NG"] = QString("𐎴𐎥"); // n-g

    // 元音组合 (Vowel Combinations)
    latinToOldPersian["AA"] = QString("𐎠𐎠"); // ā (长元音)
    latinToOldPersian["EE"] = QString("𐎡𐎡"); // ī (长元音)
    latinToOldPersian["OO"] = QString("𐎢𐎢"); // ū (长元音)
    latinToOldPersian["AE"] = QString("𐎠𐎡"); // ae
    latinToOldPersian["AI"] = QString("𐎠𐎡"); // ai
    latinToOldPersian["AY"] = QString("𐎠𐎡"); // ay
    latinToOldPersian["AU"] = QString("𐎠𐎢"); // au
    latinToOldPersian["EA"] = QString("𐎡𐎠"); // ea
    latinToOldPersian["EI"] = QString("𐎡𐎡"); // ei (近似 ī)
    latinToOldPersian["EU"] = QString("𐎡𐎢"); // eu
    latinToOldPersian["EY"] = QString("𐎡𐎡"); // ey (近似 ī)
    latinToOldPersian["IA"] = QString("𐎡𐎠"); // ia
    latinToOldPersian["IE"] = QString("𐎡𐎡"); // ie (近似 ī)
    latinToOldPersian["IO"] = QString("𐎡𐎠𐎢"); // io
    latinToOldPersian["IU"] = QString("𐎡𐎢"); // iu
    latinToOldPersian["OA"] = QString("𐎠𐎢𐎠"); // oa
    latinToOldPersian["OE"] = QString("𐎠𐎢𐎡"); // oe
    latinToOldPersian["OI"] = QString("𐎠𐎢𐎡"); // oi
    latinToOldPersian["OU"] = QString("𐎢𐎢"); // ou (近似 ū)
    latinToOldPersian["UA"] = QString("𐎢𐎠"); // ua
    latinToOldPersian["UE"] = QString("𐎢𐎡"); // ue
    latinToOldPersian["UI"] = QString("𐎢𐎡"); // ui

    // 常见辅音串 (Common Consonant Clusters)
    latinToOldPersian["BR"] = QString("𐎲𐎼"); // b-r
    latinToOldPersian["CR"] = QString("𐎣𐎼"); // k-r
    latinToOldPersian["DR"] = QString("𐎭𐎼"); // d-r
    latinToOldPersian["FR"] = QString("𐎳𐎼"); // f-r
    latinToOldPersian["GR"] = QString("𐎥𐎼"); // g-r
    latinToOldPersian["PR"] = QString("𐎱𐎼"); // p-r
    latinToOldPersian["SC"] = QString("𐎿𐎣"); // s-k
    latinToOldPersian["SK"] = QString("𐎿𐎣"); // s-k
    latinToOldPersian["SM"] = QString("𐎿𐎶"); // s-m
    latinToOldPersian["SN"] = QString("𐎿𐎴"); // s-n
    latinToOldPersian["SP"] = QString("𐎿𐎱"); // s-p
    latinToOldPersian["ST"] = QString("𐎿𐎫"); // s-t
    latinToOldPersian["SW"] = QString("𐎿𐎺"); // s-v
    latinToOldPersian["TR"] = QString("𐎫𐎼"); // t-r

    // -------------------------
    // 3. 汉语拼音特有组合 (Pinyin-Specific)
    // -------------------------
    // 注意: 大部分拼音可由以上基本字母和组合构成
    latinToOldPersian["AN"] = QString("𐎠𐎴"); // an
    latinToOldPersian["EN"] = QString("𐎡𐎴"); // en
    latinToOldPersian["IN"] = QString("𐎡𐎴"); // in
    latinToOldPersian["UN"] = QString("𐎢𐎴"); // un
    latinToOldPersian["ANG"] = QString("𐎠𐎴𐎥"); // ang
    latinToOldPersian["ENG"] = QString("𐎡𐎴𐎥"); // eng
    latinToOldPersian["ING"] = QString("𐎡𐎴𐎥"); // ing
    latinToOldPersian["ONG"] = QString("𐎠𐎢𐎴𐎥"); // ong (用 o-ng 近似)
    latinToOldPersian["ER"] = QString("𐎠𐎼"); // er (用 ar 近似)
    // 卷舌声母 (Retroflex Initials)
    latinToOldPersian["ZH"] = QString("𐏀"); // zh (用 z 近似)
    // 以下组合为了更精确地转写拼音
    latinToOldPersian["CHI"] = QString("𐏂𐎡"); // chi
    latinToOldPersian["SHI"] = QString("𐏁𐎡"); // shi
    latinToOldPersian["RI"] = QString("𐎼𐎡"); // ri




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
