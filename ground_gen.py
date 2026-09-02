import random
from math import nan, isnan
from sys import argv
import numpy as np
import string

maxalt = 4000
effective_maxalt = -1
effective_minalt = 4001
size = 250 #should be multiple of 25
mapalt = []
maptext = []

surface = {
    "wat": 80,
    "soi": 5.02,
    "coa": 0.03,
    "sal": 2.0,
    "snd": 5.0,
    "dus": 3.0,
    "lim": 1.5,
    "qua": 0.1,
    "quz": 0.3,
    "bas": 0.8,
    "gra": 0.6,
    "san": 1.0,
    "sha": 0.4,
    "mar": 0.05,
    "gyp": 0.2
}

faible_profondeur = {
    "wat": 40,
    "soi": 24.98,
    "coa": 0.05,
    "sal": 0.3,
    "snd": 13.0,
    "dus": 0.02,
    "lim": 5.0,
    "qua": 0.1,
    "quz": 0.5,
    "bas": 2.0,
    "gra": 1.2,
    "san": 7.0,
    "sha": 5.0,
    "mar": 0.05,
    "gyp": 0.8
}

profondeur = {
    "wat": 2.0,
    "soi": 0.3,
    "coa": 2.0,
    "sal": 2.0,
    "snd": 0.5,
    "dus": 0.2,
    "lim": 8.0,
    "qua": 12.0,
    "quz": 5.0,
    "bas": 22.0,
    "gra": 20.0,
    "san": 6.0,
    "sha": 7.0,
    "mar": 10.0,
    "gyp": 3.0
}

transformations = {
    "lim" : {"lii" : 1/100000000, "lis" : 1/1000000, "lim" : 1 - 1/1000000-1/100000000},
    "qua" : {"qui" : 1/10000000, "qug" : 1/100000000, "qus" : 1/100000000, "qua" : 1-1/100000000 - 1/100000000 - 1/10000000},
    "quz" : {"qzc" : 1/100000000, "qzg" : 1/1000000, "qzs" : 1/1000000, "quz" : 1-1/1000000 - 1/1000000 - 1/100000000},
    "bas" : {"bai" : 1/100000, "bac" : 1/10000000, "bal" : 1/1000000 , "bas": 1 - 1/100000- 1/10000000 - 1/1000000},
    "gra" : {"gri" : 1/1000000, "grc":  1/10000000, "grt" : 1/100000000, "grd" :  1/1000000, "grs" : 1/10000000, "gra":1-1/1000000-1/10000000-1/100000000-1/1000000-1/10000000},
    "san" : {"sai" : 1/1000000, "sag":  1/100000000, "san" : 1- 1/100000000-1/1000000},
    "sha" : {"shv" : 1/100000000, "shs": 1/100000, "shg":  1/100000000, "sht" : 1/10000000, "shl" :  1/100000000, "shc" : 1/10000000, "shi" : 1/1000000 , "sha" : 1-1/100000000 - 1/100000-1/100000000-1/10000000-1/100000000-1/10000000-1/1000000},
    "mar" : {"mai" : 1/100000000, "mar" : 1-1/100000000 },
    "gyp" : {"gys" : 1/10000, "gyp": 1-1/10000 },
    "wat" : {"wat" : 1},
    "soi" : {"soi" : 1},
    "coa" : {"coa" : 1},
    "sal" : {"sal" : 1},
    "snd" : {"snd" : 1},
    "dus" : {"dus" : 1},
}

metal_found = {
    "lii" : [], "lis" : [], "qui" : [], "qug" : [], "qus" : [],  "qzc" : [], "qzg" : [], "qzs" : [], "bai" : [], "bac" : [], "bal" : [], "gri" : [], "grc" : [],
    "grt" : [], "grd" : [], "grs" : [], "sai" : [], "sag" : [],  "shv" : [], "shs" : [], "shg" : [], "sht" : [], "shl" : [], "shc" : [], "shi" : [], "mai" : [], 
    "gys" : [], 
}

def preparer_transformations(transformations):
    transformations_preparees = {}
    for materiau, destinations in transformations.items():
        noms = np.array(list(destinations.keys()), dtype=object)
        probabilites = np.array(list(destinations.values()),dtype=np.float64)
        seuils = np.cumsum(probabilites)
        # Évite les petits problèmes d'arrondi flottant
        seuils[-1] = 1.0
        transformations_preparees[materiau] = (noms,seuils)
    return transformations_preparees


def transformer_case(case, transformations):
    nouvelle_case = []
    # Parcours des couples matériau / nombre
    for i in range(0, len(case), 2):
        materiau = case[i]
        nombre = case[i + 1]
        noms, seuils = transformations[materiau]
        # Générer tous les nombres aléatoires
        # des couches de ce matériau en une seule fois
        aleatoires = np.random.random(nombre)
        # Trouver le matériau correspondant à chaque tirage
        indices = np.searchsorted( seuils, aleatoires, side="right")
        # Ajouter les résultats dans l'ordre exact
        for index in indices:
            nouvelle_case.extend([noms[index], 1])
    return nouvelle_case

def fusionner_pairs(liste):
    resultat = []
    for i in range(0, len(liste), 2):
        nom = liste[i]
        valeur = liste[i + 1]
        if resultat and resultat[-2] == nom:
            resultat[-1] += valeur
        else:
            resultat.extend([nom, valeur])
    return resultat

