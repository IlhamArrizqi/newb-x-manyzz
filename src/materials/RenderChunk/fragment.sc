$input v_color0, v_color1, v_fog, v_refl, v_texcoord0, v_lightmapUV, v_extra, v_wpos, v_uv0

#include <bgfx_shader.sh>
#include <newb/main.sh>

SAMPLER2D_AUTOREG(s_MatTexture);
SAMPLER2D_AUTOREG(s_SeasonsTexture);
SAMPLER2D_AUTOREG(s_LightMapTexture);

/*normal mapping*/
#undef saturate
#define saturate( x ) clamp( x, 0.0, 1.0 )
#define grayscale( x ) ( ( x.r + x.g + x.b ) / 3.0 )
#define viewcoord( m, n ) mat3( -m.z, m.y * n.x, 0.0, m.x * n.y, -m.z, 0.0, m.x, m.y * n.z, 0.0 ) * n
#define tbn( m, n ) mat3( m.z, m.y * n.x, -m.x, m.x * n.y, m.z, -m.y, m.x, m.y * n.z, m.z ) * n

float heightmap( highp vec2 uv ){
    return saturate( grayscale( texture2D( s_MatTexture, uv ).rgb ) / grayscale( texture2DLod( s_MatTexture, uv, 10.0 ).rgb ) );
    } 

highp vec3 normal3D( highp vec2 uv, highp vec3 m, highp vec3 n, float offset ){
    highp vec3 vcoord = viewcoord( m, n );
                        vcoord = vec3( -vcoord.x, vcoord.y, 0.0 );  
  
    float tex0 = heightmap( uv );
    float tex1 = heightmap( uv + vcoord.xy * offset );
    
    vec2 pnx = vec2( heightmap( uv + vec2( offset, 0.0 ) ), heightmap( uv - vec2( offset, 0.0 ) ) );
    vec2 pny = vec2( heightmap( uv - vec2( 0.0, offset ) ), heightmap( uv + vec2( 0.0, offset ) ) );   
    
    vec2 normxy = clamp( ( saturate( tex0 - vec2( pnx.x, pny.x ) ) - saturate( tex0 - vec2( pnx.y, pny.y ) ) ) / 0.01, -1.0, 1.0 );
    float normz = 1.0 - saturate( abs( normxy.x + normxy.y ) );

    return mix( n, tbn( vec3( normxy, normz ), n ), saturate( ( tex0 - tex1 ) / 0.01 ) );
    }

void main() {
  #if defined(DEPTH_ONLY_OPAQUE) || defined(DEPTH_ONLY) || defined(INSTANCING)
    gl_FragColor = vec4(1.0,1.0,1.0,1.0);
    return;
  #endif

  vec4 diffuse = texture2D(s_MatTexture, v_texcoord0);
  vec4 color = v_color0;

  #ifdef ALPHA_TEST
    if (diffuse.a < 0.6) {
      discard;
    }
  #endif

  #if defined(SEASONS) && (defined(OPAQUE) || defined(ALPHA_TEST))
    diffuse.rgb *= mix(vec3(1.0,1.0,1.0), texture2D(s_SeasonsTexture, v_color1.xy).rgb * 2.0, v_color1.z);
  #endif

  vec3 glow = nlGlow(s_MatTexture, v_texcoord0, v_extra.a);

  diffuse.rgb *= diffuse.rgb;

  vec3 lightTint = texture2D(s_LightMapTexture, v_lightmapUV).rgb;
  lightTint = mix(lightTint.bbb, lightTint*lightTint, 0.35 + 0.65*v_lightmapUV.y*v_lightmapUV.y*v_lightmapUV.y);

  color.rgb *= lightTint;

  float offset = 0.000185;
  highp vec3 m = normalize( v_wpos );
  highp vec3 n = normalize( cross( dFdx( v_wpos ), dFdy( v_wpos ) ) );

  highp vec3 normal = normal3D( v_uv0, m, n, offset );
  float a = radians(45.0);
  vec3 sunDir = normalize(vec3(cos(a), sin(a), cos(a) * sin(a)));
  float ndotl = max(dot(normal, sunDir), 0.3);
  vec3 ambient= vec3(0.02,0.04,0.08);

  vec3 lighting = ambient + ndotl;
  diffuse.rgb *= lighting;

  #if defined(TRANSPARENT) && !(defined(SEASONS) || defined(RENDER_AS_BILLBOARDS))
    if (v_extra.b > 0.9) {
      diffuse.rgb = vec3_splat(1.0 - NL_WATER_TEX_OPACITY*(1.0 - diffuse.b*1.8));
      diffuse.a = color.a;
    }
  #else
    diffuse.a = 1.0;
  #endif

  diffuse.rgb *= color.rgb;
  diffuse.rgb += glow;

  if (v_extra.b > 0.9) {
    diffuse.rgb += v_refl.rgb*v_refl.a;
  } else if (v_refl.a > 0.0) {
    // reflective effect - only on xz plane
    float dy = abs(dFdy(v_extra.g));
    if (dy < 0.0002) {
      float mask = v_refl.a*(clamp(v_extra.r*10.0,8.2,8.8)-7.8);
      diffuse.rgb *= 1.0 - 0.6*mask;
      diffuse.rgb += v_refl.rgb*mask;
    }
  }

  diffuse.rgb = mix(diffuse.rgb, v_fog.rgb, v_fog.a);

  diffuse.rgb = colorCorrection(diffuse.rgb);

  gl_FragColor = diffuse;
}
