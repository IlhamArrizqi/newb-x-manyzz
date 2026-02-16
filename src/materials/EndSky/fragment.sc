#ifndef INSTANCING
$input v_texcoord0, v_posTime
#endif

#include <bgfx_shader.sh>

#ifndef INSTANCING
  #include <newb/main.sh>

  uniform vec4 FogColor;

  SAMPLER2D_AUTOREG(s_SkyTexture);
#endif

void main() {
  #ifndef INSTANCING
    vec3 viewDir = normalize(v_posTime.xyz);
    vec4 diffuse = texture2D(s_SkyTexture, v_texcoord0);

    nl_environment env;
    env.end = true;
    env.nether = false;
    env.underwater = v_posTime.w < 1.0;
    env.rainFactor = 0.0;
    env.dayFactor = 1.0;
    env.fogCol = FogColor.rgb;

    nl_skycolor skycol = nlEndSkyColors(env);
    
    vec3 color = renderEndSky(skycol.horizon, skycol.zenith, viewDir, v_posTime.w);


    #ifdef NL_END_GALAXY_STARS
      vec3 vdirGalaxy = viewDir;
      #ifdef NL_END_BLACKHOLE
        vdirGalaxy = distortByBlackhole(viewDir, v_posTime.w, 0.27); // strength
      #endif
      color += NL_END_GALAXY_STARS*nlRenderGalaxy(vdirGalaxy, color, env, v_posTime.w);
    #else
    color += 0.6*diffuse.rgb;
    #endif

    #ifdef NL_END_BLACKHOLE
      vec4 bh = renderBlackhole(viewDir, v_posTime.w);
      color *= bh.a;
      color += bh.rgb;
    #endif

    #ifdef NL_END_CLOUD
      color += renderCloudsEnd(getEndHorizonCol(), getEndZenithCol(), viewDir, v_posTime.w);
    #endif

    color = colorCorrection(color);

    gl_FragColor = vec4(color, 1.0);
  #else
    gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
  #endif
}
