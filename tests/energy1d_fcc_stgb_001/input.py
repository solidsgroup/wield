import wield
from numpy import linspace, loadtxt
from pylab import plot, show

a = 3.615
sigma = a*0.175
eps = 0.5
order = 8
tolerance = 1E-8

X = [0,   0,    0,    0,    0, a/2, -a/2,  a/2, -a/2, a/2,  a/2, -a/2, -a/2]
Y = [0, a/2,  a/2, -a/2, -a/2,   0,    0,    0,    0, a/2, -a/2,  a/2, -a/2]
Z = [0, a/2, -a/2,  a/2, -a/2, a/2,  a/2, -a/2, -a/2,   0,    0,    0,    0]

C1 = wield.CrystalGD(order, a, a, a, sigma, X, Y, Z, 1, True)
C2 = C1

Rground = wield.createMatrixFromZX([1,1,1],[-1,1,0])
ground  = wield.Surface(C1,Rground,C1,Rground,eps,tolerance)

R1 = wield.createMatrixFromZX([0,0,1],[1,0,0])
R2 = wield.createMatrixFromZX([0,0,1],[1,0,0])

energies = []
thetas = linspace(0,90,90)

for theta in thetas:
    Rtheta1 = wield.createMatrixFromXAngle(theta/2)
    Rtheta2 = wield.createMatrixFromXAngle(-theta/2)
    energy  = 1.0 - wield.Surface(C1,Rtheta1 @ R1,C2,Rtheta2 @ R2,eps,tolerance)/ground
    energies.append(energy)

plot(thetas,energies)
ref = loadtxt("output.ref")
plot(ref[:,0],ref[:,1],linestyle=":")
show()
