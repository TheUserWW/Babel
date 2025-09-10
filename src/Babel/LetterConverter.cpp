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


    // -------------------------
    // 拉丁字母到格鲁吉亚文 (Georgian) - Mkhedruli 字母表
    // -------------------------
    latinToGeorgian["A"] = QString(QChar(0x10D0)); // ა
    latinToGeorgian["B"] = QString(QChar(0x10D1)); // ბ
    latinToGeorgian["C"] = QString(QChar(0x10E3)); // ჭ
    latinToGeorgian["D"] = QString(QChar(0x10D3)); // დ
    latinToGeorgian["E"] = QString(QChar(0x10D4)); // ე
    latinToGeorgian["F"] = QString(QChar(0x10D1)) + QString(QChar(0x10E1)); // ბს
    latinToGeorgian["G"] = QString(QChar(0x10D2)); // გ
    latinToGeorgian["H"] = QString(QChar(0x10EC)); // ჰ
    latinToGeorgian["I"] = QString(QChar(0x10D8)); // ი
    latinToGeorgian["J"] = QString(QChar(0x10E3)); // ჭ
    latinToGeorgian["K"] = QString(QChar(0x10D9)); // კ
    latinToGeorgian["L"] = QString(QChar(0x10DA)); // ლ
    latinToGeorgian["M"] = QString(QChar(0x10DB)); // მ
    latinToGeorgian["N"] = QString(QChar(0x10DC)); // ნ
    latinToGeorgian["O"] = QString(QChar(0x10DD)); // ო
    latinToGeorgian["P"] = QString(QChar(0x10DE)); // პ
    latinToGeorgian["Q"] = QString(QChar(0x10EA)); // ქ
    latinToGeorgian["R"] = QString(QChar(0x10E0)); // რ
    latinToGeorgian["S"] = QString(QChar(0x10E1)); // ს
    latinToGeorgian["T"] = QString(QChar(0x10D7)); // თ
    latinToGeorgian["U"] = QString(QChar(0x10D8)); // ი (近似)
    latinToGeorgian["V"] = QString(QChar(0x10D5)); // ვ
    latinToGeorgian["W"] = QString(QChar(0x10E9)); // უ
    latinToGeorgian["X"] = QString(QChar(0x10DD)) + QString(QChar(0x10E3)); // ოჭ
    latinToGeorgian["Y"] = QString(QChar(0x10EB)); // ჲ
    latinToGeorgian["Z"] = QString(QChar(0x10D6)); // ზ

    // 双字母组合
    latinToGeorgian["Ch"] = QString(QChar(0x10E5)); // ჩ
    latinToGeorgian["Dz"] = QString(QChar(0x10E7)); // ძ
    latinToGeorgian["Gh"] = QString(QChar(0x10D2)) + QString(QChar(0x10E1)); // გს
    latinToGeorgian["Kh"] = QString(QChar(0x10EA)) + QString(QChar(0x10E1)); // ქს
    latinToGeorgian["Ph"] = QString(QChar(0x10DE)) + QString(QChar(0x10E1)); // პს
    latinToGeorgian["Sh"] = QString(QChar(0x10E4)); // შ
    latinToGeorgian["Ts"] = QString(QChar(0x10E6)); // ც
    latinToGeorgian["Tch"] = QString(QChar(0x10E3)); // ჭ
    latinToGeorgian["Tskh"] = QString(QChar(0x10E2)); // წ
    latinToGeorgian["Tz"] = QString(QChar(0x10E6)); // ც
    latinToGeorgian["Zh"] = QString(QChar(0x10DF)); // ჟ


    // -------------------------
    // 拉丁字母到吉兹字母 (Ge'ez) - 埃塞俄比亚字母
    // -------------------------
    latinToGeez["A"] = QString(QChar(0x1200)); // ሀ
    latinToGeez["B"] = QString(QChar(0x1208)); // ለ
    latinToGeez["C"] = QString(QChar(0x1218)); // መ
    latinToGeez["D"] = QString(QChar(0x1210)); // ሐ
    latinToGeez["E"] = QString(QChar(0x1230)); // ሰ
    latinToGeez["F"] = QString(QChar(0x1260)); // በ
    latinToGeez["G"] = QString(QChar(0x1308)); // ገ
    latinToGeez["H"] = QString(QChar(0x12D8)); // ዘ
    latinToGeez["I"] = QString(QChar(0x1290)); // ነ
    latinToGeez["J"] = QString(QChar(0x12A0)); // አ
    latinToGeez["K"] = QString(QChar(0x12E8)); // የ
    latinToGeez["L"] = QString(QChar(0x12F0)); // ደ
    latinToGeez["M"] = QString(QChar(0x1300)); // ጀ
    latinToGeez["N"] = QString(QChar(0x1320)); // ጠ
    latinToGeez["O"] = QString(QChar(0x1330)); // ጰ
    latinToGeez["P"] = QString(QChar(0x1338)); // ጸ
    latinToGeez["Q"] = QString(QChar(0x1340)); // ፀ
    latinToGeez["R"] = QString(QChar(0x1348)); // ፈ
    latinToGeez["S"] = QString(QChar(0x1350)); // ፐ
    latinToGeez["T"] = QString(QChar(0x1268)); // ቨ
    latinToGeez["U"] = QString(QChar(0x1270)); // ተ
    latinToGeez["V"] = QString(QChar(0x1278)); // ቸ
    latinToGeez["W"] = QString(QChar(0x1280)); // ኀ
    latinToGeez["X"] = QString(QChar(0x1298)); // ኘ
    latinToGeez["Y"] = QString(QChar(0x12A8)); // ከ
    latinToGeez["Z"] = QString(QChar(0x12B8)); // ኸ

    // 双字母组合
    latinToGeez["CH"] = QString(QChar(0x12C8)); // ወ
    latinToGeez["SH"] = QString(QChar(0x12D0)); // ዐ
    latinToGeez["KH"] = QString(QChar(0x12E0)); // ዠ
    latinToGeez["PH"] = QString(QChar(0x12F8)); // ዸ
    latinToGeez["TH"] = QString(QChar(0x1308)); // ገ
    latinToGeez["TS"] = QString(QChar(0x1310)); // ጐ
    latinToGeez["DH"] = QString(QChar(0x1328)); // ጨ
    latinToGeez["NY"] = QString(QChar(0x1338)); // ጸ
    latinToGeez["NG"] = QString(QChar(0x1348)); // ፈ
    latinToGeez["GW"] = QString(QChar(0x1358)); // ፘ

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

    // 库尔德文字母映射（基于拉丁字母转写）
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

    // 普什图文多音节映射
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
    // 拉丁字母到古突厥文 (Old Turkic, Orkhon runes)
    // -------------------------
    latinToOldTurkic["A"] = QString("𐰀"); // 𐰀
    latinToOldTurkic["B"] = QString("𐰂"); // 𐰂
    latinToOldTurkic["C"] = QString("𐰜"); // 𐰜 (使用Ç/CH表示C)
    latinToOldTurkic["D"] = QString("𐰆"); // 𐰆
    latinToOldTurkic["E"] = QString("𐰁"); // 𐰁
    latinToOldTurkic["F"] = QString("𐰋"); // 𐰋 (用S近似F)
    latinToOldTurkic["G"] = QString("𐰑"); // 𐰑
    latinToOldTurkic["H"] = QString("𐰚"); // 𐰚
    latinToOldTurkic["I"] = QString("𐰍"); // 𐰍 (Y字符，用于I)
    latinToOldTurkic["J"] = QString("𐰅"); // 𐰅
    latinToOldTurkic["K"] = QString("𐰏"); // 𐰏
    latinToOldTurkic["L"] = QString("𐰈"); // 𐰈
    latinToOldTurkic["M"] = QString("𐰎"); // 𐰎
    latinToOldTurkic["N"] = QString("𐰉"); // 𐰉
    latinToOldTurkic["O"] = QString("𐰒"); // 𐰒
    latinToOldTurkic["P"] = QString("𐰃"); // 𐰃
    latinToOldTurkic["Q"] = QString("𐰐"); // 𐰐
    latinToOldTurkic["R"] = QString("𐰇"); // 𐰇
    latinToOldTurkic["S"] = QString("𐰋"); // 𐰋
    latinToOldTurkic["T"] = QString("𐰄"); // 𐰄
    latinToOldTurkic["U"] = QString("𐰓"); // 𐰓
    latinToOldTurkic["V"] = QString("𐰂"); // 𐰂 (用B近似V)
    latinToOldTurkic["W"] = QString("𐰓"); // 𐰓 (用U近似W)
    latinToOldTurkic["X"] = QString("𐰐"); // 𐰐 (用Q近似X)
    latinToOldTurkic["Y"] = QString("𐰍"); // 𐰍
    latinToOldTurkic["Z"] = QString("𐰞"); // 𐰞

    // 添加小写字母映射
    latinToOldTurkic["a"] = QString("𐰀"); // 𐰀
    latinToOldTurkic["b"] = QString("𐰂"); // 𐰂
    latinToOldTurkic["c"] = QString("𐰜"); // 𐰜
    latinToOldTurkic["d"] = QString("𐰆"); // 𐰆
    latinToOldTurkic["e"] = QString("𐰁"); // 𐰁
    latinToOldTurkic["f"] = QString("𐰋"); // 𐰋
    latinToOldTurkic["g"] = QString("𐰑"); // 𐰑
    latinToOldTurkic["h"] = QString("𐰚"); // 𐰚
    latinToOldTurkic["i"] = QString("𐰍"); // 𐰍
    latinToOldTurkic["j"] = QString("𐰅"); // 𐰅
    latinToOldTurkic["k"] = QString("𐰏"); // 𐰏
    latinToOldTurkic["l"] = QString("𐰈"); // 𐰈
    latinToOldTurkic["m"] = QString("𐰎"); // 𐰎
    latinToOldTurkic["n"] = QString("𐰉"); // 𐰉
    latinToOldTurkic["o"] = QString("𐰒"); // 𐰒
    latinToOldTurkic["p"] = QString("𐰃"); // 𐰃
    latinToOldTurkic["q"] = QString("𐰐"); // 𐰐
    latinToOldTurkic["r"] = QString("𐰇"); // 𐰇
    latinToOldTurkic["s"] = QString("𐰋"); // 𐰋
    latinToOldTurkic["t"] = QString("𐰄"); // 𐰄
    latinToOldTurkic["u"] = QString("𐰓"); // 𐰓
    latinToOldTurkic["v"] = QString("𐰂"); // 𐰂
    latinToOldTurkic["w"] = QString("𐰓"); // 𐰓
    latinToOldTurkic["x"] = QString("𐰐"); // 𐰐
    latinToOldTurkic["y"] = QString("𐰍"); // 𐰍
    latinToOldTurkic["z"] = QString("𐰞"); // 𐰞
    latinToOldTurkic["AI"] = QString("𐰀") + QString("𐰍"); // A + Y
    latinToOldTurkic["AU"] = QString("𐰀") + QString("𐰓"); // A + U
    latinToOldTurkic["OI"] = QString("𐰒") + QString("𐰍"); // O + Y
    latinToOldTurkic["OU"] = QString("𐰒") + QString("𐰓"); // O + U
    latinToOldTurkic["EI"] = QString("𐰁") + QString("𐰍"); // E + Y
    latinToOldTurkic["IU"] = QString("𐰏") + QString("𐰓"); // I/K + U


    // -------------------------
    // 拉丁字母到古匈奴文 (Old Hunnic)
    // -------------------------
    latinToOldHunnic["A"] = QString("𐌀"); // 𐌀
    latinToOldHunnic["B"] = QString("𐌁"); // 𐌁
    latinToOldHunnic["C"] = QString("𐌂"); // 𐌂
    latinToOldHunnic["D"] = QString("𐌃"); // 𐌃
    latinToOldHunnic["E"] = QString("𐌄"); // 𐌄
    latinToOldHunnic["F"] = QString("𐌅"); // 𐌅
    latinToOldHunnic["G"] = QString("𐌆"); // 𐌆
    latinToOldHunnic["H"] = QString("𐌇"); // 𐌇
    latinToOldHunnic["I"] = QString("𐌈"); // 𐌈
    latinToOldHunnic["J"] = QString("𐌉"); // 𐌉
    latinToOldHunnic["K"] = QString("𐌊"); // 𐌊
    latinToOldHunnic["L"] = QString("𐌋"); // 𐌋
    latinToOldHunnic["M"] = QString("𐌌"); // 𐌌
    latinToOldHunnic["N"] = QString("𐌍"); // 𐌍
    latinToOldHunnic["O"] = QString("𐌎"); // 𐌎
    latinToOldHunnic["P"] = QString("𐌏"); // 𐌏
    latinToOldHunnic["Q"] = QString("𐌐"); // 𐌐
    latinToOldHunnic["R"] = QString("𐌑"); // 𐌑
    latinToOldHunnic["S"] = QString("𐌒"); // 𐌒
    latinToOldHunnic["T"] = QString("𐌓"); // 𐌓
    latinToOldHunnic["U"] = QString("𐌔"); // 𐌔
    latinToOldHunnic["V"] = QString("𐌕"); // 𐌕
    latinToOldHunnic["W"] = QString("𐌖"); // 𐌖
    latinToOldHunnic["X"] = QString("𐌗"); // 𐌗
    latinToOldHunnic["Y"] = QString("𐌘"); // 𐌘
    latinToOldHunnic["Z"] = QString("𐌙"); // 𐌙
    latinToOldHunnic["a"] = QString("𐌀"); // 𐌀
    latinToOldHunnic["b"] = QString("𐌁"); // 𐌁
    latinToOldHunnic["c"] = QString("𐌂"); // 𐌂
    latinToOldHunnic["d"] = QString("𐌃"); // 𐌃
    latinToOldHunnic["e"] = QString("𐌄"); // 𐌄
    latinToOldHunnic["f"] = QString("𐌅"); // 𐌅
    latinToOldHunnic["g"] = QString("𐌆"); // 𐌆
    latinToOldHunnic["h"] = QString("𐌇"); // 𐌇
    latinToOldHunnic["i"] = QString("𐌈"); // 𐌈
    latinToOldHunnic["j"] = QString("𐌉"); // 𐌉
    latinToOldHunnic["k"] = QString("𐌊"); // 𐌊
    latinToOldHunnic["l"] = QString("𐌋"); // 𐌋
    latinToOldHunnic["m"] = QString("𐌌"); // 𐌌
    latinToOldHunnic["n"] = QString("𐌍"); // 𐌍
    latinToOldHunnic["o"] = QString("𐌎"); // 𐌎
    latinToOldHunnic["p"] = QString("𐌏"); // 𐌏
    latinToOldHunnic["q"] = QString("𐌐"); // 𐌐
    latinToOldHunnic["r"] = QString("𐌑"); // 𐌑
    latinToOldHunnic["s"] = QString("𐌒"); // 𐌒
    latinToOldHunnic["t"] = QString("𐌓"); // 𐌓
    latinToOldHunnic["u"] = QString("𐌔"); // 𐌔
    latinToOldHunnic["v"] = QString("𐌕"); // 𐌕
    latinToOldHunnic["w"] = QString("𐌖"); // 𐌖
    latinToOldHunnic["x"] = QString("𐌗"); // 𐌗
    latinToOldHunnic["y"] = QString("𐌘"); // 𐌘
    latinToOldHunnic["z"] = QString("𐌙"); // 𐌙

    // 其他多音节/组合映射
    latinToOldHunnic["AI"] = QString("𐌀") + QString("𐌘"); // A + Y
    latinToOldHunnic["AU"] = QString("𐌀") + QString("𐌔"); // A + U
    latinToOldHunnic["OI"] = QString("𐌎") + QString("𐌘"); // O + Y
    latinToOldHunnic["OU"] = QString("𐌎") + QString("𐌔"); // O + U
    latinToOldHunnic["EI"] = QString("𐌄") + QString("𐌘"); // E + Y
    latinToOldHunnic["IU"] = QString("𐌊") + QString("𐌔"); // I/K + U


    // -------------------------
    // 拉丁字母到腓尼基文 (Phoenician)
    // -------------------------
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
    latinToPhoenician["a"] = QString("𐤀"); // 𐤀
    latinToPhoenician["b"] = QString("𐤁"); // 𐤁
    latinToPhoenician["c"] = QString("𐤂"); // 𐤂
    latinToPhoenician["d"] = QString("𐤃"); // 𐤃
    latinToPhoenician["e"] = QString("𐤄"); // 𐤄
    latinToPhoenician["f"] = QString("𐤅"); // 𐤅
    latinToPhoenician["g"] = QString("𐤆"); // 𐤆
    latinToPhoenician["h"] = QString("𐤇"); // 𐤇
    latinToPhoenician["i"] = QString("𐤉"); // 𐤉
    latinToPhoenician["j"] = QString("𐤉"); // 𐤉 (与i相同)
    latinToPhoenician["k"] = QString("𐤊"); // 𐤊
    latinToPhoenician["l"] = QString("𐤋"); // 𐤋
    latinToPhoenician["m"] = QString("𐤌"); // 𐤌
    latinToPhoenician["n"] = QString("𐤍"); // 𐤍
    latinToPhoenician["o"] = QString("𐤏"); // 𐤏
    latinToPhoenician["p"] = QString("𐤐"); // 𐤐
    latinToPhoenician["q"] = QString("𐤒"); // 𐤒
    latinToPhoenician["r"] = QString("𐤓"); // 𐤓
    latinToPhoenician["s"] = QString("𐤔"); // 𐤔
    latinToPhoenician["t"] = QString("𐤕"); // 𐤕
    latinToPhoenician["u"] = QString("𐤅"); // 𐤅 (与f相同)
    latinToPhoenician["v"] = QString("𐤅"); // 𐤅 (与f相同)
    latinToPhoenician["w"] = QString("𐤅"); // 𐤅 (与f相同)
    latinToPhoenician["x"] = QString("𐤎"); // 𐤎
    latinToPhoenician["y"] = QString("𐤉"); // 𐤉 (与i相同)
    latinToPhoenician["z"] = QString("𐤆"); // 𐤆 (与g相同)

    // 其他多音节/组合映射
    latinToPhoenician["AI"] = QString("𐤀") + QString("𐤉"); // A + I
    latinToPhoenician["AU"] = QString("𐤀") + QString("𐤅"); // A + U
    latinToPhoenician["OI"] = QString("𐤏") + QString("𐤉"); // O + I
    latinToPhoenician["OU"] = QString("𐤏") + QString("𐤅"); // O + U
    latinToPhoenician["EI"] = QString("𐤄") + QString("𐤉"); // E + I
    latinToPhoenician["IU"] = QString("𐤉") + QString("𐤅"); // I + U


    // -------------------------
    // 拉丁字母到粟特文 (Sogdian)
    // -------------------------
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
    // 拉丁字母到传统匈牙利文 (Traditional Hungarian) 映射
    // -------------------------
    latinToTraditionalHungarian["A"] = QString("𐳀"); // 𐳀
    latinToTraditionalHungarian["B"] = QString("𐳁"); // 𐳁
    latinToTraditionalHungarian["C"] = QString("𐳂"); // 𐳂
    latinToTraditionalHungarian["CS"] = QString("𐳃"); // 𐳃
    latinToTraditionalHungarian["D"] = QString("𐳄"); // 𐳄
    latinToTraditionalHungarian["E"] = QString("𐳅"); // 𐳅
    latinToTraditionalHungarian["É"] = QString("𐳆"); // 𐳆
    latinToTraditionalHungarian["F"] = QString("𐳇"); // 𐳇
    latinToTraditionalHungarian["G"] = QString("𐳈"); // 𐳈
    latinToTraditionalHungarian["GY"] = QString("𐳉"); // 𐳉
    latinToTraditionalHungarian["H"] = QString("𐳊"); // 𐳊
    latinToTraditionalHungarian["I"] = QString("𐳋"); // 𐳋
    latinToTraditionalHungarian["Í"] = QString("𐳌"); // 𐳌
    latinToTraditionalHungarian["J"] = QString("𐳍"); // 𐳍
    latinToTraditionalHungarian["K"] = QString("𐳎"); // 𐳎
    latinToTraditionalHungarian["L"] = QString("𐳏"); // 𐳏
    latinToTraditionalHungarian["LY"] = QString("𐳐"); // 𐳐
    latinToTraditionalHungarian["M"] = QString("𐳑"); // 𐳑
    latinToTraditionalHungarian["N"] = QString("𐳒"); // 𐳒
    latinToTraditionalHungarian["NY"] = QString("𐳓"); // 𐳓
    latinToTraditionalHungarian["O"] = QString("𐳔"); // 𐳔
    latinToTraditionalHungarian["Ó"] = QString("𐳕"); // 𐳕
    latinToTraditionalHungarian["Ö"] = QString("𐳖"); // 𐳖
    latinToTraditionalHungarian["Ő"] = QString("𐳗"); // 𐳗
    latinToTraditionalHungarian["P"] = QString("𐳘"); // 𐳘
    latinToTraditionalHungarian["Q"] = QString("𐳙"); // 𐳙
    latinToTraditionalHungarian["R"] = QString("𐳚"); // 𐳚
    latinToTraditionalHungarian["S"] = QString("𐳛"); // 𐳛
    latinToTraditionalHungarian["SZ"] = QString("𐳜"); // 𐳜
    latinToTraditionalHungarian["T"] = QString("𐳝"); // 𐳝
    latinToTraditionalHungarian["TY"] = QString("𐳞"); // 𐳞
    latinToTraditionalHungarian["U"] = QString("𐳟"); // 𐳟
    latinToTraditionalHungarian["Ú"] = QString("𐳠"); // 𐳠
    latinToTraditionalHungarian["Ü"] = QString("𐳡"); // 𐳡
    latinToTraditionalHungarian["Ű"] = QString("𐳢"); // 𐳢
    latinToTraditionalHungarian["V"] = QString("𐳣"); // 𐳣
    latinToTraditionalHungarian["W"] = QString("𐳤"); // 𐳤
    latinToTraditionalHungarian["X"] = QString("𐳥"); // 𐳥
    latinToTraditionalHungarian["Y"] = QString("𐳦"); // 𐳦
    latinToTraditionalHungarian["Z"] = QString("𐳧"); // 𐳧
    latinToTraditionalHungarian["ZS"] = QString("𐳨"); // 𐳨

    // 小写字母映射
    latinToTraditionalHungarian["a"] = QString("𐳩"); // 𐳩
    latinToTraditionalHungarian["b"] = QString("𐳪"); // 𐳪
    latinToTraditionalHungarian["c"] = QString("𐳫"); // 𐳫
    latinToTraditionalHungarian["cs"] = QString("𐳬"); // 𐳬
    latinToTraditionalHungarian["d"] = QString("𐳭"); // 𐳭
    latinToTraditionalHungarian["e"] = QString("𐳮"); // 𐳮
    latinToTraditionalHungarian["é"] = QString("𐳯"); // 𐳯
    latinToTraditionalHungarian["f"] = QString("𐳰"); // 𐳰
    latinToTraditionalHungarian["g"] = QString("𐳱"); // 𐳱
    latinToTraditionalHungarian["gy"] = QString("𐳲"); // 𐳲
    latinToTraditionalHungarian["h"] = QString("𐳳"); // 𐳳
    latinToTraditionalHungarian["i"] = QString("𐳴"); // 𐳴
    latinToTraditionalHungarian["í"] = QString("𐳵"); // 𐳵
    latinToTraditionalHungarian["j"] = QString("𐳶"); // 𐳶
    latinToTraditionalHungarian["k"] = QString("𐳷"); // 𐳷
    latinToTraditionalHungarian["l"] = QString("𐳸"); // 𐳸
    latinToTraditionalHungarian["ly"] = QString("𐳹"); // 𐳹
    latinToTraditionalHungarian["m"] = QString("𐳺"); // 𐳺
    latinToTraditionalHungarian["n"] = QString("𐳻"); // 𐳻
    latinToTraditionalHungarian["ny"] = QString("𐳼"); // 𐳼
    latinToTraditionalHungarian["o"] = QString("𐳽"); // 𐳽
    latinToTraditionalHungarian["ó"] = QString("𐳾"); // 𐳾
    latinToTraditionalHungarian["ö"] = QString("𐳿"); // 𐳿
    latinToTraditionalHungarian["ő"] = QString("𐴀"); // 𐴀
    latinToTraditionalHungarian["p"] = QString("𐴁"); // 𐴁
    latinToTraditionalHungarian["q"] = QString("𐴂"); // 𐴂
    latinToTraditionalHungarian["r"] = QString("𐴃"); // 𐴃
    latinToTraditionalHungarian["s"] = QString("𐴄"); // 𐴄
    latinToTraditionalHungarian["sz"] = QString("𐴅"); // 𐴅
    latinToTraditionalHungarian["t"] = QString("𐴆"); // 𐴆
    latinToTraditionalHungarian["ty"] = QString("𐴇"); // 𐴇
    latinToTraditionalHungarian["u"] = QString("𐴈"); // 𐴈
    latinToTraditionalHungarian["ú"] = QString("𐴉"); // 𐴉
    latinToTraditionalHungarian["ü"] = QString("𐴊"); // 𐴊
    latinToTraditionalHungarian["ű"] = QString("𐴋"); // 𐴋
    latinToTraditionalHungarian["v"] = QString("𐴌"); // 𐴌
    latinToTraditionalHungarian["w"] = QString("𐴍"); // 𐴍
    latinToTraditionalHungarian["x"] = QString("𐴎"); // 𐴎
    latinToTraditionalHungarian["y"] = QString("𐴏"); // 𐴏
    latinToTraditionalHungarian["z"] = QString("𐴐"); // 𐴐
    latinToTraditionalHungarian["zs"] = QString("𐴑"); // 𐴑





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
    createReverseMap(latinToOldTurkic, oldTurkicToLatin);
    createReverseMap(latinToManchu, manchuToLatin);
    createReverseMap(latinToInuktitut, inuktitutToLatin);
    createReverseMap(latinToOldHunnic, oldHunnicToLatin);
    createReverseMap(latinToPhoenician, phoenicianToLatin);
    createReverseMap(latinToTraditionalHungarian, traditionalHungarianToLatin);
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
        case OldHunnic: currentMap = &latinToOldHunnic; break;
        case Phoenician: currentMap = &latinToPhoenician; break;
        case Sogdian: currentMap = &latinToSogdian; break;
        case TraditionalHungarian: currentMap = &latinToTraditionalHungarian; break;
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
        case OldUyghur: currentMap = &oldUyghurToLatin; break; //new
        case Manchu: currentMap = &manchuToLatin; break; //new
        case Inuktitut: currentMap = &inuktitutToLatin; break; //new
        case OldTurkic: currentMap = &oldTurkicToLatin; break; //new
        case OldHunnic: currentMap = &oldHunnicToLatin; break; //new
        case Phoenician: currentMap = &phoenicianToLatin; break; //new
        case Sogdian: currentMap = &sogdianToLatin; break; //new
        case TraditionalHungarian: currentMap = &traditionalHungarianToLatin; break; //new
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


