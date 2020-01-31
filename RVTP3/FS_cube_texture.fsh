varying highp vec4 outColor;
varying highp vec2 outTexCoord;
uniform sampler2D texture0;

void main(void)
{
    gl_FragColor = outColor*texture2D(texture0, outTexCoord);
    gl_FragColor.a = outColor.a;
}