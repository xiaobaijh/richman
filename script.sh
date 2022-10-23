rm -rf ./testcase.txt
find $1 -name "*.in" > testcase.txt
python3 test.py
	

