#ifndef NL_CONFIG_H
#define NL_CONFIG_H

/*
  NEWB SHADER MAIN CONFIG
  This part contains base configuration options for the shader.

  TOGGLES
  - If [toggle] is mentioned, then
    options can be commented to disable (by adding '//')
  - eg: #define PLANTS_WAVE    -> this is ON
        //#define PLANTS_WAVE  -> this is OFF

  COLOR VALUES
  - Color format: vec3(red,green,blue)
  - 1.0 means 100%, 0.0 means 0%
  - eg: vec3(1.0,1.0,0.0) = yellow

  VALUES
  - Values must be decimal
  - eg. 32 is wrong, 32.0 is correct

  TYPES
  - Should be integer. options to choose will be mentioned there
  - eg: #define NL_CLOUD_TYPE 2

  Remember to rebuild the shader after making changes.
*/

/* Color correction */
#define NL_TONEMAP_TYPE 4              // 1:Exponential, 2:Reinhard, 3:Extended Reinhard, 4:ACES
#define NL_GAMMA 1.1                  // 0.3 low ~ 2.0 high
#define NL_EXPOSURE 1.4              // [toggle] 0.5 dark ~ 3.0 bright
#define NL_SATURATION 1.5            // [toggle] 0.0 grayscale ~ 4.0 super saturated
#define NL_TINT                      // [toggle] enable light/dark tone tinting
#define NL_TINT_LOW  vec3(0.55,0.45,0.35) // color tint for dark tone
#define NL_TINT_HIGH vec3(1.1,0.9,0.6) // color tint for light tone

/* Terrain lighting */
#define NL_SUN_INTENSITY 4.5   // 0.5 weak ~ 5.0 bright
#define NL_TORCH_INTENSITY 2.0  // 0.5 weak ~ 3.0 bright
#define NL_NIGHT_BRIGHTNESS 1.9 // 0.0 dark ~ 2.0 bright
#define NL_CAVE_BRIGHTNESS 2.0  // 0.0 dark ~ 2.0 bright
#define NL_SHADOW_INTENSITY 0.85 // 0.0 no shadow ~ 1.0 strong shadow
#define NL_BLINKING_TORCH     // [toggle] flickering light
//#define NL_CLOUD_SHADOW       // [toggle] cloud shadow (simple clouds only)

/* Sun/moon light color on terrain */
#define NL_MORNING_SUN_COL vec3(0.85,0.6,0.6)
#define NL_NOON_SUN_COL    vec3(0.7,0.8,0.95)
#define NL_NIGHT_SUN_COL   vec3(0.15,0.2,0.3)

/* Ambient light on terrain (light that is added everywhere) */
#define NL_NETHER_AMBIENT vec3(0.75,0.35,0.35)
#define NL_END_AMBIENT    vec3(0.25,0.25,0.6)

/* Torch colors */
#define NL_OVERWORLD_TORCH_COL  vec3(1.0,0.65,0.3)
#define NL_UNDERWATER_TORCH_COL vec3(0.5,0.25,0.1)
#define NL_NETHER_TORCH_COL     vec3(1.0,0.15,0.15)
#define NL_END_TORCH_COL        vec3(0.45,0.25,0.55)

/* Fog */
#define NL_FOG 1.0                // [toggle] 0.1 subtle ~ 1.0 blend with sky completely
#define NL_MIST_DENSITY 1.0      // 0.0 no mist ~ 1.0 misty
#define NL_RAIN_MIST_OPACITY 0.12 // [toggle] 0.04 very subtle ~ 0.5 thick rain mist blow
#define NL_CLOUDY_FOG 0.4         // [toggle] 0.0 subtle - 0.8 dense fog clouds

/* Sky colors - zenith=top, horizon=bottom */
#define NL_DAY_ZENITH_COL    vec3(0.15,0.38,0.85)
#define NL_DAY_HORIZON_COL   vec3(0.55,0.78,0.95)
#define NL_NIGHT_ZENITH_COL  vec3(0.01,0.015,0.03)
#define NL_NIGHT_HORIZON_COL vec3(0.15,0.15,0.55)
#define NL_RAIN_ZENITH_COL   vec3(0.85,0.9,1.0)
#define NL_RAIN_HORIZON_COL  vec3(1.0,1.0,1.0)
#define NL_DAWN_ZENITH_COL   vec3(0.05,0.08,0.15)
#define NL_DAWN_HORIZON_COL  vec3(0.85,0.45,0.35)
#define NL_DAWN_EDGE_COL     vec3(1.0,0.6,0.3)

