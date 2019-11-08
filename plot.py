import numpy as np
import scipy.interpolate as si
from mayavi import mlab
import pylab

data = np.loadtxt("field.dat")
x = data[:,0]
y = data[:,1]
d = data[:,2]
print(x)
print(y)
print(d)

# Generate the figure
#figure = mlab.figure()

# Generate the 3D mesh
xi, yi = np.meshgrid(np.linspace(min(x),max(x),100),np.linspace(min(y),max(y),100))

# Interpolate d over the 3D mesh
di = si.griddata((x, y), d, (xi, yi))

#pylab.pcolor(di)
pylab.contourf(xi,yi,di,100)
pylab.show()
## Generate the desired figure
#min_d = d.min()
#max_d = d.max()
#grid = mlab.pipeline.scalar_field(di)
#mlab.pipeline.volume(grid, vmin=min_d, vmax=min_d + .5*(max_d-min_d))
#
## Other good options too
### mlab.contour3d(di, vmin=min_d, vmax=min_d + .8*(max_d-min_d))
### pts = mlab.points3d(x, y, z, d)
#mlab.axes()
#mlab.show()
