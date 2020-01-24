varying highp vec4 outColor;

void main(void)
{
    gl_FragColor = outColor * vec4(1.0f - gl_FragCoord.z, 1.0f - gl_FragCoord.z, 1.0f - gl_FragCoord.z,1);
}
