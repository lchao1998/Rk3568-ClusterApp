in vec3 attr_pos;
in vec2 attr_uv0;

uniform mat4 modelViewProjection;

varying vec2 vTexCoord;

void main()
{
    vTexCoord = attr_uv0 + vec2(textureOffsetU, textureOffsetV);
	
    gl_Position = modelViewProjection * vec4(attr_pos, 1.0);
}