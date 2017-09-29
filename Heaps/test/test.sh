cat ../test/input.txt | ../src/useHeap.exe > ../test/output.txt
diff ../test/sample_run.txt ../test/output.txt > ../test/diff.txt
