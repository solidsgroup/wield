import wield
from numpy import linspace, loadtxt
from pylab import plot, show

a = 1.0
sigma = 0.1
eps = 0.25
order = 32
tolerance = 1E-16

X = [0,   0,    0,    0,    0, a/2, -a/2,  a/2, -a/2, a/2,  a/2, -a/2, -a/2]
Y = [0, a/2,  a/2, -a/2, -a/2,   0,    0,    0,    0, a/2, -a/2,  a/2, -a/2]
Z = [0, a/2, -a/2,  a/2, -a/2, a/2,  a/2, -a/2, -a/2,   0,    0,    0,    0]

C1 = wield.CrystalSQGD(order, a, a, a, sigma, X, Y, Z, 1, True)
C2 = C1

Rground = wield.createMatrixFromZX([1,1,1],[-1,1,0])
ground  = wield.VolumeSQGD(C1,Rground,C1,Rground,eps,tolerance)

R1 = wield.createMatrixFromZX([-1,1,0],[1,1,0])
R2 = wield.createMatrixFromZX([-1,1,0],[1,1,0])

csls = []
thetas = linspace(0,90,1000)

for theta in thetas:
    print(theta)
    Rtheta1 = wield.createMatrixFromXAngle(theta/2)
    Rtheta2 = wield.createMatrixFromXAngle(-theta/2)
    csl  = ground/wield.VolumeSQGD(C1,Rtheta1 @ R1,C2,Rtheta2 @ R2,eps,tolerance)
    csls.append(csl)

plot(thetas,csls)
ref = loadtxt("output.ref")
plot(ref[:,0],ref[:,1],linestyle=":")
show()
