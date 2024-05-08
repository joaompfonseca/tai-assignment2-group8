maxnumber = [5000000, 10000000, 15000000, 20000000, 25000000, 30000000, 35000000, 40000000]

for i in maxnumber:

    lines = []

    with open('out/daigt/train/0/train0.txt', 'r') as file:
        lines = file.readlines()

    char = 0

    with open('out/daigt/train/0/train0-' + str(i) + '.txt', 'w') as file:
        for line in lines:
            c = len(line)
            char += c
            if char < i:
                file.write(line)
            else:
                break

for i in maxnumber:

    lines = []

    with open('out/daigt/train/1/train0.txt', 'r') as file:
        lines = file.readlines()

    char = 0

    with open('out/daigt/train/1/train0-' + str(i) + '.txt', 'w') as file:
        for line in lines:
            c = len(line)
            char += c
            if char < i:
                file.write(line)
            else:
                break