def alt_of_not_watter(liste):
    ret = 0
    for i in range(len(liste)//2):
        if liste[2*i] != "wat":
            ret += liste[2*i+1]
        else:
            return ret
    return ret

def altitude(liste):
    ret = 0
    for i in range(len(liste)//2):
        ret += liste[2*i+1]
    return ret


#generate altitude
for y in range(size):
    newx = []
    for x in range(size):
        if y == 0 and x == 0:
            newx.append(random.randint(0, maxalt))
        elif x == 0:
            mxx = min(maxalt, mapalt[y -1][x] + 61)
            mnn = max(0, mapalt[y- 1][x] - 61)
            newx.append(random.randint(mnn, mxx))
        elif y == 0:
            mxx = min(maxalt, newx[x-1] + 61)
            mnn = max(0, newx[x-1] - 61)
            newx.append(random.randint(mnn, mxx))
        else:
            av = (newx[x-1] + mapalt[y-1][x])//2
            mnn = max(0, av - 61)
            mxx = min(maxalt, av + 61)
            newx.append(random.randint(mnn, mxx))
    mapalt.append(newx)

#generate base material
for y in range(size):
    newx = []
    for x in range(size):
        sur = random.choices(list(surface.keys()), weights=list(surface.values()), k=1)[0]
        fai = random.choices(list(faible_profondeur.keys()), weights=list(faible_profondeur.values()), k=1)[0]
        pro = random.choices(list(profondeur.keys()), weights=list(profondeur.values()), k=1)[0]
        pro2 = random.choices(list(profondeur.keys()), weights=list(profondeur.values()), k=1)[0]

        if mapalt[y][x] > effective_maxalt:
            effective_maxalt = mapalt[y][x]
        elif effective_minalt > mapalt[y][x]:
            effective_minalt = mapalt[y][x]
        newx.append([pro, int(mapalt[y][x]*0.44), pro2, int(mapalt[y][x]*0.44), fai, int(mapalt[y][x]*0.1), sur, int(mapalt[y][x]*0.02)])
    maptext.append(newx)

print (effective_maxalt/38, effective_minalt/38)

for y in range(size):
    for x in range(size):
        maptext[y][x] = fusionner_pairs(maptext[y][x])


transformations = preparer_transformations(transformations)
for y in range(len(maptext)):
    for x in range(len(maptext[y])):
        maptext[y][x] = transformer_case(maptext[y][x], transformations)
        maptext[y][x] = fusionner_pairs(maptext[y][x])

#transform High-altitude water into snow
for y in range(size):
    for x in range(size):
        if maptext[y][x][-2] == "wat":
            if alt_of_not_watter(maptext[y][x]) > maxalt / 1.3:
                maptext[y][x][-2] = "sno"
                
for y in range(size):
    for x in range(size):
        found = [cle for cle in metal_found if cle in maptext[y][x]]
        for i in found:
            metal_found[i].append((x,y))

print(metal_found)

ground = open(argv[1], "w")
ground.write(str(size) + " " + str(size) + "\n")
for y in range(size-1):
    for x in range(size-1):
        for ii in range(len(maptext[y][x])//2):
            ground.write(maptext[y][x][2*ii]+str(maptext[y][x][2*ii+1]))
        ground.write(' ')
    for ii in range(len(maptext[y][-1])//2):
        ground.write(maptext[y][-1][2*ii]+str(maptext[y][-1][2*ii+1]))        
    ground.write('\n')
for x in range(size-1):
    for ii in range(len(maptext[-1][x])//2):
        ground.write(maptext[-1][x][2*ii]+str(maptext[-1][x][2*ii+1]))
    ground.write(' ')
for ii in range(len(maptext[-1][-1])//2):
    ground.write(maptext[-1][-1][2*ii]+str(maptext[-1][-1][2*ii+1]))   



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


characters = []
for y in range(0, size):
    for x in range(0, size):
        tex = maptext[y][x][-2]
        alt = altitude(maptext[y][x])
        if tex == "soi" and random.randint(1,25) == 1:
            characters.append("01 " + str(len(characters)+1 )   + " 50 0 100 -1 -1 0 0 a 000000 . . . -1 0 . 0 . 0 . 0 . 0 . 0 . 0 . 0 . 0 . 0 . 0 . 0 . . . . . . . " + str(x+0.5)  + " " + str(y+0.5) + " " + str(alt/38) + " -1 -1 [] []\n")
        elif tex != "wat" and random.randint(1, 250) == 1:
            characters.append("0 " + str(len(characters)+1 )   + " 10 0 99999 -1 -1 0 0 a " + str(random.randint(0,1)) + str(random.randint(0,2)) + str(random.randint(0, 9)) + "000 . " + generate_random_name() +" . -1 10 fruit 0 . 0 . 0 . 0 . 0 . 0 . 0 . 0 . 0 . 0 . 0 . . . . . . . " + str(x+0.5) + " " + str(y+0.5) + " " + str(alt/38) + " -1 -1 [] []\n")

map = open(argv[2], "w")
for i in characters:
    map.write(i)

if len(argv) == 4:
    a = "0 "+str(len(characters))+" 10 0 99999 -1 -1 0 0 a 198000 thyma thyma . -1 1 shift 1 wooden-board 1 wooden-board 1 wooden-board 1 wooden-board 1 wooden-board 1 wooden-board 1 wooden-board 1 wooden-board 1 wooden-board 0 . 0 . . . . . . . 178.5 247.5 74.21052631578947 -1 -1 [] []"
    map.write(a)