import string

translator = str.maketrans('', '', string.punctuation + '“”')

with open('wp.txt', 'r') as f:
    for line in f:
        for word in line.split():
            print(word.translate(translator))
