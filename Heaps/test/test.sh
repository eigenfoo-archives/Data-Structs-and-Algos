cat ./input.txt | ../src/useHeap.exe > output.txt
diff ./sample_run.txt ./output.txt > diff.txt
