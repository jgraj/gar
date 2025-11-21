f64 f64_parse(ar<const u8> str);
f64 f64_min(f64 a, f64 b);
f64 f64_max(f64 a, f64 b);
f64 f64_round(f64 a);
f64 f64_clamp(f64 a, f64 min, f64 max);
bool f64_cmp(f64 a, f64 b, f64 epsilon);
f64 f64_lerp(f64 a, f64 b, f64 t);
f64 f64_smooth_step(f64 a, f64 b, f64 t, f64 dt);
f64 f64_smooth_damp(f64 a, f64 b, f64 smoothing, f64 delta_time);