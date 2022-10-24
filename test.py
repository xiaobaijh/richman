import os
import concurrent.futures
from tqdm import tqdm

sequence = {'Q': '1', 'A': '2', 'S': '3', 'J': '4', 'q': '1', 'a': '2', 's': '3', 'j': 4, '\n':'\n'}
hint = 'reset'
record = open("rocord.txt", 'w')
total = 0
right = 0


def parse_input(path):
    if len(path) == 0:
        return
    with open(path+'in') as fin:
        lines = fin.readlines()
    f = open(path+'in_tmp','w')
    f.write('10000\n')

    # with open(path+'in') as fin:
    #     fin.readline()
    #     line = fin.readline()
    # num.append(len(line.split(' ')[2]))
    
    for i in lines[0].split(' ')[2]:
        f.write(sequence[i])
    # f.write('\n')
    index = 1
    for index in range(1, len(lines)):
        if '\n' == lines[index][0]:
            continue
        elif hint == lines[index][1:6]:
            f.write(lines[index])
            index += 1
        else:
            break
    f.write('\n\n')
    for line in lines[index:]:
        if line[0] == 'F' or line[0] == 'f':
            f.write('0\n')
        else:
            f.write(line)
    f.write('\nprint\nquit\n')
    f.close()
    return path

import os



def parse_output(path):
    if len(path) == 0:
        return
    with open(path+'o') as f:
        base = f.readlines()
    with open(path+'out_tmp') as f:
        output = f.readlines()[-len(base):]
    for i in range(len(output)):
        if base[i].lower() != output[i].replace(' ', '').lower():
            record.write('\n\n')
            record.write(path)
            record.write("\ninput:\n")
            with open(path+'in') as input_file:
                for line in input_file.readlines():
                    record.write(line)            
            record.write('\ncorrect:\n')
            for i in base:
                record.write(i)
            record.write('\n\noutput:\n')
            for i in range(len(base)):
                record.write(output[i])
            return 0
    # print(path,'passed!')
    return 1

with open('testcase.txt', 'r') as f:
    testcase = [i[:-3] for i in f.readlines()]
print(len(testcase))
if len(testcase[-1]) == 0:
    testcase = testcase[:-1] 
total = len(testcase)

with concurrent.futures.ThreadPoolExecutor(128) as E:
    tasks = E.map(parse_input, testcase)
for i in tqdm(tasks):
    os.system('./build/richman < "'+i+'in_tmp" > "'+i+'out_tmp"')
# with concurrent.futures.ThreadPoolExecutor(128) as E:
#     tasks = E.map(parse_output, testcase)
for i in tqdm(testcase):
    right += parse_output(i)
print(right, '/', total)
record.close()