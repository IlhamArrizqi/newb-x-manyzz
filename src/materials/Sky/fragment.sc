#ifndef INSTANCING
  $input v_worldPos, v_underwaterRainTimeDay
#endif

#include <bgfx_shader.sh>

#ifndef INSTANCING
  #include <newb/main.sh>
  uniform vec4 TimeOfDay;
  uniform vec4 Day;
  uniform vec4 FogColor;
  uniform vec4 FogAndDistanceControl;
#endif

SAMPLER2D_AUTOREG(s_NoiseVoxel);

float pow2(float x) { return x * x; }
float pow1_5(float x) { return pow(x, 1.5); }
float clamp01(float x) { return clamp(x, 0.0, 1.0); }
float sqrt1(float x) { return sqrt(max(x, 0.0)); }

vec3 GetAurora(vec3 vDir, float time, float dither) {
    float VdotU = clamp(vDir.y, 0.0, 1.0);
    float visibility = sqrt1(clamp01(VdotU * 4.5 - 0.225));
    visibility *= 4.0 - VdotU * 0.9;
    if (visibility <= 1.0) return vec3_splat(0.0);

    vec3 aurora = vec3_splat(0.0);
    vec3 wpos = vDir;
    wpos.xz /= max(wpos.y, 0.1);
    vec2 cameraPosM = vec2_splat(0.0);
    cameraPosM.x += time * 10.0;

    const int sampleCount = 7;
    const int sampleCountP = sampleCount + 10;

    float ditherM = dither + 10.0;
    float auroraAnimate = time * 0.0;

    for (int i = 0; i < sampleCount; i++) {
        float current = pow2((float(i) + ditherM) / float(sampleCountP));
        vec2 planePos = wpos.xz * (0.8 + current) * 10.0 + cameraPosM;
        planePos *= 0.0007;
        float noise = texture2D(s_NoiseVoxel, planePos).r;
        noise = pow2(pow2(pow2(pow2(1.0- 0.8* abs(noise - 0.5)))));
        noise *= texture2D(s_NoiseVoxel, planePos * 8.0 + auroraAnimate).b;
        noise *= texture2D(s_NoiseVoxel, planePos * 1.0 - auroraAnimate).g;
        float currentM = 1.0 - current;
        aurora += noise * currentM * mix(vec3(0.65, 0.48, 1.05), vec3(0.0, 4.5, 3.0), pow2(pow2(currentM)));
    }

    aurora *= 3.8;
    return aurora * visibility / float(sampleCount);
}

void main() {
  #ifndef INSTANCING
    vec3 viewDir = normalize(v_worldPos);

    nl_environment env;
    env.end = false;
    env.nether = false;
    env.underwater = v_underwaterRainTimeDay.x > 0.5;
    env.rainFactor = v_underwaterRainTimeDay.y;
    env.dayFactor = v_underwaterRainTimeDay.w;
    env.fogCol = FogColor.rgb;
    env = calculateSunParams(env, TimeOfDay.x, Day.x);

    nl_skycolor skycol = nlOverworldSkyColors(env);

    vec3 skyColor = nlRenderSky(skycol, env, -viewDir, v_underwaterRainTimeDay.z, true);

      float dither = fract(sin(dot(gl_FragCoord.xy, vec2(12.9898, 78.233))) * 43758.5453);
     vec3 aurora = GetAurora(viewDir, v_underwaterRainTimeDay.z, dither);
    skyColor += aurora;
    
    #ifdef NL_SHOOTING_STAR
      skyColor += NL_SHOOTING_STAR*nlRenderShootingStar(viewDir, env.fogCol, v_underwaterRainTimeDay.z);
    #endif
    #ifdef NL_GALAXY_STARS
      skyColor += NL_GALAXY_STARS*nlRenderGalaxy(viewDir, env.fogCol, env, v_underwaterRainTimeDay.z);
    #endif

    skyColor = colorCorrection(skyColor);

    gl_FragColor = vec4(skyColor, 1.0);
  #else
    gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
  #endif
}
