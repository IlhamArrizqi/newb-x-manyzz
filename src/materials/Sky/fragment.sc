#ifndef INSTANCING
  $input v_fogColor, v_worldPos, v_underwaterRainTimeDay
#endif

#include <bgfx_shader.sh>

#ifndef INSTANCING
  #include <newb/main.sh>
  uniform vec4 FogAndDistanceControl;
#endif

/* Stars Bloom */
#define STAR_SIZE       0.2     
#define STAR_COLOR      vec3(1.0, 1.0, 1.0)
#define BLOOM_COLOR     vec3(1.0, 0.4, 0.7)
#define STAR_BRIGHTNESS 2.0      
#define STAR_DENSITY    160.0    

float nlRand(vec2 co) {
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

vec3 nlRenderPixelStars(vec3 dir, float nightFactor) {
    dir = normalize(dir);

    vec3 ad = abs(dir);
    vec2 uv;
    if (ad.x > ad.y && ad.x > ad.z) {
        uv = dir.yz / ad.x;
    } else if (ad.y > ad.x && ad.y > ad.z) {
        uv = dir.xz / ad.y;
    } else {
        uv = dir.xy / ad.z;
    }
    uv = uv * 0.5 + 0.5;

    vec3 color = vec3(0.0);
    vec2 gridCoord = floor(uv * STAR_DENSITY);

    for (int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            vec2 cell = gridCoord + vec2(x, y);
            float seed = nlRand(cell);

            if (seed > 0.995) {
                vec2 starPos = (cell + 0.5) / STAR_DENSITY;
                vec2 diff = (uv - starPos) * STAR_DENSITY;
                float dist = length(diff);

                float core = step(abs(diff.x), STAR_SIZE) * step(abs(diff.y), STAR_SIZE);
                color += core * STAR_COLOR;

                float bloom = exp(-dist * 2.0);
                float mask = smoothstep(2.0, 0.0, dist); 
                color += bloom * mask * BLOOM_COLOR * STAR_BRIGHTNESS;
            }
        }
    }

    return color * nightFactor;
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

    nl_skycolor skycol;
    if (env.underwater) {
      skycol = nlUnderwaterSkyColors(env.rainFactor, v_fogColor.rgb);
    } else {
      skycol = nlOverworldSkyColors(env.rainFactor, v_fogColor.rgb);
    }

    vec3 skyColor = nlRenderSky(skycol, env, -viewDir, v_fogColor, v_underwaterRainTimeDay.z);

    float nightFactor = 1.0 - env.dayFactor;

    // existing stars
    skyColor += nlRenderStars(viewDir, nightFactor, v_underwaterRainTimeDay.z);
    skyColor += nlRenderGalaxy(viewDir, nightFactor);
    skyColor += nlRenderShootingStars(viewDir, nightFactor, v_underwaterRainTimeDay.z);

    // bloom stars blended in
    skyColor += nlRenderPixelStars(viewDir, nightFactor);

    skyColor = colorCorrection(skyColor);

    gl_FragColor = vec4(skyColor, 1.0);
  #else
    gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
  #endif
}
