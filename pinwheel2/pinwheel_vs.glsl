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

	vec3 P = vec3(0.2,0.3,0.8);
	vec3 T = vec3(0,0,0.5);
	vec3 U = vec3(0,1,0);
	vec3 D = (P-T)/length(P-T);
	vec3 R = cross(U,D);
	U = cross(D,R);

	mat4 laM;
	mat4 aa;
    mat4 tt;

	aa[0]=vec4(R[0],U[0],D[0],0);
    aa[1]=vec4(R[1],U[1],D[1],0);
    aa[2]=vec4(R[2],U[2],D[2],0);
    aa[3]=vec4(0,0,0,1);
    tt[0]=vec4(1,0,0,0);
    tt[1]=vec4(0,1,0,0);
    tt[2]=vec4(0,0,1,0);
    tt[3]=vec4(-P[0],-P[1],-P[2],1);

	laM = aa*tt;

	float left = -0.1;
    float right = 0.1;
    float top = 0.07;
    float bottom = -0.07;
    float near = 0.1;
    float far = 10;
    float a = 2*near/(right-left);
    float b = 2*near/(top-bottom);
    float c = (right+left)/(right-left);
    float d = (top+bottom)/(top-bottom);
    float e = (near+far)/(near-far);
    float g = 2*near*far/(near-far);

	mat4 pjM;
	pjM[0] = vec4(a,0,0,0);
	pjM[1] = vec4(0,b,0,0);
    pjM[2] = vec4(c,d,e,-1);
    pjM[3] = vec4(0,0,g,0);

	gl_Position = pjM*laM*wM*vertices[gl_VertexID];							
	vs_color = colors[gl_VertexID%3];							
}																	