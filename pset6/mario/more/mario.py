from cs50 import get_int

# Get height from user, keep asking until 1 <= h >= 8
while True:
    h = get_int("Height: ")
    if h >= 1 and h <= 8:
        break

# Print staircase
for r in range(h):
    print(" " * (h - r - 1) + "#" * (r + 1) + "  " + "#" * (r + 1))
