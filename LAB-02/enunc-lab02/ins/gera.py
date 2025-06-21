N = 1000
M = 4000
import random
print (N, M)
for i in range(M):
    x = random.randint(0,N-1)
    y = x
    while(y == x):
        y = random.randint(0,N-1)
    print (x,y,random.randint(-100,1000))
    