// 修改convertWithMap函数，将QMap替换为QHash
QString LetterConverter::convertWithMap(const QString &text, const QHash<QString, QString> &map)
{
    QString result;
    int i = 0;
    const int length = text.length();

    while (i < length) {
        bool found = false;

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


// 希伯来字母转换逻辑
QString LetterConverter::convertToHebrew(const QString &text)
{
    QString result;
    for (int i = 0; i < text.length(); i++) {
        QChar c = text[i];
        QString current = QString(c).toUpper();
        bool isLower = c.isLower();

        // 处理双字符组合
        if (i < text.length() - 1) {
            QString pair = text.mid(i, 2).toUpper();
            if (latinToHebrew.contains(pair)) {
                QString converted = latinToHebrew[pair];
                result += converted;
                i++;
                continue;
            }
        }

        // 处理特殊规则：Bet/Vet
        if (current == "B") {
            // 检查是否在词首或前一个字符是元音
            if (i == 0 || isVowel(text[i-1])) {
                result += isLower ? QString(QChar(0x05D1)) + QString(QChar(0x05BC)) : QString(QChar(0x05D1)) + QString(QChar(0x05BC)); // בּ (带dagesh的Bet)
            } else {
                result += isLower ? QString(QChar(0x05D1)) : QString(QChar(0x05D1)); // ב (Vet)
            }
            continue;
        }

        // 处理特殊规则：Kaf/Chaf
        if (current == "K") {
            // 检查是否在词首或前一个字符是元音
            if (i == 0 || isVowel(text[i-1])) {
                result += isLower ? QString(QChar(0x05DB)) + QString(QChar(0x05BC)) : QString(QChar(0x05DB)) + QString(QChar(0x05BC)); // כּ (带dagesh的Kaf)
            } else {
                result += isLower ? QString(QChar(0x05DB)) : QString(QChar(0x05DB)); // כ (Chaf)
            }
            continue;
        }

        // 处理特殊规则：Pe/Phe
        if (current == "P") {
            // 检查是否在词首或前一个字符是元音
            if (i == 0 || isVowel(text[i-1])) {
                result += isLower ? QString(QChar(0x05E4)) + QString(QChar(0x05BC)) : QString(QChar(0x05E4)) + QString(QChar(0x05BC)); // פּ (带dagesh的Pe)
            } else {
                result += isLower ? QString(QChar(0x05E4)) : QString(QChar(0x05E4)); // פ (Phe)
            }
            continue;
        }

        // 处理特殊规则：Shin/Sin
        if (current == "S" && i < text.length() - 1 && text[i+1].toUpper() == 'H') {
            // 检查是否有Sin点标记
            if (i > 0 && text[i-1].toLower() == 's') {
                result += isLower ? QString(QChar(0x05E9)) + QString(QChar(0x05C1)) : QString(QChar(0x05E9)) + QString(QChar(0x05C1)); // שׂ (Sin)
            } else {
                result += isLower ? QString(QChar(0x05E9)) + QString(QChar(0x05C2)) : QString(QChar(0x05E9)) + QString(QChar(0x05C2)); // שׁ (Shin)
            }
            i++; // 跳过 H
            continue;
        }

        // 处理特殊规则：J (像jump中的/dʒ/音)
        if (current == "J") {
            // 使用 Gimel + 撇号 表示 /dʒ/ 音
            result += isLower ? QString(QChar(0x05D2)) + "'" : QString(QChar(0x05D2)) + "'"; // ג' (Gimel + 撇号)
            continue;
        }


        // 处理特殊规则：X (对应"西"音)
        if (current == "X") {
            // 检查后面是否跟着特定音节组合
            if (i < text.length() - 1) {
                QString nextTwo = "";
                if (i < text.length() - 2) {
                    nextTwo = text.mid(i+1, 2).toLower();
                }
                QString nextOne = text.mid(i+1, 1).toLower();

                // 检查是否跟着 in, ing, ie, ue, iang, iong, ian, iu, iao
                if (nextTwo == "in" || nextTwo == "ing" || nextTwo == "ie" ||
                    nextTwo == "ue" || nextTwo == "ia" || nextTwo == "io" ||
                    nextTwo == "iu" || nextTwo == "ia" || nextOne == "i") {
                    // 使用 Shin 表示"西"音
                    result += isLower ? QString(QChar(0x05E9)) + QString(QChar(0x05C2)) : QString(QChar(0x05E9)) + QString(QChar(0x05C2)); // שׁ (Shin)
                    continue;
                }
            }
    }

        // 处理特殊规则：Q (根据后面是否跟着i决定发音)
        if (current == "Q") {
            // 检查后面是否跟着i
            if (i < text.length() - 1 && text[i+1].toUpper() == 'I') {
                // 发"其"的音，使用 Qof + Shuruk
                result += isLower ? QString(QChar(0x05E7)) + QString(QChar(0x05BB)) : QString(QChar(0x05E7)) + QString(QChar(0x05BB)); // קוּ (Qof + Shuruk)
            } else {
                // 发question中q的音，使用 Qof
                result += isLower ? QString(QChar(0x05E7)) : QString(QChar(0x05E7)); // ק (Qof)
            }
            continue;
        }


        // 处理特殊规则：G (如果前缀为in，发鼻音效果)
        if (current == "G") {
            // 检查前缀是否为in
            if (i >= 2 && text[i-2].toLower() == 'i' && text[i-1].toLower() == 'n') {
                // 发鼻音效果，使用 Gimel + Rafeh
                result += isLower ? QString(QChar(0x05D2)) + QString(QChar(0x05BF)) : QString(QChar(0x05D2)) + QString(QChar(0x05BF)); // גֿ (Gimel + Rafeh)
            } else {
                // 默认情况，使用原来的映射
                result += isLower ? QString(QChar(0x05D2)) : QString(QChar(0x05D2)); // ג (Gimel)
            }
            continue;
        }



        // 处理元音
        if (isVowel(c)) {
            // 检查前一个字符是否是辅音
            if (i > 0 && !isVowel(text[i-1])) {
                // 添加相应的元音符号
                QString vowelSymbol = getHebrewVowelSymbol(c);
                if (!vowelSymbol.isEmpty()) {
                    result += vowelSymbol;
                    continue;
                }
            }
        }

        // 默认映射
        if (latinToHebrew.contains(current)) {
            QString converted = latinToHebrew[current];
            result += converted;
        } else {
            result += c;
        }
    }
    return result;
}

QString LetterConverter::convertFromHebrew(const QString &text)
{
    // 使用反向映射表进行转换
    return convertWithMap(text, hebrewToLatin);
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
