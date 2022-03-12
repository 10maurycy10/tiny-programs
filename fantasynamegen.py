#!/bin/python
import random

count = 10

namelists = {
    "elf": [
            ['Cae','Aen','Kay','Di','Vel','Pae','Gal', 'Fol', 'Ka',"Gae","Gord","Lu","Merel","Lar","Sov"],
            ["","","on"],
            ["in","uin","von","lien","alis"],
    ]
}
    
for race in namelists.keys():
    print(race + ":")
    for i in range(count):
        name = ""
        for part in namelists[race]:
            name = name + random.choice(part)
        print("\t" + name)
