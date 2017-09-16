import string

translator = str.maketrans('', '', string.punctuation + '“”')

with open('warpeace.txt', 'r') as f:
    for line in f:
        for word in line.split():
            print(word.translate(translator))
