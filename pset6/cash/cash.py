import re
from math import floor
while True:

    dolars = input("change owed:")
    x = re.search("\d\.*", dolars)
    y = re.search("\D", dolars)
    if x:
        while float(dolars) < 0:
            print("you should enter valid number:")
            dolars = input("change owed:")
        cents = floor(float(dolars) * 100)
        break;

    elif y:
        print("please enter a valid input:")


quarters = cents // 25

dimes = (cents % 25) // 10

nickels = ((cents % 25) % 10) // 5

pennies = ((cents % 25) % 10) % 5


print(f"coins:{quarters + dimes + nickels + pennies}")