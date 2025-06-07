print (1000, 1004)

Tam_ciclo = 200
Num_ciclos = 5
Deltas = [Tam_ciclo * i for i in range(Num_ciclos)]

for delta in Deltas:
    for v in range(Tam_ciclo):
        print (delta + v, delta + ((v+1) % Tam_ciclo))

for c in range(Num_ciclos-1):
    print(Tam_ciclo//2 + Tam_ciclo * c, Tam_ciclo//2 + Tam_ciclo * (c+1))