/* The end sky colors */
#define NL_END_SKY_TYPE    1
#define NL_END_ZENITH_COL  vec3(0.08, 0.001, 0.1)
#define NL_END_HORIZON_COL vec3(0.4, 0.02, 0.4)
#define NL_END_STREAK      vec3(0.95, 0.45, 0.15)

/* Rainbow */
#define NL_RAINBOW         // [toggle] enable rainbow in sky
#define NL_RAINBOW_CLEAR 0.0 // 0.3 subtle ~ 1.7 bright during clear
#define NL_RAINBOW_RAIN 1.3  // 0.5 subtle ~ 2.0 bright during rain

/* Ore glow intensity */
#define NL_GLOW_TEX 4.0           // 0.4 weak ~ 8.0 bright
#define NL_GLOW_SHIMMER 0.8       // [toggle] 0.1 subtle ~ 1.0 100% shimmer
#define NL_GLOW_SHIMMER_SPEED 0.9 // 0.5 slow - 2.0 fast
//#define NL_GLOW_LEAK 0.6        // [toggle] 0.08 subtle ~ 1.0 100% brightness of NL_GLOW_TEX

/* Waving */
#define NL_PLANTS_WAVE 0.05    // [toggle] 0.02 gentle ~ 0.4 violent
#define NL_LANTERN_WAVE 0.12   // [toggle] 0.05 subtle ~ 0.4 large swing
#define NL_WAVE_SPEED 2.2      // 0.5 slow wave ~ 5.0 very fast wave
//#define NL_EXTRA_PLANTS_WAVE // [toggle] !dont use! wave using texture coords (1.21.0 vanilla 2048x1024)
#define NL_WAVE_RANGE 16.0     // 6.0 upto 6 blocks ~ 32.0 upto 32 blocks away (slower)

/* Water */
#define NL_WATER_TRANSPARENCY 0.75 // 0.0 transparent ~ 1.0 normal
#define NL_WATER_BUMP 0.2        // 0.001 plain ~ 0.2 bumpy water
#define NL_WATER_WAVE_SPEED  1.0  // 0.2 calm ~ 2.0 turbulent
#define NL_WATER_TEX_OPACITY 0.77  // 0.0 plain water ~ 1.0 vanilla water texture
#define NL_WATER_WAVE             // [toggle] wave effect
#define NL_WATER_CLOUD_AURORA_REFLECTION // [toggle] simple clouds/aurora reflection
#define NL_WATER_REFL_MASK      // [toggle] fake water reflection mask
#define NL_WATER_TINT vec3(0.8,0.85,1.0)

/* Underwater */
#define NL_UNDERWATER_BRIGHTNESS 1.8         // 0.0 dark ~ 3.0 bright
#define NL_CAUSTIC_INTENSITY 1.7             // 0.5 weak ~ 5.0 bright
#define NL_UNDERWATER_WAVE 0.18               // [toggle] 0.02 subtle ~ 0.6 trippy
#define NL_UNDERWATER_STREAKS 1.0            // [toggle] 0.8 subtle - 2.0 bright streaks from top
#define NL_UNDERWATER_TINT vec3(0.9,1.0,0.9) // fog tint color when underwater

/* Cloud type */
#define NL_CLOUD_TYPE 3 // 0:vanilla, 1:soft, 2:rounded, 3:realistic

/* Vanilla cloud settings - make sure to remove clouds.png when using this */
#define NL_CLOUD0_THICKNESS 2.1      // 0.5 slim ~ 8.0 fat
#define NL_CLOUD0_RAIN_THICKNESS 4.0 // 0.5 slim ~ 8.0 fat
#define NL_CLOUD0_OPACITY 0.9        // 0.0 invisible ~ 1.0 opaque
#define NL_CLOUD0_MULTILAYER         // [toggle] extra cloud layer

/* Soft cloud settings */
#define NL_CLOUD1_SCALE vec2(0.016, 0.022) // 0.003 large ~ 0.2 tiny
#define NL_CLOUD1_DEPTH 1.3                // 0.0 no bump ~ 10.0 large bumps
#define NL_CLOUD1_SPEED 0.24               // 0.0 static ~ 0.4 fast moving
#define NL_CLOUD1_DENSITY 0.5             // 0.1 less clouds ~ 0.8 more clouds
#define NL_CLOUD1_OPACITY 0.8              // 0.0 invisible ~ 1.0 opaque

