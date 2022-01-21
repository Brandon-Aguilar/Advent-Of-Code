

from os import read


def answer():
    f = open("day1.txt", "r")
    line = f.readline()
    curr = int(line)
    line = f.readline()
    count = 0
    while(line != ""):
        if int(line) > curr:
            count += 1
        curr = int(line)
        line = f.readline()
    return count

    


if __name__ == "__main__":
    print(answer())