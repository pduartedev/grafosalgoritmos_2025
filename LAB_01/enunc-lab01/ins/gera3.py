Tam_ciclo = 1000
Num_ciclos = 5
Deltas = [Tam_ciclo * i for i in range(Num_ciclos)]

print (Tam_ciclo*Num_ciclos, Tam_ciclo*Num_ciclos + (Num_ciclos-1)*2)

for delta in Deltas:
    for v in range(Tam_ciclo):
        print (delta + v, delta + ((v+1) % Tam_ciclo))

for c in range(Num_ciclos-1):
    print(Tam_ciclo//2 + Tam_ciclo * c, Tam_ciclo//2 + Tam_ciclo * (c+1))

for c in range(Num_ciclos-1):
    print(Tam_ciclo//2 + Tam_ciclo * c + 3, Tam_ciclo//2 + Tam_ciclo * (c+1) + 3)

