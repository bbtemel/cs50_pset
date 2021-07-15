import sys
import csv


if len(sys.argv) != 3:
    print("Usage : dna.py [csvfile][txtfile]")
    exit(1)
# open the csv file and dna sequence file ,read contents into memory.
strands = []
persons = {}
firstrow = False
with open (sys.argv[1],"r") as csvfile:
    reader = csv.reader(csvfile)
    for row in reader:
        if firstrow == False:
            strands = row[1:]
            firstrow = True
        else:
            persons[row[0]] = [int(x) for x in row[1:]]



print(strands)
print(persons)


Str = open(sys.argv[2], "r").read()

#for each STR compute longest consequtive repeats

final_strands = []

for strand in strands:
    i = 0
    max_strand = -1
    cur_max = 0
    while i < len(Str):
        #go through in slice
        cur_window = Str[i:i+len(strand)]
        if cur_window == strand:
            i += len(strand)
            cur_max += 1
            max_strand = max(max_strand,cur_max)
        else:
            i += 1
            cur_max = 0
    final_strands.append(max_strand)

match = False
for name in persons:
    if persons[name] == final_strands:
        print(name)
        match = True
if match == False:
    print("No Match")