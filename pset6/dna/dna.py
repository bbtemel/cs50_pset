import sys
import csv

def main():

    if len(sys.argv) != 3:
        print("Usage : dna.py [csvfile][txtfile]")
        exit(1)
    # open the csv file and dna sequence file ,read contents into memory.
    csvfile = open (sys.argv[1],"r")

    strands = []
    persons = {}

    for ind,row in enumerate(csvfile):
        if ind == 0:
            strands = [strands for strands in row.strip().split(",")][1:]
        else:
            curr_row = row.strip().split(",")
            persons[curr_row[0]] = [int(x) for x in curr_row[1:]]



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

main()



