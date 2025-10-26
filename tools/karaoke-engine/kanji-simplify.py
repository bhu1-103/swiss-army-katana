from kanjiconv import KanjiConv
import os

input_file = input().strip()

with open(input_file, "r", encoding="utf-8") as f:
    ocr_text = f.read().strip()

kanji_conv = KanjiConv(separator="/", use_unidic=True)

hiragana_text = kanji_conv.to_hiragana(ocr_text)

#katakana_text = kanji_conv.to_katakana(ocr_text)
#print("Katakana:", katakana_text)

#romaji_text = kanji_conv.to_roman(ocr_text)
#print("Romaji:", romaji_text)


base_name = os.path.splitext(input_file)[0]

output_file = f"{base_name}-hiragana.txt"

print(f"Saving specific file to: {output_file}")
with open(output_file, "w", encoding="utf-8") as f:
    f.write(hiragana_text)
