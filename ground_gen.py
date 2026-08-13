import random
from math import nan, isnan
from sys import argv
import numpy as np
import string

maxalt = 3800
biomsize = 25 #plz do not change
nb_bioms =  20
bioms =     [[nan for i in range(nb_bioms)] for i in range(nb_bioms)]

def generate_random_name():
    # Définir la longueur du nom aléatoire entre 4 et 20
    name_length = random.randint(4, 20)
    
    # Créer une liste de lettres (minuscules et majuscules) et de voyelles pour avoir un nom plus naturel
    vowels = "aeiouy"
    consonants = "bcdfghjklmnpqrstvwxyz"
    
    # Créer un nom en alternant voyelles et consonnes pour plus de réalisme
    name = []
    for i in range(name_length):
        if i % 2 == 0:
            name.append(random.choice(consonants))
        else:
            name.append(random.choice(vowels))
    
    # Joindre les lettres pour créer un string
    return ''.join(name).capitalize()  # On capitalise la première lettre pour ressembler à un nom propre

for y in range(nb_bioms):
    for x in range(nb_bioms):
        if y == 0 and x == 0:
            bioms[y][x] = random.randint(0, maxalt)
        elif x == 0:
            mxx = min(maxalt, bioms[y -1][x] + 650)
            mnn = max(0, bioms[y- 1][x] - 650)
            bioms[y][x] = random.randint(mnn, mxx)
        elif y == 0:
            mxx = min(maxalt, bioms[y][x-1] + 650)
            mnn = max(0, bioms[y][x-1] - 650)
            bioms[y][x] = random.randint(mnn, mxx)
        else:
            av = (bioms[y][x-1] + bioms[y-1][x])//2
            mnn = max(0, av - 650)
            mxx = min(maxalt, av + 650)
            bioms[y][x] = random.randint(mnn, mxx)

pd =  ["sa1", "sa2" ,"sa3","he1", "he2", "he3", "he4", "he5"]
d = ["sa1", "sa2" ,"sa3"] 
p =  ["he1", "he2", "he3", "he4", "he5"]

texture = []
for i in range(nb_bioms):
    to_add = []
    for j in range(nb_bioms):
        if bioms[i][j] > 0.8*maxalt:
            to_add.append(p)
        else:
            to_add.append(pd)
    texture.append(to_add)


stones = ["mar", "gra", "sch", "gre", "cal", "bas"]

sizex = len(bioms[0])* biomsize 
sizey = len(bioms) * biomsize
size = sizex*sizey

altitude = np.array([[nan for i in range(sizex)] for i in range (sizey)])
riverid = np.array([[nan for i in range(sizex)] for i in range (sizey)])

characters = []

def max_alt():
    maxaltx = -1
    maxalty = -1
    maxalt = -1
    for y in range(sizey):
        for x in range(sizex):
            if altitude[y][x] > maxalt:
                maxalt = altitude[y][x]
                maxaltx = x
                maxalty = y
    return maxalt, maxaltx, maxalty

for i in range(len(bioms)):
    for j in range(len(bioms[i])):
        altitude[i*biomsize + int(biomsize/2)][j*biomsize + int(biomsize/2)] = bioms[i][j] 
        if len(bioms[0]) - 1 > j:
            incr = (bioms[i][j+1] - bioms[i][j])/biomsize
            for k in range(biomsize):
                altitude[i*biomsize + int(biomsize/2)][j*biomsize + int(biomsize/2) + k] = int(bioms[i][j] + k * incr)
    for j in range(int(biomsize/2)):
        altitude[i*biomsize + int(biomsize/2)][j] = bioms[i][0]
        altitude[i*biomsize + int(biomsize/2)][-j-1] = bioms[i][-1]
        

for j in range(len(altitude[0])):
    for i in range(0, len(bioms)-1):
        incr = (altitude[int(biomsize/2)+(i+1)*biomsize][j] - altitude[int(biomsize/2)+i*biomsize][j]) / biomsize
        for k in range(biomsize):
            #print(int(biomsize/2)+i*biomsize, j)
            altitude[int(biomsize/2)+i*biomsize+k][j] = int(altitude[int(biomsize/2)+i*biomsize][j] + k * incr)



for i in range(int(biomsize/2)):
    for j in range(len(altitude[i])):
        altitude[i][j] = altitude[int(biomsize/2)+1][j]
        altitude[-i-1][j] = altitude[-int(biomsize/2)-2][j]


for y in range(sizey):
    for x in range(sizex):
        if bioms[y//biomsize][x//biomsize] % 10 != 7:
            altitude[y][x] += random.randint(-10, 10)
        if 0 >  altitude[y][x]:
            altitude[y][x] = 0


ground = open(argv[1], "w")
ground.write(str(sizex) + " " + str(sizey) + "\n")

to_write = ""
cnt1 = 0
cnt2 = 0
cnt3 = 0
for y in range(0, sizey):
    for x in range(0, sizex):
        tex = texture[y//biomsize][x//biomsize][random.randint(0,len(texture[y//biomsize][x//biomsize])-1)]
        sto = stones[random.randint(0,5)]
        if altitude[y][x] > int(0.8*maxalt):
            cnt1 += 1
            to_write+=(sto+str(int(altitude[y][x]*0.7))+tex+str(int(altitude[y][x]*0.2))+"ne"+str(random.randint(1,3))+str(int(altitude[y][x]*0.1))+ " ")
        else:
            if altitude[y][x] > int(0.2*maxalt):
                cnt2 += 1
            else:
                cnt3 += 1
            to_write+=(sto+str(int(altitude[y][x]*0.7))+tex+str(int(altitude[y][x]*0.3))+" ")
            if "he" in tex:
                if random.randint(1,50) == 1:
                    characters.append("01 " + str(len(characters)+1 )   + " 50 0 100 -1 -1 0 0 a 000000 . . . -1 0 . 0 . 0 . 0 . 0 . 0 . 0 . 0 . 0 . 0 . 0 . 0 . . . . . . . " + str(x+0.5)  + " " + str(y+0.5) + " " + str(altitude[y][x]/38) + " -1 -1 [] []\n")
                elif random.randint(1, 1500) == 1:
                    characters.append("0 " + str(len(characters)+1 )   + " 10 0 99999 -1 -1 0 0 a " + str(random.randint(0,1)) + str(random.randint(0,2)) + str(random.randint(0, 9)) + "000 . " + generate_random_name() +" . -1 10 fruit 0 . 0 . 0 . 0 . 0 . 0 . 0 . 0 . 0 . 0 . 0 . . . . . . . " + str(x+0.5) + " " + str(y+0.5) + " " + str(altitude[y][x]/38) + " -1 -1 [] []\n")
    to_write = to_write[:-1] + "\n"



ground.write(to_write)
print("snow", cnt1, "not snow", cnt2, "low ground", cnt3)
map = open(argv[2], "w")
for i in characters:
    map.write(i)
