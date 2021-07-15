import re

while True:

    cnum = input("Card Number:")
    x = re.search("\d", cnum)
    if x and int(cnum) > 0:
        break;
    else:
        print("invalid number")
def main():
    if len(cnum) == 15 and (cnum[0:2] in ["34","37"]):
        if checksum:
            print("AMEX")

    elif len(cnum) == 16 and 51 <= int(cnum[0:2]) <= 55 :
        if checksum:
            print("MasterCard")

    elif (len(cnum) == 13 or len(cnum) == 16) and cnum[0] == "4":
        if checksum:
            print("Visa")
    else:
        print("INVALID")


def checksum():
    second_sum = [((int(x) * 2) // 10 + (int(x) * 2) % 10) for x in cnum[-2::-2]]
    first_sum = [cnum[-1::-2]]
    total_sum = sum(second_sum) + sum(first_sum)

    if (total_sum % 10 == 0):
        return True
    else:
        return False

main()

