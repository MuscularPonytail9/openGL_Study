#version 430 core													
																	
void main(void)													
{																	
   const vec4 vertices[6] = vec4[6](vec4(0.02, 0.0, 0.5, 1.0),	
									vec4(-0.02, 0.0, 0.5, 1.0),	
									vec4(-0.02, -1.0, 0.5, 1.0),	
									vec4(0.02, 0.0, 0.5, 1.0),	
									vec4(-0.02, -1.0, 0.5, 1.0),	
									vec4(0.02, -1.0, 0.5, 1.0));	

    // 2. �� ��Ʈ���� �����
	// 2-1. ī�޶� ��ġ, Ÿ��, �ʱ� ������ �����ϱ�
	vec3 eyePos = vec3(0.2, 0.3, 0.8);
	vec3 target = vec3(0.0, 0.0, 0.5);
	vec3 upVec = vec3(0.0, 1.0, 0.0);
	// 2-2. ī�޶� 3�� ���ϱ�
	vec3 D = (eyePos - target)/length(eyePos - target);
	vec3 R = cross(upVec, D);
	vec3 U = cross(D, R);
	// 2-3. LookAt ��Ʈ���� ���ϱ�
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

	// 3. ���� ��� �����
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

	gl_Position = prjM*LookAtM*vertices[gl_VertexID];							
}																	