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

	// 1. 로테이션 매트릭스 만들기
	float angle = time;
	mat4 wM = mat4(1.0);
	wM[0][0] = cos(radians(angle));
	wM[1][0] = -sin(radians(angle));
	wM[0][1] = sin(radians(angle));
	wM[1][1] = cos(radians(angle));

	// 2. 뷰 매트릭스 만들기
	// 2-1. 카메라 위치, 타겟, 초기 업벡터 설정하기
	vec3 eyePos = vec3(0.2, 0.3, 0.8);
	vec3 target = vec3(0.0, 0.0, 0.5);
	vec3 upVec = vec3(0.0, 1.0, 0.0);
	// 2-2. 카메라 3축 구하기
	vec3 D = (eyePos - target)/length(eyePos - target);
	vec3 R = cross(upVec, D);
	vec3 U = cross(D, R);
	// 2-3. LookAt 매트릭스 구하기
	mat4 vM_axis = mat4(1.0);
	vM_axis[0][0] = R.x;
	vM_axis[1][0] = R.y;
	vM_axis[2][0] = R.z;
	vM_axis[0][1] = U.x;
	vM_axis[1][1] = U.y;
	vM_axis[2][1] = U.z;
	vM_axis[0][2] = D.x;
	vM_axis[1][2] = D.y;
	vM_axis[2][2] = D.z;
	mat4 vM_trans = mat4(1.0);
	vM_trans[3][0] = -eyePos.x;
	vM_trans[3][1] = -eyePos.y;
	vM_trans[3][2] = -eyePos.z;
	mat4 LookAtM = vM_axis*vM_trans;

	// 3. 원근 행렬 만들기
	float left = -0.1;
	float right = 0.1;
	float top = 0.07;
	float bottom = -0.07;
	float near = 0.1;
	float far = 10;
	mat4 prjM = mat4(1.0);
	prjM[0][0] = 2*near/(right - left);
	prjM[2][0] = (right + left)/(right - left);
	prjM[1][1] = 2*near/(top - bottom);
	prjM[2][1] = (top + bottom)/(top - bottom);
	prjM[2][2] = (near + far)/(near - far);
	prjM[3][2] = (2*near*far)/(near - far);
	prjM[2][3] = -1;
	
	gl_Position = prjM*LookAtM*wM*vertices[gl_VertexID];							
	vs_color = colors[gl_VertexID%3];							
}																	

