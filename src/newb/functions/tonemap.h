#ifndef TONEMAP_H
#define TONEMAP_H

vec3 colorCorrection(vec3 col)
{
#ifdef NL_EXPOSURE
  col *= NL_EXPOSURE;
#endif

  col = clamp((col * (JD_CONST_ACES_A * col + JD_CONST_ACES_B)) / (col * (JD_CONST_ACES_C * col + JD_CONST_ACES_D) + JD_CONST_ACES_E), 0.0, 1.0);
  return col;
}

// inv used in fogcolor for nether
vec3 colorCorrectionInv(vec3 col)
{

#ifdef NL_TINT
  col /= NL_TINT;
#endif

  // #ifdef NL_SATURATION
  //  col = mix(vec3_splat(dot(col,vec3(0.21, 0.71, 0.08))), col, NL_SATURATION);
  // #endif

  // incomplete
  // extended reinhard only
  float ws = 0.7966;
  col = pow(col, vec3_splat(1.0 / NL_CONSTRAST));
  col = col * (ws + col) / (ws + col * (1.0 - ws));

#ifdef NL_EXPOSURE
  col /= NL_EXPOSURE;
#endif

  return col;
}

#endif
