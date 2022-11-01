#include "convert.h"
#include <QtCore>
#include <QRegExp>
#include <QMessageBox>

void experimental() {

    QString f1 = "Experimental.txt";
    QString f2 = "BibleNames.txt";
    QFile File1(f1);  // This file is for writing results.
    QFile File2(f2);  // This file contains data and will be opened only for reading.
    File1.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&File1);
    out.setCodec("UTF-8");
    File2.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&File2);
    in.setCodec("UTF-8");

    QString str;
    while (!File2.atEnd()) {
        str = in.readLine();
        out << str << endl;
    }

    File1.flush();
    File1.close();
    File2.close();

}

void converter_from_original (QString lang, QString addorig) {
    QString f1 = "";
    if (addorig == "True") {
        if (lang == "Ingush") {
            f1 = "BibleNamesIngush.txt";
        }
        else if (lang == "Avar") {
            f1 = "BibleNamesAvar.txt";
        }
        else if (lang == "Chechen") {
            f1 = "BibleNamesChechen.txt";
        }
    }
    else if (addorig == "False") {
        if (lang == "Ingush") {
            f1 = "BibleNamesIngushOnly.txt";
        }
        else if (lang == "Avar") {
            f1 = "BibleNamesAvarOnly.txt";
        }
        else if (lang == "Chechen") {
            f1 = "BibleNamesChechenOnly.txt";
        }
    }
    QString f2 = "BibleNames.txt";
    QFile File1(f1);  // This file is for writing results.
    QFile File2(f2);  // This file contains data and will be opened only for reading.
    File1.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&File1);
    out.setCodec("UTF-8");
    File2.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&File2);
    in.setCodec("UTF-8");

    //if ((File2.open(QIODevice::ReadOnly)) || (File1.open(QIODevice::WriteOnly))) {
    QString str;
    while (!File2.atEnd()) {
        str = in.readLine();
        QString txtorig = str;

        // Greek -> Ingush/Avar/Chechen

        // Greek / Erasmian
        // Greek aspirations and stresses (Erasmian)
        QRegExp rgx1("(᾿|῍|῎|῏|`|´|῀|᾽|῭|΅|῁|ͺ)");
        str.replace(rgx1, "");
        if ((lang == "Ingush") || (lang == "Chechen")) {
            QRegExp rgx2("(῾|῝|῞|῟)");
            str.replace(rgx2, "хӀ");          // In Avar, "хӀ" -> "гь"
        }
        else if (lang == "Avar") {
            QRegExp rgx3("(῾|῝|῞|῟)");
            str.replace(rgx3, "гь");
        }

        // Greek diphthongs (Erasmian)
        QRegExp rgx4("(Α|Ἀ|Ἂ|Ἄ|Ἆ)ι");
        str.replace(rgx4, "А");        // iota subscriptum
        QRegExp rgx5("(Ἁ|Ἃ|Ἅ|Ἇ)ι");
        str.replace(rgx5, "ХӀа");
        QRegExp rgx6("(Η|Ἠ|Ἢ|Ἤ|Ἦ)ι");
        str.replace(rgx6, "Э");
        QRegExp rgx7("(Ἡ|Ἣ|Ἥ|Ἧ)ι");
        str.replace(rgx7, "ХӀе");
        QRegExp rgx8("(Ω|Ὠ|Ὢ|Ὤ|Ὦ)ι");
        str.replace(rgx8, "О");
        QRegExp rgx9("(Ὡ|Ὣ|Ὥ|Ὧ)ι");
        str.replace(rgx9, "ХӀо");
        QRegExp rgx10("Α(υ|ὐ|ὒ|ὔ|ὖ|ύ)");
        str.replace(rgx10, "Ав");
        QRegExp rgx11("Α(ὑ|ὓ|ὕ|ὗ|ύ)");
        str.replace(rgx11, "ХӀав");
        QRegExp rgx12("α(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ύ)");
        str.replace(rgx12, "ав");
        QRegExp rgx13("α(ὑ|ὓ|ὕ|ὗ|ύ)");
        str.replace(rgx13, "хӀав");
        QRegExp rgx14("Ε(υ|ὐ|ὒ|ὔ|ὖ|ύ)");
        str.replace(rgx14, "Эв");
        QRegExp rgx15("Ε(ὑ|ὓ|ὕ|ὗ|ύ)");
        str.replace(rgx15, "ХӀев");
        QRegExp rgx16("\\Bε(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ύ)");
        str.replace(rgx16, "эв");
        QRegExp rgx17("\\Bε(ὑ|ὓ|ὕ|ὗ|ύ)");
        str.replace(rgx17, "хӀев");
        QRegExp rgx18("ε(υ|ὺ|ύ|ῦ|ύ)");
        str.replace(rgx18, "ев");
        QRegExp rgx19("Η(υ|ὐ|ὒ|ὔ|ὖ|ύ)");
        str.replace(rgx19, "Эв");
        QRegExp rgx20("Η(ὑ|ὓ|ὕ|ὗ|ύ)");
        str.replace(rgx20, "ХӀев");
        QRegExp rgx21("\\Bη(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ύ)");
        str.replace(rgx21, "эв");
        QRegExp rgx22("\\Bη(ὑ|ὓ|ὕ|ὗ|ύ)");
        str.replace(rgx22, "хӀев");
        QRegExp rgx23("η(υ|ὺ|ύ|ῦ|ύ)");
        str.replace(rgx23, "ев");
        QRegExp rgx24("Ο(υ|ὐ|ὒ|ὔ|ὖ|ύ)");
        str.replace(rgx24, "У");
        QRegExp rgx25("Ο(ὑ|ὓ|ὕ|ὗ|ύ)");
        str.replace(rgx25, "ХӀу");
        QRegExp rgx26("ο(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ύ)");
        str.replace(rgx26, "у");
        QRegExp rgx27("ο(ὑ|ὓ|ὕ|ὗ|ύ)");
        str.replace(rgx27, "хӀу");
        QRegExp rgx28("Α(ι|ἰ|ἲ|ἴ|ἶ|ί)");
        str.replace(rgx28, "Ай");
        QRegExp rgx29("Α(ἱ|ἳ|ἷ|ἷ|ί)");
        str.replace(rgx29, "ХӀай");
        QRegExp rgx30("α(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ί)");
        str.replace(rgx30, "ай");
        QRegExp rgx31("α(ἱ|ἳ|ἷ|ἷ|ί)");
        str.replace(rgx31, "хӀай");
        QRegExp rgx32("Ε(ι|ἰ|ἲ|ἴ|ἶ|ί)");
        str.replace(rgx32, "Эй");
        QRegExp rgx33("Ε(ἱ|ἳ|ἵ|ἷ|ί)");
        str.replace(rgx33, "ХӀей");
        QRegExp rgx34("\\Bε(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ί)");
        str.replace(rgx34, "эй");
        QRegExp rgx35("\\Bε(ἱ|ἳ|ἵ|ἷ|ί)");
        str.replace(rgx35, "хӀей");
        QRegExp rgx36("ε(ι|ὶ|ί|ῖ|ί)");
        str.replace(rgx36, "ей");
        QRegExp rgx37("Ο(ι|ἰ|ἲ|ἴ|ἶ|ί)");
        str.replace(rgx37, "Ой");
        QRegExp rgx38("Ο(ἱ|ἳ|ἵ|ἷ|ί)");
        str.replace(rgx38, "ХӀой");
        QRegExp rgx39("ο(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ί)");
        str.replace(rgx39, "ой");
        QRegExp rgx40("ο(ἱ|ἵ|ἳ|ἷ|ί)");
        str.replace(rgx40, "хӀой");
        if ((lang == "Ingush") || (lang == "Avar")) {
            QRegExp rgx41("Υ(ι|ἰ|ἲ|ἴ|ἶ|ί)");
            str.replace(rgx41, "Уй");       //in Chechen, уьй
            QRegExp rgx42("Υ(ἱ|ἳ|ἵ|ἷ|ί)");
            str.replace(rgx42, "ХӀуй");
            QRegExp rgx43("υ(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ί)");
            str.replace(rgx43, "уй");
            QRegExp rgx44("υ(ἱ|ἵ|ἳ|ἷ|ί)");
            str.replace(rgx44, "хӀуй");
        }
        else if (lang == "Chechen") {
            QRegExp rgx45("Υ(ι|ἰ|ἲ|ἴ|ἶ|ί)");
            str.replace(rgx45, "Уьй");
            QRegExp rgx46("Υ(ἱ|ἳ|ἵ|ἷ|ί)");
            str.replace(rgx46, "ХӀуьй");
            QRegExp rgx47("υ(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ί)");
            str.replace(rgx47, "уьй");
            QRegExp rgx48("υ(ἱ|ἵ|ἳ|ἷ|ί)");
            str.replace(rgx48, "хӀуьй");
        }
        if (lang == "Avar") {
            str.replace("ХӀ", "Гь");
            str.replace("хӀ", "гь");
        }

        // Greek vowels (Erasmian)
        QRegExp rgx49("(Α|Ἀ|Ἂ|Ἄ|Ἆ)");
        str.replace(rgx49, "А");
        QRegExp rgx50("(Ἁ|Ἃ|Ἅ|Ἇ)");
        str.replace(rgx50, "ХӀа");
        QRegExp rgx51("(α|ἀ|ἂ|ἄ|ἆ|ὰ|ά|ᾶ|ᾀ|ᾂ|ᾄ|ᾆ|ᾳ|ᾲ|ᾴ|ᾷ|ά)");
        str.replace(rgx51, "а");
        QRegExp rgx52("(ἁ|ἃ|ἅ|ἇ|ᾁ|ᾃ|ᾅ|ᾇ)");
        str.replace(rgx52, "хӀа");
        QRegExp rgx53("(Ε|Ἐ|Ἒ|Ἔ)");
        str.replace(rgx53, "Э");
        QRegExp rgx54("(Ἑ|Ἓ|Ἕ)");
        str.replace(rgx54, "ХӀе");
        QRegExp rgx55("\\B(ε|ἐ|ἒ|ἔ|έ)");
        str.replace(rgx55, "э");
        QRegExp rgx56("\\B(ἑ|ἓ|ἕ)");
        str.replace(rgx56, "хӀе");
        QRegExp rgx57("(ε|ὲ|έ|έ)");
        str.replace(rgx57, "е");
        QRegExp rgx58("(Η|Ἠ|Ἢ|Ἤ|Ἦ)");
        str.replace(rgx58, "Э");
        QRegExp rgx59("(Ἡ|Ἣ|Ἥ|Ἧ)");
        str.replace(rgx59, "ХӀе");
        QRegExp rgx60("\\B(η|ἠ|ἢ|ἤ|ἦ|ᾐ|ᾒ|ᾔ|ᾖ|ή)");
        str.replace(rgx60, "э");
        QRegExp rgx61("\\B(ἡ|ἣ|ἥ|ἧ|ᾑ|ᾓ|ᾕ|ᾗ)");
        str.replace(rgx61, "хӀе");
        QRegExp rgx62("(η|ὴ|ή|ῆ|ῃ|ῂ|ῄ|ῇ|ή)");
        str.replace(rgx62, "е");
        QRegExp rgx63("(Ι|Ἰ|Ἲ|Ἴ|Ἶ|Ἶ)");
        str.replace(rgx63, "И");
        QRegExp rgx64("(Ἱ|Ἳ|Ἵ|Ἷ|Ἷ)");
        str.replace(rgx64, "ХӀи");
        QRegExp rgx65("(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ϊ|ῒ|ΐ|ῗ|ἶ|ῖ|ί|ΐ)");
        str.replace(rgx65, "и");
        QRegExp rgx66("(ἱ|ἳ|ἷ|ἷ|ἵ)");
        str.replace(rgx66, "хӀи");
        QRegExp rgx67("(Ο|Ὀ|Ὂ|Ὄ)");
        str.replace(rgx67, "О");
        QRegExp rgx68("(Ὁ|Ὃ|Ὅ)");
        str.replace(rgx68, "ХӀо");
        QRegExp rgx69("(ο|ὀ|ὂ|ὄ|ὸ|ό|ό)");
        str.replace(rgx69, "о");
        QRegExp rgx70("(ὁ|ὃ|ὅ)");
        str.replace(rgx70, "хӀо");
        if ((lang == "Ingush") || ("Avar")) {
            QRegExp rgx71("(Υ|Ὑ|Ὓ|Ὕ|Ὗ)");
            str.replace(rgx71, "ХӀу");
            QRegExp rgx72("(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ϋ|ῢ|ΰ|ῧ|ύ)");
            str.replace(rgx72, "у");  // in Chechen, уь
            QRegExp rgx73("(ὑ|ὓ|ὕ|ὗ)");
            str.replace(rgx73, "хӀу");
        }
        else if (lang == "Chechen") {
            QRegExp rgx74("(Υ|Ὑ|Ὓ|Ὕ|Ὗ)");
            str.replace(rgx74, "ХӀьу");
            QRegExp rgx75("(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ϋ|ῢ|ΰ|ῧ|ύ)");
            str.replace(rgx75, "уь");  // in Chechen, уь
            QRegExp rgx76("(ὑ|ὓ|ὕ|ὗ)");
            str.replace(rgx76, "хӀуь");
        }
        QRegExp rgx77("(Ω|Ὠ|Ὢ|Ὤ|Ὦ)");
        str.replace(rgx77, "О");
        QRegExp rgx78("(Ὡ|Ὣ|Ὥ|Ὧ)");
        str.replace(rgx78, "ХӀо");
        QRegExp rgx79("(ω|ὠ|ὢ|ὤ|ὦ|ὼ|ώ|ῶ|ᾠ|ᾢ|ᾤ|ᾦ|ῳ|ῲ|ῴ|ῷ|ώ)");
        str.replace(rgx79, "о");
        QRegExp rgx80("(ὡ|ὣ|ὥ|ὧ|ᾡ|ᾣ|ᾥ|ᾧ)");
        str.replace(rgx80, "хӀо");
        if (lang == "Avar") {
            str.replace("ХӀ", "Гь");
            str.replace("хӀ", "гь");
        }

        // Greek consonants (Erasmian)
        str.replace("Β", "Б");
        str.replace("β", "б");
        str.replace("Γ", "Г");
        str.replace("γγ", "нг");
        str.replace("γκ", "нк");
        str.replace("γξ", "нкс");
        str.replace("γχ", "нх");
        str.replace("γ", "г");
        str.replace("Δ", "Д");
        str.replace("δ", "д");
        str.replace("Ζ", "Дз");
        str.replace("ζ", "дз");
        if ((lang == "Ingush") || (lang == "Chechen")) {
            str.replace("Θ", "ТхӀ");
            str.replace("θ", "тхӀ");
        }
        else if (lang == "Avar") {
            str.replace("Θ", "Тгь");
            str.replace("θ", "тгь");
        }
        str.replace("Κ", "К");
        str.replace("κ", "к");
        str.replace("Λ", "Л");
        str.replace("λ", "л");
        str.replace("Μ", "М");
        str.replace("μ", "м");
        str.replace("Ν", "Н");
        str.replace("ν", "н");
        str.replace("Ξ", "Кс");
        str.replace("ξ", "кс");
        str.replace("Π", "П");
        str.replace("π", "п");
        str.replace("Ρ", "Р");
        QRegExp rgx81("(Ρ|Ῥ)");
        str.replace(rgx81, "Р");
        QRegExp rgx82("(ρ|ῤ|ῥ)");
        str.replace(rgx82, "р");
        str.replace("Σ", "С");
        QRegExp rgx83("(σ|ς)");
        str.replace(rgx83, "с");
        str.replace("Τ", "Т");
        str.replace("τ", "т");
        str.replace("Φ", "Ф");
        str.replace("φ", "ф");
        str.replace("Χ", "Х");
        str.replace("χ", "х");
        str.replace("Ψ", "Пс");
        str.replace("ψ", "пс");

        // correction of Cyrillic text
        QRegExp rgx84("\\BЕ");
        str.replace(rgx84, "Э");
        QRegExp rgx85("\\Bе");
        str.replace(rgx85, "э");
        QRegExp rgx86("(А|а|Э|е|э|И|и|О|о|У|у)е");
        str.replace(rgx86, "\\1э");
        if (lang == "Ingush") {
            QRegExp rgx87("(О|о)а");
            str.replace(rgx87, "\\1ъа");  // In Chechen and Avar, no need of this line.
        }
        if ((lang == "Ingush") || (lang == "Chechen")) {
            QRegExp rgx88("(Т|т)хӀтхӀ");
            str.replace(rgx88, "\\1тхӀ");
        }
        else if (lang == "Avar") {
            QRegExp rgx89("(Т|т)гьтгь");
            str.replace(rgx89, "\\1тгь");
        }

        QString txtErasm = str;
        str = txtorig;

        // Greek aspirations and stresses (Reuchlin's)
        QRegExp rgx90("(᾿|῍|῎|῏|`|´|῀|᾽|῭|΅|῁|ͺ|῾|῝|῞|῟)");
        str.replace(rgx90, "");

        // Greek diphthongs (Reuchlin"s)
        QRegExp rgx91("(Α|Ἀ|Ἂ|Ἄ|Ἆ|Ἁ|Ἃ|Ἅ|Ἇ)ι");
        str.replace(rgx91, "А");        // iota subscriptum
        QRegExp rgx92("(Η|Ἠ|Ἢ|Ἤ|Ἦ|Ἡ|Ἣ|Ἥ|Ἧ)ι");
        str.replace(rgx92, "Э");
        QRegExp rgx93("(Ω|Ὠ|Ὢ|Ὤ|Ὦ|Ὡ|Ὣ|Ὥ|Ὧ)ι");
        str.replace(rgx93, "О");

        // before voiceless consonants af
        QRegExp rgx94("Α(υ|ὐ|ὒ|ὔ|ὖ|ὑ|ὓ|ὕ|ὗ|ύ)(Θ|Φ|κ|ξ|π|σ|ς|τ|χ|ψ)");
        str.replace(rgx94, "Аф\\2");
        QRegExp rgx95("α(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ὑ|ὓ|ὕ|ὗ|ύ)(Θ|Φ|κ|ξ|π|σ|ς|τ|χ|ψ)");
        str.replace(rgx95, "аф\\2");
        // before voiced consonants and vowels av
        QRegExp rgx96("Α(υ|ὐ|ὒ|ὔ|ὖ|ὑ|ὓ|ὕ|ὗ|ύ)");
        str.replace(rgx96, "Ав");
        QRegExp rgx97("α(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ὑ|ὓ|ὕ|ὗ|ύ)");
        str.replace(rgx97, "ав");
        // before voiceless consonants ef
        QRegExp rgx98("Ε(υ|ὐ|ὒ|ὔ|ὖ|ὑ|ὓ|ὕ|ὗ|ύ)(Θ|Φ|κ|ξ|π|σ|ς|τ|χ|ψ)");
        str.replace(rgx98, "Эф\\2");
        QRegExp rgx99("\\Bε(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ὑ|ὓ|ὕ|ὗ|ύ)(Θ|Φ|κ|ξ|π|σ|ς|τ|χ|ψ)");
        str.replace(rgx99, "эф\\2");
        QRegExp rgx100("ε(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ὑ|ὓ|ὕ|ὗ|ύ)(Θ|Φ|κ|ξ|π|σ|ς|τ|χ|ψ)");
        str.replace(rgx100, "еф\\2");
        // before voiced conconants and vowels ev
        QRegExp rgx101("Ε(υ|ὐ|ὒ|ὔ|ὖ|ὑ|ὓ|ὕ|ὗ|ύ)");
        str.replace(rgx101, "Эв");
        QRegExp rgx102("\\Bε(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ὑ|ὓ|ὕ|ὗ|ύ)");
        str.replace(rgx102, "эв");
        QRegExp rgx103("ε(υ|ὺ|ύ|ῦ|ύ)");
        str.replace(rgx103, "ев");
        // before voiceless consonants if
        QRegExp rgx104("Η(υ|ὐ|ὒ|ὔ|ὖ|ὑ|ὓ|ὕ|ὗ|ύ)(Θ|Φ|κ|ξ|π|σ|ς|τ|χ|ψ)");
        str.replace(rgx104, "Иф\\2");
        QRegExp rgx105("η(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ὑ|ὓ|ὕ|ὗ|ύ)(Θ|Φ|κ|ξ|π|σ|ς|τ|χ|ψ)");
        str.replace(rgx105, "иф\\2");
        // before voiced consonants and vowels iv
        QRegExp rgx106("Η(υ|ὐ|ὒ|ὔ|ὖ|ὑ|ὓ|ὕ|ὗ|ύ)");
        str.replace(rgx106, "Ив");
        QRegExp rgx107("η(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ὑ|ὓ|ὕ|ὗ|ύ)");
        str.replace(rgx107, "ив");
        QRegExp rgx108("Ο(υ|ὐ|ὒ|ὔ|ὖ|ὑ|ὓ|ὕ|ὗ|ύ)");
        str.replace(rgx108, "У");
        QRegExp rgx109("ο(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ὑ|ὓ|ὕ|ὗ|ύ)");
        str.replace(rgx109, "у");
        QRegExp rgx110("Α(ι|ἰ|ἲ|ἴ|ἶ|ἱ|ἳ|ἷ|ἷ|ί)");
        str.replace(rgx110, "Э");
        QRegExp rgx111("\\Bα(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ἱ|ἳ|ἷ|ἷ|ί)");
        str.replace(rgx111, "э");
        QRegExp rgx112("α(ι|ὶ|ί|ῖ|ί)");
        str.replace(rgx112, "е");
        QRegExp rgx113("Ε(ι|ἰ|ἲ|ἴ|ἶ|ἱ|ἳ|ἵ|ἷ|ί)");
        str.replace(rgx113, "И");
        QRegExp rgx114("ε(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ἱ|ἳ|ἵ|ἷ|ί)");
        str.replace(rgx114, "и");
        QRegExp rgx115("Ο(ι|ἰ|ἲ|ἴ|ἶ|ἱ|ἳ|ἵ|ἷ|ί)");
        str.replace(rgx115, "И");
        QRegExp rgx116("ο(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ἱ|ἵ|ἳ|ἷ|ί)");
        str.replace(rgx116, "и");
        QRegExp rgx117("Υ(ι|ἰ|ἲ|ἴ|ἶ|ἱ|ἳ|ἵ|ἷ|ί)");
        str.replace(rgx117, "и");
        QRegExp rgx118("υ(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ἱ|ἵ|ἳ|ἷ|ί)");
        str.replace(rgx118, "и");

        // Greek vowels (Reuchlin's)
        QRegExp rgx119("(Α|Ἀ|Ἂ|Ἄ|Ἆ|Ἁ|Ἃ|Ἅ|Ἇ)");
        str.replace(rgx119, "А");
        QRegExp rgx120("(α|ἀ|ἂ|ἄ|ἆ|ἁ|ἃ|ἅ|ἇ|ὰ|ά|ᾶ|ᾀ|ᾂ|ᾄ|ᾆ|ᾳ|ᾲ|ᾴ|ᾷ|ᾁ|ᾃ|ᾅ|ᾇ|ά)");
        str.replace(rgx120, "а");
        QRegExp rgx121("(Ε|Ἐ|Ἒ|Ἔ|Ἑ|Ἓ|Ἕ)");
        str.replace(rgx121, "Э");
        QRegExp rgx122("\\B(ε|ἐ|ἒ|ἔ|ἑ|ἓ|ἕ|έ)");
        str.replace(rgx122, "э");
        QRegExp rgx123("(ε|ὲ|έ|έ)");
        str.replace(rgx123, "е");
        QRegExp rgx124("(Η|Ἠ|Ἢ|Ἤ|Ἦ|Ἡ|Ἣ|Ἥ|Ἧ)");
        str.replace(rgx124, "И");
        QRegExp rgx125("(η|ἠ|ἢ|ἤ|ἦ|ἡ|ἣ|ἥ|ἧ|ὴ|ή|ῆ|ᾐ|ᾒ|ᾔ|ᾖ|ᾑ|ᾓ|ᾕ|ᾗ|ῃ|ῂ|ῄ|ῇ|ή)");
        str.replace(rgx125, "и");
        QRegExp rgx126("(Ι|Ἰ|Ἲ|Ἴ|Ἶ|Ἱ|Ἳ|Ἵ|Ἷ)");
        str.replace(rgx126, "И");
        QRegExp rgx127("(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ἱ|ἳ|ἵ|ἷ|ϊ|ῒ|ΐ|ῗ|ί|ἵ|ΐ)");
        str.replace(rgx127, "и");
        QRegExp rgx128("(Ο|Ὀ|Ὂ|Ὄ|Ὁ|Ὃ|Ὅ)");
        str.replace(rgx128, "О");
        QRegExp rgx129("(ο|ὀ|ὂ|ὄ|ὸ|ό|ὁ|ὃ|ὅ|ό)");
        str.replace(rgx129, "о");
        QRegExp rgx130("(Υ|Ὑ|Ὓ|Ὕ|Ὗ)");
        str.replace(rgx130, "И");
        QRegExp rgx131("(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ὑ|ὓ|ὕ|ὗ|ϋ|ῢ|ΰ|ῧ|ύ)");
        str.replace(rgx131, "и");
        QRegExp rgx132("(Ω|Ὠ|Ὢ|Ὤ|Ὦ|Ὡ|Ὣ|Ὥ|Ὧ)");
        str.replace(rgx132, "О");
        QRegExp rgx133("(ω|ὠ|ὢ|ὤ|ὦ|ὼ|ώ|ῶ|ὡ|ὣ|ὥ|ὧ|ᾠ|ᾢ|ᾤ|ᾦ|ῳ|ῲ|ῴ|ῷ|ᾡ|ᾣ|ᾥ|ᾧ|ώ)");
        str.replace(rgx133, "о");

        // Greek consonants (Reuchlin"s)
        str.replace("Β", "В");
        str.replace("β", "в");
        str.replace("Γ", "Г");
        str.replace("γγ", "нг");
        str.replace("γκ", "нг");
        str.replace("γξ", "нкс");
        str.replace("γχ", "нх");
        str.replace("γ", "г");
        str.replace("Δ", "Д");
        str.replace("δ", "д");
        str.replace("Ζ", "З");
        str.replace("ζ", "з");
        QRegExp rgx134("(Θ|Φ)");
        str.replace(rgx134, "Ф");
        QRegExp rgx135("(θ|φ)");
        str.replace(rgx135, "ф");
        str.replace("Κ", "К");
        str.replace("κ", "к");
        str.replace("Λ", "Л");
        str.replace("λ", "л");
        str.replace("μπ", "мб");
        str.replace("Μ", "М");
        str.replace("μ", "м");
        str.replace("νκ", "нг");
        str.replace("νπ", "нб");
        str.replace("ντ", "нд");
        str.replace("Ν", "Н");
        str.replace("ν", "н");
        str.replace("Ξ", "Кс");
        str.replace("ξ", "кс");
        str.replace("Π", "П");
        str.replace("π", "п");
        str.replace("Ρ", "Р");
        QRegExp rgx136("(Ρ|Ῥ)");
        str.replace(rgx136, "Р");
        QRegExp rgx137("(ρ|ῤ|ῥ)");
        str.replace(rgx137, "р");
        str.replace("Σ", "С");
        QRegExp rgx138("(σ|ς)");
        str.replace(rgx138, "с");
        str.replace("Τ", "Т");
        str.replace("τ", "т");
        str.replace("Χ", "Х");
        str.replace("χ", "х");
        str.replace("Ψ", "Пс");
        str.replace("ψ", "пс");

        // correction of Cyrillic text
        QRegExp rgx139("\\BЕ");
        str.replace(rgx139, "Э");
        QRegExp rgx140("\\Bе");
        str.replace(rgx140, "э");
        QRegExp rgx141("(А|а|Э|е|э|И|и|О|о|У|у)е");
        str.replace(rgx141, "\\1э");

        QString txtReuch = str;

        str = txtorig;

        // Hebrew -> Ingush/Avar/Chechen

        // Step 1: Conversion into "pseudo-transliteration"
        // Hebrew cantilation marks (accents)
        QRegExp rgx142("(\u05C3|\u0591|\u0592|\u0593)");
        str.replace(rgx142, "");    // removal of accents
        QRegExp rgx143("(\u0594|\u0595|\u0596|\u0597)");
        str.replace(rgx143, "");
        QRegExp rgx144("(\u0598|\u05AE|\u0599|\u05A8)");
        str.replace(rgx144, "");
        QRegExp rgx145("(\u059A|\u059B|\u05A1|\u059F)");
        str.replace(rgx145, "");
        QRegExp rgx146("(\u05A0|\u059C|\u059E|\u05A3)");
        str.replace(rgx146, "");
        QRegExp rgx147("(\u05A5|\u05A3|\u05A4|\u05A7)");
        str.replace(rgx147, "");
        QRegExp rgx148("(\u05A8|\u05A9|\u05A6|\u05AA)");
        str.replace(rgx148, "");
        QRegExp rgx149("(\u059D|\u05A2|\u05AB|\u05AC|\u05AD)");
        str.replace(rgx149, "");
        QRegExp rgx150("(\u05C0|\u05BD|\u05BF)");
        str.replace(rgx150, ""); // removal of paseq, meteg, rafe
        str.replace("־", "-"); // maqaf

        // Hebrew letters
        str.replace("א", "ъ");
        str.replace("ב", "в");
        if ((lang == "Ingush") || (lang == "Chechen")) {
            str.replace("ג", "гӀ"); // in Avar it will be гъ
        }
        else if (lang == "Avar") {
            str.replace("ג", "гъ");
        }
        str.replace("ד", "д");
        str.replace("ה", "Х"); // will be changed to хӀ // in Avar it will be гь
        str.replace("ו", "В"); // will be changed to в
        str.replace("ז", "з");
        str.replace("ח", "Ь"); // will be changed to хь // in Avar it will be хӀ
        str.replace("ט", "Т"); // will be changed to тӀ
        str.replace("י", "й");
        str.replace("כ", "х");
        str.replace("ך", "х");
        str.replace("ל", "л");
        str.replace("מ", "м");
        str.replace("ם", "м");
        str.replace("נ", "н");
        str.replace("ן", "н");
        str.replace("ס", "с");
        if ((lang == "Ingush") || (lang == "Chechen")) {
            str.replace("ע", "Ӏ"); // in Avar it will be гӀ
        }
        else if (lang == "Avar") {
            str.replace("ע", "гӀ");
        }
        str.replace("פ", "ф");
        str.replace("ף", "ф");
        str.replace("צ", "Ц"); // will be changed to цӀ
        str.replace("ץ", "Ц"); // will be changed to цӀ
        str.replace("ק", "Ъ"); // will be changed to къ
        str.replace("ר", "р");
        str.replace("ש", "ш");
        str.replace("ת", "т");

        // Hebrew points
        str.replace("ְ", "Э"); // sheva // will be changed to е or no vowel
        str.replace("ֱ", "е"); //hataf segol // will be changed to е or э
        str.replace("ֲ", "а"); // hataf patah // will be changed to а
        str.replace("ֳ", "о"); // hataf qamats // will be changed to о
        str.replace("ִ", "и"); // hiriq
        str.replace("ֵ", "е"); // tsere
        str.replace("ֶ", "е"); // segol
        str.replace("ַ", "а"); // patah
        str.replace("ָ", "а"); // qamats
        // it should be a or o, but without meteg there is no way to discern
        str.replace("ֹ", "о"); // holam
        str.replace("ֻ", "у"); // qubuts

        QRegExp rgx151("\u05BA");
        str.replace(rgx151, "HOLAM HASER for VAV "); // checking if it is used here
        QRegExp rgx152("\u05BC");
        str.replace(rgx152, "Д"); // "DAGESH (or MAPIQ)"
        QRegExp rgx153("\u05BD");
        str.replace(rgx153, "METEG "); // checking if it is used here
        QRegExp rgx154("\u05BE");
        str.replace(rgx154, "MAQAF "); // checking if it is used here
        QRegExp rgx155("\u05BF");
        str.replace(rgx155, "RAFE "); // checking if it is used here
        QRegExp rgx156("\u05C0");
        str.replace(rgx156, "PASEQ "); // checking if it is used here
        QRegExp rgx157("\u05C1");
        str.replace(rgx157, "Ш"); // "SHIN DOT"
        QRegExp rgx158("\u05C2");
        str.replace(rgx158, "С"); // "SIN DOT"
        QRegExp rgx159("\u05C3");
        str.replace(rgx159, "SOF PASUQ "); // checking if it is used here
        QRegExp rgx160("\u05C4");
        str.replace(rgx160, "UPPER DOT "); // checking if it is used here
        QRegExp rgx161("\u05C5");
        str.replace(rgx161, "LOWER DOT "); // checking if it is used here
        QRegExp rgx162("\u05C6");
        str.replace(rgx162, "NUN HAFUKHA "); // checking if it is used here
        QRegExp rgx163("\u05C7");
        str.replace(rgx163, "QAMATS QATAN "); // checking if it is used here

        // Step 2: Conversion into normal transliteration

        // bet
        if ((lang == "Ingush") || (lang == "Chechen")) {
            QRegExp rgx164("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭвД");
            str.replace(rgx164, "\\1ебб");
            QRegExp rgx165("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭвДЭ");
            str.replace(rgx165, "\\1еббе");
            QRegExp rgx166("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭвЭД");
            str.replace(rgx166, "\\1еббе");
            QRegExp rgx167("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эв(и|е|а|о|у)Д");
            str.replace(rgx167, "\\1ебб\\2");
        }
        else if (lang == "Avar") {
            QRegExp rgx168("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭвД");
            str.replace(rgx168, "\\1ебб");
            QRegExp rgx169("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭвДЭ");
            str.replace(rgx169, "\\1еббе");
            QRegExp rgx170("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭвЭД");
            str.replace(rgx170, "\\1еббе");
            QRegExp rgx171("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эв(и|е|а|о|у)Д");
            str.replace(rgx171, "\\1ебб\\2");
        }
        QRegExp rgx172("\\BвД");
        str.replace(rgx172, "б"); // in the beginning of a word
        QRegExp rgx173("\\BвЭД");
        str.replace(rgx173, "бе"); // in the beginning with sheva
        QRegExp rgx174("\\BвДЭ");
        str.replace(rgx174, "бе"); // in the beginning with sheva
        QRegExp rgx175("\\Bв(и|е|а|о|у)Д");
        str.replace(rgx175, "б\\1"); // in the beginning of a word
        QRegExp rgx176("вД\\B");
        str.replace(rgx176, "б"); // in the end of a word
        QRegExp rgx177("вЭД\\B");
        str.replace(rgx177, "б");
        QRegExp rgx178("вДЭ\\B");
        str.replace(rgx178, "б");
        QRegExp rgx179("\\BвД\\B");
        str.replace(rgx179, "бб"); // in the middle of a word
        QRegExp rgx180("\\BвЭД\\B");
        str.replace(rgx180, "ббе");
        QRegExp rgx181("\\BвДЭ\\B");
        str.replace(rgx181, "ббе");
        QRegExp rgx182("\\Bв(и|е|а|о|у)Д\\B");
        str.replace(rgx182, "бб\\1");

        // gimel
        if ((lang == "Ingush") || (lang == "Chechen")) {
            QRegExp rgx183("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭгӀД");
            str.replace(rgx183, "\\1егг");
            QRegExp rgx184("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭгӀДЭ");
            str.replace(rgx184, "\\1егге");
            QRegExp rgx185("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭгӀЭД");
            str.replace(rgx185, "\\1егге");
            QRegExp rgx186("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭгӀ(и|е|а|о|у)Д");
            str.replace(rgx186, "\\1егг\\2");
            QRegExp rgx187("\\BгӀД");
            str.replace(rgx187, "г"); // in the beginning of a word
            QRegExp rgx188("\\BгӀЭД");
            str.replace(rgx188, "ге"); // in the beginning with sheva
            QRegExp rgx189("\\BгӀДЭ");
            str.replace(rgx189, "ге"); // in the beginning with sheva
            QRegExp rgx190("\\BгӀ(и|е|а|о|у)Д");
            str.replace(rgx190, "г\\1"); // in the beginning of a word
            QRegExp rgx191("гӀД\\B");
            str.replace(rgx191, "г"); // in the end of a word
            QRegExp rgx192("гӀЭД\\B");
            str.replace(rgx192, "г");
            QRegExp rgx193("гӀДЭ\\B");
            str.replace(rgx193, "г");
            QRegExp rgx194("\\BгӀД\\B");
            str.replace(rgx194, "гг"); // in the middle of a word
            QRegExp rgx195("\\BгӀЭД\\B");
            str.replace(rgx195, "гге");
            QRegExp rgx196("\\BгӀДЭ\\B");
            str.replace(rgx196, "гге");
            QRegExp rgx197("\\BгӀ(и|е|а|о|у)Д\\B");
            str.replace(rgx197, "гг\\1");
        }
        else if (lang == "Avar") {
            QRegExp rgx198("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭгъД");
            str.replace(rgx198, "\\1егг");
            QRegExp rgx199("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭгъДЭ");
            str.replace(rgx199, "\\1егге");
            QRegExp rgx200("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭгъЭД");
            str.replace(rgx200, "\\1егге");
            QRegExp rgx201("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эгъ(и|е|а|о|у)Д");
            str.replace(rgx201, "\\1егг\\2");
            QRegExp rgx202("\\BгъД");
            str.replace(rgx202, "г"); // in the beginning of a word
            QRegExp rgx203("\\BгъЭД");
            str.replace(rgx203, "ге"); // in the beginning with sheva
            QRegExp rgx204("\\BгъДЭ");
            str.replace(rgx204, "ге"); // in the beginning with sheva
            QRegExp rgx205("\\Bгъ(и|е|а|о|у)Д");
            str.replace(rgx205, "г\\1"); // in the beginning of a word
            QRegExp rgx206("гъД\\B");
            str.replace(rgx206, "г"); // in the end of a word
            QRegExp rgx207("гъЭД\\B");
            str.replace(rgx207, "г");
            QRegExp rgx208("гъДЭ\\B");
            str.replace(rgx208, "г");
            QRegExp rgx209("\\BгъД\\B");
            str.replace(rgx209, "гг"); // in the middle of a word
            QRegExp rgx210("\\BгъЭД\\B");
            str.replace(rgx210, "гге");
            QRegExp rgx211("\\BгъДЭ\\B");
            str.replace(rgx211, "гге");
            QRegExp rgx212("\\Bгъ(и|е|а|о|у)Д\\B");
            str.replace(rgx212, "гг\\1");
        }

        // dalet
        if ((lang == "Ingush") || (lang == "Chechen")) {
            QRegExp rgx213("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭдД");
            str.replace(rgx213, "\\1едд");
            QRegExp rgx214("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭдДЭ");
            str.replace(rgx214, "\\1едде");
            QRegExp rgx215("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭдЭД");
            str.replace(rgx215, "\\1едде");
            QRegExp rgx216("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эд(и|е|а|о|у)Д");
            str.replace(rgx216, "\\1едд\\2");
        }
        else if (lang == "Avar") {
            QRegExp rgx217("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭдД");
            str.replace(rgx217, "\\1едд");
            QRegExp rgx218("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭдДЭ");
            str.replace(rgx218, "\\1едде");
            QRegExp rgx219("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭдЭД");
            str.replace(rgx219, "\\1едде");
            QRegExp rgx220("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эд(и|е|а|о|у)Д");
            str.replace(rgx220, "\\1едд\\2");
        }
        QRegExp rgx221("\\BдД");
        str.replace(rgx221, "д"); // in the beginning of a word
        QRegExp rgx222("\\BдЭД");
        str.replace(rgx222, "де"); // in the beginning with sheva
        QRegExp rgx223("\\BдДЭ");
        str.replace(rgx223, "де"); // in the beginning with sheva
        QRegExp rgx224("\\Bд(и|е|а|о|у)Д");
        str.replace(rgx224, "д\\1"); // in the beginning of a word
        QRegExp rgx225("дД\\B");
        str.replace(rgx225, "д"); // in the end of a word
        QRegExp rgx226("дЭД\\B");
        str.replace(rgx226, "д");
        QRegExp rgx227("дДЭ\\B");
        str.replace(rgx227, "д");
        QRegExp rgx228("\\BдД\\B");
        str.replace(rgx228, "дд"); // in the middle of a word
        QRegExp rgx229("\\BдЭД\\B");
        str.replace(rgx229, "дде");
        QRegExp rgx230("\\BдДЭ\\B");
        str.replace(rgx230, "дде");
        QRegExp rgx231("\\Bд(и|е|а|о|у)Д\\B");
        str.replace(rgx231, "дд\\1");

        // kaph and final kaph
        if ((lang == "Ingush") || (lang == "Chechen")) {
            QRegExp rgx232("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭхД");
            str.replace(rgx232, "\\1екк");
            QRegExp rgx233("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭхДЭ");
            str.replace(rgx233, "\\1екк");
            QRegExp rgx234("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭхЭД");
            str.replace(rgx234, "\\1екке");
            QRegExp rgx235("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эх(и|е|а|о|у)Д");
            str.replace(rgx235, "\\1ехх\\2");
        }
        else if (lang == "Avar") {
            QRegExp rgx236("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭхД");
            str.replace(rgx236, "\\1екк");
            QRegExp rgx237("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭхДЭ");
            str.replace(rgx237, "\\1екк");
            QRegExp rgx238("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭхЭД");
            str.replace(rgx238, "\\1екке");
            QRegExp rgx239("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эх(и|е|а|о|у)Д");
            str.replace(rgx239, "\\1ехх\\2");
        }
        QRegExp rgx240("\\BхД");
        str.replace(rgx240, "к"); // in the beginning of a word
        QRegExp rgx241("\\BхЭД");
        str.replace(rgx241, "ке"); // in the beginning with sheva
        QRegExp rgx242("\\BхДЭ");
        str.replace(rgx242, "ке"); // in the beginning with sheva
        QRegExp rgx243("\\Bх(и|е|а|о|у)Д");
        str.replace(rgx243, "к\\1"); // in the beginning of a word
        QRegExp rgx244("хД\\B");
        str.replace(rgx244, "к"); // in the end of a word
        QRegExp rgx245("хЭД\\B");
        str.replace(rgx245, "к");
        QRegExp rgx246("хДЭ\\B");
        str.replace(rgx246, "к");
        QRegExp rgx247("\\BхД\\B");
        str.replace(rgx247, "кк"); // in the middle of a word
        QRegExp rgx248("\\BхЭД\\B");
        str.replace(rgx248, "кке");
        QRegExp rgx249("\\BхДЭ\\B");
        str.replace(rgx249, "кке");
        QRegExp rgx250("\\Bх(и|е|а|о|у)Д\\B");
        str.replace(rgx250, "кк\\1");
        QRegExp rgx251("хЭ\\B");
        str.replace(rgx251, "х"); // in the end

        // pe and final pe
        if ((lang == "Ingush") || (lang == "Chechen")) {
            QRegExp rgx252("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭфД");
            str.replace(rgx252, "\\1епп");
            QRegExp rgx253("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭфДЭ");
            str.replace(rgx253, "\\1еппе");
            QRegExp rgx254("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭфЭД");
            str.replace(rgx254, "\\1еппе");
            QRegExp rgx255("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эф(и|е|а|о|у)Д");
            str.replace(rgx255, "\\1епп\\2");
        }
        else if (lang == "Avar") {
            QRegExp rgx256("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭфД");
            str.replace(rgx256, "\\1епп");
            QRegExp rgx257("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭфДЭ");
            str.replace(rgx257, "\\1еппе");
            QRegExp rgx258("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭфЭД");
            str.replace(rgx258, "\\1еппе");
            QRegExp rgx259("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эф(и|е|а|о|у)Д");
            str.replace(rgx259, "\\1епп\\2");
        }
        QRegExp rgx260("\\BфД");
        str.replace(rgx260, "п"); // in the beginning of a word
        QRegExp rgx261("\\BфЭД");
        str.replace(rgx261, "пе"); // in the beginning with sheva
        QRegExp rgx262("\\BфДЭ");
        str.replace(rgx262, "пе"); // in the beginning with sheva
        QRegExp rgx263("\\Bф(и|е|а|о|у)Д");
        str.replace(rgx263, "п\\1"); // in the beginning of a word
        QRegExp rgx264("фД\\B");
        str.replace(rgx264, "п"); // in the end of a word
        QRegExp rgx265("фЭД\\B");
        str.replace(rgx265, "п");
        QRegExp rgx266("фДЭ\\B");
        str.replace(rgx266, "п");
        QRegExp rgx267("\\BфД\\B");
        str.replace(rgx267, "пп"); // in the middle of a word
        QRegExp rgx268("\\BфЭД\\B");
        str.replace(rgx268, "ппе");
        QRegExp rgx269("\\BфДЭ\\B");
        str.replace(rgx269, "ппе");
        QRegExp rgx270("\\Bф(и|е|а|о|у)Д\\B");
        str.replace(rgx270, "пп\\1");

        // taw
        if ((lang == "Ingush") || (lang == "Chechen")) {
            QRegExp rgx271("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭтД");
            str.replace(rgx271, "\\1етт");
            QRegExp rgx272("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭтДЭ");
            str.replace(rgx272, "\\1етте");
            QRegExp rgx273("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭтЭД");
            str.replace(rgx273, "\\1етте");
            QRegExp rgx274("\\B(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эт(и|е|а|о|у)Д");
            str.replace(rgx274, "\\1етт\\2");
        }
        else if (lang == "Avar") {
            QRegExp rgx275("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭтД");
            str.replace(rgx275, "\\1етт");
            QRegExp rgx276("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭтДЭ");
            str.replace(rgx276, "\\1етте");
            QRegExp rgx277("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭтЭД");
            str.replace(rgx277, "\\1етте");
            QRegExp rgx278("\\B(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эт(и|е|а|о|у)Д");
            str.replace(rgx278, "\\1етт\\2");
        }
        QRegExp rgx279("\\BтД");
        str.replace(rgx279, "т"); // in the beginning of a word
        QRegExp rgx280("\\BтЭД");
        str.replace(rgx280, "те"); // in the beginning with sheva
        QRegExp rgx281("\\BтДЭ");
        str.replace(rgx281, "те"); // in the beginning with sheva
        QRegExp rgx282("\\Bт(и|е|а|о|у)Д");
        str.replace(rgx282, "т\\1"); // in the beginning of a word
        QRegExp rgx283("тД\\B");
        str.replace(rgx283, "т"); // in the end of a word
        QRegExp rgx284("тЭД\\B");
        str.replace(rgx284, "т");
        QRegExp rgx285("тДЭ\\B");
        str.replace(rgx285, "т");
        QRegExp rgx286("\\BтД\\B");
        str.replace(rgx286, "тт"); // in the middle of a word
        QRegExp rgx287("\\BтЭД\\B");
        str.replace(rgx287, "тте");
        QRegExp rgx288("\\BтДЭ\\B");
        str.replace(rgx288, "тте");
        QRegExp rgx289("\\Bт(и|е|а|о|у)Д\\B");
        str.replace(rgx289, "тт\\1");

        // zayin
        QRegExp rgx290("з(и|е|а|о|у)Д");
        str.replace(rgx290, "зз\\1");
        str.replace("зЭД", "ззе");
        str.replace("зДЭ", "ззе");
        str.replace("зД", "зз");

        // tet
        if ((lang == "Ingush") || (lang == "Chechen")) {
            QRegExp rgx291("Т(и|е|а|о|у)Д");
            str.replace(rgx291, "ттӀ\\1");  // in Avar it will be тӀтӀ
            str.replace("ТЭД", "ттӀе");
            str.replace("ТДЭ", "ттӀе");
            str.replace("ТД", "ттӀ");
        }
        else if (lang == "Avar") {
            QRegExp rgx292("Т(и|е|а|о|у)Д");
            str.replace(rgx292, "тӀтӀ\\1");  // in Avar it will be тӀтӀ
            str.replace("ТЭД", "тӀтӀе");
            str.replace("ТДЭ", "тӀтӀе");
            str.replace("ТД", "тӀтӀ");
        }
        str.replace("Т", "тӀ");


        // lamed
        QRegExp rgx293("л(и|е|а|о|у)Д");
        str.replace(rgx293, "лл\\1");
        str.replace("лЭД", "лле");
        str.replace("лДЭ", "лле");
        str.replace("лД", "лл");

        // mim and final min
        QRegExp rgx294("м(и|е|а|о|у)Д");
        str.replace(rgx294, "мм\\1");
        str.replace("мЭД", "мме");
        str.replace("мДЭ", "мме");
        str.replace("мД", "мм");

        // nun and final nun
        QRegExp rgx295("н(и|е|а|о|у)Д");
        str.replace(rgx295, "нн\\1");
        str.replace("нЭД", "нне");
        str.replace("нДЭ", "нне");
        str.replace("нД", "нн");

        // samech
        QRegExp rgx296("с(и|е|а|о|у)Д");
        str.replace(rgx296, "сс\\1");
        str.replace("сЭД", "ссе");
        str.replace("сДЭ", "ссе");
        str.replace("сД", "сс");

        // tsade and final tsade
        if ((lang == "Ingush") || (lang == "Chechen")) {
            QRegExp rgx297("Ц(и|е|а|о|у)Д");
            str.replace(rgx297, "ццӀ\\1");  // in Avar it will be цӀцӀ
            str.replace("ЦЭД", "ццӀе");
            str.replace("ЦДЭ", "ццӀе");
            str.replace("ЦД", "ццӀ");
        }
        else if (lang == "Avar") {
            QRegExp rgx298("Ц(и|е|а|о|у)Д");
            str.replace(rgx298, "цӀцӀ\\1");  // in Avar it will be цӀцӀ
            str.replace("ЦЭД", "цӀцӀе");
            str.replace("ЦДЭ", "цӀцӀе");
            str.replace("ЦД", "цӀцӀ");
        }
        str.replace("Ц", "цӀ");

        // koph
        if ((lang == "Ingush") || (lang == "Chechen")) {
            QRegExp rgx299("Ъ(и|е|а|о|у)Д");
            str.replace(rgx299, "ккъ\\1");  // in Avar it will be къкъ
            str.replace("ЪЭД", "ккъе");
            str.replace("ЪДЭ", "ккъе");
            str.replace("ЪД", "ккъ");
        }
        else if (lang == "Avar") {
            QRegExp rgx300("Ъ(и|е|а|о|у)Д");
            str.replace(rgx300, "къкъ\\1");  // in Avar it will be къкъ
            str.replace("ЪЭД", "къкъе");
            str.replace("ЪДЭ", "къкъе");
            str.replace("ЪД", "къкъ");
        }
        str.replace("Ъ", "къ");


        // sin
        if ((lang == "Ingush") || (lang == "Chechen")) {
            str.replace("шДС", "сс");    // in Avar, Adyghe, and Kabardian, sin can be rendered as лъ
            QRegExp rgx301("ш(и|е|а|о|у)ДС");
            str.replace(rgx301, "сс\\1");
            str.replace("шЭДС", "ссе");
            str.replace("шДЭС", "ссе");
            str.replace("шСДЭ", "ссе");
            str.replace("шСЭД", "ссе");
            str.replace("шСД", "сс");
            str.replace("шС", "с");
            QRegExp rgx302("ш(и|е|а|о|у)С");
            str.replace(rgx302, "с\\1");
            str.replace("шЭС", "сЭ");
        }
        else if (lang == "Avar") {
            str.replace("шДС", "лълъ");    // in Avar, Adyghe, and Kabardian, sin can be rendered as лъ
            QRegExp rgx303("ш(и|е|а|о|у)ДС");
            str.replace(rgx303, "лълъ\\1");
            str.replace("шЭДС", "лълъе");
            str.replace("шДЭС", "лълъе");
            str.replace("шСДЭ", "лълъе");
            str.replace("шСЭД", "лълъе");
            str.replace("шСД", "лълъ");
            str.replace("шС", "лъ");
            QRegExp rgx304("ш(и|е|а|о|у)С");
            str.replace(rgx304, "лъ\\1");
            str.replace("шЭС", "лъЭ");
        }

        // shin
        if ((lang == "Ingush") || (lang == "Chechen")) {
            str.replace("шДШ", "шш"); // in Avar, it will be щ
            QRegExp rgx305("ш(и|е|а|о|у)ДШ");
            str.replace(rgx305, "шш\\1");
            str.replace("шЭДШ", "шше");
            str.replace("шДЭШ", "шше");
            str.replace("шШДЭ", "шше");
            str.replace("шШЭД", "шше");
            str.replace("шШД", "шш");
            str.replace("шШ", "ш");
        }
        else if (lang == "Avar") {
            str.replace("шДШ", "щ"); // in Avar it will be щ
            QRegExp rgx306("ш(и|е|а|о|у)ДШ");
            str.replace(rgx306, "щ\\1");
            str.replace("шЭДШ", "ще");
            str.replace("шДЭШ", "ще");
            str.replace("шШДЭ", "ще");
            str.replace("шШЭД", "ще");
            str.replace("шШД", "щ");
            str.replace("шШ", "ш");
        }
        QRegExp rgx307("ш(и|е|а|о|у)Ш");
        str.replace(rgx307, "ш\\1");
        str.replace("шЭШ", "шЭ");

        // he
        if ((lang == "Ingush") || (lang == "Chechen")) {
            QRegExp rgx308("ХД\\B");
            str.replace(rgx308, "хӀ"); // with mappiq in the end
            QRegExp rgx309("ХаД\\B");
            str.replace(rgx309, "ахӀ"); // with mappiq and patach furtivum
            QRegExp rgx310("ХДа\\B");
            str.replace(rgx310, "ахӀ"); // with mappiq and patach furtivum
            QRegExp rgx311("Х\\B");
            str.replace(rgx311, "хӀ"); // not in the end (pronounced)
        }
        else if (lang == "Avar") {
            QRegExp rgx312("ХД\\B");
            str.replace(rgx312, "гь"); // with mappiq in the end
            QRegExp rgx313("ХаД\\B");
            str.replace(rgx313, "агь"); // with mappiq and patach furtivum
            QRegExp rgx314("ХДа\\B");
            str.replace(rgx314, "агь"); // with mappiq and patach furtivum
            QRegExp rgx315("Х\\B");
            str.replace(rgx315, "гь"); // not in the end (pronounced)
        }

        // het
        if ((lang == "Ingush") || (lang == "Chechen")) {
            QRegExp rgx316("Ьа\\B");
            str.replace(rgx316, "ахь"); // with patach furvitum
            str.replace("Ь", "хь");
        }
        else if (lang == "Avar") {
            QRegExp rgx317("Ьа\\B");
            str.replace(rgx317, "ахӀ"); // with patach furvitum
            str.replace("Ь", "хӀ");
        }

        // ayin
        if ((lang == "Ingush") || (lang == "Chechen")) {
            QRegExp rgx318("Ӏа\\B");
            str.replace(rgx318, "аӀ"); // with patach furvitum
        }
        else if (lang == "Avar") {
            QRegExp rgx319("гӀа\\B");
            str.replace(rgx319, "агӀ"); // with patach furvitum
        }

        // yod
        str.replace("йД", "йй");
        QRegExp rgx320("й(и|е|а|о|у)Д");
        str.replace(rgx320, "йй\\1");
        str.replace("йЭД", "ййе");
        QRegExp rgx321("ей(и|е|а|о|у)");
        str.replace(rgx321, "ЕЙ\\1"); // to keep from changes
        QRegExp rgx322("ий(и|е|а|о|у)");
        str.replace(rgx322, "ИЙ\\1"); // to keep from changes
        str.replace("ей", "е"); // in these four lines
        str.replace("ий", "и"); // the order is very
        str.replace("ей", "ейй"); // important and cannot
        str.replace("ий", "ийй"); // be changed
        str.replace("ЕЙ", "ей");
        str.replace("ИЙ", "ий");

        // waw
        QRegExp rgx323("\\BВД");
        str.replace(rgx323, "у");
        QRegExp rgx324("\\BВо");
        str.replace(rgx324, "во");
        QRegExp rgx325("\\BВЭ");
        str.replace(rgx325, "ве");
        QRegExp rgx326("(и|е|а|о|у)ВД");
        str.replace(rgx326, "\\1вв");
        QRegExp rgx327("(и|е|а|о|у)Во");
        str.replace(rgx327, "\\1во");
        QRegExp rgx328("В(и|е|а|о|у)Д");
        str.replace(rgx328, "вв\\1");
        str.replace("ВЭД", "вве");
        str.replace("ЭВД", "Эвв");
        str.replace("ЭВо", "Эво");
        str.replace("ВД", "у");
        str.replace("Во", "о");

        // sheva
        if ((lang == "Ingush") || (lang == "Chechen")) {
            QRegExp rgx329("\\B(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|тӀ|ф|х|хь|хӀ|цӀ|ш|ъ|Ӏ)Э");
            str.replace(rgx329, "\\1е");
            QRegExp rgx330("Э(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|тӀ|ф|х|хь|хӀ|цӀ|ш|ъ|Ӏ)Э");
            str.replace(rgx330, "\\1е");
            QRegExp rgx331("Э(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|тӀ|ф|х|хь|хӀ|цӀ|ш|ъ|Ӏ)Э\\B");
            str.replace(rgx331, "\\1");
        }
        else if (lang == "Avar") {
            QRegExp rgx332("\\B(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|тӀ|ф|х|хӀ|гь|цӀ|ш|щ|ъ|гӀ|лъ)Э");
            str.replace(rgx332, "\\1е");
            QRegExp rgx333("Э(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|тӀ|ф|х|хӀ|гь|цӀ|ш|щ|ъ|гӀ|лъ)Э");
            str.replace(rgx333, "\\1е");
            QRegExp rgx334("Э(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|тӀ|ф|х|хӀ|гь|цӀ|ш|щ|ъ|гӀ|лъ)Э\\B");
            str.replace(rgx334, "\\1");
        }
        str.replace("Э", "");

        // aleph
        QRegExp rgx335("\\Bъ");
        str.replace(rgx335, ""); // aleph in the beginning (pronounced, but ъ is not used)
        QRegExp rgx336("къ\\B");
        str.replace(rgx336, "къъ"); // correction for къ in the end
        if (lang == "Avar") {
            QRegExp rgx337("гъ\\B");
            str.replace(rgx337, "гъъ"); // correction for гъ in the end
            QRegExp rgx338("лъ\\B");
            str.replace(rgx338, "лъъ"); // correction for гъ in the end
        }
        QRegExp rgx339("ъ\\B");
        str.replace(rgx339, ""); // aleph is not not pronounced in the end
        // aleph before consonants is not pronounced (this regex should be in the end)
        QRegExp rgx340("къ(б|в|г|д|з|й|к|л|м|н|п|р|с|т|ф|х|ц|ш|Ӏ)");
        str.replace(rgx340, "къъ\\1"); // new correction
        if (lang == "Avar") {
            QRegExp rgx341("гъ(б|в|г|д|з|й|к|л|м|н|п|р|с|т|ф|х|цӀ|ш|щ|гӀ)");
            str.replace(rgx341, "гъъ\\1"); // new correction
            QRegExp rgx342("лъ(б|в|г|д|з|й|к|л|м|н|п|р|с|т|ф|х|цӀ|ш|щ|гӀ)");
            str.replace(rgx342, "лъъ\\1"); // new correction
        }
        QRegExp rgx343("ъ(б|в|г|д|з|й|к|л|м|н|п|р|с|т|ф|х|ц|ш|Ӏ)");
        str.replace(rgx343, "\\1");
        // he in the end
        QRegExp rgx344("Х\\B");
        str.replace(rgx344, ""); // in the end (not pronounced)
        // waw
        str.replace("В", "в");

        // correction of begadkephat letters
        if ((lang == "Ingush") || (lang == "Chechen")) {
            QRegExp rgx345("бб(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ|Ӏ)");
            str.replace(rgx345, "ббе\\1");
            QRegExp rgx346("гг(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ)");
            str.replace(rgx346, "гге\\1");
            QRegExp rgx347("дд(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ|Ӏ)");
            str.replace(rgx347, "дде\\1");
            QRegExp rgx348("кк(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|Ӏ)");
            str.replace(rgx348, "кке\\1");
            QRegExp rgx349("пп(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ|Ӏ)");
            str.replace(rgx349, "ппе\\1");
            QRegExp rgx350("тт(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ)");
            str.replace(rgx350, "тте\\1");
            QRegExp rgx351("(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ|Ӏ)бб");
            str.replace(rgx351, "\\1б");
            QRegExp rgx352("(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ|Ӏ)гг");
            str.replace(rgx352, "\\1г");
            QRegExp rgx353("(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ|Ӏ)дд");
            str.replace(rgx353, "\\1д");
            QRegExp rgx354("(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ|Ӏ)кк");
            str.replace(rgx354, "\\1к");
            QRegExp rgx355("(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ|Ӏ)пп");
            str.replace(rgx355, "\\1п");
            QRegExp rgx356("(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ|Ӏ)тт");
            str.replace(rgx356, "\\1т");
        }
        else if (lang == "Avar") {
            QRegExp rgx357("бб(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|щ|ъ|гӀ|лъ)");
            str.replace(rgx357, "ббе\\1");
            QRegExp rgx358("гг(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|щ|ъ|гӀ|лъ)");
            str.replace(rgx358, "гге\\1");
            QRegExp rgx359("дд(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|щ|ъ|гӀ|лъ)");
            str.replace(rgx359, "дде\\1");
            QRegExp rgx360("кк(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|щ|ъ|гӀ|лъ)");
            str.replace(rgx360, "кке\\1");
            QRegExp rgx361("пп(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|щ|ъ|гӀ|лъ)");
            str.replace(rgx361, "ппе\\1");
            QRegExp rgx362("тт(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|щ|ъ|гӀ|лъ)");
            str.replace(rgx362, "тте\\1");
            QRegExp rgx363("(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|ъ|щ|гӀ|лъ)бб");
            str.replace(rgx363, "\\1б");
            QRegExp rgx364("(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|ъ|щ|гӀ|лъ)гг");
            str.replace(rgx364, "\\1г");
            QRegExp rgx365("(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|ъ|щ|гӀ|лъ)дд");
            str.replace(rgx365, "\\1д");
            QRegExp rgx366("(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|ъ|щ|гӀ|лъ)кк");
            str.replace(rgx366, "\\1к");
            QRegExp rgx367("(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|ъ|щ|гӀ|лъ)пп");
            str.replace(rgx367, "\\1п");
            QRegExp rgx368("(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|ъ|щ|гӀ|лъ)тт");
            str.replace(rgx368, "\\1т");
        }

        // correction
        QRegExp rgx369("\\Bе");
        str.replace(rgx369, "э");
        if ((lang == "Ingush") || (lang == "Chechen")) {
            str.replace("кх", "кьх"); // in Avar no need of this line
        }

        QString txtTranslit = str;
        if (addorig == "True") {
            if (txtorig != txtErasm) {
                txtErasm.front() = txtErasm.front().toUpper();  // capitalize all the words
                txtReuch.front() = txtReuch.front().toUpper();  // capitalize all the words
                QString txt = txtorig + "\n" + "\t" + "\t" + txtErasm + "\n" + "\t" + "\t" + txtReuch;
                out << txt << endl;
            }

            else if (txtorig != txtTranslit) {
                txtTranslit.front() = txtTranslit.front().toUpper();
                QString txt = txtorig + "\n" + "\t" + "\t" + txtTranslit;
                out << txt << endl;
            }
        }
        else if (addorig == "False") {
            if (txtorig != txtErasm) {
                txtErasm.front() = txtErasm.front().toUpper();  // capitalize all the words
                txtReuch.front() = txtReuch.front().toUpper();  // capitalize all the words

                QString txt = txtErasm + "/" + txtReuch;
                out << txt << endl;
            }

            else if (txtorig != txtTranslit) {
                txtTranslit.front() = txtTranslit.front().toUpper();  // capitalize all the words
                QString txt = txtTranslit;
                out << txt << endl;
            }
        }
    }
    File1.flush();
    File1.close();
    File2.close();
}

void sorter (QString lang, QString addorig) {
    if (addorig == "True") {
        return;
    }
    QString f1, f2;
    if (lang == "Ingush") {
        f2 = "BibleNamesIngushOnly.txt";
        f1 = "BibleNamesIngushOnlyordered.txt";
    }
    else if (lang == "Avar") {
        f2 = "BibleNamesAvarOnly.txt";
        f1 = "BibleNamesAvarOnlyordered.txt";
    }
    else if (lang == "Chechen") {
        f2 = "BibleNamesChechenOnly.txt";
        f1 = "BibleNamesChechenOnlyordered.txt";
    }

    QFile File1(f1);  // This file is for writing results.
    QFile File2(f2);  // This file contains data and will be opened only for reading.
    File1.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&File1);
    out.setCodec("UTF-8");
    File2.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&File2);
    in.setCodec("UTF-8");

    QString str = in.readAll();
    str = str.replace("(Ar)", "");
    QStringList str_lst = str.split("\n");
    str_lst.sort();
    QString output = str_lst.join("\n");
    out << output << endl;

    File1.flush();
    File1.close();
    File2.close();
}


