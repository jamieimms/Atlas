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
		<target x="0" y="0.0" z="0.0"/>
	</camera>
		
	<sky name="muddysky"/>
	
	<lights>
		<ambient>
			<colour r="1.0" g="0.5" b="0.5"/>
		</ambient>
		<point id="1">
			<position x="0" y="5.0" z="0.0"/>
			<colour r="1.0" g="1.0" b="1.0"/>		
		</point>
	</lights>
	
	<entities>
		<origin/>
		<plane name="ground" id="1">
			<shader name="littex"/>
			<position x="0" y="-0.01" z="0"/>
			<uniformscale value="10"/>
			<texture name="wall.jpg"/>
		</plane>
		<cube name="other" id="2">
			<shader name="littex"/>
			<position x="0" y="5.0" z="0"/>
			<uniformscale value="1"/>
			<texture name="crate.jpg"/>
		</cube>
	</entities>
</atlasscene>




