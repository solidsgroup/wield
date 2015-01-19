import bpy
from numpy import sqrt

#User defined variables
a= 0.3209
c= 0.5209
Sigma1= 0.2
Sigma2= Sigma1
Epsilon= 0.5

AlphaX1= a
AlphaY1= a*sqrt(3.)
AlphaZ1= c
l1= a*sqrt(3.)/3.
l2= a*sqrt(3.)/6.


X =  [0.,  a/2.,  a/2., -a/2., -a/2.,      0.,  a/2., -a/2.,           0.,     0.,  a/2., -a/2. ,          0.]
Y =  [0.,  AlphaY1/2., -AlphaY1/2.,  AlphaY1/2., -AlphaY1/2.,     l1 ,  -l2 ,   -l2,   l1-AlphaY1,     l1,  -l2,    -l2 ,  l1-AlphaY1]
Z =  [0.,    0.,    0.,    0.,    0.,   -c/2., -c/2., -c/2.,        -c/2.,   c/2.,  c/2.,  c/2. ,        c/2.]

#Clear the scene
def allSelect(value=True,type='MESH'):
    scene = bpy.context.scene;
    for ob in scene.objects:
        if ob.type==type:
            ob.select=value;
if (bpy.context.scene.objects.active):
    bpy.ops.object.mode_set(mode='OBJECT');
scene = bpy.context.scene
scene.cursor_location = (0,0,0);
allSelect(True,type='MESH');
allSelect(True,type='LAMP');
bpy.ops.object.delete();    



for x,y,z in zip(X,Y,Z):
    bpy.ops.mesh.primitive_uv_sphere_add(segments=32, ring_count=16, size=0.1, view_align=False, enter_editmode=False, location=(x,y,z), rotation=(0.0, 0.0, 0.0))
    bpy.ops.object.shade_smooth()

bpy.ops.mesh.primitive_cube_add()
bpy.ops.transform.resize(value=[AlphaX1/2,AlphaY1/2,AlphaZ1/2])



