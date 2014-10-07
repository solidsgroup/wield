#!/usr/bin/env python
import numpy as np

#specify header dimension
nx, ny, nz, nframes = 100,100,100,1
header = np.array([nx,ny,nz,nframes])

#create simple distance to center texture
x = np.linspace(-1,1,nx)
y = np.linspace(-1,1,ny)
z = np.linspace(-1,1,nz)
xx,yy,zz = np.meshgrid(x,y,z,indexing='ij')
pointdata = yy.flatten()**2+zz.flatten()**2+xx.flatten()**2

#open and write to file
binfile = open('test1.bvox','wb')
header.astype('<i4').tofile(binfile)
pointdata.astype('<f4').tofile(binfile)
