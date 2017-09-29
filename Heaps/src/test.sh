cat ../test/input.txt | ./useHeap.exe > ../test/output.txt
diff ../test/sample_run.txt ../test/output.txt > diff.txt
