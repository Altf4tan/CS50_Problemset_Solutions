def letter_counter(text):
    count_of_letters = 0
    for i in range(0, len(text)):
        if text[i].isalpha():
            count_of_letters += 1
    return count_of_letters


def word_counter(text):
    count_of_words = 0
    is_word = False
    for char in text:
        if char.isspace():
            is_word = True
            if is_word:
                count_of_words += 1
        else:
            is_word = True
    # If text ends with a word, count that last word.
    if is_word:
        count_of_words += 1
    return count_of_words


def sentence_counter(text):
    count_of_sentence = 0
    for i in range(0, len(text)):
        if text[i] == '.' or text[i] == '?' or text[i] == '!':
            count_of_sentence += 1
    return count_of_sentence


def grader(index):
    rounded_index = round(index)
    if rounded_index < 1:
        print("Before Grade 1")
    elif rounded_index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {rounded_index}")


def main():
    user_text = input("Enter the text to be graded: ")
    average_letter = 0.0
    average_sentence = 0.0
    index = 0.0
    letters = letter_counter(user_text)
    words = word_counter(user_text)
    sentences = sentence_counter(user_text)
    average_letter = (letters / words) * 100
    average_sentence = (sentences / words) * 100
    index = (0.0588 * average_letter) - (0.296 * average_sentence) - 15.8
    grader(index)


if __name__ == "__main__":
    main()
