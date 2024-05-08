

maxlenghts = [50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000]

for maxlenght in maxlenghts:
    
    lines = []

    #Open the file
    with open('out/daigt/run/run0.txt', 'r') as file:
        lines = file.readlines()

    for i in range(0, len(lines)):
        if len(lines[i]) > maxlenght:
            lines[i] = lines[i][:maxlenght] + '\n'

    with open('out/daigt/run/run0-' + str(maxlenght) +  '.txt', 'w') as file:
        file.writelines(lines)