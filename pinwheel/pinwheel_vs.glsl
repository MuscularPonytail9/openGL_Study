#version 430 core													
																	
layout (location = 0) in vec4 color1; 							    
layout (location = 1) in vec4 color2; 							    
layout (location = 2) in vec4 color3; 							    

layout (location = 3) in float time;
out vec4 vs_color;						 							

void main(void)													
{																	
	const vec4 vertices[12] = vec4[12](vec4(0.0, 0.0, 0.5, 1.0),	
									   vec4(-0.5, 0.5, 0.5, 1.0),	
									   vec4(0.0, 0.5, 0.5, 1.0),	
									   vec4(0.0, 0.0, 0.5, 1.0),	
									   vec4(-0.5, -0.5, 0.5, 1.0),	
									   vec4(-0.5, 0.0, 0.5, 1.0),	
									   vec4(0.0, 0.0, 0.5, 1.0),	
									   vec4(0.5, -0.5, 0.5, 1.0),	
									   vec4(0.0, -0.5, 0.5, 1.0),	
									   vec4(0.0, 0.0, 0.5, 1.0),	
									   vec4(0.5, 0.5, 0.5, 1.0),	
									   vec4(0.5, 0.0, 0.5, 1.0));	
	const vec4 colors[3] = vec4[3](color1, color2, color3);		

	float angle = time;
	mat4 wM = mat4(1.0);
	wM[0][0] = cos(radians(angle));
	wM[1][0] = -sin(radians(angle));
	wM[0][1] = sin(radians(angle));
	wM[1][1] = cos(radians(angle));

	gl_Position = wM*vertices[gl_VertexID];							
	vs_color = colors[gl_VertexID%3];							
}																	