from cs50 import get_string


def main():
    input = get_string("Text: ")
    letter_avg = float()
    sentence_avg = float()

    letter_count = letters(input)

    word_count = words(input)

    sentence_count = sentences(input)

    letter_avg = (letter_count / word_count) * 100
    sentence_avg = (sentence_count / word_count) * 100

    index = 0.0588 * letter_avg - 0.296 * sentence_avg - 15.8

    if index >= 16:
        print("Grade 16+")

    elif index < 1:
        print("Before Grade 1")
    else:
        print("Grade " + str(round(index)))


def sentences(text):
    count = 0
    for i in text:
        if i == "?" or i == "." or i == "!":
            count += 1

    return count


def words(text):
    list = text.split(" ")
    return len(list)


def letters(text):
    letter_count = 0
    for i in range(len(text)):
        if text[i].isalpha():
            letter_count += 1
    return letter_count


main()
