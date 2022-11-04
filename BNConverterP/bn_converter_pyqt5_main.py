# Copyright (C) 2022 Aleksandr Migunov

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
  
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.

# -*- coding: utf-8 -*-

import sys, re
from bn_converter_pyqt5_gui import *
from PyQt5 import QtCore, QtGui, QtWidgets

class MyWin(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        super().__init__(parent=None)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.ui.actionExit.triggered.connect(self.close)
        self.ui.actionSave_original.triggered.connect(self.saveToFile_1)
        self.ui.actionSave_converted.triggered.connect(self.saveToFile_2)
        self.ui.actionOpen_original.triggered.connect(self.openFile_1)
        self.ui.actionOpen_converted.triggered.connect(self.openFile_2)
        self.ui.actionNew_original.triggered.connect(self.clearText_1)
        self.ui.actionNew_converted.triggered.connect(self.clearText_2)

        self.ui.actionIngush_with_original.triggered.connect(self.Ingush_original)
        self.ui.actionIngush_without_original.triggered.connect(self.Ingush)
        self.ui.actionAvar_with_original.triggered.connect(self.Avar_original)
        self.ui.actionAvar_without_original.triggered.connect(self.Avar)
        self.ui.actionChechen_with_original.triggered.connect(self.Chechen_original)
        self.ui.actionChechen_without_original.triggered.connect(self.Chechen)
        self.ui.actionAbout.triggered.connect(self.aboutDialog)
        self.ui.actionAbout_Qt.triggered.connect(self.aboutQt)

    def HG_converter(self, lang, addOrig):
        ##This file is for writing results
        if (addOrig == True):
            if (lang == "Ingush"):
                f1 = open(r"BibleNamesIngush.txt", "w")	
            elif (lang == "Avar"):
                f1 = open(r"BibleNamesAvar.txt", "w")
            elif (lang == "Chechen"):
                f1 = open(r"BibleNamesChechen.txt", "w")
        elif (addOrig == False):
            if (lang == "Ingush"):
                f1 = open(r"BibleNamesIngushOnly.txt", "w")	
            elif (lang == "Avar"):
                f1 = open(r"BibleNamesAvarOnly.txt", "w")
            elif (lang == "Chechen"):
                f1 = open(r"BibleNamesChechenOnly.txt", "w")
        ##This file contains data, it will be open only for reading
        f2 = open(r"BibleNames.txt", "r") 
          
        for line in f2:                         
            txt = line
            txtOrig = line

            ##Greek -> Ingush/Avar/Chechen

            #Greek / Erasmian
            #Greek aspirations and stresses (Erasmian)
            txt = re.sub(r"(᾿|῍|῎|῏|`|´|῀|᾽|῭|΅|῁|ͺ)", r"", txt)
            if (lang == "Ingush" or lang == "Chechen"):
                txt = re.sub(r"(῾|῝|῞|῟)", r"хӀ", txt)          ## In Avar, "хӀ" -> "гь".
            elif (lang == "Avar"):
                txt = re.sub(r"(῾|῝|῞|῟)", r"гь", txt)
       
            #Greek diphthongs (Erasmian)
            txt = re.sub(r"(Α|Ἀ|Ἂ|Ἄ|Ἆ)ι", r"А", txt)        ## iota subscriptum
            txt = re.sub(r"(Ἁ|Ἃ|Ἅ|Ἇ)ι", r"ХӀа", txt)
            txt = re.sub(r"(Η|Ἠ|Ἢ|Ἤ|Ἦ)ι", r"Э", txt) 
            txt = re.sub(r"(Ἡ|Ἣ|Ἥ|Ἧ)ι", r"ХӀе", txt) 
            txt = re.sub(r"(Ω|Ὠ|Ὢ|Ὤ|Ὦ)ι", r"О", txt) 
            txt = re.sub(r"(Ὡ|Ὣ|Ὥ|Ὧ)ι", r"ХӀо", txt)               
            txt = re.sub(r"Α(υ|ὐ|ὒ|ὔ|ὖ|ύ)", r"Ав", txt) 
            txt = re.sub(r"Α(ὑ|ὓ|ὕ|ὗ|ύ)", r"ХӀав", txt) 
            txt = re.sub(r"α(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ύ)", r"ав", txt) 
            txt = re.sub(r"α(ὑ|ὓ|ὕ|ὗ|ύ)", r"хӀав", txt) 
            txt = re.sub(r"Ε(υ|ὐ|ὒ|ὔ|ὖ|ύ)", r"Эв", txt) 
            txt = re.sub(r"Ε(ὑ|ὓ|ὕ|ὗ|ύ)", r"ХӀев", txt) 
            txt = re.sub(r"\bε(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ύ)", r"эв", txt) 
            txt = re.sub(r"\bε(ὑ|ὓ|ὕ|ὗ|ύ)", r"хӀев", txt) 
            txt = re.sub(r"ε(υ|ὺ|ύ|ῦ|ύ)", r"ев", txt) 
            txt = re.sub(r"Η(υ|ὐ|ὒ|ὔ|ὖ|ύ)", r"Эв", txt) 
            txt = re.sub(r"Η(ὑ|ὓ|ὕ|ὗ|ύ)", r"ХӀев", txt) 
            txt = re.sub(r"\bη(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ύ)", r"эв", txt) 
            txt = re.sub(r"\bη(ὑ|ὓ|ὕ|ὗ|ύ)", r"хӀев", txt) 
            txt = re.sub(r"η(υ|ὺ|ύ|ῦ|ύ)", r"ев", txt) 
            txt = re.sub(r"Ο(υ|ὐ|ὒ|ὔ|ὖ|ύ)", r"У", txt) 
            txt = re.sub(r"Ο(ὑ|ὓ|ὕ|ὗ|ύ)", r"ХӀу", txt) 
            txt = re.sub(r"ο(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ύ)", r"у", txt) 
            txt = re.sub(r"ο(ὑ|ὓ|ὕ|ὗ|ύ)", r"хӀу", txt) 
            txt = re.sub(r"Α(ι|ἰ|ἲ|ἴ|ἶ|ί)", r"Ай", txt) 
            txt = re.sub(r"Α(ἱ|ἳ|ἷ|ἷ|ί)", r"ХӀай", txt) 
            txt = re.sub(r"α(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ί)", r"ай", txt) 
            txt = re.sub(r"α(ἱ|ἳ|ἷ|ἷ|ί)", r"хӀай", txt) 
            txt = re.sub(r"Ε(ι|ἰ|ἲ|ἴ|ἶ|ί)", r"Эй", txt)
            txt = re.sub(r"Ε(ἱ|ἳ|ἵ|ἷ|ί)", r"ХӀей", txt)
            txt = re.sub(r"\bε(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ί)", r"эй", txt)
            txt = re.sub(r"\bε(ἱ|ἳ|ἵ|ἷ|ί)", r"хӀей", txt)
            txt = re.sub(r"ε(ι|ὶ|ί|ῖ|ί)", r"ей", txt)
            txt = re.sub(r"Ο(ι|ἰ|ἲ|ἴ|ἶ|ί)", r"Ой", txt)
            txt = re.sub(r"Ο(ἱ|ἳ|ἵ|ἷ|ί)", r"ХӀой", txt)
            txt = re.sub(r"ο(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ί)", r"ой", txt)
            txt = re.sub(r"ο(ἱ|ἵ|ἳ|ἷ|ί)", r"хӀой", txt)
            if (lang == "Ingush" or lang == "Avar"):
                txt = re.sub(r"Υ(ι|ἰ|ἲ|ἴ|ἶ|ί)", r"Уй", txt)       ##in Chechen, уьй
                txt = re.sub(r"Υ(ἱ|ἳ|ἵ|ἷ|ί)", r"ХӀуй", txt)
                txt = re.sub(r"υ(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ί)", r"уй", txt)
                txt = re.sub(r"υ(ἱ|ἵ|ἳ|ἷ|ί)", r"хӀуй", txt)
            elif (lang == "Chechen"):
                txt = re.sub(r"Υ(ι|ἰ|ἲ|ἴ|ἶ|ί)", r"Уьй", txt)
                txt = re.sub(r"Υ(ἱ|ἳ|ἵ|ἷ|ί)", r"ХӀуьй", txt)         
                txt = re.sub(r"υ(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ί)", r"уьй", txt)
                txt = re.sub(r"υ(ἱ|ἵ|ἳ|ἷ|ί)", r"хӀуьй", txt)
            if (lang == "Avar"):
                txt = re.sub(r"ХӀ", r"Гь", txt)
                txt = re.sub(r"хӀ", r"гь", txt)
                
            #Greek vowels (Erasmian)
            txt = re.sub(r"(Α|Ἀ|Ἂ|Ἄ|Ἆ)", r"А", txt)
            txt = re.sub(r"(Ἁ|Ἃ|Ἅ|Ἇ)", r"ХӀа", txt)
            txt = re.sub(r"(α|ἀ|ἂ|ἄ|ἆ|ὰ|ά|ᾶ|ᾀ|ᾂ|ᾄ|ᾆ|ᾳ|ᾲ|ᾴ|ᾷ|ά)", r"а", txt)
            txt = re.sub(r"(ἁ|ἃ|ἅ|ἇ|ᾁ|ᾃ|ᾅ|ᾇ)", r"хӀа", txt)
            txt = re.sub(r"(Ε|Ἐ|Ἒ|Ἔ)", r"Э", txt)
            txt = re.sub(r"(Ἑ|Ἓ|Ἕ)", r"ХӀе", txt)
            txt = re.sub(r"\b(ε|ἐ|ἒ|ἔ|έ)", r"э", txt)
            txt = re.sub(r"\b(ἑ|ἓ|ἕ)", r"хӀе", txt)
            txt = re.sub(r"(ε|ὲ|έ|έ)", r"е", txt)
            txt = re.sub(r"(Η|Ἠ|Ἢ|Ἤ|Ἦ)", r"Э", txt)
            txt = re.sub(r"(Ἡ|Ἣ|Ἥ|Ἧ)", r"ХӀе", txt)
            txt = re.sub(r"\b(η|ἠ|ἢ|ἤ|ἦ|ᾐ|ᾒ|ᾔ|ᾖ|ή)", r"э", txt)
            txt = re.sub(r"\b(ἡ|ἣ|ἥ|ἧ|ᾑ|ᾓ|ᾕ|ᾗ)", r"хӀе", txt)
            txt = re.sub(r"(η|ὴ|ή|ῆ|ῃ|ῂ|ῄ|ῇ|ή)", r"е", txt)
            txt = re.sub(r"(Ι|Ἰ|Ἲ|Ἴ|Ἶ|Ἶ)", r"И", txt)
            txt = re.sub(r"(Ἱ|Ἳ|Ἵ|Ἷ|Ἷ)", r"ХӀи", txt)
            txt = re.sub(r"(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ϊ|ῒ|ΐ|ῗ|ἶ|ῖ|ί|ΐ)", r"и", txt)
            txt = re.sub(r"(ἱ|ἳ|ἷ|ἷ|ἵ)", r"хӀи", txt)
            txt = re.sub(r"(Ο|Ὀ|Ὂ|Ὄ)", r"О", txt)
            txt = re.sub(r"(Ὁ|Ὃ|Ὅ)", r"ХӀо", txt)
            txt = re.sub(r"(ο|ὀ|ὂ|ὄ|ὸ|ό|ό)", r"о", txt)
            txt = re.sub(r"(ὁ|ὃ|ὅ)", r"хӀо", txt)
            if (lang == "Ingush" or "Avar"):
                txt = re.sub(r"(Υ|Ὑ|Ὓ|Ὕ|Ὗ)", r"ХӀу", txt)
                txt = re.sub(r"(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ϋ|ῢ|ΰ|ῧ|ύ)", r"у", txt)  ##in Chechen, уь
                txt = re.sub(r"(ὑ|ὓ|ὕ|ὗ)", r"хӀу", txt)
            elif (lang == "Chechen"):    
                txt = re.sub(r"(Υ|Ὑ|Ὓ|Ὕ|Ὗ)", r"ХӀьу", txt)
                txt = re.sub(r"(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ϋ|ῢ|ΰ|ῧ|ύ)", r"уь", txt)  ##in Chechen, уь
                txt = re.sub(r"(ὑ|ὓ|ὕ|ὗ)", r"хӀуь", txt)
            txt = re.sub(r"(Ω|Ὠ|Ὢ|Ὤ|Ὦ)", r"О", txt)
            txt = re.sub(r"(Ὡ|Ὣ|Ὥ|Ὧ)", r"ХӀо", txt)
            txt = re.sub(r"(ω|ὠ|ὢ|ὤ|ὦ|ὼ|ώ|ῶ|ᾠ|ᾢ|ᾤ|ᾦ|ῳ|ῲ|ῴ|ῷ|ώ)", r"о", txt)
            txt = re.sub(r"(ὡ|ὣ|ὥ|ὧ|ᾡ|ᾣ|ᾥ|ᾧ)", r"хӀо", txt)
            if (lang == "Avar"):
                txt = re.sub(r"ХӀ", r"Гь", txt)
                txt = re.sub(r"хӀ", r"гь", txt)

            #Greek consonants (Erasmian)
            txt = txt.replace('Β', 'Б')
            txt = txt.replace('β', 'б')
            txt = txt.replace('Γ', 'Г')
            txt = txt.replace('γγ', 'нг')
            txt = txt.replace('γκ', 'нк')
            txt = txt.replace('γξ', 'нкс')
            txt = txt.replace('γχ', 'нх')
            txt = txt.replace('γ', 'г')
            txt = txt.replace('Δ', 'Д')
            txt = txt.replace('δ', 'д')
            txt = txt.replace('Ζ', 'Дз')
            txt = txt.replace('ζ', 'дз')
            if (lang == "Ingush" or lang == "Chechen"):
                txt = txt.replace('Θ', 'ТхӀ')
                txt = txt.replace('θ', 'тхӀ')
            elif (lang == "Avar"):
                txt = txt.replace('Θ', 'Тгь')
                txt = txt.replace('θ', 'тгь')
            txt = txt.replace('Κ', 'К')
            txt = txt.replace('κ', 'к')
            txt = txt.replace('Λ', 'Л')
            txt = txt.replace('λ', 'л')
            txt = txt.replace('Μ', 'М')
            txt = txt.replace('μ', 'м')
            txt = txt.replace('Ν', 'Н')
            txt = txt.replace('ν', 'н')
            txt = txt.replace('Ξ', 'Кс')
            txt = txt.replace('ξ', 'кс')
            txt = txt.replace('Π', 'П')
            txt = txt.replace('π', 'п')
            txt = txt.replace('Ρ', 'Р')
            txt = re.sub(r"(Ρ|Ῥ)", r"Р", txt)
            txt = re.sub(r"(ρ|ῤ|ῥ)", r"р", txt)
            txt = txt.replace('Σ', 'С')
            txt = re.sub(r"(σ|ς)", r"с", txt)
            txt = txt.replace('Τ', 'Т')
            txt = txt.replace('τ', 'т')
            txt = txt.replace('Φ', 'Ф')
            txt = txt.replace('φ', 'ф')
            txt = txt.replace('Χ', 'Х')
            txt = txt.replace('χ', 'х')
            txt = txt.replace('Ψ', 'Пс')
            txt = txt.replace('ψ', 'пс')

            #correction of Cyrillic text
            txt = re.sub(r"\bЕ", r"Э", txt)
            txt = re.sub(r"\bе", r"э", txt)
            txt = re.sub(r"(А|а|Э|е|э|И|и|О|о|У|у)е", r"\1э", txt)
            if (lang == "Ingush"):
                txt = re.sub(r"(О|о)а", r"\1ъа", txt)  ## In Chechen and Avar, no need of this line.
            if (lang == "Ingush" or lang == "Chechen"):
                txt = re.sub(r"(Т|т)хӀтхӀ", r"\1тхӀ", txt)
            elif (lang == "Avar"):
                txt = re.sub(r"(Т|т)гьтгь", r"\1тгь", txt)
            
            txtErasm = txt
            txt = txtOrig
            
            #Greek aspirations and stresses (Reuchlin's)
            txt = re.sub(r"(᾿|῍|῎|῏|`|´|῀|᾽|῭|΅|῁|ͺ|῾|῝|῞|῟)", r"", txt)  
            
            #Greek diphthongs (Reuchlin's)
            txt = re.sub(r"(Α|Ἀ|Ἂ|Ἄ|Ἆ|Ἁ|Ἃ|Ἅ|Ἇ)ι", r"А", txt)        ## iota subscriptum
            txt = re.sub(r"(Η|Ἠ|Ἢ|Ἤ|Ἦ|Ἡ|Ἣ|Ἥ|Ἧ)ι", r"Э", txt)
            txt = re.sub(r"(Ω|Ὠ|Ὢ|Ὤ|Ὦ|Ὡ|Ὣ|Ὥ|Ὧ)ι", r"О", txt)
            
            ## before voiceless consonants af
            txt = re.sub(r"Α(υ|ὐ|ὒ|ὔ|ὖ|ὑ|ὓ|ὕ|ὗ|ύ)(Θ|Φ|κ|ξ|π|σ|ς|τ|χ|ψ)", r"Аф\2", txt)   
            txt = re.sub(r"α(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ὑ|ὓ|ὕ|ὗ|ύ)(Θ|Φ|κ|ξ|π|σ|ς|τ|χ|ψ)", r"аф\2", txt)
            ## before voiced consonants and vowels av
            txt = re.sub(r"Α(υ|ὐ|ὒ|ὔ|ὖ|ὑ|ὓ|ὕ|ὗ|ύ)", r"Ав", txt)
            txt = re.sub(r"α(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ὑ|ὓ|ὕ|ὗ|ύ)", r"ав", txt)  
            ## before voiceless consonants ef
            txt = re.sub(r"Ε(υ|ὐ|ὒ|ὔ|ὖ|ὑ|ὓ|ὕ|ὗ|ύ)(Θ|Φ|κ|ξ|π|σ|ς|τ|χ|ψ)", r"Эф\2", txt)  
            txt = re.sub(r"\bε(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ὑ|ὓ|ὕ|ὗ|ύ)(Θ|Φ|κ|ξ|π|σ|ς|τ|χ|ψ)", r"эф\2", txt)
            txt = re.sub(r"ε(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ὑ|ὓ|ὕ|ὗ|ύ)(Θ|Φ|κ|ξ|π|σ|ς|τ|χ|ψ)", r"еф\2", txt)
            ## before voiced conconants and vowels ev 
            txt = re.sub(r"Ε(υ|ὐ|ὒ|ὔ|ὖ|ὑ|ὓ|ὕ|ὗ|ύ)", r"Эв", txt)           
            txt = re.sub(r"\bε(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ὑ|ὓ|ὕ|ὗ|ύ)", r"эв", txt)
            txt = re.sub(r"ε(υ|ὺ|ύ|ῦ|ύ)", r"ев", txt)    
            ## before voiceless consonants if
            txt = re.sub(r"Η(υ|ὐ|ὒ|ὔ|ὖ|ὑ|ὓ|ὕ|ὗ|ύ)(Θ|Φ|κ|ξ|π|σ|ς|τ|χ|ψ)", r"Иф\2", txt)           
            txt = re.sub(r"η(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ὑ|ὓ|ὕ|ὗ|ύ)(Θ|Φ|κ|ξ|π|σ|ς|τ|χ|ψ)", r"иф\2", txt)
            ## before voiced consonants and vowels iv
            txt = re.sub(r"Η(υ|ὐ|ὒ|ὔ|ὖ|ὑ|ὓ|ὕ|ὗ|ύ)", r"Ив", txt)           
            txt = re.sub(r"η(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ὑ|ὓ|ὕ|ὗ|ύ)", r"ив", txt)
            txt = re.sub(r"Ο(υ|ὐ|ὒ|ὔ|ὖ|ὑ|ὓ|ὕ|ὗ|ύ)", r"У", txt)
            txt = re.sub(r"ο(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ὑ|ὓ|ὕ|ὗ|ύ)", r"у", txt)
            txt = re.sub(r"Α(ι|ἰ|ἲ|ἴ|ἶ|ἱ|ἳ|ἷ|ἷ|ί)", r"Э", txt) 
            txt = re.sub(r"\bα(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ἱ|ἳ|ἷ|ἷ|ί)", r"э", txt) 
            txt = re.sub(r"α(ι|ὶ|ί|ῖ|ί)", r"е", txt) 
            txt = re.sub(r"Ε(ι|ἰ|ἲ|ἴ|ἶ|ἱ|ἳ|ἵ|ἷ|ί)", r"И", txt) 
            txt = re.sub(r"ε(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ἱ|ἳ|ἵ|ἷ|ί)", r"и", txt) 
            txt = re.sub(r"Ο(ι|ἰ|ἲ|ἴ|ἶ|ἱ|ἳ|ἵ|ἷ|ί)", r"И", txt) 
            txt = re.sub(r"ο(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ἱ|ἵ|ἳ|ἷ|ί)", r"и", txt) 
            txt = re.sub(r"Υ(ι|ἰ|ἲ|ἴ|ἶ|ἱ|ἳ|ἵ|ἷ|ί)", r"и", txt) 
            txt = re.sub(r"υ(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ἱ|ἵ|ἳ|ἷ|ί)", r"и", txt) 
            
            #Greek vowels (Reuchlin's)
            txt = re.sub(r"(Α|Ἀ|Ἂ|Ἄ|Ἆ|Ἁ|Ἃ|Ἅ|Ἇ)", r"А", txt)
            txt = re.sub(r"(α|ἀ|ἂ|ἄ|ἆ|ἁ|ἃ|ἅ|ἇ|ὰ|ά|ᾶ|ᾀ|ᾂ|ᾄ|ᾆ|ᾳ|ᾲ|ᾴ|ᾷ|ᾁ|ᾃ|ᾅ|ᾇ|ά)", r"а", txt)
            txt = re.sub(r"(Ε|Ἐ|Ἒ|Ἔ|Ἑ|Ἓ|Ἕ)", r"Э", txt)
            txt = re.sub(r"\b(ε|ἐ|ἒ|ἔ|ἑ|ἓ|ἕ|έ)", r"э", txt)
            txt = re.sub(r"(ε|ὲ|έ|έ)", r"е", txt)
            txt = re.sub(r"(Η|Ἠ|Ἢ|Ἤ|Ἦ|Ἡ|Ἣ|Ἥ|Ἧ)", r"И", txt)
            txt = re.sub(r"(η|ἠ|ἢ|ἤ|ἦ|ἡ|ἣ|ἥ|ἧ|ὴ|ή|ῆ|ᾐ|ᾒ|ᾔ|ᾖ|ᾑ|ᾓ|ᾕ|ᾗ|ῃ|ῂ|ῄ|ῇ|ή)", r"и", txt)
            txt = re.sub(r"(Ι|Ἰ|Ἲ|Ἴ|Ἶ|Ἱ|Ἳ|Ἵ|Ἷ)", r"И", txt)
            txt = re.sub(r"(ι|ἰ|ἲ|ἴ|ἶ|ὶ|ί|ῖ|ἱ|ἳ|ἵ|ἷ|ϊ|ῒ|ΐ|ῗ|ί|ἵ|ΐ)", r"и", txt)
            txt = re.sub(r"(Ο|Ὀ|Ὂ|Ὄ|Ὁ|Ὃ|Ὅ)", r"О", txt)
            txt = re.sub(r"(ο|ὀ|ὂ|ὄ|ὸ|ό|ὁ|ὃ|ὅ|ό)", r"о", txt)
            txt = re.sub(r"(Υ|Ὑ|Ὓ|Ὕ|Ὗ)", r"И", txt)
            txt = re.sub(r"(υ|ὐ|ὒ|ὔ|ὖ|ὺ|ύ|ῦ|ὑ|ὓ|ὕ|ὗ|ϋ|ῢ|ΰ|ῧ|ύ)", r"и", txt)
            txt = re.sub(r"(Ω|Ὠ|Ὢ|Ὤ|Ὦ|Ὡ|Ὣ|Ὥ|Ὧ)", r"О", txt)
            txt = re.sub(r"(ω|ὠ|ὢ|ὤ|ὦ|ὼ|ώ|ῶ|ὡ|ὣ|ὥ|ὧ|ᾠ|ᾢ|ᾤ|ᾦ|ῳ|ῲ|ῴ|ῷ|ᾡ|ᾣ|ᾥ|ᾧ|ώ)", r"о", txt)
                                
            #Greek consonants (Reuchlin's)
            txt = txt.replace('Β', 'В')
            txt = txt.replace('β', 'в')
            txt = txt.replace('Γ', 'Г')
            txt = txt.replace('γγ', 'нг')
            txt = txt.replace('γκ', 'нг')
            txt = txt.replace('γξ', 'нкс')
            txt = txt.replace('γχ', 'нх')
            txt = txt.replace('γ', 'г')
            txt = txt.replace('Δ', 'Д')
            txt = txt.replace('δ', 'д')
            txt = txt.replace('Ζ', 'З')
            txt = txt.replace('ζ', 'з')
            txt = re.sub(r"(Θ|Φ)", r"Ф", txt)
            txt = re.sub(r"(θ|φ)", r"ф", txt)
            txt = txt.replace('Κ', 'К')
            txt = txt.replace('κ', 'к')
            txt = txt.replace('Λ', 'Л')
            txt = txt.replace('λ', 'л')
            txt = txt.replace('μπ', 'мб')
            txt = txt.replace('Μ', 'М')
            txt = txt.replace('μ', 'м')
            txt = txt.replace('νκ', 'нг')
            txt = txt.replace('νπ', 'нб')
            txt = txt.replace('ντ', 'нд')
            txt = txt.replace('Ν', 'Н')
            txt = txt.replace('ν', 'н')
            txt = txt.replace('Ξ', 'Кс')
            txt = txt.replace('ξ', 'кс')
            txt = txt.replace('Π', 'П')
            txt = txt.replace('π', 'п')
            txt = txt.replace('Ρ', 'Р')
            txt = re.sub(r"(Ρ|Ῥ)", r"Р", txt)
            txt = re.sub(r"(ρ|ῤ|ῥ)", r"р", txt)
            txt = txt.replace('Σ', 'С')
            txt = re.sub(r"(σ|ς)", r"с", txt)
            txt = txt.replace('Τ', 'Т')
            txt = txt.replace('τ', 'т')
            txt = txt.replace('Χ', 'Х')
            txt = txt.replace('χ', 'х')
            txt = txt.replace('Ψ', 'Пс')
            txt = txt.replace('ψ', 'пс')             

            #correction of Cyrillic text
            txt = re.sub(r"\bЕ", r"Э", txt)
            txt = re.sub(r"\bе", r"э", txt)
            txt = re.sub(r"(А|а|Э|е|э|И|и|О|о|У|у)е", r"\1э", txt)
                 
            txtReuch = txt

            txt = txtOrig

            ##Hebrew -> Ingush/Avar/Chechen

            ## Step 1: Conversion into "pseudo-transliteration"
            #Hebrew cantilation marks (accents)
            txt = re.sub(r"(\u05C3|\u0591|\u0592|\u0593)", r"", txt)    #removal of accents
            txt = re.sub(r"(\u0594|\u0595|\u0596|\u0597)", r"", txt)
            txt = re.sub(r"(\u0598|\u05AE|\u0599|\u05A8)", r"", txt)
            txt = re.sub(r"(\u059A|\u059B|\u05A1|\u059F)", r"", txt)
            txt = re.sub(r"(\u05A0|\u059C|\u059E|\u05A3)", r"", txt)
            txt = re.sub(r"(\u05A5|\u05A3|\u05A4|\u05A7)", r"", txt)
            txt = re.sub(r"(\u05A8|\u05A9|\u05A6|\u05AA)", r"", txt)
            txt = re.sub(r"(\u059D|\u05A2|\u05AB|\u05AC|\u05AD)", r"", txt)
            txt = re.sub(r"(\u05C0|\u05BD|\u05BF)", r"", txt) #removal of paseq, meteg, rafe
            txt = txt.replace('־', '-') ##maqaf

            #Hebrew letters
            txt = txt.replace('א', 'ъ')
            txt = txt.replace('ב', 'в')
            if (lang == "Ingush" or lang == "Chechen"):
                txt = txt.replace('ג', 'гӀ') ##in Avar it will be гъ
            elif (lang == "Avar"):
                txt = txt.replace('ג', 'гъ')
            txt = txt.replace('ד', 'д')
            txt = txt.replace('ה', 'Х') ##will be changed to хӀ ##in Avar it will be гь
            txt = txt.replace('ו', 'В') ##will be changed to в
            txt = txt.replace('ז', 'з')
            txt = txt.replace('ח', 'Ь') ##will be changed to хь ##in Avar it will be хӀ
            txt = txt.replace('ט', 'Т') ##will be changed to тӀ
            txt = txt.replace('י', 'й')
            txt = txt.replace('כ', 'х') 
            txt = txt.replace('ך', 'х') 
            txt = txt.replace('ל', 'л')
            txt = txt.replace('מ', 'м')
            txt = txt.replace('ם', 'м')
            txt = txt.replace('נ', 'н')
            txt = txt.replace('ן', 'н')
            txt = txt.replace('ס', 'с')
            if (lang == "Ingush" or lang == "Chechen"):
                txt = txt.replace('ע', 'Ӏ') ##in Avar it will be гӀ
            elif (lang == "Avar"):
                txt = txt.replace('ע', 'гӀ')
            txt = txt.replace('פ', 'ф') 
            txt = txt.replace('ף', 'ф') 
            txt = txt.replace('צ', 'Ц') ##will be changed to цӀ
            txt = txt.replace('ץ', 'Ц') ##will be changed to цӀ
            txt = txt.replace('ק', 'Ъ') ##will be changed to къ
            txt = txt.replace('ר', 'р')
            txt = txt.replace('ש', 'ш')
            txt = txt.replace('ת', 'т')

            #Hebrew points
            txt = txt.replace('ְ', 'Э') ##sheva ##will be changed to е or no vowel
            txt = txt.replace('ֱ', 'е') ##hataf segol ##will be changed to е or э
            txt = txt.replace('ֲ', 'а') ##hataf patah ##will be changed to а
            txt = txt.replace('ֳ', 'о') ##hataf qamats ##will be changed to о
            txt = txt.replace('ִ', 'и') ##hiriq
            txt = txt.replace('ֵ', 'е') ##tsere
            txt = txt.replace('ֶ', 'е') ##segol
            txt = txt.replace('ַ', 'а') ##patah
            txt = txt.replace('ָ', 'а') ##qamats
            ##it should be a or o, but without meteg there is no way to discern
            txt = txt.replace('ֹ', 'о') ##holam
            txt = txt.replace('ֻ', 'у') ##qubuts

            txt = txt.replace('\u05BA', 'HOLAM HASER FOR VAV ') ##checking if it is used here
            txt = txt.replace('\u05BC', 'Д') # 'DAGESH (OR MAPIQ)'
            txt = txt.replace('\u05BD', 'METEG ') ##checking if it is used here
            txt = txt.replace('\u05BE', 'MAQAF ') ##checking if it is used here
            txt = txt.replace('\u05BF', 'RAFE ') ##checking if it is used here
            txt = txt.replace('\u05C0', 'PASEQ ') ##checking if it is used here
            txt = txt.replace('\u05C1', 'Ш') # 'SHIN DOT'
            txt = txt.replace('\u05C2', 'С') # 'SIN DOT'
            txt = txt.replace('\u05C3', 'SOF PASUQ ') ##checking if it is used here
            txt = txt.replace('\u05C4', 'UPPER DOT ') ##checking if it is used here
            txt = txt.replace('\u05C5', 'LOWER DOT ') ##checking if it is used here
            txt = txt.replace('\u05C6', 'NUN HAFUKHA ') ##checking if it is used here
            txt = txt.replace('\u05C7', 'QAMATS QATAN ') ##checking if it is used here

            ## Step 2: Conversion into normal transliteration
            
            #bet
            if (lang == "Ingush" or lang == "Chechen"):
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭвД", r"\1ебб", txt) 
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭвДЭ", r"\1еббе", txt) 
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭвЭД", r"\1еббе", txt) 
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эв(и|е|а|о|у)Д", r"\1ебб\2", txt)
            elif (lang == "Avar"):
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭвД", r"\1ебб", txt) 
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭвДЭ", r"\1еббе", txt) 
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭвЭД", r"\1еббе", txt) 
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эв(и|е|а|о|у)Д", r"\1ебб\2", txt)  
            txt = re.sub(r"\bвД", r"б", txt) ##in the beginning of a word
            txt = re.sub(r"\bвЭД", r"бе", txt) ##in the beginning with sheva
            txt = re.sub(r"\bвДЭ", r"бе", txt) ##in the beginning with sheva
            txt = re.sub(r"\bв(и|е|а|о|у)Д", r"б\1", txt) ##in the beginning of a word
            txt = re.sub(r"вД\b", r"б", txt) ##in the end of a word
            txt = re.sub(r"вЭД\b", r"б", txt) 
            txt = re.sub(r"вДЭ\b", r"б", txt) 
            txt = re.sub(r"\BвД\B", r"бб", txt) ##in the middle of a word
            txt = re.sub(r"\BвЭД\B", r"ббе", txt) 
            txt = re.sub(r"\BвДЭ\B", r"ббе", txt) 
            txt = re.sub(r"\Bв(и|е|а|о|у)Д\B", r"бб\1", txt) 

            #gimel
            if (lang == "Ingush" or lang == "Chechen"):
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭгӀД", r"\1егг", txt) 
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭгӀДЭ", r"\1егге", txt) 
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭгӀЭД", r"\1егге", txt) 
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭгӀ(и|е|а|о|у)Д", r"\1егг\2", txt) 
                txt = re.sub(r"\bгӀД", r"г", txt) ##in the beginning of a word
                txt = re.sub(r"\bгӀЭД", r"ге", txt) ##in the beginning with sheva
                txt = re.sub(r"\bгӀДЭ", r"ге", txt) ##in the beginning with sheva
                txt = re.sub(r"\bгӀ(и|е|а|о|у)Д", r"г\1", txt) ##in the beginning of a word
                txt = re.sub(r"гӀД\b", r"г", txt) ##in the end of a word
                txt = re.sub(r"гӀЭД\b", r"г", txt) 
                txt = re.sub(r"гӀДЭ\b", r"г", txt) 
                txt = re.sub(r"\BгӀД\B", r"гг", txt) ##in the middle of a word
                txt = re.sub(r"\BгӀЭД\B", r"гге", txt) 
                txt = re.sub(r"\BгӀДЭ\B", r"гге", txt) 
                txt = re.sub(r"\BгӀ(и|е|а|о|у)Д\B", r"гг\1", txt)
            elif (lang == "Avar"):
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭгъД", r"\1егг", txt) 
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭгъДЭ", r"\1егге", txt) 
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭгъЭД", r"\1егге", txt) 
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эгъ(и|е|а|о|у)Д", r"\1егг\2", txt) 
                txt = re.sub(r"\bгъД", r"г", txt) ##in the beginning of a word
                txt = re.sub(r"\bгъЭД", r"ге", txt) ##in the beginning with sheva
                txt = re.sub(r"\bгъДЭ", r"ге", txt) ##in the beginning with sheva
                txt = re.sub(r"\bгъ(и|е|а|о|у)Д", r"г\1", txt) ##in the beginning of a word
                txt = re.sub(r"гъД\b", r"г", txt) ##in the end of a word
                txt = re.sub(r"гъЭД\b", r"г", txt) 
                txt = re.sub(r"гъДЭ\b", r"г", txt) 
                txt = re.sub(r"\BгъД\B", r"гг", txt) ##in the middle of a word
                txt = re.sub(r"\BгъЭД\B", r"гге", txt) 
                txt = re.sub(r"\BгъДЭ\B", r"гге", txt) 
                txt = re.sub(r"\Bгъ(и|е|а|о|у)Д\B", r"гг\1", txt) 
                

            #dalet
            if (lang == "Ingush" or lang == "Chechen"):    
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭдД", r"\1едд", txt) 
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭдДЭ", r"\1едде", txt) 
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭдЭД", r"\1едде", txt) 
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эд(и|е|а|о|у)Д", r"\1едд\2", txt)
            elif (lang == "Avar"):
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭдД", r"\1едд", txt) 
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭдДЭ", r"\1едде", txt) 
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭдЭД", r"\1едде", txt) 
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эд(и|е|а|о|у)Д", r"\1едд\2", txt) 
            txt = re.sub(r"\bдД", r"д", txt) ##in the beginning of a word
            txt = re.sub(r"\bдЭД", r"де", txt) ##in the beginning with sheva
            txt = re.sub(r"\bдДЭ", r"де", txt) ##in the beginning with sheva
            txt = re.sub(r"\bд(и|е|а|о|у)Д", r"д\1", txt) ##in the beginning of a word
            txt = re.sub(r"дД\b", r"д", txt) ##in the end of a word
            txt = re.sub(r"дЭД\b", r"д", txt) 
            txt = re.sub(r"дДЭ\b", r"д", txt) 
            txt = re.sub(r"\BдД\B", r"дд", txt) ##in the middle of a word
            txt = re.sub(r"\BдЭД\B", r"дде", txt) 
            txt = re.sub(r"\BдДЭ\B", r"дде", txt) 
            txt = re.sub(r"\Bд(и|е|а|о|у)Д\B", r"дд\1", txt) 

            #kaph and final kaph
            if (lang == "Ingush" or lang == "Chechen"):
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭхД", r"\1екк", txt) 
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭхДЭ", r"\1екк", txt) 
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭхЭД", r"\1екке", txt) 
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эх(и|е|а|о|у)Д", r"\1ехх\2", txt)
            elif (lang == "Avar"):
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭхД", r"\1екк", txt) 
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭхДЭ", r"\1екк", txt) 
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭхЭД", r"\1екке", txt) 
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эх(и|е|а|о|у)Д", r"\1ехх\2", txt) 
            txt = re.sub(r"\bхД", r"к", txt) ##in the beginning of a word
            txt = re.sub(r"\bхЭД", r"ке", txt) ##in the beginning with sheva
            txt = re.sub(r"\bхДЭ", r"ке", txt) ##in the beginning with sheva
            txt = re.sub(r"\bх(и|е|а|о|у)Д", r"к\1", txt) ##in the beginning of a word
            txt = re.sub(r"хД\b", r"к", txt) ##in the end of a word
            txt = re.sub(r"хЭД\b", r"к", txt) 
            txt = re.sub(r"хДЭ\b", r"к", txt) 
            txt = re.sub(r"\BхД\B", r"кк", txt) ##in the middle of a word
            txt = re.sub(r"\BхЭД\B", r"кке", txt) 
            txt = re.sub(r"\BхДЭ\B", r"кке", txt) 
            txt = re.sub(r"\Bх(и|е|а|о|у)Д\B", r"кк\1", txt) 
            txt = re.sub(r"хЭ\b", r"х", txt) ##in the end

            #pe and final pe
            if (lang == "Ingush" or lang == "Chechen"):
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭфД", r"\1епп", txt) 
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭфДЭ", r"\1еппе", txt) 
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭфЭД", r"\1еппе", txt) 
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эф(и|е|а|о|у)Д", r"\1епп\2", txt)
            elif (lang == "Avar"):
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭфД", r"\1епп", txt) 
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭфДЭ", r"\1еппе", txt) 
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭфЭД", r"\1еппе", txt) 
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эф(и|е|а|о|у)Д", r"\1епп\2", txt) 
            txt = re.sub(r"\bфД", r"п", txt) ##in the beginning of a word
            txt = re.sub(r"\bфЭД", r"пе", txt) ##in the beginning with sheva
            txt = re.sub(r"\bфДЭ", r"пе", txt) ##in the beginning with sheva
            txt = re.sub(r"\bф(и|е|а|о|у)Д", r"п\1", txt) ##in the beginning of a word
            txt = re.sub(r"фД\b", r"п", txt) ##in the end of a word
            txt = re.sub(r"фЭД\b", r"п", txt) 
            txt = re.sub(r"фДЭ\b", r"п", txt) 
            txt = re.sub(r"\BфД\B", r"пп", txt) ##in the middle of a word
            txt = re.sub(r"\BфЭД\B", r"ппе", txt) 
            txt = re.sub(r"\BфДЭ\B", r"ппе", txt) 
            txt = re.sub(r"\Bф(и|е|а|о|у)Д\B", r"пп\1", txt) 

            #taw
            if (lang == "Ingush" or lang == "Chechen"):
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭтД", r"\1етт", txt) 
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭтДЭ", r"\1етте", txt) 
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭтЭД", r"\1етте", txt) 
                txt = re.sub(r"\b(б|в|г|гӀ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эт(и|е|а|о|у)Д", r"\1етт\2", txt)
            elif (lang == "Avar"):
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭтД", r"\1етт", txt) 
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭтДЭ", r"\1етте", txt) 
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)ЭтЭД", r"\1етте", txt) 
                txt = re.sub(r"\b(б|в|г|гъ|д|В|з|Т|й|к|х|л|м|н|с|п|ф|Ц|Ъ|р|ш|т)Эт(и|е|а|о|у)Д", r"\1етт\2", txt) 
            txt = re.sub(r"\bтД", r"т", txt) ##in the beginning of a word
            txt = re.sub(r"\bтЭД", r"те", txt) ##in the beginning with sheva
            txt = re.sub(r"\bтДЭ", r"те", txt) ##in the beginning with sheva
            txt = re.sub(r"\bт(и|е|а|о|у)Д", r"т\1", txt) ##in the beginning of a word
            txt = re.sub(r"тД\b", r"т", txt) ##in the end of a word
            txt = re.sub(r"тЭД\b", r"т", txt) 
            txt = re.sub(r"тДЭ\b", r"т", txt) 
            txt = re.sub(r"\BтД\B", r"тт", txt) ##in the middle of a word
            txt = re.sub(r"\BтЭД\B", r"тте", txt) 
            txt = re.sub(r"\BтДЭ\B", r"тте", txt) 
            txt = re.sub(r"\Bт(и|е|а|о|у)Д\B", r"тт\1", txt) 

            #zayin
            txt = re.sub(r"з(и|е|а|о|у)Д", r"зз\1", txt)
            txt = re.sub(r"зЭД", r"ззе", txt)
            txt = re.sub(r"зДЭ", r"ззе", txt) 
            txt = re.sub(r"зД", r"зз", txt)

            #tet
            if (lang == "Ingush" or lang == "Chechen"):
                txt = re.sub(r"Т(и|е|а|о|у)Д", r"ттӀ\1", txt)  ##in Avar it will be тӀтӀ
                txt = re.sub(r"ТЭД", r"ттӀе", txt)
                txt = re.sub(r"ТДЭ", r"ттӀе", txt) 
                txt = re.sub(r"ТД", r"ттӀ", txt)
            elif (lang == "Avar"):
                txt = re.sub(r"Т(и|е|а|о|у)Д", r"тӀтӀ\1", txt)  ##in Avar it will be тӀтӀ
                txt = re.sub(r"ТЭД", r"тӀтӀе", txt)
                txt = re.sub(r"ТДЭ", r"тӀтӀе", txt) 
                txt = re.sub(r"ТД", r"тӀтӀ", txt)
            txt = re.sub(r"Т", r"тӀ", txt)

            #lamed
            txt = re.sub(r"л(и|е|а|о|у)Д", r"лл\1", txt)
            txt = re.sub(r"лЭД", r"лле", txt)
            txt = re.sub(r"лДЭ", r"лле", txt) 
            txt = re.sub(r"лД", r"лл", txt)

            #mim and final min
            txt = re.sub(r"м(и|е|а|о|у)Д", r"мм\1", txt)
            txt = re.sub(r"мЭД", r"мме", txt)
            txt = re.sub(r"мДЭ", r"мме", txt) 
            txt = re.sub(r"мД", r"мм", txt)

            #nun and final nun
            txt = re.sub(r"н(и|е|а|о|у)Д", r"нн\1", txt)
            txt = re.sub(r"нЭД", r"нне", txt)
            txt = re.sub(r"нДЭ", r"нне", txt) 
            txt = re.sub(r"нД", r"нн", txt)

            #samech
            txt = re.sub(r"с(и|е|а|о|у)Д", r"сс\1", txt)
            txt = re.sub(r"сЭД", r"ссе", txt)
            txt = re.sub(r"сДЭ", r"ссе", txt) 
            txt = re.sub(r"сД", r"сс", txt)

            #tsade and final tsade
            if (lang == "Ingush" or lang == "Chechen"):
                txt = re.sub(r"Ц(и|е|а|о|у)Д", r"ццӀ\1", txt)  ##in Avar it will be цӀцӀ
                txt = re.sub(r"ЦЭД", r"ццӀе", txt)
                txt = re.sub(r"ЦДЭ", r"ццӀе", txt) 
                txt = re.sub(r"ЦД", r"ццӀ", txt)
            elif (lang == "Avar"):
                txt = re.sub(r"Ц(и|е|а|о|у)Д", r"цӀцӀ\1", txt)  ##in Avar it will be цӀцӀ
                txt = re.sub(r"ЦЭД", r"цӀцӀе", txt)
                txt = re.sub(r"ЦДЭ", r"цӀцӀе", txt) 
                txt = re.sub(r"ЦД", r"цӀцӀ", txt) 
            txt = re.sub(r"Ц", r"цӀ", txt)

            #koph
            if (lang == "Ingush" or lang == "Chechen"):
                txt = re.sub(r"Ъ(и|е|а|о|у)Д", r"ккъ\1", txt)  ##in Avar it will be къкъ
                txt = re.sub(r"ЪЭД", r"ккъе", txt)
                txt = re.sub(r"ЪДЭ", r"ккъе", txt) 
                txt = re.sub(r"ЪД", r"ккъ", txt)
            elif (lang == "Avar"):
                txt = re.sub(r"Ъ(и|е|а|о|у)Д", r"къкъ\1", txt)  ##in Avar it will be къкъ
                txt = re.sub(r"ЪЭД", r"къкъе", txt)
                txt = re.sub(r"ЪДЭ", r"къкъе", txt) 
                txt = re.sub(r"ЪД", r"къкъ", txt)
            txt = re.sub(r"Ъ", r"къ", txt)

            #sin
            if (lang == "Ingush" or lang == "Chechen"):
                txt = re.sub(r"шДС", r"сс", txt)    ##in Avar, Adyghe, and Kabardian, sin can be rendered as лъ
                txt = re.sub(r"ш(и|е|а|о|у)ДС", r"сс\1", txt)
                txt = re.sub(r"шЭДС", r"ссе", txt)
                txt = re.sub(r"шДЭС", r"ссе", txt) 
                txt = re.sub(r"шСДЭ", r"ссе", txt) 
                txt = re.sub(r"шСЭД", r"ссе", txt) 
                txt = re.sub(r"шСД", r"сс", txt) 
                txt = re.sub(r"шС", r"с", txt)
                txt = re.sub(r"ш(и|е|а|о|у)С", r"с\1", txt)
                txt = re.sub(r"шЭС", r"сЭ", txt)
            elif (lang == "Avar"):
                txt = re.sub(r"шДС", r"лълъ", txt)    ##in Avar, Adyghe, and Kabardian, sin can be rendered as лъ
                txt = re.sub(r"ш(и|е|а|о|у)ДС", r"лълъ\1", txt)
                txt = re.sub(r"шЭДС", r"лълъе", txt)
                txt = re.sub(r"шДЭС", r"лълъе", txt) 
                txt = re.sub(r"шСДЭ", r"лълъе", txt) 
                txt = re.sub(r"шСЭД", r"лълъе", txt) 
                txt = re.sub(r"шСД", r"лълъ", txt) 
                txt = re.sub(r"шС", r"лъ", txt)
                txt = re.sub(r"ш(и|е|а|о|у)С", r"лъ\1", txt)
                txt = re.sub(r"шЭС", r"лъЭ", txt)

            #shin
            if (lang == "Ingush" or lang == "Chechen"):
                txt = re.sub(r"шДШ", r"шш", txt) ##in Avar, it will be щ
                txt = re.sub(r"ш(и|е|а|о|у)ДШ", r"шш\1", txt)
                txt = re.sub(r"шЭДШ", r"шше", txt)
                txt = re.sub(r"шДЭШ", r"шше", txt) 
                txt = re.sub(r"шШДЭ", r"шше", txt) 
                txt = re.sub(r"шШЭД", r"шше", txt) 
                txt = re.sub(r"шШД", r"шш", txt) 
                txt = re.sub(r"шШ", r"ш", txt)
            elif (lang == "Avar"):
                txt = re.sub(r"шДШ", r"щ", txt) ##in Avar it will be щ
                txt = re.sub(r"ш(и|е|а|о|у)ДШ", r"щ\1", txt)
                txt = re.sub(r"шЭДШ", r"ще", txt)
                txt = re.sub(r"шДЭШ", r"ще", txt) 
                txt = re.sub(r"шШДЭ", r"ще", txt) 
                txt = re.sub(r"шШЭД", r"ще", txt) 
                txt = re.sub(r"шШД", r"щ", txt) 
                txt = re.sub(r"шШ", r"ш", txt)
            txt = re.sub(r"ш(и|е|а|о|у)Ш", r"ш\1", txt)
            txt = re.sub(r"шЭШ", r"шЭ", txt)
                
            #he
            if (lang == "Ingush" or lang == "Chechen"):
                txt = re.sub(r"ХД\b", r"хӀ", txt) ##with mappiq in the end
                txt = re.sub(r"ХаД\b", r"ахӀ", txt) ##with mappiq and patach furtivum
                txt = re.sub(r"ХДа\b", r"ахӀ", txt) ##with mappiq and patach furtivum
                txt = re.sub(r"Х\B", r"хӀ", txt) ##not in the end (pronounced)
            elif (lang == "Avar"):
                txt = re.sub(r"ХД\b", r"гь", txt) ##with mappiq in the end
                txt = re.sub(r"ХаД\b", r"агь", txt) ##with mappiq and patach furtivum
                txt = re.sub(r"ХДа\b", r"агь", txt) ##with mappiq and patach furtivum
                txt = re.sub(r"Х\B", r"гь", txt) ##not in the end (pronounced)

            #het
            if (lang == "Ingush" or lang == "Chechen"):    
                txt = re.sub(r"Ьа\b", r"ахь", txt) ##with patach furvitum
                txt = re.sub(r"Ь", r"хь", txt)
            elif (lang == "Avar"):
                txt = re.sub(r"Ьа\b", r"ахӀ", txt) ##with patach furvitum
                txt = re.sub(r"Ь", r"хӀ", txt)

            #ayin
            if (lang == "Ingush" or lang == "Chechen"):
                txt = re.sub(r"Ӏа\b", r"аӀ", txt) ##with patach furvitum
            elif (lang == "Avar"):
                txt = re.sub(r"гӀа\b", r"агӀ", txt) ##with patach furvitum

            #yod
            txt = re.sub(r"йД", r"йй", txt)
            txt = re.sub(r"й(и|е|а|о|у)Д", r"йй\1", txt)
            txt = re.sub(r"йЭД", r"ййе", txt)
            txt = re.sub(r"ей(и|е|а|о|у)", r"ЕЙ\1", txt) ##to keep from changes
            txt = re.sub(r"ий(и|е|а|о|у)", r"ИЙ\1", txt) ##to keep from changes
            txt = re.sub(r"ей", r"е", txt) ##in these four lines 
            txt = re.sub(r"ий", r"и", txt) ##the order is very
            txt = re.sub(r"ей", r"ейй", txt) ##important and cannot
            txt = re.sub(r"ий", r"ийй", txt) ##be changed
            txt = re.sub(r"ЕЙ", r"ей", txt) 
            txt = re.sub(r"ИЙ", r"ий", txt) 
            
            #waw
            txt = re.sub(r"\bВД", r"у", txt)
            txt = re.sub(r"\bВо", r"во", txt)
            txt = re.sub(r"\bВЭ", r"ве", txt) 
            txt = re.sub(r"(и|е|а|о|у)ВД", r"\1вв", txt)
            txt = re.sub(r"(и|е|а|о|у)Во", r"\1во", txt)
            txt = re.sub(r"В(и|е|а|о|у)Д", r"вв\1", txt)
            txt = re.sub(r"ВЭД", r"вве", txt)
            txt = re.sub(r"ЭВД", r"Эвв", txt)
            txt = re.sub(r"ЭВо", r"Эво", txt)
            txt = re.sub(r"ВД", r"у", txt)
            txt = re.sub(r"Во", r"о", txt)

            #sheva
            if (lang == "Ingush" or lang == "Chechen"):
                txt = re.sub(r"\b(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|тӀ|ф|х|хь|хӀ|цӀ|ш|ъ|Ӏ)Э", r"\1е", txt)
                txt = re.sub(r"Э(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|тӀ|ф|х|хь|хӀ|цӀ|ш|ъ|Ӏ)Э", r"\1е", txt)
                txt = re.sub(r"Э(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|тӀ|ф|х|хь|хӀ|цӀ|ш|ъ|Ӏ)Э\b", r"\1", txt)
            elif (lang == "Avar"):
                txt = re.sub(r"\b(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|тӀ|ф|х|хӀ|гь|цӀ|ш|щ|ъ|гӀ|лъ)Э", r"\1е", txt)
                txt = re.sub(r"Э(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|тӀ|ф|х|хӀ|гь|цӀ|ш|щ|ъ|гӀ|лъ)Э", r"\1е", txt)
                txt = re.sub(r"Э(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|тӀ|ф|х|хӀ|гь|цӀ|ш|щ|ъ|гӀ|лъ)Э\b", r"\1", txt) 
            txt = re.sub(r"Э", r"", txt)
            
            #aleph
            txt = re.sub(r"\bъ", r"", txt) ##aleph in the beginning (pronounced, but ъ is not used)
            txt = re.sub(r"къ\b", r"къъ", txt) ##correction for къ in the end
            if (lang == "Avar"):
                txt = re.sub(r"гъ\b", r"гъъ", txt) ##correction for гъ in the end
                txt = re.sub(r"лъ\b", r"лъъ", txt) ##correction for гъ in the end  
            txt = re.sub(r"ъ\b", r"", txt) ##aleph is not not pronounced in the end
            ##aleph before consonants is not pronounced (this regex should be in the end)
            txt = re.sub(r"къ(б|в|г|д|з|й|к|л|м|н|п|р|с|т|ф|х|ц|ш|Ӏ)", r"къъ\1", txt) ##new correction
            if (lang == "Avar"):
                txt = re.sub(r"гъ(б|в|г|д|з|й|к|л|м|н|п|р|с|т|ф|х|цӀ|ш|щ|гӀ)", r"гъъ\1", txt) ##new correction
                txt = re.sub(r"лъ(б|в|г|д|з|й|к|л|м|н|п|р|с|т|ф|х|цӀ|ш|щ|гӀ)", r"лъъ\1", txt) ##new correction
            txt = re.sub(r"ъ(б|в|г|д|з|й|к|л|м|н|п|р|с|т|ф|х|ц|ш|Ӏ)", r"\1", txt)
            ##he in the end 
            txt = re.sub(r"Х\b", r"", txt) ##in the end (not pronounced)
            ##waw
            txt = re.sub(r"В", r"в", txt)

            #correction of begadkephat letters
            if (lang == "Ingush" or lang == "Chechen"):
                txt = re.sub(r"бб(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ|Ӏ)", r"ббе\1", txt) 
                txt = re.sub(r"гг(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ)", r"гге\1", txt) 
                txt = re.sub(r"дд(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ|Ӏ)", r"дде\1", txt) 
                txt = re.sub(r"кк(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|Ӏ)", r"кке\1", txt) 
                txt = re.sub(r"пп(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ|Ӏ)", r"ппе\1", txt) 
                txt = re.sub(r"тт(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ)", r"тте\1", txt)
                txt = re.sub(r"(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ|Ӏ)бб", r"\1б", txt) 
                txt = re.sub(r"(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ|Ӏ)гг", r"\1г", txt) 
                txt = re.sub(r"(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ|Ӏ)дд", r"\1д", txt) 
                txt = re.sub(r"(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ|Ӏ)кк", r"\1к", txt) 
                txt = re.sub(r"(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ|Ӏ)пп", r"\1п", txt) 
                txt = re.sub(r"(б|в|г|гӀ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хь|хӀ|ц|ш|ъ|Ӏ)тт", r"\1т", txt)
            elif (lang == "Avar"):
                txt = re.sub(r"бб(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|щ|ъ|гӀ|лъ)", r"ббе\1", txt) 
                txt = re.sub(r"гг(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|щ|ъ|гӀ|лъ)", r"гге\1", txt) 
                txt = re.sub(r"дд(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|щ|ъ|гӀ|лъ)", r"дде\1", txt) 
                txt = re.sub(r"кк(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|щ|ъ|гӀ|лъ)", r"кке\1", txt) 
                txt = re.sub(r"пп(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|щ|ъ|гӀ|лъ)", r"ппе\1", txt) 
                txt = re.sub(r"тт(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|щ|ъ|гӀ|лъ)", r"тте\1", txt)
                txt = re.sub(r"(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|ъ|щ|гӀ|лъ)бб", r"\1б", txt) 
                txt = re.sub(r"(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|ъ|щ|гӀ|лъ)гг", r"\1г", txt) 
                txt = re.sub(r"(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|ъ|щ|гӀ|лъ)дд", r"\1д", txt) 
                txt = re.sub(r"(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|ъ|щ|гӀ|лъ)кк", r"\1к", txt) 
                txt = re.sub(r"(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|ъ|щ|гӀ|лъ)пп", r"\1п", txt) 
                txt = re.sub(r"(б|в|г|гъ|д|з|й|к|къ|л|м|н|п|р|с|т|ф|х|хӀ|гь|цӀ|ш|ъ|щ|гӀ|лъ)тт", r"\1т", txt) 
            
            #correction
            txt = re.sub(r"\bе", r"э", txt)
            if (lang == "Ingush" or lang == "Chechen"):
                txt = re.sub(r"кх", r"кьх", txt) ##in Avar no need of this line
            
            txtTranslit = txt

            if (addOrig == True):
                if (txtOrig != txtErasm):
                    txtErasm = txtErasm.title()     ##capitalize all the words
                    txtReuch = txtReuch.title()     ##capitalize all the words

                    txt = txtOrig + '\t' + '\t' + txtErasm + '\t' + '\t' + txtReuch
                    f1.write(txt)

                elif (txtOrig != txtTranslit):
                    txtTranslit = txtTranslit.title()   ##capitalize all the words

                    txt = txtOrig + '\t' + '\t' + txtTranslit
                    f1.write(txt)
            elif (addOrig == False):
                if (txtOrig != txtErasm):
                    txtErasm = txtErasm.title()     ##capitalize all the words
                    txtReuch = txtReuch.title()     ##capitalize all the words

                    #txt = txtOrig + '\t' + '\t' + txtErasm + '\t' + '\t' + txtReuch
                    #txt = txtErasm+'/'+txtReuch
                    txt = []
                    txt.append(txtErasm)
                    txt.append('/')
                    txt.append(txtReuch)
                    txt = str(txt)
                    txt = txt.replace('[', '')
                    txt = txt.replace(']', '')
                    txt = txt.replace('\n', '')
                    txt = txt.replace('\\', '')
                    txt = txt.replace('n', '')
                    txt = txt.replace("'", '')
                    txt = txt.replace(',', '')

                    #txt = txtErasm
                    f1.write(txt + '\n')

                elif (txtOrig != txtTranslit):
                    txtTranslit = txtTranslit.title()   ##capitalize all the words

                    #txt = txtOrig + '\t' + '\t' + txtTranslit
                    txt = txtTranslit
                    f1.write(txt)
        
        f1.close()
        f2.close()

    def sorter(self, lang):
        if (lang == "Ingush"):
            f1 = open(r"BibleNamesIngushOnly.txt", "r")
            f2 = open(r"BibleNamesIngushOnlyOrdered.txt", "w")
        elif (lang == "Avar"):
            f1 = open(r"BibleNamesAvarOnly.txt", "r")
            f2 = open(r"BibleNamesAvarOnlyOrdered.txt", "w")
        elif (lang == "Chechen"):
            f1 = open(r"BibleNamesChechenOnly.txt", "r")
            f2 = open(r"BibleNamesChechenOnlyOrdered.txt", "w")
            
        txt = []
        for line in f1:
            line = line.replace('(Ar)', '')
            txt.append(line)
        txt.sort()
        "".join(txt)
        for word in txt:
            f2.write(word)
        f1.close()
        f2.close()    
    

    def closeEvent(self, e):
        result = QtWidgets.QMessageBox.question(self, "Confirm Dialog",
                                                "Really quit?",
                                                QtWidgets.QMessageBox.Yes |
                                                QtWidgets.QMessageBox.No,
                                                QtWidgets.QMessageBox.No)
        if result == QtWidgets.QMessageBox.Yes:
            e.accept()
        else:
            e.ignore()

    def saveToFile_1(self):
        options = QtWidgets.QFileDialog.Options()
        self.fileName, _ = QtWidgets.QFileDialog.getSaveFileName(self, "Save To File", "",
                                                                 "Text Files (*.txt)", options=options)
        if self.fileName:
            self.writeFile = open(self.fileName, 'w', encoding='utf-8')
            self.writeFile.write(self.ui.textEdit.toPlainText())
            self.writeFile.close()
            self.ui.statusbar.showMessage('Saved to %s' % self.fileName)

    def saveToFile_2(self):
        options = QtWidgets.QFileDialog.Options()
        self.fileName, _ = QtWidgets.QFileDialog.getSaveFileName(self, "Save To File", "",
                                                                 "Text Files (*.txt)", options=options)
        if self.fileName:
            self.writeFile = open(self.fileName, 'w', encoding='utf-8')
            self.writeFile.write(self.ui.textEdit_2.toPlainText())
            self.writeFile.close()
            self.ui.statusbar.showMessage('Saved to %s' % self.fileName)        

    def openFile_1(self):
        options = QtWidgets.QFileDialog.Options()
        self.fileName, _ = QtWidgets.QFileDialog.getOpenFileName(self, "Open File", "",
                                                                 "Text Files (*.txt)", options=options)
        if self.fileName:
            self.ui.textEdit.clear()
            self.openF = open(self.fileName, 'r', encoding='utf-8')
            self.ui.textEdit.insertPlainText(self.openF.read())
            self.openF.close()
            self.ui.statusbar.showMessage('%s opened' % self.fileName)

    def openFile_2(self):
        options = QtWidgets.QFileDialog.Options()
        self.fileName, _ = QtWidgets.QFileDialog.getOpenFileName(self, "Open File", "",
                                                                 "Text Files (*.txt)", options=options)
        if self.fileName:
            self.ui.textEdit_2.clear()
            self.openF = open(self.fileName, 'r', encoding='utf-8')
            self.ui.textEdit_2.insertPlainText(self.openF.read())
            self.openF.close()
            self.ui.statusbar.showMessage('%s opened' % self.fileName)


    def clearText_1(self):
        answer = QtWidgets.QMessageBox.question(self, "Clear Text", 
            "Do you want to clear the text?", QtWidgets.QMessageBox.No | QtWidgets.QMessageBox.Yes,
            QtWidgets.QMessageBox.Yes)
        if answer == QtWidgets.QMessageBox.Yes:
            self.ui.textEdit.clear()
        else:
            pass


    def clearText_2(self):
        answer = QtWidgets.QMessageBox.question(self, "Clear Text", 
            "Do you want to clear the text?", QtWidgets.QMessageBox.No | QtWidgets.QMessageBox.Yes,
            QtWidgets.QMessageBox.Yes)
        if answer == QtWidgets.QMessageBox.Yes:
            self.ui.textEdit_2.clear()
        else:
            pass
        

    def Ingush_original(self):
        QtWidgets.QMessageBox.information(self, "Converting...",
            "Conversion will begin after you click \"OK\". It might take some time. Please  wait.")

        self.ui.textEdit.clear()
        self.ui.textEdit_2.clear()
        f_original = open(r"BibleNames.txt", "r")
        self.ui.textEdit.insertPlainText(f_original.read())
        f_original.close()
        self.HG_converter("Ingush", True)
        f_ingush = open(r"BibleNamesIngush.txt", "r")
        self.ui.textEdit_2.insertPlainText(f_ingush.read())
        f_ingush.close()
            

    def Avar_original(self):
        QtWidgets.QMessageBox.information(self, "Converting...",
            "Conversion will begin after you click \"OK\". It might take some time. Please  wait.")

        self.ui.textEdit.clear()
        self.ui.textEdit_2.clear()
        f_original = open(r"BibleNames.txt", "r")
        self.ui.textEdit.insertPlainText(f_original.read())
        f_original.close()
        self.HG_converter("Avar", True)
        f_avar = open(r"BibleNamesAvar.txt", "r")
        self.ui.textEdit_2.insertPlainText(f_avar.read())
        f_avar.close()


    def Chechen_original(self):
        QtWidgets.QMessageBox.information(self, "Converting...",
            "Conversion will begin after you click \"OK\". It might take some time. Please  wait.")

        self.ui.textEdit.clear()
        self.ui.textEdit_2.clear()
        f_original = open(r"BibleNames.txt", "r")
        self.ui.textEdit.insertPlainText(f_original.read())
        f_original.close()
        self.HG_converter("Chechen", True)
        f_chechen = open(r"BibleNamesChechen.txt", "r")
        self.ui.textEdit_2.insertPlainText(f_chechen.read())
        f_chechen.close()

    def Ingush(self):
        QtWidgets.QMessageBox.information(self, "Converting...",
            "Conversion will begin after you click \"OK\". It might take some time. Please  wait.")

        self.ui.textEdit.clear()
        self.ui.textEdit_2.clear()
        f_original = open(r"BibleNames.txt", "r")
        self.ui.textEdit.insertPlainText(f_original.read())
        f_original.close()
        self.HG_converter("Ingush", False)
        self.sorter("Ingush")
        f_ingush = open(r"BibleNamesIngushOnlyOrdered.txt", "r")
        self.ui.textEdit_2.insertPlainText(f_ingush.read())
        f_ingush.close()
            

    def Avar(self):
        QtWidgets.QMessageBox.information(self, "Converting...",
            "Conversion will begin after you click \"OK\". It might take some time. Please  wait.")

        self.ui.textEdit.clear()
        self.ui.textEdit_2.clear()
        f_original = open(r"BibleNames.txt", "r")
        self.ui.textEdit.insertPlainText(f_original.read())
        f_original.close()
        self.HG_converter("Avar", False)
        self.sorter("Avar")
        f_avar = open(r"BibleNamesAvarOnlyOrdered.txt", "r")
        self.ui.textEdit_2.insertPlainText(f_avar.read())
        f_avar.close()


    def Chechen(self):
        QtWidgets.QMessageBox.information(self, "Converting...",
            "Conversion will begin after you click \"OK\". It might take some time. Please  wait.")

        self.ui.textEdit.clear()
        self.ui.textEdit_2.clear()
        f_original = open(r"BibleNames.txt", "r")
        self.ui.textEdit.insertPlainText(f_original.read())
        f_original.close()
        self.HG_converter("Chechen", False)
        self.sorter("Chechen")
        f_chechen = open(r"BibleNamesChechenOnlyOrdered.txt", "r")
        self.ui.textEdit_2.insertPlainText(f_chechen.read())
        f_chechen.close()     
        
    def aboutDialog(self):
        QtWidgets.QMessageBox.about(self, "About Program", "This is a program for converting Biblical names from original into some Caucasian languages. \n\nCopyright (C) 2022 Aleksandr Migunov \n\nThis program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version. \n\nThis program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. \n\nYou should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.")     
   
    def aboutQt(self):
        QtWidgets.QMessageBox.aboutQt(self)
           
        

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    myapp = MyWin()
    myapp.show()
    sys.exit(app.exec_())
