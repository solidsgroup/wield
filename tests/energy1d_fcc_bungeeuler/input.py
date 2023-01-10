import wield

a = 1.0
sigma = 0.1
eps = 0.25
order = 32
tolerance = 1E-16

X = [0,   0,    0,    0,    0, a/2, -a/2,  a/2, -a/2, a/2,  a/2, -a/2, -a/2]
Y = [0, a/2,  a/2, -a/2, -a/2,   0,    0,    0,    0, a/2, -a/2,  a/2, -a/2]
Z = [0, a/2, -a/2,  a/2, -a/2, a/2,  a/2, -a/2, -a/2,   0,    0,    0,    0]

C1 = wield.CrystalGD(order, a, a, a, sigma, X, Y, Z, 1, True)
C2 = C1

#Rground = wield.createMatrixFromBungeEulerAngles(4,0,2)
#ground  = wield.Surface(C1,Rground,C1,Rground,eps,tolerance)

R1 = wield.createMatrixFromBungeEulerAngles(4,0,2)
R2 = wield.createMatrixFromBungeEulerAngles(0,0,6)


theta = 150


print(theta)
Rtheta1 = wield.createMatrixFromXAngle(theta)
Rtheta2 = wield.createMatrixFromXAngle(theta)
energy  = wield.SurfaceGD(C1,Rtheta1 @ R1,C2,Rtheta2 @ R2,eps,tolerance)


with open('output_py.ref', 'w') as f:
    
    f.write("%s %s\n" % (theta, energy))


