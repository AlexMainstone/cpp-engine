uniform sampler2D tex;
uniform vec2 playerpos;

void main()
{
    vec4 pixel = texture2D(tex, gl_TexCoord[0].xy);
    float dist = distance(gl_TexCoord[0].xy, playerpos.xy);

    if(dist > 10) {
        gl_FragColor = gl_Color * 0;
    } else {
        gl_FragColor = gl_Color;
    }
}