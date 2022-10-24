from concurrent.futures import ThreadPoolExecutor


def sort_player(lines):
    num = len(lines[0].split(' ')[1].replace('\n',''))
    seq = []
    for i in range(num):
        seq.append(lines[1+i][0])
    seq = dict((key, val) for val, key in enumerate(seq))
    return seq

def building_key(target):
    if len(target) < 2:
        return -1
    return int(target.split(' ')[1])
    

def format(path):
    path = path[:-3]
    with open(path+'out') as f:
        lines = f.readlines()
    f = open(path+'o', 'w')
    f.write(lines[0].replace(' ', ''))
    seq = sort_player(lines)
    for i in 'QqAaSsJj':
        if seq.get(i, 12) != 12:
            f.write(lines[1+seq[i]].replace(' ', ''))
            if(lines[1+seq[i]][-1] != '\n'):
                f.write('\n')
    lines = [i for i in filter(lambda x: len(x) > 2, lines[1+len(seq.keys()):])]
    if(lines is None or len(lines) == 0):
        return
    if(len(lines) > 1):
        lines.sort(key=building_key)
    for line in lines:
        line = line.replace(' ', '')
        if(len(line) > 1):
            f.write(line)
            if line[-1] != '\n':
                f.write('\n')


with open('testcase.txt', 'r') as f:
    testcase = f.readlines()
if testcase[-1] == '\n':
    testcase = testcase[:-1]
for i in testcase:
    format(i)
# with ThreadPoolExecutor(123) as E:
#     tasks = E.map(format, testcase)
# for i in tasks:
#     pass