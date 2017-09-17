'''
Python3 script to read in all .txt files in current directory, and create
a new file in Sable's dictionary format.

This script was developed with English .txt files from Project Gutenberg in
mind: https://www.gutenberg.org/
'''

import os
import subprocess
import string

remove = string.punctuation.replace('-', '')
translator = str.maketrans('', '', remove + '“”‘’')

txt_files = filter(lambda x: x[-4:] == '.txt', os.listdir('./'))

subprocess.run(['touch', 'wordlist'])

with open('wordlist', 'w') as outfile:
    for txt in txt_files:
        with open(txt, 'r') as infile:
            for line in infile:
                for word in line.split():
                    outfile.write(word.translate(translator) + '\n')

subprocess.run(['sort', '-u', '-o', 'wordlist', 'wordlist'])
