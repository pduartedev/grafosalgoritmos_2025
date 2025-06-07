import random

Tam_ciclo = 30
Num_ciclos = 10
Tam_grafo = Tam_ciclo * Num_ciclos
Deltas = [Tam_ciclo * i for i in range(Num_ciclos)]

print (Tam_ciclo*Num_ciclos, Tam_ciclo*Num_ciclos + Tam_grafo - 10)

for delta in Deltas:
    for v in range(Tam_ciclo):
        print (delta + v, delta + ((v+1) % Tam_ciclo))

for v in range(Tam_grafo - 10):
    w = random.randrange(v+3, Tam_grafo)
    print (v,w)