/* Rounded cloud settings */
#define NL_CLOUD2_THICKNESS 1.0            // 0.5 slim ~ 5.0 fat
#define NL_CLOUD2_RAIN_THICKNESS 1.0       // 0.5 slim ~ 5.0 fat
#define NL_CLOUD2_STEPS 5                  // 3 low quality ~ 16 high quality
#define NL_CLOUD2_SCALE vec2(0.033, 0.033) // 0.003 large ~ 0.3 tiny
#define NL_CLOUD2_SHAPE vec2(0.5, 0.5)     // 0.0 round ~ 1.0 box vec2(horizontal shape, vertical shape)
#define NL_CLOUD2_DENSITY 25.0             // 1.0 blurry ~ 100.0 sharp
#define NL_CLOUD2_VELOCITY 0.8             // 0.0 static ~ 4.0 very fast
//#define NL_CLOUD2_SUBTLE                 // [toggle] like REALISTIS Clouds
//#define NL_CLOUD2_SMOOTH                      // [toggle] super soft clouds
//#define NL_CLOUD2_LAYER2                        // [toggle] extra cloud layer
#define NL_CLOUD2_LAYER2_OFFSET 143.0           // 30.0 near ~ 300.0 very high
#define NL_CLOUD2_LAYER2_THICKNESS 2.5          // 0.7 slim ~ 5.0 fat
#define NL_CLOUD2_LAYER2_RAIN_THICKNESS 3.0     // 0.7 slim ~ 5.0 fat
#define NL_CLOUD2_LAYER2_STEPS 3                // 3 low quality ~ 16 high quality
#define NL_CLOUD2_LAYER2_SCALE vec2(0.03, 0.03) // 0.003 large ~ 0.3 tiny
#define NL_CLOUD2_LAYER2_SHAPE vec2(0.5, 0.4)   // 0.0 round ~ 1.0 box vec2(horizontal shape, vertical shape)
#define NL_CLOUD2_LAYER2_DENSITY 25.0           // 1.0 blurry ~ 100.0 sharp
#define NL_CLOUD2_LAYER2_VELOCITY 0.8           // 0.0 static ~ 4.0 very fast

/* Realistic cloud settings */
#define NL_CLOUD3_SCALE vec2(0.03, 0.04) // 0.003 large ~ 1.0 tiny
#define NL_CLOUD3_SPEED 0.03            // 0.0 static ~ 4.0 fast moving
#define NL_CLOUD3_SHADOW 0.9             // 0.1 subtle ~ 1.0 dark
#define NL_CLOUD3_SHADOW_OFFSET 0.3      // 0.05 minimal ~ 1.0 large

/* The end cloud settings (experimental) */
//#define NL_END_CLOUD              // [toggle] the end cloud
#define NL_END_CLOUD_SPEED   0.25   // 0.0 static ~ 3.0 fast
#define NL_END_CLOUD_DENSITY 1.0    // 0.1 sublte ~ 2.0 massive

/* Aurora settings */
#define NL_AURORA 1.2           // [toggle] 0.4 dim ~ 4.0 very bright
#define NL_AURORA_VELOCITY 0.14 // 0.0 static ~ 0.3 very fast
#define NL_AURORA_SCALE 0.02    // 0.002 large ~ 0.4 tiny
#define NL_AURORA_WIDTH 0.15    // 0.04 thin line ~ 0.4 thick lines
#define NL_AURORA_COL1 vec3(0.0,0.5,1.0)
#define NL_AURORA_COL2 vec3(0.5,0.0,0.5)

/* Shooting star */
#define NL_SHOOTING_STAR 1.0        // [toggle] 0.2 dim ~ 1.0 bright
#define NL_SHOOTING_STAR_PERIOD 5.0 // 0.4 fast ~ 12.0 slow (12 secs)
#define NL_SHOOTING_STAR_DELAY 32.0 // 0.0 no delay ~ 100.0 long time (100 secs)

/* Galaxy */
#define NL_GALAXY_STARS 2.0           // [toggle] 0.1 dim - 4.0 bright
#define NL_GALAXY_VIBRANCE 0.75          // 0.0 white - 1.0 colorful
#define NL_GALAXY_SPEED 0.15            // 0.01 slow motion - 0.2 fast motion
#define NL_GALAXY_DAY_VISIBILITY 0.3    // 0.0 invisible - 1.0 visible
#define NL_END_GALAXY_STARS      4.0     // [toggle] 0.1 dim ~ 4.0 bright (auto distorted when blackhole is enabled)

/* Chunk loading slide in animation */
#define NL_CHUNK_LOAD_ANIM 140.0 // [toggle] -600.0 fall from top ~ 600.0 rise from bottom

/* Sun/Moon */
#define NL_SUNMOON_ANGLE 83.0        // [toggle] 0.0 no tilt ~ 90.0 tilt of 90 degrees
#define NL_SUNMOON_SIZE 1.0            // 0.3 tiny ~ 4.0 massive

/* Fake godrays during sunrise/sunset */
#define NL_GODRAY 0.8 // [toggle] 0.1 subtle ~ 0.8 strong

