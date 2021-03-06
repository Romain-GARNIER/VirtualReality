// Cours de Réalité Virtuelle
// leo.donati@univ-cotedazur.fr
//
// 2019_2020
//
// Modèle de Phong
//
varying highp vec4 outColor;
varying highp vec2 outTexCoord;
varying   highp vec3 outPos;
varying   highp vec3 outNormal;

uniform sampler2D texture0;
uniform samplerCube skybox;

uniform vec4 light_ambient_color;
uniform vec4 light_diffuse_color;
uniform vec4 light_specular_color;
uniform float light_specular_strength;
uniform vec3 light_position;
uniform vec3 eye_position;

void main(void)
{
    //Lecture de la texture
    vec4 color = vec4(outColor.rgb, 0.1f);

    //calcul de la composante ambiante
    vec4 ambient = light_ambient_color;

    //calcul de la composante diffuse
    vec3 norm = normalize(outNormal);
    vec3 lightdir = normalize(light_position - outPos);
    float coeff_diffusion = max(dot(lightdir, norm), 0.0);
    vec4 diffuse = (coeff_diffusion * light_diffuse_color) * color;

    //calcul de la composante spéculaire
    vec3 viewdir = normalize(outPos - eye_position);
    vec3 reflectdir = reflect(viewdir, norm);
    float coeff_specular = pow(max(dot(viewdir, reflectdir), 0.0), light_specular_strength);
    vec4 specular = (coeff_specular * light_specular_color) * vec4(outColor.rgb, 1.0f);

    //couleur finale
    gl_FragColor = vec4(textureCube(skybox, reflectdir).rgb + specular.rgb, outColor.a);
}
