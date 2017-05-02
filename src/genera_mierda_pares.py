# XXX: http://stackoverflow.com/questions/30890434/how-to-generate-random-pairs-of-numbers-in-python-including-pairs-with-one-entr
from random import randint

def gencoordinates(m, n):
    seen = set()

    x, y = randint(m, n), randint(m, n)

    while True:
        seen.add((x, y))
        yield (x, y)
        x, y = randint(m, n), randint(m, n)
        while (x, y) in seen:
            x, y = randint(m, n), randint(m, n)

if __name__ == "__main__":
    generados=0
    cacas=[]
    g=gencoordinates(1,10)
    while (generados<10):
        cacas.append(next(g))
        generados+=1
    print(cacas)
