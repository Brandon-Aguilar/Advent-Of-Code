def getArray():
    with open("day1.txt", "r") as file:
        array = list(map(int, file))

    return array

def answer():
    array = getArray()
    if(len(array) < 3):
        print("invalid input length")
        return -1

    count = 0

    currSum = array[0] + array[1] + array[2]
    
    i = 1
    while(i <= len(array) - 3):
        newSum = array[i] + array[i + 1] + array[i + 2]
        if(newSum > currSum):
            count += 1
        i += 1
        currSum = newSum
    return count

    


if __name__ == "__main__":
    print(answer())
