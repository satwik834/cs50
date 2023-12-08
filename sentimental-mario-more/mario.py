from cs50 import get_int

height1 = get_int("height: ")
while height1 not in range(1, 9):
    height1 = get_int("height: ")


def build(height):
    if height > 1:
        build(height - 1)

    print(" " * (height1 - height) + "#" * height, "#" * height, sep="  ", end="\n")


build(height1)
