

from os import read


def answer():
    f = open("input.txt", "r")
    rawline = f.readline()
    print(rawline)
    horiz = 0
    depth = 0
    aim = 0
    while(rawline != ""):
        line = rawline.split()
        print(line)
        direction = line[0]
        if(direction == "forward"):
            horiz += int(line[1])
            depth += aim * int(line[1])
        elif(direction == "down"):
            aim += int(line[1])
        elif(direction == "up"):
            aim -= int(line[1])
        rawline = f.readline()

    print(horiz, depth)
    print(horiz * depth)
        

        



if __name__ == "__main__":
    print(answer())
