import re

def main():
    text = input("Text:")
    """
    wordcount = len(text.split())

    L = (len(re.findall("[a-z]|[A-Z]", text)) * 100) // wordcount

    S = (len(re.findall("\.|!|\?", text)) * 100) // wordcount"""
    wordcount = L = S = 0
    for char in text:
        if char.isspace():
            wordcount += 1
        if char.isalpha():
            L += 1
        if char in [".", "!", "?"]:
            S += 1
    wordcount += 1
    grade =round((0.0588 * (L*100/wordcount)) - (0.296 * (S*100/wordcount)) - 15.8)

    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print("Grade:", grade)

main()