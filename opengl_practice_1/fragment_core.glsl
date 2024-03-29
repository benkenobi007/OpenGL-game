#version 450

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

//Uniforms
uniform Material material;
uniform vec3 lightPos0;
uniform vec3 camPosition;

//Functions

vec3 calculateAmbient(Material material){
	return material.ambient;
}

vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0)
{
	vec3 posToLightDirVec = normalize(lightPos0 - vs_position);
	float diffuse = clamp(dot(vs_normal, posToLightDirVec), 0, 1);
	vec3 diffuseFinal = material.diffuse * diffuse;

	return diffuseFinal;
}

vec3 calculateSpecular(Material material, vec3 vs_position, vec3 vs_normal, vec3 lightPos0, vec3 camPosition){
	vec3 lightToPosDirVec = normalize(vs_position - lightPos0);
	vec3 reflectedDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(camPosition - vs_position);
	float specularConstant = pow(max(dot(reflectedDirVec, posToViewDirVec), 0), 10);
	vec3 specularFinal = material.specular * specularConstant * texture(material.specularTex, vs_texcoord).rgb;

	return specularFinal;
}

void main(){
//	fs_color = vec4(vs_color, 1.f);
//	fs_color = texture(texture0, vs_texcoord) + texture(texture1, vs_texcoord);

	//Ambient Lighting
	vec3 ambientFinal = calculateAmbient(material);

	//Diffuse Lighting
	vec3 diffuseFinal = calculateDiffuse(material, vs_position, vs_normal, lightPos0);

	//Specular Lighting
	vec3 specularFinal = calculateSpecular(material, vs_position, vs_normal, lightPos0, camPosition);

	//Attenuation

	//Final light
	fs_color = texture(material.diffuseTex, vs_texcoord) 
	 //vec4(vs_color, 1.f)
	* (vec4(ambientFinal, 1.f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f));
}