#ifndef CLOUDS_H
#define CLOUDS_H

#include "noise.h"
#include "sky.h"

// simple clouds 2D noise
float cloudNoise2D(vec2 p, highp float t, float rain) {
  t *= NL_CLOUD1_SPEED;
  p += t;
  p.x += sin(p.y*0.4 + t);

  vec2 p0 = floor(p);
  vec2 u = p-p0;
  u *= u*(3.0-2.0*u);
  vec2 v = 1.0-u;

  // rain transition
  vec2 d = vec2(0.09+0.5*rain,0.089+0.5*rain*rain);

  return v.y*(randt(p0,d)*v.x + randt(p0+vec2(1.0,0.0),d)*u.x) +
         u.y*(randt(p0+vec2(0.0,1.0),d)*v.x + randt(p0+vec2(1.0,1.0),d)*u.x);
}

// simple clouds
vec4 renderCloudsSimple(nl_skycolor skycol, vec3 pos, highp float t, float rain) {
  pos.xz *= NL_CLOUD1_SCALE;

  float cloudAlpha = cloudNoise2D(pos.xz, t, rain);
  float cloudShadow = cloudNoise2D(pos.xz*0.91, t, rain);

  vec4 color = vec4(0.02,0.04,0.05,cloudAlpha);

  color.rgb += skycol.horizonEdge;
  color.rgb *= 1.0 - 0.5*cloudShadow*step(0.0, pos.y);

  color.rgb += skycol.zenith*0.7;
  color.rgb *= 1.0 - 0.4*rain;

  return color;
}

// rounded clouds
#ifdef NL_CLOUD2_REALISTIC
float mod289(float x){return x - floor(x * (1.0 / 289.0)) * 289.0;}
vec4 mod289(vec4 x){return x - floor(x * (1.0 / 289.0)) * 289.0;}
vec4 perm(vec4 x){return mod289(((x * 34.0) + 1.0) * x);}

float noise(vec3 p){
    vec3 a = floor(p);
    vec3 d = p - a;
    d = d * d * (2.0 - 1.0 * d);

    vec4 b = a.xxyy + vec4(0.0, 1.0, 0.0, 1.0);
    vec4 k1 = perm(b.xyxy);
    vec4 k2 = perm(k1.xyxy + b.zzww);

    vec4 c = k2 + a.zzzz;
    vec4 k3 = perm(c);
    vec4 k4 = perm(c + 1.0);

    vec4 o1 = fract(k3 * (1.0 / 41.0));
    vec4 o2 = fract(k4 * (1.0 / 41.0));

    vec4 o3 = o2 * d.z + o1 * (1.0 - d.z);
    vec2 o4 = o3.yw * d.x + o3.xz * (1.0 - d.x);

    return o4.y * d.y + o4.x * (1.0 - d.y);
}
#endif

#ifdef NL_CLOUD2_SMOOTH
float noise(vec2 p){
  vec2 p0 = floor(p);
  vec2 u = p-p0;

  u *= u*(2.0-1.0*u);
  vec2 v = 1.0 - u;

  float c1 = rand(p0);
  float c2 = rand(p0+vec2(1.0,0.0));
  float c3 = rand(p0+vec2(0.0,1.0));
  float c4 = rand(p0+vec2(1.0,1.0));
  float c5 = rand(p0+vec2(1.0,0.0));
  float c6 = rand(p0+vec2(1.0,0.0));

  float n = v.y*mix(c1,c2,u.x+c6) + u.y*(c3*v.x+c4+c5*u.x);
  return n;
}
#endif
// rounded clouds 3D density map
float cloudDf(vec3 pos, float rain, float boxiness) {
  #ifdef NL_CLOUD2_REALISTIC
  pos.xyz += 0.0*noise(pos.xyz);
  pos.xz += 0.7*noise(7.0*pos.xyz);
#endif

  #ifdef NL_CLOUD2_SMOOTH
  pos.xz += 1.99*noise(99.99*pos.xz);
#endif
  vec2 p0 = floor(pos.xz);
  vec2 u = smoothstep(0.999*boxiness, 1.0, pos.xz-p0);

  // rain transition
  vec2 t = vec2(0.1001+0.2*rain, 0.1+0.2*rain*rain);

  float n = mix(
    mix(randt(p0, t),randt(p0+vec2(1.0,0.0), t), u.x),
    mix(randt(p0+vec2(0.0,1.0), t),randt(p0+vec2(1.0,1.0), t), u.x),
    u.y
  );

  // round y
  float b = 1.0 - 1.9*smoothstep(boxiness, 2.0 - boxiness, 2.0*abs(pos.y-0.5));
  return smoothstep(0.2, 1.0, n * b);
}

vec4 renderClouds(
    vec3 vDir, vec3 vPos, float rain, float time, vec3 fogCol, vec3 skyCol,
    const int steps, const float thickness, const float thickness_rain, const float speed,
    const vec2 scale, const float density, const float boxiness
) {
  float height = 7.0*mix(thickness, thickness_rain, rain);
  float stepsf = float(steps);

  // scaled ray offset
  vec3 deltaP;
  deltaP.y = 1.0;
  deltaP.xz = height*scale*vDir.xz/(0.02+0.98*abs(vDir.y));
  //deltaP.xyz = (scale*height)*vDir.xyz;
  //deltaP.y = abs(deltaP.y);

  // local cloud pos
  vec3 pos;
  pos.y = 0.0;
  pos.xz = scale*(vPos.xz + vec2(1.0,0.5)*(time*speed));
  pos += deltaP;

  deltaP /= -stepsf;

  // alpha, gradient
  vec2 d = vec2(0.0,1.0);
  for (int i=1; i<=steps; i++) {
    float m = cloudDf(pos, rain, boxiness);

    d.x += m;
    d.y = mix(d.y, pos.y, m);

    //if (d.x == 0.0 && i > steps/2) {
    //	break;
    //} 

    pos += deltaP;
  }
  //d.x *= vDir.y*vDir.y; 
  d.x *= smoothstep(0.03, 0.1, d.x);
  d.x /= (stepsf/density) + d.x;

  if (vPos.y > 0.0) { // view from bottom
    d.y = 1.0 - d.y;
  }

  d.y = 1.0 - 0.7*d.y*d.y;

  vec4 col = vec4(0.6*skyCol, d.x);
  col.rgb += (vec3(0.03,0.05,0.05) + 0.8*fogCol)*d.y;
  col.rgb *= 1.0 - 0.5*rain;

  return col;
}

// aurora is rendered on clouds layer
#ifdef NL_AURORA
vec4 renderAurora(vec3 p, float t, float rain, vec3 FOG_COLOR) {
  t *= NL_AURORA_VELOCITY;
  p.xz *= NL_AURORA_SCALE;
  p.xz += 0.05*sin(p.x*4.0 + 20.0*t);

  float d0 = sin(p.x*0.1 + t + sin(p.z*0.2));
  float d1 = sin(p.z*0.1 - t + sin(p.x*0.2));
  float d2 = sin(p.z*0.1 + 1.0*sin(d0 + d1*2.0) + d1*2.0 + d0*1.0);
  d0 *= d0; d1 *= d1; d2 *= d2;
  d2 = d0/(1.0 + d2/NL_AURORA_WIDTH);

  float mask = (1.0-0.8*rain)*max(1.0 - 4.0*max(FOG_COLOR.b, FOG_COLOR.g), 0.0);
  return vec4(NL_AURORA*mix(NL_AURORA_COL1,NL_AURORA_COL2,d1),1.0)*d2*mask;
}
#endif

#endif
