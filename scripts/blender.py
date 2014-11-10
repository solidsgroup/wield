import bpy
from numpy import sqrt,linalg

facet4 = False;
print("-------------------------");

#
# USER DEFINED VARIABLE REGION
#
b  = 0.3;
#facet4 = True;
n1 = [0, .7];
n2 = [0,-.7];
n3 = [0,0,0];
#n1 = [-0.35,0];
#n2 = [.35, 0];
#n3 = [0,-.975]
rep1 = 10;
rep2 = 10;
lenX = 12;
lenY = 12;
lenZ = 4;
seperation = 2;
translation = (.25,.25,1);

#Make normal vectors 3D
n1 = [n1[0],n1[1],sqrt(1-linalg.norm(n1)**2)];
n2 = [n2[0],n2[1],sqrt(1-linalg.norm(n2)**2)];
n3 = [n3[0],n3[1],sqrt(1-linalg.norm(n3)**2)];
print(n1);
print(n2);
print(n3);

def add(a,b):
    return [a[0]+b[0],a[1]+b[1],a[2]+b[2]];
def subtract(a,b):
    return [a[0]-b[0],a[1]-b[1],a[2]-b[2]];
def multiply(a,alpha):
    return [alpha*a[0],alpha*a[1],alpha*a[2]];
def dot(a,b):
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
def norm(a):
    return sqrt(dot(a,a));
def cross(a,b):
    return (a[1]*b[2]-a[2]*b[1], a[2]*b[0]-a[0]*b[2], a[0]*b[1]-a[1]*b[0]);
def getIntersectionPoint(n1,n2,b):
    A = [[n1[0],n1[1]],[n2[0],n2[1]]];
    B = [b,b];
    X = linalg.solve(A,B);
    return [X[0],X[1],0];
def addFacet2(i):
    verts=[];
    faces=[];
    d1 = (0,0,b);
    d2 = cross(n1,d1); 
    d2 = multiply(d2, 0.5*sqrt(lenX**2 + lenY**2)/norm(d2));
    d3 = multiply(cross(d1,d2),norm(cross(d1,d2)));
    d3 = multiply(d3, dot(d1,n1)/dot(d3,n1));
    d4 = multiply(cross(d1,d2),norm(cross(d1,d2)));
    d4 = multiply(d4, dot(d1,n2)/dot(d4,n2));
    offset = multiply(add(d3,multiply(d4,-1)),i/2);
    verts.append(add(add(offset,multiply(d2,+1.)), add(offset, d1)));
    verts.append(add(add(offset,multiply(d2,-1.)), add(offset, d1)));
    verts.append(add(add(offset,multiply(d2,+1.)), add(offset, d3)));
    verts.append(add(add(offset,multiply(d2,-1.)), add(offset, d3)));
    verts.append(add(add(offset,multiply(d2,+1.)), add(offset, d4)));
    verts.append(add(add(offset,multiply(d2,-1.)), add(offset, d4)));
    faces.append((2,3,1,0));
    faces.append((0,1,5,4));
    mesh = bpy.data.meshes.new("facet");
    object = bpy.data.objects.new("facet",mesh);
    object.location=bpy.context.scene.cursor_location;
    bpy.context.scene.objects.link(object);
    mesh.from_pydata(verts,[],faces);
    mesh.update(calc_edges=True);

def addFacet(i,j,k):
    verts=[];
    faces=[];
    #Points of original simplex
    e0 = [0,0,b];
    e1 = getIntersectionPoint(n2,n3,b);
    e2 = getIntersectionPoint(n3,n1,b);
    e3 = getIntersectionPoint(n1,n2,b);
    #Offset vectors
    d1 = multiply(subtract(e2,e1),i);
    d2 = multiply(subtract(e3,e1),j);
    d3 = multiply(subtract(e1,e2),k);
    # Original symplex facet
    verts.append(add(d1,add(d2,add(d3,e0))));
    verts.append(add(d1,add(d2,add(d3,e1))));
    verts.append(add(d1,add(d2,add(d3,e2))));
    verts.append(add(d1,add(d2,add(d3,e3))));
    # Inverted Facet
    e0 = [e1[0]+e2[0]-e0[0],e1[1]+e2[1]-e0[1],-b];
    verts.append(add(d1,add(d2,add(d3,e0))));
    e1 = add(e1,subtract(e2,e3));
    verts.append(add(d1,add(d2,add(d3,e1))));
    # Add all faces
    faces.append((0,1,2));
    faces.append((0,2,3));
    faces.append((0,3,1));
    faces.append((4,2,1));
    faces.append((4,5,2));
    faces.append((4,1,5));
    #Use vertices and faces to create blender object
    mesh = bpy.data.meshes.new("facet");
    object = bpy.data.objects.new("facet",mesh);
    object.location=bpy.context.scene.cursor_location;
    bpy.context.scene.objects.link(object);
    mesh.from_pydata(verts,[],faces);
    mesh.update(calc_edges=True);

def addFacet4(i,j):
    verts=[];
    faces=[];
    d0 = (0,0,b);
    d1 = (n1[0],n1[1],0); d1 = multiply(d1,1./norm(d1));
    d1 = multiply(d1, dot(d0,n1)/dot(d1,n1));
    d2 = cross(n1,d1);    d2 = multiply(d2,norm(d1)/norm(d2));
    d3 = multiply(d1,-1.);
    d4 = multiply(d2,-1.);
    
    offset = add(multiply(add(d1,multiply(d3,-1.)),i),multiply(add(d2,multiply(d4,-1.)),j));
    print(offset);
    verts.append(add(offset,d0));
    verts.append(add(offset,add(d1,d2)));
    verts.append(add(offset,add(d1,d4)));
    verts.append(add(offset,add(d3,d2)));
    verts.append(add(offset,add(d3,d4)));

    faces.append((0,2,1));
    faces.append((0,3,4));
    faces.append((0,1,3));
    faces.append((0,4,2));
    mesh = bpy.data.meshes.new("facet");
    object = bpy.data.objects.new("facet",mesh);
    object.location=bpy.context.scene.cursor_location;
    bpy.context.scene.objects.link(object);
    mesh.from_pydata(verts,[],faces);
    mesh.update(calc_edges=True);