/* Sky reflection */
#define NL_GROUND_REFL 1.0       // [toggle] 0.2 slightly reflective ~ 1.0 fully reflect sky 
#define NL_GROUND_RAIN_WETNESS 1.0 // 0.0 no wetness ~ 1.0 fully wet blocks when raining
#define NL_GROUND_RAIN_PUDDLES 1.0 // 0.0 no puddles ~ 1.0 puddles
#define NL_GROUND_AURORA_REFL    // [toggle] aurora reflection on ground

/* Entity (Actor, ItemInHand) */
#define NL_ENTITY_BRIGHTNESS     0.65 // 0.1 dark ~ 1.6 bright
#define NL_ENTITY_EDGE_HIGHLIGHT 0.41 // 0.0 no highlight ~ 1.6 bright highlight

/* Weather particles */
#define NL_WEATHER_SPECK 0.6         // [toggle] 0.0 vanilla texture ~ 1.0 soft speck
#define NL_WEATHER_RAIN_SLANT 4.0    // 1.0 minimal ~ 8.0 violent
#define NL_WEATHER_PARTICLE_SIZE 1.0 // 0.5 tiny ~ 4.0 large

/* Lava effects */
#define NL_LAVA_NOISE            // [toggle] darken lava in certain regions
#define NL_LAVA_NOISE_BUMP 0.2 // [toggle] 0.1 subtle ~ 0.8 massive waves
#define NL_LAVA_NOISE_SPEED 0.02 // 0.0 still ~ 0.1 fast

/* Blackhole */
#define NL_END_BLACKHOLE    // [toggle] blackhole in the end sky
#define NL_BH_COL_LOW  vec3(0.02, 0.01, 0.05)
#define NL_BH_COL_HIGH vec3(0.9, 0.4, 0.1)
#define NL_BH_DIR      1.96     // 3.14 radius
#define NL_BH_DIST     2.0      // 1.0 close - 4.0 far
#define NL_BH_SPEED    1.2      // 0.0 static - 2.0 violent

/*
  NEWB SHADER SUBPACK CONFIG
  This part contains custom configuration options for each subpack.

  If a value is already defined,
  then you must undefine it before modifying:
  eg: #undef OPTION_NAME

  Subpack names and flags are inside `pack_config.toml`.
  Build tool will enable corresponding flags when compiling.
*/

#ifdef LITE
  #define NO_WAVE
  #undef NL_GLOW_SHIMMER
  #undef NL_LAVA_NOISE
  #undef NL_WEATHER_SPECK
  #undef NL_SHOOTING_STAR
  #undef NL_WATER_CLOUD_AURORA_REFLECTION
  #undef NL_UNDERWATER_STREAKS
  #undef NL_RAIN_MIST_OPACITY
  #undef NL_CLOUDY_FOG
  #undef NL_ENTITY_EDGE_HIGHLIGHT
#endif

#ifdef NIGHT_VISION
  #undef NL_NIGHT_BRIGHTNESS
  #define NL_NIGHT_BRIGHTNESS 100.0
  #undef NL_CAVE_BRIGHTNESS
  #define NL_CAVE_BRIGHTNESS 100.0
#endif

#ifdef NO_FOG
  #undef NL_FOG
#endif

#ifdef VANILLA_CLOUDS
  #undef NL_CLOUD_TYPE
  #undef NL_CLOUD0_MULTILAYER
  #define NL_CLOUD_TYPE 0
#endif

#ifdef MULTILAYER_VANILLA_CLOUDS
  #undef NL_CLOUD_TYPE
  #define NL_CLOUD_TYPE 0
#endif

#ifdef SOFT_CLOUDS
  #undef NL_CLOUD_TYPE
  #define NL_CLOUD_TYPE 1
#endif

#ifdef SUPER_SOFT_CLOUDS
  #undef NL_CLOUD_TYPE
  #define NL_CLOUD_TYPE 2
  #define NL_CLOUD2_SMOOTH
  #define NL_CLOUD2_LAYER2
#endif

#ifdef ROUNDED_CLOUDS
  #undef NL_CLOUD_TYPE
  #define NL_CLOUD_TYPE 2
#endif

#ifdef MULTILAYER_ROUNDED_CLOUDS
  #undef NL_CLOUD_TYPE
  #define NL_CLOUD_TYPE 2
  #define NL_CLOUD2_LAYER2
#endif

#ifdef SUBTLE_CLOUDS
  #undef NL_CLOUD_TYPE
  #define NL_CLOUD_TYPE 2
  #define NL_CLOUD2_SUBTLE
  #define NL_CLOUD2_LAYER2
#endif

#endif
