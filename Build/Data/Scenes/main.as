<?xml version="1.0" encoding="UTF-8"?>
<!--# Basic scene (map) text format
# Some are optional depending on the entity type, but should be specified in the given order
# Format = EntityTypeID shaderID [xpos ypos zpos] [size] [quality] [textureID]-->
<atlasscene name="main.as">
	<bgmusic>
		<sound file="test01.mp3"/>
		<sound file="test02.mp3"/>
	</bgmusic>
	<script file="main.asc"/>
	
	<camera>
		<position x="0" y="3.0" z="5.0"/>
		<position x="0" y="0.0" z="0.0"/>
	</camera>
		
	<sky name="muddysky"/>
	
	<lights>
		<ambient r="0.5" g="1.0" b="1.0"/>
	</lights>
	
	<entities>
		<origin/>
		<plane name="ground">
			<shader value="texture"/>
			<position x="0" y="-0.01" z="0"/>
			<uniformscale value="2"/>	
		</plane>
		<cone/>
	</entities>
</atlasscene>




