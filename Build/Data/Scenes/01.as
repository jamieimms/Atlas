# Basic scene (map) text format
# Some are optional depending on the entity type, but should be specified in the given order
# Format = EntityTypeID shaderID [xpos ypos zpos] [size] [quality] [textureID]


## Lights
a 1.0 1.0 1.0

## origin helper arrows
0 0 1.0

## ground
1 2 2 -0.01 2 2 0
1 2 2 -0.01 -2 2 0
1 2 -2 -0.01 2 2 0
1 2 -2 -0.01 -2 2 0
1 2 -2 -0.01 -6 2 1
1 2 2 -0.01 -6 2 1

## cubes
3 2 0.0 10 0 0.5 4
3 2 0.2 12 0 0.5 4
3 2 0.4 14 0 0.5 4
3 2 0.6 16 0 0.5 4
3 2 0.8 18 0 0.5 4
3 2 1.0 20 0 0.5 4
3 2 1.2 22 0 0.5 4
3 2 1.4 24 0 0.5 4
3 2 1.6 26 0 0.5 4
3 2 1.8 28 0 0.5 4
3 2 2.0 30 0 0.5 4

# lit cone
4 2 0 5 0 0.2 10


