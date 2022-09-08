import wield

a = 3.615
sigma = a*0.125
eps = 0.5
order = 32


X = [0,   0,    0,    0,    0, a/2, -a/2,  a/2, -a/2, a/2,  a/2, -a/2, -a/2]
Y = [0, a/2,  a/2, -a/2, -a/2,   0,    0,    0,    0, a/2, -a/2,  a/2, -a/2]
Z = [0, a/2, -a/2,  a/2, -a/2, a/2,  a/2, -a/2, -a/2,   0,    0,    0,    0]

C1 = wield.Crystal(order, a, a, a, sigma, X, Y, Z, 1, True)
C2 = C1

Rground = 

R1 = wield.createMatrixFromAngle(3.0,'y').transpose()
R2 = wield.createMatrixFromAngle(1.0,'z').transpose()

energy = wield.Surface(C1,R1,C2,R2,eps,0.0) #C1,R,C2,R,eps,1.0)
print("done! energy is",energy)
