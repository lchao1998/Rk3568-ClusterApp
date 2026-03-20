
varying vec2 vTexCoord;

out vec4 fragColor;

void main()
{
    precision lowp float;
    
    vec4 pointer = vec4(0.0);
    
    vec4 colorfg_positive_Blue = texture2D(textureDrivingPower_Blue, vTexCoord + vec2(textureDrivingPower_BlueOffsetU, textureDrivingPower_BlueOffsetV));
	vec4 colorfg_positive_Red = texture2D(textureDrivingPower_Red, vTexCoord + vec2(textureDrivingPower_RedOffsetU, textureDrivingPower_RedOffsetV));
    vec4 colorfg_negitive = texture2D(textureEnergyRecovery,vTexCoord + vec2(textureEnergyRecoveryOffsetU, textureEnergyRecoveryOffsetV));
    vec4 colorfg = vec4(0.0);
    if(vTexCoord.y >= 0.2 && vTexCoord.y <= 0.7)
    {
        colorfg = colorfg_positive_Blue;
        pointer = texture2D(texturePointer,vTexCoord + vec2(textureDrivingPower_BlueOffsetU, textureDrivingPower_BlueOffsetV + 0.45));
    }
	else if(vTexCoord.y > 0.7)
	{
		colorfg = colorfg_positive_Red;
		pointer = texture2D(texturePointer,vTexCoord + vec2(textureDrivingPower_RedOffsetU, textureDrivingPower_RedOffsetV+ 0.4));
	}
    else 
    {
        colorfg = colorfg_negitive;
        pointer = texture2D(texturePointer, vTexCoord + vec2(textureEnergyRecoveryOffsetU, textureEnergyRecoveryOffsetV));
    }
    
    colorfg = mix(colorfg ,pointer, pointer.a); 
	    
    fragColor = colorfg * blendIntensity;		
}
