Dependencies:

GLEW: The OpenGL Extension Wrangler Library:  http://glew.sourceforge.net/

OpenGL Mathematics 0.9.8: http://glm.g-truc.net/0.9.8/index.html

Bullet Physics 2.86: http://bulletphysics.org/wordpress/
	Note: I built bullet using vs2015 so the libs required are e.g. "LinearMath_vs2015_debug.lib". Also note that I changed the runtime library
	to Multi-Threaded DLL (/MDd or /MD). Change this under code generation in vs project properties. You will get linker errors if bullet isn't built with this set.
 