

userIn = input()
n = int(userIn)
count1 = 0
outputList = []

while count1 < n:

    numChildrenStr = input()

    if (numChildrenStr == ""):
        continue
    
    numChildren = int(numChildrenStr)
    count2 = 0
    sum = 0
    while count2 < numChildren:

        if (count2 + 1 >= numChildren):
            if ((sum + numCandy) % numChildren == 0):
                outputList.append("YES")
                break
            outputList.append("NO")
            break 

        numCandyStr = input()
        numCandy = int(numCandyStr)
        sum += (numCandy % numChildren)
        count2 += 1
    
    count1 += 1

for s in range(0, len(outputList)):
    print(outputList[s])
