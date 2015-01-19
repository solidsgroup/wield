import bpy

scale = 5.; # Coordinate scaling
max = 0.5; # Maximum value for color shading


crystal1Tex = bpy.data.textures.new("crystal1Tex",type="VOXEL_DATA");
crystal1Tex.voxel_data.file_format = "BLENDER_VOXEL";
crystal1Tex.voxel_data.filepath = "/home/brandon/LANL_2013/Wield/scripts/blender/voxels.bvox"
crystal1Tex.voxel_data.extension = "REPEAT"
crystal1Tex.use_color_ramp = True;
crystal1Tex.color_ramp.elements.new(0.00*max).color=(0,0,1,0.2);
crystal1Tex.color_ramp.elements.remove(crystal1Tex.color_ramp.elements[0]);
crystal1Tex.color_ramp.elements.remove(crystal1Tex.color_ramp.elements[1]);
crystal1Tex.color_ramp.elements.new(0.25*max).color=(0,1,1,1);
crystal1Tex.color_ramp.elements.new(0.50*max).color=(0,1,0,1);
crystal1Tex.color_ramp.elements.new(0.75*max).color=(1,1,0,1);
crystal1Tex.color_ramp.elements.new(1.00*max).color=(1,0,0,1);
#crystal1Tex.use_map_density;
#crystal1Tex.use_map_emission;

crystal1Mat = bpy.data.materials.new("crystal1Mat");
crystal1Mat.type = "VOLUME"
crystal1Mat.volume.density=0.;
crystal1Mat.volume.density_scale=10.;
crystal1Mat.volume.step_size = 0.01;
crystal1TextureSlot = crystal1Mat.texture_slots.add();
crystal1TextureSlot.texture = crystal1Tex;
crystal1TextureSlot.texture_coords = "GLOBAL"
crystal1TextureSlot.use_map_density = True;
crystal1TextureSlot.density_factor = 4.;
crystal1TextureSlot.use_map_emission = True;
crystal1TextureSlot.emission_factor = 2.;
crystal1TextureSlot.scale = [scale,scale,scale];



