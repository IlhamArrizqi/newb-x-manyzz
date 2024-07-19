$input v_color0

#include <bgfx_shader.sh>

#ifndef INSTANCING
uniform vec4 StarsColor;
#endif

void main() {
#ifndef INSTANCING
  vec4 color = v_color0;
  color.rgb *= StarsColor.rgb * v_color0.a;
  gl_FragColor = color;
#else
  gl_FragColor = vec4(0.0,0.0,0.0,0.0);
#endif
}

