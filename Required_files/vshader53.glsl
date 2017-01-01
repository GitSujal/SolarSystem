attribute  vec2 vTexCoord;
varying vec2 texCoord;

attribute  vec4 vPosition;
attribute  vec3 vNormal;

varying  vec3 fN;
varying  vec3 fE;
varying  vec3 fL;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec4 LightPosition;

void main()
{
    vec3 pos = (View * Model * vPosition).xyz;
    
    fN = (View*Model*vec4(vNormal, 0.0)).xyz;
    fE = -pos;
    fL = (View*LightPosition).xyz;
    
    if( LightPosition.w != 0.0 ) {
        fL = (View*LightPosition).xyz - pos;
    }
    
    gl_Position = Projection * View * Model * vPosition;
    texCoord    = vTexCoord;

}
