import sys
from PIL import Image

# Get png file
if len(sys.argv) < 2:
    print("Usage: python png_to_char_array.py <input.png>")
    sys.exit(1)

INPUT_FILE = sys.argv[1]

# Name of the Arduino array to generate
ARRAY_NAME = INPUT_FILE[:-4]

# Map exact RGB colors to characters
COLOR_MAP = {
    (255, 0, 0): "r",        # red
    (255, 255, 255): "w",    # white
    (0, 0, 255): "b",        # blue
    (245, 193, 66): "y",     #brown university yellow
    (0, 0, 0): ".",          # black / transparent
}

DEFAULT_CHAR = "."


def closest_color_char(r, g, b, a):
    # Treat transparent pixels as empty
    if a == 0:
        return "."

    best_char = DEFAULT_CHAR
    best_distance = float("inf")

    for (cr, cg, cb), char in COLOR_MAP.items():
        distance = (r - cr) ** 2 + (g - cg) ** 2 + (b - cb) ** 2

        if distance < best_distance:
            best_distance = distance
            best_char = char

    return best_char


img = Image.open(INPUT_FILE).convert("RGBA")
width, height = img.size

print(f"const char {ARRAY_NAME}[{height}][{width + 1}] = {{")

for y in range(height):
    row = ""

    for x in range(width):
        r, g, b, a = img.getpixel((x, y))
        row += closest_color_char(r, g, b, a)

    comma = "," if y < height - 1 else ""
    print(f'  "{row}"{comma}')

print("};")
