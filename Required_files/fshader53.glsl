varying  vec2 texCoord;

uniform sampler2D texture;


// per-fragment/pixel interpolated values from the vertex shader
varying  vec3 fN;
varying  vec3 fL;
varying  vec3 fE;

uniform vec4 AmbientLight, DiffuseLight, SpecularLight;
uniform vec4 ka, kd, ks;
uniform float Shininess;

void main()
{
    // Normalize the input lighting vectors
    vec3 N = normalize(fN);
    vec3 E = normalize(fE);
    vec3 L = normalize(fL);
    
    vec3 H = normalize( L + E );
    
    // Compute terms in the illumination equation
    vec4 ambient = AmbientLight * texture2D( texture, texCoord );
    
    vec4  diffuse = DiffuseLight * texture2D( texture, texCoord ) * max( dot(L, N), 0.0 );///(0.2*pow(length((view * LightPosition).xyz - pos),2.0));
    
    vec4  specular = SpecularLight * ks * pow( max(dot(N, H), 0.0), Shininess );
    
    if ( dot(L, N) < 0.0 ) specular = vec4(0.0, 0.0, 0.0, 1.0);
    
    gl_FragColor = ambient + specular + diffuse ;
    //gl_FragColor = ambient + texture2D( texture, texCoord ) + specular;
    //gl_FragColor = texture2D( texture, texCoord );
    gl_FragColor.a = 1.0;
}
