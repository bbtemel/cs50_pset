while True:
    height = int(input("height:"))
    if height < 9 and height > 0:
        break;


for i in range(0,height+1):
    print(" " * (height-i)+"#" * i)