def addCube(lx,ly,lz,name="cube"):
    verts=[];
    faces=[];
    #20  64
    #31  75
    verts.append((+lx/2,+ly/2,-lz/2));
    verts.append((+lx/2,-ly/2,-lz/2));
    verts.append((-lx/2,+ly/2,-lz/2));
    verts.append((-lx/2,-ly/2,-lz/2));
    verts.append((+lx/2,+ly/2,+lz/2));
    verts.append((+lx/2,-ly/2,+lz/2));
    verts.append((-lx/2,+ly/2,+lz/2));
    verts.append((-lx/2,-ly/2,+lz/2));
    faces.append((0,1,3,2));
    faces.append((1,0,4,5)); # Ok
    faces.append((2,3,7,6)); # Ok
    faces.append((5,4,6,7)); # Ok
    faces.append((0,2,6,4));
    faces.append((3,1,5,7));
    #Use vertices and faces to create blender object
    mesh = bpy.data.meshes.new(name);
    object = bpy.data.objects.new(name,mesh);
    object.location=bpy.context.scene.cursor_location;
    bpy.context.scene.objects.link(object);
    mesh.from_pydata(verts,[],faces);
    mesh.update(calc_edges=True);

def allSelect(value=True,type='MESH'):
    scene = bpy.context.scene;
    for ob in scene.objects:
        if ob.type==type:
            ob.select=value;
def select(name):
    allSelect(False);
    scene = bpy.context.scene;
    for ob in scene.objects:
        if ob.name==name:
            ob.select=True;
def selectActive(name):
    select(name);
    bpy.context.scene.objects.active = bpy.data.objects[name];
def delete(name):
    allSelect(False);
    selectActive(name);
    bpy.ops.object.delete();    
    

#Clear the scene
if (bpy.context.scene.objects.active):
    bpy.ops.object.mode_set(mode='OBJECT');
scene = bpy.context.scene
scene.cursor_location = (0,0,0);
allSelect(True,type='MESH');
allSelect(True,type='LAMP');
bpy.ops.object.delete();    

#Generate facets
if abs(norm(cross((n1[0],n1[1],0),(n2[0],n2[1],0)))) < .01:
    if facet4 == True:
        for i in range(-rep1,rep1):
            for j in range(-rep2,rep2):
                addFacet4(i,j);
    else:
        for i in range(-rep1,rep1):
            addFacet2(i);
else:
    for i in range(-rep1,rep1):
        for j in range(-rep2,rep2):
            addFacet(i,j,0);

#Merge facets together
for ob in scene.objects:
    if ob.name[0:5]=='facet' and ob.type=='MESH':
        ob.select=True;
bpy.context.scene.objects.active = bpy.data.objects["facet"];
bpy.ops.object.join();

#Remove excess points
bpy.context.scene.objects.active = bpy.data.objects["facet"];
bpy.ops.object.mode_set(mode='EDIT');
bpy.ops.mesh.remove_doubles();
bpy.ops.object.mode_set(mode='OBJECT');

#Create Box
addCube(lenX/2,lenY/2,lenZ/2,"bottom");
selectActive("bottom");
chopper = bpy.data.objects["bottom"].modifiers.new('Booh', 'BOOLEAN');
chopper.object = bpy.data.objects["facet"];
chopper.operation = 'INTERSECT';
bpy.ops.object.modifier_apply(apply_as='DATA',modifier="Booh");
delete("facet");

addCube(lenX/2,lenY/2,lenZ/2,"top");
selectActive("top");
chopper = bpy.data.objects["top"].modifiers.new('Booh', 'BOOLEAN');
chopper.object = bpy.data.objects["bottom"];
chopper.operation = 'DIFFERENCE';
bpy.ops.object.modifier_apply(apply_as='DATA',modifier="Booh");

#Convert as many triangles to parallelograms as possible
selectActive("bottom");
bpy.ops.object.mode_set(mode='EDIT');
bpy.ops.mesh.quads_convert_to_tris(); #bpy.ops.mesh.tris_convert_to_quads(limit=180);
bpy.ops.object.mode_set(mode='OBJECT');
selectActive("top");
bpy.ops.object.mode_set(mode='EDIT');
bpy.ops.mesh.quads_convert_to_tris(); #bpy.ops.mesh.tris_convert_to_quads(limit=180);
bpy.ops.object.mode_set(mode='OBJECT');

#Render settings
bpy.context.scene.render.use_freestyle = True;
bpy.context.scene.render.line_thickness = 2.;
#bpy.ops.scene.freestyle.crease_angle = 28;
bpy.context.scene.render.resolution_y = bpy.context.scene.render.resolution_x;
bpy.context.scene.render.alpha_mode = 'TRANSPARENT';

#World and lighting settings
bpy.context.scene.world.light_settings.use_environment_light = True;
bpy.context.scene.world.light_settings.environment_energy = .3;
bpy.context.scene.world.light_settings.use_ambient_occlusion = True;


allSelect(False);
select("top");
bpy.ops.transform.translate(value=(translation[0],translation[1],translation[2] + seperation/2.));
select("bottom");
bpy.ops.transform.translate(value=(translation[0],translation[1],translation[2] - seperation/2.));
