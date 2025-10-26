from kanjiconv import KanjiConv

input_file = input("Enter input file: ")
with open(input_file, "r", encoding="utf-8") as f:
    ocr_text = f.read().strip()

#print("text with kanji:", ocr_text)
kanji_conv = KanjiConv(separator="/", use_unidic=True)

hiragana_text = kanji_conv.to_hiragana(ocr_text)
print("Hiragana:", hiragana_text)
with open("hiragana_output.txt", "w", encoding="utf-8") as f:
    f.write(hiragana_text)

#katakana_text = kanji_conv.to_katakana(ocr_text)
#print("Katakana:", katakana_text)

#romaji_text = kanji_conv.to_roman(ocr_text)
#print("Romaji:", romaji_text)

