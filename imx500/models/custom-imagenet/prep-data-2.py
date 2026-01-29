import os
import shutil
import yaml
from pathlib import Path

SOURCE_DIR = Path("dog-cat-3")
DEST_DIR = Path("my_dataset")
YAML_FILE = SOURCE_DIR / "data.yaml"

def convert():
    if not YAML_FILE.exists():
        print(f"Error: Could not find {YAML_FILE}")
        return

    with open(YAML_FILE) as f:
        data = yaml.safe_load(f)
        names = data.get('names', [])
        print(f"Found classes: {names}")

    for split in ['train', 'valid', 'test']:
        images_dir = SOURCE_DIR / split / "images"
        labels_dir = SOURCE_DIR / split / "labels"
        
        if not images_dir.exists():
            continue

        print(f"Processing {split}...")
        
        for label_file in labels_dir.glob("*.txt"):
            with open(label_file, 'r') as f:
                line = f.readline()
                if not line: continue
                class_id = int(line.split()[0])

            class_name = names[class_id]
            dest_folder = DEST_DIR / class_name
            dest_folder.mkdir(parents=True, exist_ok=True)

            image_name = label_file.stem
            
            found = False
            for ext in ['.jpg', '.jpeg', '.png']:
                src_img = images_dir / (image_name + ext)
                if src_img.exists():
                    shutil.copy(src_img, dest_folder / src_img.name)
                    found = True
                    break
            
            if not found:
                pass

    print(f"\nData ready in '{DEST_DIR}'")
    print(f"Structure:")
    for cls in names:
        count = len(list((DEST_DIR / cls).glob('*')))
        print(f"  - {DEST_DIR}/{cls}: {count} images")

if __name__ == "__main__":
    convert()
