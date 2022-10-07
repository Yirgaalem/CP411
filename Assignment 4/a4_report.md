# A4 Report

Author: Nahor Yirgaalem (sign your name here)

Date: November 1, 2021   (insert the date)

Check [readme.txt](readme.txt) for lab work statement and self-evaluation. 

## Q1 Culling, Lighting, Shading (short_answer)
	
### Q1.1 Concepts of culling
When given a set of polygons, culling is the process of determining which polygon is visible at each pixel. Clipping is the process of removing the non culled polygon (the polygon that is not visible)

Object Precision uses binary space partition trees which splits 3D world with planes. It can also be used to modle the shape of objects, and in other visibility algorithims
Image Precision assumes polygons do not intersect one another (although they may at edges or verticies). 

### Q1.2 Culling computing
It is front face because N * PrefPeye = -7 < 0. 

The depth of the triangle is 44/(3*sqrt(17)).

### Q1.3 Concepts of lighting and shading
	1. The four light models are;Ambient, Point light, Directional, Emission
	2. Light model's determine the approximate illumination effects in the real world
	3. The three shading models are; Constant shading, Gouraud shading, Phong Shading

### Q1.4 Lighting computing

	images/a4q1.4.jpg
## Q2 OpenGL culling, lighting, shading (lab practice)
	
### Q2.1 Hidden surface removal
 
Complete? (Yes/No) Yes

If Yes, insert a screen shot image to show the completion.

![image caption](images/demo.png){width=90%} opengl_culling.png

If No,  Add a short description to describe the issues encountered.

### Q2.2 Lighting and Shading
 
Complete? (Yes/No) Yes

If Yes, insert a screen shot image to show the completion.

![image caption](images/demo.png){width=90%} opengl_cube_draw.png

If No,  Add a short description to describe the issues encountered.



## Q3 SimpleView2 - culling, lighting, shading (programming)
	
### Q3.1 Culling
 

Complete? (Yes/No) Yes

If Yes, insert a screen shot image to show the completion.

[image caption](images/demo.png){width=90%} simple_light.png

If No, add a short description to describe the issues encountered.



### Q3.2 Lighting
 

Complete? (Yes/No) Yes

If Yes, insert a screen shot image to show the completion.

[image caption](images/demo.png){width=90%} images/light.png

If No, add a short description to describe the issues encountered.



### Q3.3 Shading
 

Complete? (Yes/No) Yes

If Yes, insert a screen shot image to show the completion.

[image caption](images/demo.png){width=90%} images/shading.png

If No, add a short description to describe the issues encountered.



### Q3.4 Animations
 

Complete? (Yes/No) Yes

If Yes, insert a screen shot image to show the completion.

[image caption](images/demo.png){width=90%} images/animation.png

If No, add a short description to describe the issues encountered.






**References**

1. CP411 a4
2. Add your references if you used. 
