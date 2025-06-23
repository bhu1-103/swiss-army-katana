import os

# Directories
input_dir = 'extracted-pages'
output_dir = 'chapters'

# Create output directory if it doesn't exist
os.makedirs(output_dir, exist_ok=True)

# Find all text files in the extracted-pages directory
txt_files = sorted([f for f in os.listdir(input_dir) if f.endswith('.txt')])

# Variables to track chapter
current_chapter = None
chapter_text = ""

# Function to write content to a chapter file
def write_chapter(chapter_num, text):
    with open(f"{output_dir}/chapter{chapter_num:03d}.txt", "w", encoding='utf-8') as f:
        f.write(text)

# Process each file
for file_name in txt_files:
    file_path = os.path.join(input_dir, file_name)

    with open(file_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    for line in lines:
        # Look for "Chapter x"
        if line.startswith("Chapter "):
            # If we already have a chapter in progress, save it
            if current_chapter is not None:
                write_chapter(current_chapter, chapter_text)
            
            # Clean up the chapter number part (strip the colon and convert to int)
            try:
                current_chapter = int(line.split()[1].strip(':'))  # Get chapter number
            except ValueError:
                continue  # Skip if we can't parse the chapter number properly
            
            chapter_text = line  # Start with the current line (chapter header)
        else:
            # Add line to the current chapter text
            chapter_text += line

# Write the last chapter if any
if current_chapter is not None:
    write_chapter(current_chapter, chapter_text)

print("Chapters have been written to the 'chapters' directory.")

