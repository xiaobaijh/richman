rm -f ./testcase.txt
rm -f ./record.txt
find $1 -name "*.in" > testcase.txt
python3 reformat_output.py
python3 test.py


