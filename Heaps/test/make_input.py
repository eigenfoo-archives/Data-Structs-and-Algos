import random
import string


with open('big_input.txt', 'w') as outfile:
    print('100000', file=outfile)
    for _ in range(100000):
        case = random.randint(1, 4)
        key = ''.join(random.choices(string.ascii_uppercase, k=3))
        value = random.randint(1, 100000)
        if case == 1:
            print('1', file=outfile)
            print(key, file=outfile)
            print(str(value), file=outfile)
        elif case == 2:
            print('2', file=outfile)
            print(key, file=outfile)
            print(str(value), file=outfile)
        elif case == 3:
            print('3', file=outfile)
            print(key, file=outfile)
        elif case == 4:
            print('4', file=outfile)
