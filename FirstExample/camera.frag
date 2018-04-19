#version 430 core
in vec2 texCoord;
in vec3 fragPos;

out vec4 fColor;

uniform sampler2D texture0;
uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform float Ambient;
uniform vec3 ViewPos;

void main(){
	vec4 texColor = texture(texture0, texCoord);
	
	vec3 ambient = Ambient * LightColor;

	vec3 norm = normalize(vec3(0,1,0));
	vec3 lightDir = normalize(LightPosition - fragPos);
	float diff = max(dot(norm, lightDir), 0.0) / pow(distance(LightPosition, fragPos), 2);
	vec3 diffuse = diff * LightColor;

	vec3 viewDir = normalize(ViewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = 0.5 * spec * LightColor;

	vec3 result = (ambient + diffuse + specular) * texColor.xyz;
	fColor = vec4(result , 1.0f);
}