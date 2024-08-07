#version 420 core

layout (isolines) in;
in vec3 tessA[];
in vec3 tessB[];
in vec3 tessC[];
in vec3 tessD[];
in float tessDt[];
in float divisionY[];

uniform mat4 projectionViewMatrix;

vec3 polynomial(vec3 a, vec3 b, vec3 c, vec3 d, float t);

void main()
{
	float t = (gl_TessCoord.x / divisionY[0] + gl_TessCoord.y) * tessDt[0];
	gl_Position =
		projectionViewMatrix * vec4(polynomial(tessA[0], tessB[0], tessC[0], tessD[0], t), 1);
}

vec3 polynomial(vec3 a, vec3 b, vec3 c, vec3 d, float t)
{
	return a + t * (b + t * (c + t * d));
}
