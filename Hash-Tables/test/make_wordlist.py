import os
import subprocess
import string

remove = string.punctuation.replace('-', '')
translator = str.maketrans('', '', remove + '“”‘’')

txt_files = filter(lambda x: x[-4:] == '.txt', os.listdir('./'))

subprocess.run(['touch', 'wordlist_george'])

with open('wordlist_george', 'w') as outfile:
    for txt in txt_files:
        with open(txt, 'r') as infile:
            for line in infile:
                for word in line.split():
                    outfile.write(word.translate(translator) + '\n')

subprocess.run(['sort', '-u', '-o', 'wordlist_george', 'wordlist_george'])
