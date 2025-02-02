void main() {
    float time = iGlobalTime * 1.0;
    vec2 uv = (gl_FragCoord.xy * 2.0 - iResolution.xy)/iResolution.y;
    float b = 0.0;
    float d = length(uv);
    // d-=0.4;
    // d=abs(d);
    // d=step(0.01,d);
//   vec2 uv0 = uv;
//   float i0 = 1.0;
//   float i1 = 1.0;
//   float i2 = 1.0;
//   float i4 = 0.0;
// //   for (int s = 0; s < 0; s++) {
//     // vec2 r;
// //     r = vec2(cos(uv.y * i0 - i4 + time / i1), sin(uv.x * i0 - i4 + time / i1)) / i2;
// //     r += vec2(-r.y, r.x) * 0.3;
// //     uv.xy += r;

// //     i0 *= 1.93;
// //     i1 *= 1.15;
// //     i2 *= 1.7;
// //     i4 += 0.05 + 0.1 * time * i1;
// //   }
//   float r = sin(uv.x - time) * 0.5 + 0.5;
//   float b = sin(uv.y + time) * 0.5 + 0.5;
//   float g = sin((uv.x + uv.y + sin(time * 0.5)) * 0.5) * 0.5 + 0.5;
    gl_FragColor = vec4(d, d,d, 1.0);
}
