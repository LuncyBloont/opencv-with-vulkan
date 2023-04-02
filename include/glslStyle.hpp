#ifndef CVVK_GLSLSTYLE_HPP
#define CVVK_GLSLSTYLE_HPP
#include "glm/glm.hpp" // IWYU pragma: keep

namespace mltsg
{

inline float _x(const glm::vec2& v) { return float(v.x); }
inline float _r(const glm::vec2& v) { return float(v.r); }
inline float _y(const glm::vec2& v) { return float(v.y); }
inline float _g(const glm::vec2& v) { return float(v.g); }
inline glm::vec2 _xx(const glm::vec2& v) { return glm::vec2(v.x, v.x); }
inline glm::vec2 _rr(const glm::vec2& v) { return glm::vec2(v.r, v.r); }
inline glm::vec2 _xy(const glm::vec2& v) { return glm::vec2(v.x, v.y); }
inline glm::vec2 _rg(const glm::vec2& v) { return glm::vec2(v.r, v.g); }
inline glm::vec2 _yx(const glm::vec2& v) { return glm::vec2(v.y, v.x); }
inline glm::vec2 _gr(const glm::vec2& v) { return glm::vec2(v.g, v.r); }
inline glm::vec2 _yy(const glm::vec2& v) { return glm::vec2(v.y, v.y); }
inline glm::vec2 _gg(const glm::vec2& v) { return glm::vec2(v.g, v.g); }

inline float _x(const glm::vec3& v) { return float(v.x); }
inline float _r(const glm::vec3& v) { return float(v.r); }
inline float _y(const glm::vec3& v) { return float(v.y); }
inline float _g(const glm::vec3& v) { return float(v.g); }
inline float _z(const glm::vec3& v) { return float(v.z); }
inline float _b(const glm::vec3& v) { return float(v.b); }
inline glm::vec2 _xx(const glm::vec3& v) { return glm::vec2(v.x, v.x); }
inline glm::vec2 _rr(const glm::vec3& v) { return glm::vec2(v.r, v.r); }
inline glm::vec2 _xy(const glm::vec3& v) { return glm::vec2(v.x, v.y); }
inline glm::vec2 _rg(const glm::vec3& v) { return glm::vec2(v.r, v.g); }
inline glm::vec2 _xz(const glm::vec3& v) { return glm::vec2(v.x, v.z); }
inline glm::vec2 _rb(const glm::vec3& v) { return glm::vec2(v.r, v.b); }
inline glm::vec2 _yx(const glm::vec3& v) { return glm::vec2(v.y, v.x); }
inline glm::vec2 _gr(const glm::vec3& v) { return glm::vec2(v.g, v.r); }
inline glm::vec2 _yy(const glm::vec3& v) { return glm::vec2(v.y, v.y); }
inline glm::vec2 _gg(const glm::vec3& v) { return glm::vec2(v.g, v.g); }
inline glm::vec2 _yz(const glm::vec3& v) { return glm::vec2(v.y, v.z); }
inline glm::vec2 _gb(const glm::vec3& v) { return glm::vec2(v.g, v.b); }
inline glm::vec2 _zx(const glm::vec3& v) { return glm::vec2(v.z, v.x); }
inline glm::vec2 _br(const glm::vec3& v) { return glm::vec2(v.b, v.r); }
inline glm::vec2 _zy(const glm::vec3& v) { return glm::vec2(v.z, v.y); }
inline glm::vec2 _bg(const glm::vec3& v) { return glm::vec2(v.b, v.g); }
inline glm::vec2 _zz(const glm::vec3& v) { return glm::vec2(v.z, v.z); }
inline glm::vec2 _bb(const glm::vec3& v) { return glm::vec2(v.b, v.b); }
inline glm::vec3 _xxx(const glm::vec3& v) { return glm::vec3(v.x, v.x, v.x); }
inline glm::vec3 _rrr(const glm::vec3& v) { return glm::vec3(v.r, v.r, v.r); }
inline glm::vec3 _xxy(const glm::vec3& v) { return glm::vec3(v.x, v.x, v.y); }
inline glm::vec3 _rrg(const glm::vec3& v) { return glm::vec3(v.r, v.r, v.g); }
inline glm::vec3 _xxz(const glm::vec3& v) { return glm::vec3(v.x, v.x, v.z); }
inline glm::vec3 _rrb(const glm::vec3& v) { return glm::vec3(v.r, v.r, v.b); }
inline glm::vec3 _xyx(const glm::vec3& v) { return glm::vec3(v.x, v.y, v.x); }
inline glm::vec3 _rgr(const glm::vec3& v) { return glm::vec3(v.r, v.g, v.r); }
inline glm::vec3 _xyy(const glm::vec3& v) { return glm::vec3(v.x, v.y, v.y); }
inline glm::vec3 _rgg(const glm::vec3& v) { return glm::vec3(v.r, v.g, v.g); }
inline glm::vec3 _xyz(const glm::vec3& v) { return glm::vec3(v.x, v.y, v.z); }
inline glm::vec3 _rgb(const glm::vec3& v) { return glm::vec3(v.r, v.g, v.b); }
inline glm::vec3 _xzx(const glm::vec3& v) { return glm::vec3(v.x, v.z, v.x); }
inline glm::vec3 _rbr(const glm::vec3& v) { return glm::vec3(v.r, v.b, v.r); }
inline glm::vec3 _xzy(const glm::vec3& v) { return glm::vec3(v.x, v.z, v.y); }
inline glm::vec3 _rbg(const glm::vec3& v) { return glm::vec3(v.r, v.b, v.g); }
inline glm::vec3 _xzz(const glm::vec3& v) { return glm::vec3(v.x, v.z, v.z); }
inline glm::vec3 _rbb(const glm::vec3& v) { return glm::vec3(v.r, v.b, v.b); }
inline glm::vec3 _yxx(const glm::vec3& v) { return glm::vec3(v.y, v.x, v.x); }
inline glm::vec3 _grr(const glm::vec3& v) { return glm::vec3(v.g, v.r, v.r); }
inline glm::vec3 _yxy(const glm::vec3& v) { return glm::vec3(v.y, v.x, v.y); }
inline glm::vec3 _grg(const glm::vec3& v) { return glm::vec3(v.g, v.r, v.g); }
inline glm::vec3 _yxz(const glm::vec3& v) { return glm::vec3(v.y, v.x, v.z); }
inline glm::vec3 _grb(const glm::vec3& v) { return glm::vec3(v.g, v.r, v.b); }
inline glm::vec3 _yyx(const glm::vec3& v) { return glm::vec3(v.y, v.y, v.x); }
inline glm::vec3 _ggr(const glm::vec3& v) { return glm::vec3(v.g, v.g, v.r); }
inline glm::vec3 _yyy(const glm::vec3& v) { return glm::vec3(v.y, v.y, v.y); }
inline glm::vec3 _ggg(const glm::vec3& v) { return glm::vec3(v.g, v.g, v.g); }
inline glm::vec3 _yyz(const glm::vec3& v) { return glm::vec3(v.y, v.y, v.z); }
inline glm::vec3 _ggb(const glm::vec3& v) { return glm::vec3(v.g, v.g, v.b); }
inline glm::vec3 _yzx(const glm::vec3& v) { return glm::vec3(v.y, v.z, v.x); }
inline glm::vec3 _gbr(const glm::vec3& v) { return glm::vec3(v.g, v.b, v.r); }
inline glm::vec3 _yzy(const glm::vec3& v) { return glm::vec3(v.y, v.z, v.y); }
inline glm::vec3 _gbg(const glm::vec3& v) { return glm::vec3(v.g, v.b, v.g); }
inline glm::vec3 _yzz(const glm::vec3& v) { return glm::vec3(v.y, v.z, v.z); }
inline glm::vec3 _gbb(const glm::vec3& v) { return glm::vec3(v.g, v.b, v.b); }
inline glm::vec3 _zxx(const glm::vec3& v) { return glm::vec3(v.z, v.x, v.x); }
inline glm::vec3 _brr(const glm::vec3& v) { return glm::vec3(v.b, v.r, v.r); }
inline glm::vec3 _zxy(const glm::vec3& v) { return glm::vec3(v.z, v.x, v.y); }
inline glm::vec3 _brg(const glm::vec3& v) { return glm::vec3(v.b, v.r, v.g); }
inline glm::vec3 _zxz(const glm::vec3& v) { return glm::vec3(v.z, v.x, v.z); }
inline glm::vec3 _brb(const glm::vec3& v) { return glm::vec3(v.b, v.r, v.b); }
inline glm::vec3 _zyx(const glm::vec3& v) { return glm::vec3(v.z, v.y, v.x); }
inline glm::vec3 _bgr(const glm::vec3& v) { return glm::vec3(v.b, v.g, v.r); }
inline glm::vec3 _zyy(const glm::vec3& v) { return glm::vec3(v.z, v.y, v.y); }
inline glm::vec3 _bgg(const glm::vec3& v) { return glm::vec3(v.b, v.g, v.g); }
inline glm::vec3 _zyz(const glm::vec3& v) { return glm::vec3(v.z, v.y, v.z); }
inline glm::vec3 _bgb(const glm::vec3& v) { return glm::vec3(v.b, v.g, v.b); }
inline glm::vec3 _zzx(const glm::vec3& v) { return glm::vec3(v.z, v.z, v.x); }
inline glm::vec3 _bbr(const glm::vec3& v) { return glm::vec3(v.b, v.b, v.r); }
inline glm::vec3 _zzy(const glm::vec3& v) { return glm::vec3(v.z, v.z, v.y); }
inline glm::vec3 _bbg(const glm::vec3& v) { return glm::vec3(v.b, v.b, v.g); }
inline glm::vec3 _zzz(const glm::vec3& v) { return glm::vec3(v.z, v.z, v.z); }
inline glm::vec3 _bbb(const glm::vec3& v) { return glm::vec3(v.b, v.b, v.b); }

inline float _x(const glm::vec4& v) { return float(v.x); }
inline float _r(const glm::vec4& v) { return float(v.r); }
inline float _y(const glm::vec4& v) { return float(v.y); }
inline float _g(const glm::vec4& v) { return float(v.g); }
inline float _z(const glm::vec4& v) { return float(v.z); }
inline float _b(const glm::vec4& v) { return float(v.b); }
inline float _w(const glm::vec4& v) { return float(v.w); }
inline float _a(const glm::vec4& v) { return float(v.a); }
inline glm::vec2 _xx(const glm::vec4& v) { return glm::vec2(v.x, v.x); }
inline glm::vec2 _rr(const glm::vec4& v) { return glm::vec2(v.r, v.r); }
inline glm::vec2 _xy(const glm::vec4& v) { return glm::vec2(v.x, v.y); }
inline glm::vec2 _rg(const glm::vec4& v) { return glm::vec2(v.r, v.g); }
inline glm::vec2 _xz(const glm::vec4& v) { return glm::vec2(v.x, v.z); }
inline glm::vec2 _rb(const glm::vec4& v) { return glm::vec2(v.r, v.b); }
inline glm::vec2 _xw(const glm::vec4& v) { return glm::vec2(v.x, v.w); }
inline glm::vec2 _ra(const glm::vec4& v) { return glm::vec2(v.r, v.a); }
inline glm::vec2 _yx(const glm::vec4& v) { return glm::vec2(v.y, v.x); }
inline glm::vec2 _gr(const glm::vec4& v) { return glm::vec2(v.g, v.r); }
inline glm::vec2 _yy(const glm::vec4& v) { return glm::vec2(v.y, v.y); }
inline glm::vec2 _gg(const glm::vec4& v) { return glm::vec2(v.g, v.g); }
inline glm::vec2 _yz(const glm::vec4& v) { return glm::vec2(v.y, v.z); }
inline glm::vec2 _gb(const glm::vec4& v) { return glm::vec2(v.g, v.b); }
inline glm::vec2 _yw(const glm::vec4& v) { return glm::vec2(v.y, v.w); }
inline glm::vec2 _ga(const glm::vec4& v) { return glm::vec2(v.g, v.a); }
inline glm::vec2 _zx(const glm::vec4& v) { return glm::vec2(v.z, v.x); }
inline glm::vec2 _br(const glm::vec4& v) { return glm::vec2(v.b, v.r); }
inline glm::vec2 _zy(const glm::vec4& v) { return glm::vec2(v.z, v.y); }
inline glm::vec2 _bg(const glm::vec4& v) { return glm::vec2(v.b, v.g); }
inline glm::vec2 _zz(const glm::vec4& v) { return glm::vec2(v.z, v.z); }
inline glm::vec2 _bb(const glm::vec4& v) { return glm::vec2(v.b, v.b); }
inline glm::vec2 _zw(const glm::vec4& v) { return glm::vec2(v.z, v.w); }
inline glm::vec2 _ba(const glm::vec4& v) { return glm::vec2(v.b, v.a); }
inline glm::vec2 _wx(const glm::vec4& v) { return glm::vec2(v.w, v.x); }
inline glm::vec2 _ar(const glm::vec4& v) { return glm::vec2(v.a, v.r); }
inline glm::vec2 _wy(const glm::vec4& v) { return glm::vec2(v.w, v.y); }
inline glm::vec2 _ag(const glm::vec4& v) { return glm::vec2(v.a, v.g); }
inline glm::vec2 _wz(const glm::vec4& v) { return glm::vec2(v.w, v.z); }
inline glm::vec2 _ab(const glm::vec4& v) { return glm::vec2(v.a, v.b); }
inline glm::vec2 _ww(const glm::vec4& v) { return glm::vec2(v.w, v.w); }
inline glm::vec2 _aa(const glm::vec4& v) { return glm::vec2(v.a, v.a); }
inline glm::vec3 _xxx(const glm::vec4& v) { return glm::vec3(v.x, v.x, v.x); }
inline glm::vec3 _rrr(const glm::vec4& v) { return glm::vec3(v.r, v.r, v.r); }
inline glm::vec3 _xxy(const glm::vec4& v) { return glm::vec3(v.x, v.x, v.y); }
inline glm::vec3 _rrg(const glm::vec4& v) { return glm::vec3(v.r, v.r, v.g); }
inline glm::vec3 _xxz(const glm::vec4& v) { return glm::vec3(v.x, v.x, v.z); }
inline glm::vec3 _rrb(const glm::vec4& v) { return glm::vec3(v.r, v.r, v.b); }
inline glm::vec3 _xxw(const glm::vec4& v) { return glm::vec3(v.x, v.x, v.w); }
inline glm::vec3 _rra(const glm::vec4& v) { return glm::vec3(v.r, v.r, v.a); }
inline glm::vec3 _xyx(const glm::vec4& v) { return glm::vec3(v.x, v.y, v.x); }
inline glm::vec3 _rgr(const glm::vec4& v) { return glm::vec3(v.r, v.g, v.r); }
inline glm::vec3 _xyy(const glm::vec4& v) { return glm::vec3(v.x, v.y, v.y); }
inline glm::vec3 _rgg(const glm::vec4& v) { return glm::vec3(v.r, v.g, v.g); }
inline glm::vec3 _xyz(const glm::vec4& v) { return glm::vec3(v.x, v.y, v.z); }
inline glm::vec3 _rgb(const glm::vec4& v) { return glm::vec3(v.r, v.g, v.b); }
inline glm::vec3 _xyw(const glm::vec4& v) { return glm::vec3(v.x, v.y, v.w); }
inline glm::vec3 _rga(const glm::vec4& v) { return glm::vec3(v.r, v.g, v.a); }
inline glm::vec3 _xzx(const glm::vec4& v) { return glm::vec3(v.x, v.z, v.x); }
inline glm::vec3 _rbr(const glm::vec4& v) { return glm::vec3(v.r, v.b, v.r); }
inline glm::vec3 _xzy(const glm::vec4& v) { return glm::vec3(v.x, v.z, v.y); }
inline glm::vec3 _rbg(const glm::vec4& v) { return glm::vec3(v.r, v.b, v.g); }
inline glm::vec3 _xzz(const glm::vec4& v) { return glm::vec3(v.x, v.z, v.z); }
inline glm::vec3 _rbb(const glm::vec4& v) { return glm::vec3(v.r, v.b, v.b); }
inline glm::vec3 _xzw(const glm::vec4& v) { return glm::vec3(v.x, v.z, v.w); }
inline glm::vec3 _rba(const glm::vec4& v) { return glm::vec3(v.r, v.b, v.a); }
inline glm::vec3 _xwx(const glm::vec4& v) { return glm::vec3(v.x, v.w, v.x); }
inline glm::vec3 _rar(const glm::vec4& v) { return glm::vec3(v.r, v.a, v.r); }
inline glm::vec3 _xwy(const glm::vec4& v) { return glm::vec3(v.x, v.w, v.y); }
inline glm::vec3 _rag(const glm::vec4& v) { return glm::vec3(v.r, v.a, v.g); }
inline glm::vec3 _xwz(const glm::vec4& v) { return glm::vec3(v.x, v.w, v.z); }
inline glm::vec3 _rab(const glm::vec4& v) { return glm::vec3(v.r, v.a, v.b); }
inline glm::vec3 _xww(const glm::vec4& v) { return glm::vec3(v.x, v.w, v.w); }
inline glm::vec3 _raa(const glm::vec4& v) { return glm::vec3(v.r, v.a, v.a); }
inline glm::vec3 _yxx(const glm::vec4& v) { return glm::vec3(v.y, v.x, v.x); }
inline glm::vec3 _grr(const glm::vec4& v) { return glm::vec3(v.g, v.r, v.r); }
inline glm::vec3 _yxy(const glm::vec4& v) { return glm::vec3(v.y, v.x, v.y); }
inline glm::vec3 _grg(const glm::vec4& v) { return glm::vec3(v.g, v.r, v.g); }
inline glm::vec3 _yxz(const glm::vec4& v) { return glm::vec3(v.y, v.x, v.z); }
inline glm::vec3 _grb(const glm::vec4& v) { return glm::vec3(v.g, v.r, v.b); }
inline glm::vec3 _yxw(const glm::vec4& v) { return glm::vec3(v.y, v.x, v.w); }
inline glm::vec3 _gra(const glm::vec4& v) { return glm::vec3(v.g, v.r, v.a); }
inline glm::vec3 _yyx(const glm::vec4& v) { return glm::vec3(v.y, v.y, v.x); }
inline glm::vec3 _ggr(const glm::vec4& v) { return glm::vec3(v.g, v.g, v.r); }
inline glm::vec3 _yyy(const glm::vec4& v) { return glm::vec3(v.y, v.y, v.y); }
inline glm::vec3 _ggg(const glm::vec4& v) { return glm::vec3(v.g, v.g, v.g); }
inline glm::vec3 _yyz(const glm::vec4& v) { return glm::vec3(v.y, v.y, v.z); }
inline glm::vec3 _ggb(const glm::vec4& v) { return glm::vec3(v.g, v.g, v.b); }
inline glm::vec3 _yyw(const glm::vec4& v) { return glm::vec3(v.y, v.y, v.w); }
inline glm::vec3 _gga(const glm::vec4& v) { return glm::vec3(v.g, v.g, v.a); }
inline glm::vec3 _yzx(const glm::vec4& v) { return glm::vec3(v.y, v.z, v.x); }
inline glm::vec3 _gbr(const glm::vec4& v) { return glm::vec3(v.g, v.b, v.r); }
inline glm::vec3 _yzy(const glm::vec4& v) { return glm::vec3(v.y, v.z, v.y); }
inline glm::vec3 _gbg(const glm::vec4& v) { return glm::vec3(v.g, v.b, v.g); }
inline glm::vec3 _yzz(const glm::vec4& v) { return glm::vec3(v.y, v.z, v.z); }
inline glm::vec3 _gbb(const glm::vec4& v) { return glm::vec3(v.g, v.b, v.b); }
inline glm::vec3 _yzw(const glm::vec4& v) { return glm::vec3(v.y, v.z, v.w); }
inline glm::vec3 _gba(const glm::vec4& v) { return glm::vec3(v.g, v.b, v.a); }
inline glm::vec3 _ywx(const glm::vec4& v) { return glm::vec3(v.y, v.w, v.x); }
inline glm::vec3 _gar(const glm::vec4& v) { return glm::vec3(v.g, v.a, v.r); }
inline glm::vec3 _ywy(const glm::vec4& v) { return glm::vec3(v.y, v.w, v.y); }
inline glm::vec3 _gag(const glm::vec4& v) { return glm::vec3(v.g, v.a, v.g); }
inline glm::vec3 _ywz(const glm::vec4& v) { return glm::vec3(v.y, v.w, v.z); }
inline glm::vec3 _gab(const glm::vec4& v) { return glm::vec3(v.g, v.a, v.b); }
inline glm::vec3 _yww(const glm::vec4& v) { return glm::vec3(v.y, v.w, v.w); }
inline glm::vec3 _gaa(const glm::vec4& v) { return glm::vec3(v.g, v.a, v.a); }
inline glm::vec3 _zxx(const glm::vec4& v) { return glm::vec3(v.z, v.x, v.x); }
inline glm::vec3 _brr(const glm::vec4& v) { return glm::vec3(v.b, v.r, v.r); }
inline glm::vec3 _zxy(const glm::vec4& v) { return glm::vec3(v.z, v.x, v.y); }
inline glm::vec3 _brg(const glm::vec4& v) { return glm::vec3(v.b, v.r, v.g); }
inline glm::vec3 _zxz(const glm::vec4& v) { return glm::vec3(v.z, v.x, v.z); }
inline glm::vec3 _brb(const glm::vec4& v) { return glm::vec3(v.b, v.r, v.b); }
inline glm::vec3 _zxw(const glm::vec4& v) { return glm::vec3(v.z, v.x, v.w); }
inline glm::vec3 _bra(const glm::vec4& v) { return glm::vec3(v.b, v.r, v.a); }
inline glm::vec3 _zyx(const glm::vec4& v) { return glm::vec3(v.z, v.y, v.x); }
inline glm::vec3 _bgr(const glm::vec4& v) { return glm::vec3(v.b, v.g, v.r); }
inline glm::vec3 _zyy(const glm::vec4& v) { return glm::vec3(v.z, v.y, v.y); }
inline glm::vec3 _bgg(const glm::vec4& v) { return glm::vec3(v.b, v.g, v.g); }
inline glm::vec3 _zyz(const glm::vec4& v) { return glm::vec3(v.z, v.y, v.z); }
inline glm::vec3 _bgb(const glm::vec4& v) { return glm::vec3(v.b, v.g, v.b); }
inline glm::vec3 _zyw(const glm::vec4& v) { return glm::vec3(v.z, v.y, v.w); }
inline glm::vec3 _bga(const glm::vec4& v) { return glm::vec3(v.b, v.g, v.a); }
inline glm::vec3 _zzx(const glm::vec4& v) { return glm::vec3(v.z, v.z, v.x); }
inline glm::vec3 _bbr(const glm::vec4& v) { return glm::vec3(v.b, v.b, v.r); }
inline glm::vec3 _zzy(const glm::vec4& v) { return glm::vec3(v.z, v.z, v.y); }
inline glm::vec3 _bbg(const glm::vec4& v) { return glm::vec3(v.b, v.b, v.g); }
inline glm::vec3 _zzz(const glm::vec4& v) { return glm::vec3(v.z, v.z, v.z); }
inline glm::vec3 _bbb(const glm::vec4& v) { return glm::vec3(v.b, v.b, v.b); }
inline glm::vec3 _zzw(const glm::vec4& v) { return glm::vec3(v.z, v.z, v.w); }
inline glm::vec3 _bba(const glm::vec4& v) { return glm::vec3(v.b, v.b, v.a); }
inline glm::vec3 _zwx(const glm::vec4& v) { return glm::vec3(v.z, v.w, v.x); }
inline glm::vec3 _bar(const glm::vec4& v) { return glm::vec3(v.b, v.a, v.r); }
inline glm::vec3 _zwy(const glm::vec4& v) { return glm::vec3(v.z, v.w, v.y); }
inline glm::vec3 _bag(const glm::vec4& v) { return glm::vec3(v.b, v.a, v.g); }
inline glm::vec3 _zwz(const glm::vec4& v) { return glm::vec3(v.z, v.w, v.z); }
inline glm::vec3 _bab(const glm::vec4& v) { return glm::vec3(v.b, v.a, v.b); }
inline glm::vec3 _zww(const glm::vec4& v) { return glm::vec3(v.z, v.w, v.w); }
inline glm::vec3 _baa(const glm::vec4& v) { return glm::vec3(v.b, v.a, v.a); }
inline glm::vec3 _wxx(const glm::vec4& v) { return glm::vec3(v.w, v.x, v.x); }
inline glm::vec3 _arr(const glm::vec4& v) { return glm::vec3(v.a, v.r, v.r); }
inline glm::vec3 _wxy(const glm::vec4& v) { return glm::vec3(v.w, v.x, v.y); }
inline glm::vec3 _arg(const glm::vec4& v) { return glm::vec3(v.a, v.r, v.g); }
inline glm::vec3 _wxz(const glm::vec4& v) { return glm::vec3(v.w, v.x, v.z); }
inline glm::vec3 _arb(const glm::vec4& v) { return glm::vec3(v.a, v.r, v.b); }
inline glm::vec3 _wxw(const glm::vec4& v) { return glm::vec3(v.w, v.x, v.w); }
inline glm::vec3 _ara(const glm::vec4& v) { return glm::vec3(v.a, v.r, v.a); }
inline glm::vec3 _wyx(const glm::vec4& v) { return glm::vec3(v.w, v.y, v.x); }
inline glm::vec3 _agr(const glm::vec4& v) { return glm::vec3(v.a, v.g, v.r); }
inline glm::vec3 _wyy(const glm::vec4& v) { return glm::vec3(v.w, v.y, v.y); }
inline glm::vec3 _agg(const glm::vec4& v) { return glm::vec3(v.a, v.g, v.g); }
inline glm::vec3 _wyz(const glm::vec4& v) { return glm::vec3(v.w, v.y, v.z); }
inline glm::vec3 _agb(const glm::vec4& v) { return glm::vec3(v.a, v.g, v.b); }
inline glm::vec3 _wyw(const glm::vec4& v) { return glm::vec3(v.w, v.y, v.w); }
inline glm::vec3 _aga(const glm::vec4& v) { return glm::vec3(v.a, v.g, v.a); }
inline glm::vec3 _wzx(const glm::vec4& v) { return glm::vec3(v.w, v.z, v.x); }
inline glm::vec3 _abr(const glm::vec4& v) { return glm::vec3(v.a, v.b, v.r); }
inline glm::vec3 _wzy(const glm::vec4& v) { return glm::vec3(v.w, v.z, v.y); }
inline glm::vec3 _abg(const glm::vec4& v) { return glm::vec3(v.a, v.b, v.g); }
inline glm::vec3 _wzz(const glm::vec4& v) { return glm::vec3(v.w, v.z, v.z); }
inline glm::vec3 _abb(const glm::vec4& v) { return glm::vec3(v.a, v.b, v.b); }
inline glm::vec3 _wzw(const glm::vec4& v) { return glm::vec3(v.w, v.z, v.w); }
inline glm::vec3 _aba(const glm::vec4& v) { return glm::vec3(v.a, v.b, v.a); }
inline glm::vec3 _wwx(const glm::vec4& v) { return glm::vec3(v.w, v.w, v.x); }
inline glm::vec3 _aar(const glm::vec4& v) { return glm::vec3(v.a, v.a, v.r); }
inline glm::vec3 _wwy(const glm::vec4& v) { return glm::vec3(v.w, v.w, v.y); }
inline glm::vec3 _aag(const glm::vec4& v) { return glm::vec3(v.a, v.a, v.g); }
inline glm::vec3 _wwz(const glm::vec4& v) { return glm::vec3(v.w, v.w, v.z); }
inline glm::vec3 _aab(const glm::vec4& v) { return glm::vec3(v.a, v.a, v.b); }
inline glm::vec3 _www(const glm::vec4& v) { return glm::vec3(v.w, v.w, v.w); }
inline glm::vec3 _aaa(const glm::vec4& v) { return glm::vec3(v.a, v.a, v.a); }
inline glm::vec4 _xxxx(const glm::vec4& v) { return glm::vec4(v.x, v.x, v.x, v.x); }
inline glm::vec4 _rrrr(const glm::vec4& v) { return glm::vec4(v.r, v.r, v.r, v.r); }
inline glm::vec4 _xxxy(const glm::vec4& v) { return glm::vec4(v.x, v.x, v.x, v.y); }
inline glm::vec4 _rrrg(const glm::vec4& v) { return glm::vec4(v.r, v.r, v.r, v.g); }
inline glm::vec4 _xxxz(const glm::vec4& v) { return glm::vec4(v.x, v.x, v.x, v.z); }
inline glm::vec4 _rrrb(const glm::vec4& v) { return glm::vec4(v.r, v.r, v.r, v.b); }
inline glm::vec4 _xxxw(const glm::vec4& v) { return glm::vec4(v.x, v.x, v.x, v.w); }
inline glm::vec4 _rrra(const glm::vec4& v) { return glm::vec4(v.r, v.r, v.r, v.a); }
inline glm::vec4 _xxyx(const glm::vec4& v) { return glm::vec4(v.x, v.x, v.y, v.x); }
inline glm::vec4 _rrgr(const glm::vec4& v) { return glm::vec4(v.r, v.r, v.g, v.r); }
inline glm::vec4 _xxyy(const glm::vec4& v) { return glm::vec4(v.x, v.x, v.y, v.y); }
inline glm::vec4 _rrgg(const glm::vec4& v) { return glm::vec4(v.r, v.r, v.g, v.g); }
inline glm::vec4 _xxyz(const glm::vec4& v) { return glm::vec4(v.x, v.x, v.y, v.z); }
inline glm::vec4 _rrgb(const glm::vec4& v) { return glm::vec4(v.r, v.r, v.g, v.b); }
inline glm::vec4 _xxyw(const glm::vec4& v) { return glm::vec4(v.x, v.x, v.y, v.w); }
inline glm::vec4 _rrga(const glm::vec4& v) { return glm::vec4(v.r, v.r, v.g, v.a); }
inline glm::vec4 _xxzx(const glm::vec4& v) { return glm::vec4(v.x, v.x, v.z, v.x); }
inline glm::vec4 _rrbr(const glm::vec4& v) { return glm::vec4(v.r, v.r, v.b, v.r); }
inline glm::vec4 _xxzy(const glm::vec4& v) { return glm::vec4(v.x, v.x, v.z, v.y); }
inline glm::vec4 _rrbg(const glm::vec4& v) { return glm::vec4(v.r, v.r, v.b, v.g); }
inline glm::vec4 _xxzz(const glm::vec4& v) { return glm::vec4(v.x, v.x, v.z, v.z); }
inline glm::vec4 _rrbb(const glm::vec4& v) { return glm::vec4(v.r, v.r, v.b, v.b); }
inline glm::vec4 _xxzw(const glm::vec4& v) { return glm::vec4(v.x, v.x, v.z, v.w); }
inline glm::vec4 _rrba(const glm::vec4& v) { return glm::vec4(v.r, v.r, v.b, v.a); }
inline glm::vec4 _xxwx(const glm::vec4& v) { return glm::vec4(v.x, v.x, v.w, v.x); }
inline glm::vec4 _rrar(const glm::vec4& v) { return glm::vec4(v.r, v.r, v.a, v.r); }
inline glm::vec4 _xxwy(const glm::vec4& v) { return glm::vec4(v.x, v.x, v.w, v.y); }
inline glm::vec4 _rrag(const glm::vec4& v) { return glm::vec4(v.r, v.r, v.a, v.g); }
inline glm::vec4 _xxwz(const glm::vec4& v) { return glm::vec4(v.x, v.x, v.w, v.z); }
inline glm::vec4 _rrab(const glm::vec4& v) { return glm::vec4(v.r, v.r, v.a, v.b); }
inline glm::vec4 _xxww(const glm::vec4& v) { return glm::vec4(v.x, v.x, v.w, v.w); }
inline glm::vec4 _rraa(const glm::vec4& v) { return glm::vec4(v.r, v.r, v.a, v.a); }
inline glm::vec4 _xyxx(const glm::vec4& v) { return glm::vec4(v.x, v.y, v.x, v.x); }
inline glm::vec4 _rgrr(const glm::vec4& v) { return glm::vec4(v.r, v.g, v.r, v.r); }
inline glm::vec4 _xyxy(const glm::vec4& v) { return glm::vec4(v.x, v.y, v.x, v.y); }
inline glm::vec4 _rgrg(const glm::vec4& v) { return glm::vec4(v.r, v.g, v.r, v.g); }
inline glm::vec4 _xyxz(const glm::vec4& v) { return glm::vec4(v.x, v.y, v.x, v.z); }
inline glm::vec4 _rgrb(const glm::vec4& v) { return glm::vec4(v.r, v.g, v.r, v.b); }
inline glm::vec4 _xyxw(const glm::vec4& v) { return glm::vec4(v.x, v.y, v.x, v.w); }
inline glm::vec4 _rgra(const glm::vec4& v) { return glm::vec4(v.r, v.g, v.r, v.a); }
inline glm::vec4 _xyyx(const glm::vec4& v) { return glm::vec4(v.x, v.y, v.y, v.x); }
inline glm::vec4 _rggr(const glm::vec4& v) { return glm::vec4(v.r, v.g, v.g, v.r); }
inline glm::vec4 _xyyy(const glm::vec4& v) { return glm::vec4(v.x, v.y, v.y, v.y); }
inline glm::vec4 _rggg(const glm::vec4& v) { return glm::vec4(v.r, v.g, v.g, v.g); }
inline glm::vec4 _xyyz(const glm::vec4& v) { return glm::vec4(v.x, v.y, v.y, v.z); }
inline glm::vec4 _rggb(const glm::vec4& v) { return glm::vec4(v.r, v.g, v.g, v.b); }
inline glm::vec4 _xyyw(const glm::vec4& v) { return glm::vec4(v.x, v.y, v.y, v.w); }
inline glm::vec4 _rgga(const glm::vec4& v) { return glm::vec4(v.r, v.g, v.g, v.a); }
inline glm::vec4 _xyzx(const glm::vec4& v) { return glm::vec4(v.x, v.y, v.z, v.x); }
inline glm::vec4 _rgbr(const glm::vec4& v) { return glm::vec4(v.r, v.g, v.b, v.r); }
inline glm::vec4 _xyzy(const glm::vec4& v) { return glm::vec4(v.x, v.y, v.z, v.y); }
inline glm::vec4 _rgbg(const glm::vec4& v) { return glm::vec4(v.r, v.g, v.b, v.g); }
inline glm::vec4 _xyzz(const glm::vec4& v) { return glm::vec4(v.x, v.y, v.z, v.z); }
inline glm::vec4 _rgbb(const glm::vec4& v) { return glm::vec4(v.r, v.g, v.b, v.b); }
inline glm::vec4 _xyzw(const glm::vec4& v) { return glm::vec4(v.x, v.y, v.z, v.w); }
inline glm::vec4 _rgba(const glm::vec4& v) { return glm::vec4(v.r, v.g, v.b, v.a); }
inline glm::vec4 _xywx(const glm::vec4& v) { return glm::vec4(v.x, v.y, v.w, v.x); }
inline glm::vec4 _rgar(const glm::vec4& v) { return glm::vec4(v.r, v.g, v.a, v.r); }
inline glm::vec4 _xywy(const glm::vec4& v) { return glm::vec4(v.x, v.y, v.w, v.y); }
inline glm::vec4 _rgag(const glm::vec4& v) { return glm::vec4(v.r, v.g, v.a, v.g); }
inline glm::vec4 _xywz(const glm::vec4& v) { return glm::vec4(v.x, v.y, v.w, v.z); }
inline glm::vec4 _rgab(const glm::vec4& v) { return glm::vec4(v.r, v.g, v.a, v.b); }
inline glm::vec4 _xyww(const glm::vec4& v) { return glm::vec4(v.x, v.y, v.w, v.w); }
inline glm::vec4 _rgaa(const glm::vec4& v) { return glm::vec4(v.r, v.g, v.a, v.a); }
inline glm::vec4 _xzxx(const glm::vec4& v) { return glm::vec4(v.x, v.z, v.x, v.x); }
inline glm::vec4 _rbrr(const glm::vec4& v) { return glm::vec4(v.r, v.b, v.r, v.r); }
inline glm::vec4 _xzxy(const glm::vec4& v) { return glm::vec4(v.x, v.z, v.x, v.y); }
inline glm::vec4 _rbrg(const glm::vec4& v) { return glm::vec4(v.r, v.b, v.r, v.g); }
inline glm::vec4 _xzxz(const glm::vec4& v) { return glm::vec4(v.x, v.z, v.x, v.z); }
inline glm::vec4 _rbrb(const glm::vec4& v) { return glm::vec4(v.r, v.b, v.r, v.b); }
inline glm::vec4 _xzxw(const glm::vec4& v) { return glm::vec4(v.x, v.z, v.x, v.w); }
inline glm::vec4 _rbra(const glm::vec4& v) { return glm::vec4(v.r, v.b, v.r, v.a); }
inline glm::vec4 _xzyx(const glm::vec4& v) { return glm::vec4(v.x, v.z, v.y, v.x); }
inline glm::vec4 _rbgr(const glm::vec4& v) { return glm::vec4(v.r, v.b, v.g, v.r); }
inline glm::vec4 _xzyy(const glm::vec4& v) { return glm::vec4(v.x, v.z, v.y, v.y); }
inline glm::vec4 _rbgg(const glm::vec4& v) { return glm::vec4(v.r, v.b, v.g, v.g); }
inline glm::vec4 _xzyz(const glm::vec4& v) { return glm::vec4(v.x, v.z, v.y, v.z); }
inline glm::vec4 _rbgb(const glm::vec4& v) { return glm::vec4(v.r, v.b, v.g, v.b); }
inline glm::vec4 _xzyw(const glm::vec4& v) { return glm::vec4(v.x, v.z, v.y, v.w); }
inline glm::vec4 _rbga(const glm::vec4& v) { return glm::vec4(v.r, v.b, v.g, v.a); }
inline glm::vec4 _xzzx(const glm::vec4& v) { return glm::vec4(v.x, v.z, v.z, v.x); }
inline glm::vec4 _rbbr(const glm::vec4& v) { return glm::vec4(v.r, v.b, v.b, v.r); }
inline glm::vec4 _xzzy(const glm::vec4& v) { return glm::vec4(v.x, v.z, v.z, v.y); }
inline glm::vec4 _rbbg(const glm::vec4& v) { return glm::vec4(v.r, v.b, v.b, v.g); }
inline glm::vec4 _xzzz(const glm::vec4& v) { return glm::vec4(v.x, v.z, v.z, v.z); }
inline glm::vec4 _rbbb(const glm::vec4& v) { return glm::vec4(v.r, v.b, v.b, v.b); }
inline glm::vec4 _xzzw(const glm::vec4& v) { return glm::vec4(v.x, v.z, v.z, v.w); }
inline glm::vec4 _rbba(const glm::vec4& v) { return glm::vec4(v.r, v.b, v.b, v.a); }
inline glm::vec4 _xzwx(const glm::vec4& v) { return glm::vec4(v.x, v.z, v.w, v.x); }
inline glm::vec4 _rbar(const glm::vec4& v) { return glm::vec4(v.r, v.b, v.a, v.r); }
inline glm::vec4 _xzwy(const glm::vec4& v) { return glm::vec4(v.x, v.z, v.w, v.y); }
inline glm::vec4 _rbag(const glm::vec4& v) { return glm::vec4(v.r, v.b, v.a, v.g); }
inline glm::vec4 _xzwz(const glm::vec4& v) { return glm::vec4(v.x, v.z, v.w, v.z); }
inline glm::vec4 _rbab(const glm::vec4& v) { return glm::vec4(v.r, v.b, v.a, v.b); }
inline glm::vec4 _xzww(const glm::vec4& v) { return glm::vec4(v.x, v.z, v.w, v.w); }
inline glm::vec4 _rbaa(const glm::vec4& v) { return glm::vec4(v.r, v.b, v.a, v.a); }
inline glm::vec4 _xwxx(const glm::vec4& v) { return glm::vec4(v.x, v.w, v.x, v.x); }
inline glm::vec4 _rarr(const glm::vec4& v) { return glm::vec4(v.r, v.a, v.r, v.r); }
inline glm::vec4 _xwxy(const glm::vec4& v) { return glm::vec4(v.x, v.w, v.x, v.y); }
inline glm::vec4 _rarg(const glm::vec4& v) { return glm::vec4(v.r, v.a, v.r, v.g); }
inline glm::vec4 _xwxz(const glm::vec4& v) { return glm::vec4(v.x, v.w, v.x, v.z); }
inline glm::vec4 _rarb(const glm::vec4& v) { return glm::vec4(v.r, v.a, v.r, v.b); }
inline glm::vec4 _xwxw(const glm::vec4& v) { return glm::vec4(v.x, v.w, v.x, v.w); }
inline glm::vec4 _rara(const glm::vec4& v) { return glm::vec4(v.r, v.a, v.r, v.a); }
inline glm::vec4 _xwyx(const glm::vec4& v) { return glm::vec4(v.x, v.w, v.y, v.x); }
inline glm::vec4 _ragr(const glm::vec4& v) { return glm::vec4(v.r, v.a, v.g, v.r); }
inline glm::vec4 _xwyy(const glm::vec4& v) { return glm::vec4(v.x, v.w, v.y, v.y); }
inline glm::vec4 _ragg(const glm::vec4& v) { return glm::vec4(v.r, v.a, v.g, v.g); }
inline glm::vec4 _xwyz(const glm::vec4& v) { return glm::vec4(v.x, v.w, v.y, v.z); }
inline glm::vec4 _ragb(const glm::vec4& v) { return glm::vec4(v.r, v.a, v.g, v.b); }
inline glm::vec4 _xwyw(const glm::vec4& v) { return glm::vec4(v.x, v.w, v.y, v.w); }
inline glm::vec4 _raga(const glm::vec4& v) { return glm::vec4(v.r, v.a, v.g, v.a); }
inline glm::vec4 _xwzx(const glm::vec4& v) { return glm::vec4(v.x, v.w, v.z, v.x); }
inline glm::vec4 _rabr(const glm::vec4& v) { return glm::vec4(v.r, v.a, v.b, v.r); }
inline glm::vec4 _xwzy(const glm::vec4& v) { return glm::vec4(v.x, v.w, v.z, v.y); }
inline glm::vec4 _rabg(const glm::vec4& v) { return glm::vec4(v.r, v.a, v.b, v.g); }
inline glm::vec4 _xwzz(const glm::vec4& v) { return glm::vec4(v.x, v.w, v.z, v.z); }
inline glm::vec4 _rabb(const glm::vec4& v) { return glm::vec4(v.r, v.a, v.b, v.b); }
inline glm::vec4 _xwzw(const glm::vec4& v) { return glm::vec4(v.x, v.w, v.z, v.w); }
inline glm::vec4 _raba(const glm::vec4& v) { return glm::vec4(v.r, v.a, v.b, v.a); }
inline glm::vec4 _xwwx(const glm::vec4& v) { return glm::vec4(v.x, v.w, v.w, v.x); }
inline glm::vec4 _raar(const glm::vec4& v) { return glm::vec4(v.r, v.a, v.a, v.r); }
inline glm::vec4 _xwwy(const glm::vec4& v) { return glm::vec4(v.x, v.w, v.w, v.y); }
inline glm::vec4 _raag(const glm::vec4& v) { return glm::vec4(v.r, v.a, v.a, v.g); }
inline glm::vec4 _xwwz(const glm::vec4& v) { return glm::vec4(v.x, v.w, v.w, v.z); }
inline glm::vec4 _raab(const glm::vec4& v) { return glm::vec4(v.r, v.a, v.a, v.b); }
inline glm::vec4 _xwww(const glm::vec4& v) { return glm::vec4(v.x, v.w, v.w, v.w); }
inline glm::vec4 _raaa(const glm::vec4& v) { return glm::vec4(v.r, v.a, v.a, v.a); }
inline glm::vec4 _yxxx(const glm::vec4& v) { return glm::vec4(v.y, v.x, v.x, v.x); }
inline glm::vec4 _grrr(const glm::vec4& v) { return glm::vec4(v.g, v.r, v.r, v.r); }
inline glm::vec4 _yxxy(const glm::vec4& v) { return glm::vec4(v.y, v.x, v.x, v.y); }
inline glm::vec4 _grrg(const glm::vec4& v) { return glm::vec4(v.g, v.r, v.r, v.g); }
inline glm::vec4 _yxxz(const glm::vec4& v) { return glm::vec4(v.y, v.x, v.x, v.z); }
inline glm::vec4 _grrb(const glm::vec4& v) { return glm::vec4(v.g, v.r, v.r, v.b); }
inline glm::vec4 _yxxw(const glm::vec4& v) { return glm::vec4(v.y, v.x, v.x, v.w); }
inline glm::vec4 _grra(const glm::vec4& v) { return glm::vec4(v.g, v.r, v.r, v.a); }
inline glm::vec4 _yxyx(const glm::vec4& v) { return glm::vec4(v.y, v.x, v.y, v.x); }
inline glm::vec4 _grgr(const glm::vec4& v) { return glm::vec4(v.g, v.r, v.g, v.r); }
inline glm::vec4 _yxyy(const glm::vec4& v) { return glm::vec4(v.y, v.x, v.y, v.y); }
inline glm::vec4 _grgg(const glm::vec4& v) { return glm::vec4(v.g, v.r, v.g, v.g); }
inline glm::vec4 _yxyz(const glm::vec4& v) { return glm::vec4(v.y, v.x, v.y, v.z); }
inline glm::vec4 _grgb(const glm::vec4& v) { return glm::vec4(v.g, v.r, v.g, v.b); }
inline glm::vec4 _yxyw(const glm::vec4& v) { return glm::vec4(v.y, v.x, v.y, v.w); }
inline glm::vec4 _grga(const glm::vec4& v) { return glm::vec4(v.g, v.r, v.g, v.a); }
inline glm::vec4 _yxzx(const glm::vec4& v) { return glm::vec4(v.y, v.x, v.z, v.x); }
inline glm::vec4 _grbr(const glm::vec4& v) { return glm::vec4(v.g, v.r, v.b, v.r); }
inline glm::vec4 _yxzy(const glm::vec4& v) { return glm::vec4(v.y, v.x, v.z, v.y); }
inline glm::vec4 _grbg(const glm::vec4& v) { return glm::vec4(v.g, v.r, v.b, v.g); }
inline glm::vec4 _yxzz(const glm::vec4& v) { return glm::vec4(v.y, v.x, v.z, v.z); }
inline glm::vec4 _grbb(const glm::vec4& v) { return glm::vec4(v.g, v.r, v.b, v.b); }
inline glm::vec4 _yxzw(const glm::vec4& v) { return glm::vec4(v.y, v.x, v.z, v.w); }
inline glm::vec4 _grba(const glm::vec4& v) { return glm::vec4(v.g, v.r, v.b, v.a); }
inline glm::vec4 _yxwx(const glm::vec4& v) { return glm::vec4(v.y, v.x, v.w, v.x); }
inline glm::vec4 _grar(const glm::vec4& v) { return glm::vec4(v.g, v.r, v.a, v.r); }
inline glm::vec4 _yxwy(const glm::vec4& v) { return glm::vec4(v.y, v.x, v.w, v.y); }
inline glm::vec4 _grag(const glm::vec4& v) { return glm::vec4(v.g, v.r, v.a, v.g); }
inline glm::vec4 _yxwz(const glm::vec4& v) { return glm::vec4(v.y, v.x, v.w, v.z); }
inline glm::vec4 _grab(const glm::vec4& v) { return glm::vec4(v.g, v.r, v.a, v.b); }
inline glm::vec4 _yxww(const glm::vec4& v) { return glm::vec4(v.y, v.x, v.w, v.w); }
inline glm::vec4 _graa(const glm::vec4& v) { return glm::vec4(v.g, v.r, v.a, v.a); }
inline glm::vec4 _yyxx(const glm::vec4& v) { return glm::vec4(v.y, v.y, v.x, v.x); }
inline glm::vec4 _ggrr(const glm::vec4& v) { return glm::vec4(v.g, v.g, v.r, v.r); }
inline glm::vec4 _yyxy(const glm::vec4& v) { return glm::vec4(v.y, v.y, v.x, v.y); }
inline glm::vec4 _ggrg(const glm::vec4& v) { return glm::vec4(v.g, v.g, v.r, v.g); }
inline glm::vec4 _yyxz(const glm::vec4& v) { return glm::vec4(v.y, v.y, v.x, v.z); }
inline glm::vec4 _ggrb(const glm::vec4& v) { return glm::vec4(v.g, v.g, v.r, v.b); }
inline glm::vec4 _yyxw(const glm::vec4& v) { return glm::vec4(v.y, v.y, v.x, v.w); }
inline glm::vec4 _ggra(const glm::vec4& v) { return glm::vec4(v.g, v.g, v.r, v.a); }
inline glm::vec4 _yyyx(const glm::vec4& v) { return glm::vec4(v.y, v.y, v.y, v.x); }
inline glm::vec4 _gggr(const glm::vec4& v) { return glm::vec4(v.g, v.g, v.g, v.r); }
inline glm::vec4 _yyyy(const glm::vec4& v) { return glm::vec4(v.y, v.y, v.y, v.y); }
inline glm::vec4 _gggg(const glm::vec4& v) { return glm::vec4(v.g, v.g, v.g, v.g); }
inline glm::vec4 _yyyz(const glm::vec4& v) { return glm::vec4(v.y, v.y, v.y, v.z); }
inline glm::vec4 _gggb(const glm::vec4& v) { return glm::vec4(v.g, v.g, v.g, v.b); }
inline glm::vec4 _yyyw(const glm::vec4& v) { return glm::vec4(v.y, v.y, v.y, v.w); }
inline glm::vec4 _ggga(const glm::vec4& v) { return glm::vec4(v.g, v.g, v.g, v.a); }
inline glm::vec4 _yyzx(const glm::vec4& v) { return glm::vec4(v.y, v.y, v.z, v.x); }
inline glm::vec4 _ggbr(const glm::vec4& v) { return glm::vec4(v.g, v.g, v.b, v.r); }
inline glm::vec4 _yyzy(const glm::vec4& v) { return glm::vec4(v.y, v.y, v.z, v.y); }
inline glm::vec4 _ggbg(const glm::vec4& v) { return glm::vec4(v.g, v.g, v.b, v.g); }
inline glm::vec4 _yyzz(const glm::vec4& v) { return glm::vec4(v.y, v.y, v.z, v.z); }
inline glm::vec4 _ggbb(const glm::vec4& v) { return glm::vec4(v.g, v.g, v.b, v.b); }
inline glm::vec4 _yyzw(const glm::vec4& v) { return glm::vec4(v.y, v.y, v.z, v.w); }
inline glm::vec4 _ggba(const glm::vec4& v) { return glm::vec4(v.g, v.g, v.b, v.a); }
inline glm::vec4 _yywx(const glm::vec4& v) { return glm::vec4(v.y, v.y, v.w, v.x); }
inline glm::vec4 _ggar(const glm::vec4& v) { return glm::vec4(v.g, v.g, v.a, v.r); }
inline glm::vec4 _yywy(const glm::vec4& v) { return glm::vec4(v.y, v.y, v.w, v.y); }
inline glm::vec4 _ggag(const glm::vec4& v) { return glm::vec4(v.g, v.g, v.a, v.g); }
inline glm::vec4 _yywz(const glm::vec4& v) { return glm::vec4(v.y, v.y, v.w, v.z); }
inline glm::vec4 _ggab(const glm::vec4& v) { return glm::vec4(v.g, v.g, v.a, v.b); }
inline glm::vec4 _yyww(const glm::vec4& v) { return glm::vec4(v.y, v.y, v.w, v.w); }
inline glm::vec4 _ggaa(const glm::vec4& v) { return glm::vec4(v.g, v.g, v.a, v.a); }
inline glm::vec4 _yzxx(const glm::vec4& v) { return glm::vec4(v.y, v.z, v.x, v.x); }
inline glm::vec4 _gbrr(const glm::vec4& v) { return glm::vec4(v.g, v.b, v.r, v.r); }
inline glm::vec4 _yzxy(const glm::vec4& v) { return glm::vec4(v.y, v.z, v.x, v.y); }
inline glm::vec4 _gbrg(const glm::vec4& v) { return glm::vec4(v.g, v.b, v.r, v.g); }
inline glm::vec4 _yzxz(const glm::vec4& v) { return glm::vec4(v.y, v.z, v.x, v.z); }
inline glm::vec4 _gbrb(const glm::vec4& v) { return glm::vec4(v.g, v.b, v.r, v.b); }
inline glm::vec4 _yzxw(const glm::vec4& v) { return glm::vec4(v.y, v.z, v.x, v.w); }
inline glm::vec4 _gbra(const glm::vec4& v) { return glm::vec4(v.g, v.b, v.r, v.a); }
inline glm::vec4 _yzyx(const glm::vec4& v) { return glm::vec4(v.y, v.z, v.y, v.x); }
inline glm::vec4 _gbgr(const glm::vec4& v) { return glm::vec4(v.g, v.b, v.g, v.r); }
inline glm::vec4 _yzyy(const glm::vec4& v) { return glm::vec4(v.y, v.z, v.y, v.y); }
inline glm::vec4 _gbgg(const glm::vec4& v) { return glm::vec4(v.g, v.b, v.g, v.g); }
inline glm::vec4 _yzyz(const glm::vec4& v) { return glm::vec4(v.y, v.z, v.y, v.z); }
inline glm::vec4 _gbgb(const glm::vec4& v) { return glm::vec4(v.g, v.b, v.g, v.b); }
inline glm::vec4 _yzyw(const glm::vec4& v) { return glm::vec4(v.y, v.z, v.y, v.w); }
inline glm::vec4 _gbga(const glm::vec4& v) { return glm::vec4(v.g, v.b, v.g, v.a); }
inline glm::vec4 _yzzx(const glm::vec4& v) { return glm::vec4(v.y, v.z, v.z, v.x); }
inline glm::vec4 _gbbr(const glm::vec4& v) { return glm::vec4(v.g, v.b, v.b, v.r); }
inline glm::vec4 _yzzy(const glm::vec4& v) { return glm::vec4(v.y, v.z, v.z, v.y); }
inline glm::vec4 _gbbg(const glm::vec4& v) { return glm::vec4(v.g, v.b, v.b, v.g); }
inline glm::vec4 _yzzz(const glm::vec4& v) { return glm::vec4(v.y, v.z, v.z, v.z); }
inline glm::vec4 _gbbb(const glm::vec4& v) { return glm::vec4(v.g, v.b, v.b, v.b); }
inline glm::vec4 _yzzw(const glm::vec4& v) { return glm::vec4(v.y, v.z, v.z, v.w); }
inline glm::vec4 _gbba(const glm::vec4& v) { return glm::vec4(v.g, v.b, v.b, v.a); }
inline glm::vec4 _yzwx(const glm::vec4& v) { return glm::vec4(v.y, v.z, v.w, v.x); }
inline glm::vec4 _gbar(const glm::vec4& v) { return glm::vec4(v.g, v.b, v.a, v.r); }
inline glm::vec4 _yzwy(const glm::vec4& v) { return glm::vec4(v.y, v.z, v.w, v.y); }
inline glm::vec4 _gbag(const glm::vec4& v) { return glm::vec4(v.g, v.b, v.a, v.g); }
inline glm::vec4 _yzwz(const glm::vec4& v) { return glm::vec4(v.y, v.z, v.w, v.z); }
inline glm::vec4 _gbab(const glm::vec4& v) { return glm::vec4(v.g, v.b, v.a, v.b); }
inline glm::vec4 _yzww(const glm::vec4& v) { return glm::vec4(v.y, v.z, v.w, v.w); }
inline glm::vec4 _gbaa(const glm::vec4& v) { return glm::vec4(v.g, v.b, v.a, v.a); }
inline glm::vec4 _ywxx(const glm::vec4& v) { return glm::vec4(v.y, v.w, v.x, v.x); }
inline glm::vec4 _garr(const glm::vec4& v) { return glm::vec4(v.g, v.a, v.r, v.r); }
inline glm::vec4 _ywxy(const glm::vec4& v) { return glm::vec4(v.y, v.w, v.x, v.y); }
inline glm::vec4 _garg(const glm::vec4& v) { return glm::vec4(v.g, v.a, v.r, v.g); }
inline glm::vec4 _ywxz(const glm::vec4& v) { return glm::vec4(v.y, v.w, v.x, v.z); }
inline glm::vec4 _garb(const glm::vec4& v) { return glm::vec4(v.g, v.a, v.r, v.b); }
inline glm::vec4 _ywxw(const glm::vec4& v) { return glm::vec4(v.y, v.w, v.x, v.w); }
inline glm::vec4 _gara(const glm::vec4& v) { return glm::vec4(v.g, v.a, v.r, v.a); }
inline glm::vec4 _ywyx(const glm::vec4& v) { return glm::vec4(v.y, v.w, v.y, v.x); }
inline glm::vec4 _gagr(const glm::vec4& v) { return glm::vec4(v.g, v.a, v.g, v.r); }
inline glm::vec4 _ywyy(const glm::vec4& v) { return glm::vec4(v.y, v.w, v.y, v.y); }
inline glm::vec4 _gagg(const glm::vec4& v) { return glm::vec4(v.g, v.a, v.g, v.g); }
inline glm::vec4 _ywyz(const glm::vec4& v) { return glm::vec4(v.y, v.w, v.y, v.z); }
inline glm::vec4 _gagb(const glm::vec4& v) { return glm::vec4(v.g, v.a, v.g, v.b); }
inline glm::vec4 _ywyw(const glm::vec4& v) { return glm::vec4(v.y, v.w, v.y, v.w); }
inline glm::vec4 _gaga(const glm::vec4& v) { return glm::vec4(v.g, v.a, v.g, v.a); }
inline glm::vec4 _ywzx(const glm::vec4& v) { return glm::vec4(v.y, v.w, v.z, v.x); }
inline glm::vec4 _gabr(const glm::vec4& v) { return glm::vec4(v.g, v.a, v.b, v.r); }
inline glm::vec4 _ywzy(const glm::vec4& v) { return glm::vec4(v.y, v.w, v.z, v.y); }
inline glm::vec4 _gabg(const glm::vec4& v) { return glm::vec4(v.g, v.a, v.b, v.g); }
inline glm::vec4 _ywzz(const glm::vec4& v) { return glm::vec4(v.y, v.w, v.z, v.z); }
inline glm::vec4 _gabb(const glm::vec4& v) { return glm::vec4(v.g, v.a, v.b, v.b); }
inline glm::vec4 _ywzw(const glm::vec4& v) { return glm::vec4(v.y, v.w, v.z, v.w); }
inline glm::vec4 _gaba(const glm::vec4& v) { return glm::vec4(v.g, v.a, v.b, v.a); }
inline glm::vec4 _ywwx(const glm::vec4& v) { return glm::vec4(v.y, v.w, v.w, v.x); }
inline glm::vec4 _gaar(const glm::vec4& v) { return glm::vec4(v.g, v.a, v.a, v.r); }
inline glm::vec4 _ywwy(const glm::vec4& v) { return glm::vec4(v.y, v.w, v.w, v.y); }
inline glm::vec4 _gaag(const glm::vec4& v) { return glm::vec4(v.g, v.a, v.a, v.g); }
inline glm::vec4 _ywwz(const glm::vec4& v) { return glm::vec4(v.y, v.w, v.w, v.z); }
inline glm::vec4 _gaab(const glm::vec4& v) { return glm::vec4(v.g, v.a, v.a, v.b); }
inline glm::vec4 _ywww(const glm::vec4& v) { return glm::vec4(v.y, v.w, v.w, v.w); }
inline glm::vec4 _gaaa(const glm::vec4& v) { return glm::vec4(v.g, v.a, v.a, v.a); }
inline glm::vec4 _zxxx(const glm::vec4& v) { return glm::vec4(v.z, v.x, v.x, v.x); }
inline glm::vec4 _brrr(const glm::vec4& v) { return glm::vec4(v.b, v.r, v.r, v.r); }
inline glm::vec4 _zxxy(const glm::vec4& v) { return glm::vec4(v.z, v.x, v.x, v.y); }
inline glm::vec4 _brrg(const glm::vec4& v) { return glm::vec4(v.b, v.r, v.r, v.g); }
inline glm::vec4 _zxxz(const glm::vec4& v) { return glm::vec4(v.z, v.x, v.x, v.z); }
inline glm::vec4 _brrb(const glm::vec4& v) { return glm::vec4(v.b, v.r, v.r, v.b); }
inline glm::vec4 _zxxw(const glm::vec4& v) { return glm::vec4(v.z, v.x, v.x, v.w); }
inline glm::vec4 _brra(const glm::vec4& v) { return glm::vec4(v.b, v.r, v.r, v.a); }
inline glm::vec4 _zxyx(const glm::vec4& v) { return glm::vec4(v.z, v.x, v.y, v.x); }
inline glm::vec4 _brgr(const glm::vec4& v) { return glm::vec4(v.b, v.r, v.g, v.r); }
inline glm::vec4 _zxyy(const glm::vec4& v) { return glm::vec4(v.z, v.x, v.y, v.y); }
inline glm::vec4 _brgg(const glm::vec4& v) { return glm::vec4(v.b, v.r, v.g, v.g); }
inline glm::vec4 _zxyz(const glm::vec4& v) { return glm::vec4(v.z, v.x, v.y, v.z); }
inline glm::vec4 _brgb(const glm::vec4& v) { return glm::vec4(v.b, v.r, v.g, v.b); }
inline glm::vec4 _zxyw(const glm::vec4& v) { return glm::vec4(v.z, v.x, v.y, v.w); }
inline glm::vec4 _brga(const glm::vec4& v) { return glm::vec4(v.b, v.r, v.g, v.a); }
inline glm::vec4 _zxzx(const glm::vec4& v) { return glm::vec4(v.z, v.x, v.z, v.x); }
inline glm::vec4 _brbr(const glm::vec4& v) { return glm::vec4(v.b, v.r, v.b, v.r); }
inline glm::vec4 _zxzy(const glm::vec4& v) { return glm::vec4(v.z, v.x, v.z, v.y); }
inline glm::vec4 _brbg(const glm::vec4& v) { return glm::vec4(v.b, v.r, v.b, v.g); }
inline glm::vec4 _zxzz(const glm::vec4& v) { return glm::vec4(v.z, v.x, v.z, v.z); }
inline glm::vec4 _brbb(const glm::vec4& v) { return glm::vec4(v.b, v.r, v.b, v.b); }
inline glm::vec4 _zxzw(const glm::vec4& v) { return glm::vec4(v.z, v.x, v.z, v.w); }
inline glm::vec4 _brba(const glm::vec4& v) { return glm::vec4(v.b, v.r, v.b, v.a); }
inline glm::vec4 _zxwx(const glm::vec4& v) { return glm::vec4(v.z, v.x, v.w, v.x); }
inline glm::vec4 _brar(const glm::vec4& v) { return glm::vec4(v.b, v.r, v.a, v.r); }
inline glm::vec4 _zxwy(const glm::vec4& v) { return glm::vec4(v.z, v.x, v.w, v.y); }
inline glm::vec4 _brag(const glm::vec4& v) { return glm::vec4(v.b, v.r, v.a, v.g); }
inline glm::vec4 _zxwz(const glm::vec4& v) { return glm::vec4(v.z, v.x, v.w, v.z); }
inline glm::vec4 _brab(const glm::vec4& v) { return glm::vec4(v.b, v.r, v.a, v.b); }
inline glm::vec4 _zxww(const glm::vec4& v) { return glm::vec4(v.z, v.x, v.w, v.w); }
inline glm::vec4 _braa(const glm::vec4& v) { return glm::vec4(v.b, v.r, v.a, v.a); }
inline glm::vec4 _zyxx(const glm::vec4& v) { return glm::vec4(v.z, v.y, v.x, v.x); }
inline glm::vec4 _bgrr(const glm::vec4& v) { return glm::vec4(v.b, v.g, v.r, v.r); }
inline glm::vec4 _zyxy(const glm::vec4& v) { return glm::vec4(v.z, v.y, v.x, v.y); }
inline glm::vec4 _bgrg(const glm::vec4& v) { return glm::vec4(v.b, v.g, v.r, v.g); }
inline glm::vec4 _zyxz(const glm::vec4& v) { return glm::vec4(v.z, v.y, v.x, v.z); }
inline glm::vec4 _bgrb(const glm::vec4& v) { return glm::vec4(v.b, v.g, v.r, v.b); }
inline glm::vec4 _zyxw(const glm::vec4& v) { return glm::vec4(v.z, v.y, v.x, v.w); }
inline glm::vec4 _bgra(const glm::vec4& v) { return glm::vec4(v.b, v.g, v.r, v.a); }
inline glm::vec4 _zyyx(const glm::vec4& v) { return glm::vec4(v.z, v.y, v.y, v.x); }
inline glm::vec4 _bggr(const glm::vec4& v) { return glm::vec4(v.b, v.g, v.g, v.r); }
inline glm::vec4 _zyyy(const glm::vec4& v) { return glm::vec4(v.z, v.y, v.y, v.y); }
inline glm::vec4 _bggg(const glm::vec4& v) { return glm::vec4(v.b, v.g, v.g, v.g); }
inline glm::vec4 _zyyz(const glm::vec4& v) { return glm::vec4(v.z, v.y, v.y, v.z); }
inline glm::vec4 _bggb(const glm::vec4& v) { return glm::vec4(v.b, v.g, v.g, v.b); }
inline glm::vec4 _zyyw(const glm::vec4& v) { return glm::vec4(v.z, v.y, v.y, v.w); }
inline glm::vec4 _bgga(const glm::vec4& v) { return glm::vec4(v.b, v.g, v.g, v.a); }
inline glm::vec4 _zyzx(const glm::vec4& v) { return glm::vec4(v.z, v.y, v.z, v.x); }
inline glm::vec4 _bgbr(const glm::vec4& v) { return glm::vec4(v.b, v.g, v.b, v.r); }
inline glm::vec4 _zyzy(const glm::vec4& v) { return glm::vec4(v.z, v.y, v.z, v.y); }
inline glm::vec4 _bgbg(const glm::vec4& v) { return glm::vec4(v.b, v.g, v.b, v.g); }
inline glm::vec4 _zyzz(const glm::vec4& v) { return glm::vec4(v.z, v.y, v.z, v.z); }
inline glm::vec4 _bgbb(const glm::vec4& v) { return glm::vec4(v.b, v.g, v.b, v.b); }
inline glm::vec4 _zyzw(const glm::vec4& v) { return glm::vec4(v.z, v.y, v.z, v.w); }
inline glm::vec4 _bgba(const glm::vec4& v) { return glm::vec4(v.b, v.g, v.b, v.a); }
inline glm::vec4 _zywx(const glm::vec4& v) { return glm::vec4(v.z, v.y, v.w, v.x); }
inline glm::vec4 _bgar(const glm::vec4& v) { return glm::vec4(v.b, v.g, v.a, v.r); }
inline glm::vec4 _zywy(const glm::vec4& v) { return glm::vec4(v.z, v.y, v.w, v.y); }
inline glm::vec4 _bgag(const glm::vec4& v) { return glm::vec4(v.b, v.g, v.a, v.g); }
inline glm::vec4 _zywz(const glm::vec4& v) { return glm::vec4(v.z, v.y, v.w, v.z); }
inline glm::vec4 _bgab(const glm::vec4& v) { return glm::vec4(v.b, v.g, v.a, v.b); }
inline glm::vec4 _zyww(const glm::vec4& v) { return glm::vec4(v.z, v.y, v.w, v.w); }
inline glm::vec4 _bgaa(const glm::vec4& v) { return glm::vec4(v.b, v.g, v.a, v.a); }
inline glm::vec4 _zzxx(const glm::vec4& v) { return glm::vec4(v.z, v.z, v.x, v.x); }
inline glm::vec4 _bbrr(const glm::vec4& v) { return glm::vec4(v.b, v.b, v.r, v.r); }
inline glm::vec4 _zzxy(const glm::vec4& v) { return glm::vec4(v.z, v.z, v.x, v.y); }
inline glm::vec4 _bbrg(const glm::vec4& v) { return glm::vec4(v.b, v.b, v.r, v.g); }
inline glm::vec4 _zzxz(const glm::vec4& v) { return glm::vec4(v.z, v.z, v.x, v.z); }
inline glm::vec4 _bbrb(const glm::vec4& v) { return glm::vec4(v.b, v.b, v.r, v.b); }
inline glm::vec4 _zzxw(const glm::vec4& v) { return glm::vec4(v.z, v.z, v.x, v.w); }
inline glm::vec4 _bbra(const glm::vec4& v) { return glm::vec4(v.b, v.b, v.r, v.a); }
inline glm::vec4 _zzyx(const glm::vec4& v) { return glm::vec4(v.z, v.z, v.y, v.x); }
inline glm::vec4 _bbgr(const glm::vec4& v) { return glm::vec4(v.b, v.b, v.g, v.r); }
inline glm::vec4 _zzyy(const glm::vec4& v) { return glm::vec4(v.z, v.z, v.y, v.y); }
inline glm::vec4 _bbgg(const glm::vec4& v) { return glm::vec4(v.b, v.b, v.g, v.g); }
inline glm::vec4 _zzyz(const glm::vec4& v) { return glm::vec4(v.z, v.z, v.y, v.z); }
inline glm::vec4 _bbgb(const glm::vec4& v) { return glm::vec4(v.b, v.b, v.g, v.b); }
inline glm::vec4 _zzyw(const glm::vec4& v) { return glm::vec4(v.z, v.z, v.y, v.w); }
inline glm::vec4 _bbga(const glm::vec4& v) { return glm::vec4(v.b, v.b, v.g, v.a); }
inline glm::vec4 _zzzx(const glm::vec4& v) { return glm::vec4(v.z, v.z, v.z, v.x); }
inline glm::vec4 _bbbr(const glm::vec4& v) { return glm::vec4(v.b, v.b, v.b, v.r); }
inline glm::vec4 _zzzy(const glm::vec4& v) { return glm::vec4(v.z, v.z, v.z, v.y); }
inline glm::vec4 _bbbg(const glm::vec4& v) { return glm::vec4(v.b, v.b, v.b, v.g); }
inline glm::vec4 _zzzz(const glm::vec4& v) { return glm::vec4(v.z, v.z, v.z, v.z); }
inline glm::vec4 _bbbb(const glm::vec4& v) { return glm::vec4(v.b, v.b, v.b, v.b); }
inline glm::vec4 _zzzw(const glm::vec4& v) { return glm::vec4(v.z, v.z, v.z, v.w); }
inline glm::vec4 _bbba(const glm::vec4& v) { return glm::vec4(v.b, v.b, v.b, v.a); }
inline glm::vec4 _zzwx(const glm::vec4& v) { return glm::vec4(v.z, v.z, v.w, v.x); }
inline glm::vec4 _bbar(const glm::vec4& v) { return glm::vec4(v.b, v.b, v.a, v.r); }
inline glm::vec4 _zzwy(const glm::vec4& v) { return glm::vec4(v.z, v.z, v.w, v.y); }
inline glm::vec4 _bbag(const glm::vec4& v) { return glm::vec4(v.b, v.b, v.a, v.g); }
inline glm::vec4 _zzwz(const glm::vec4& v) { return glm::vec4(v.z, v.z, v.w, v.z); }
inline glm::vec4 _bbab(const glm::vec4& v) { return glm::vec4(v.b, v.b, v.a, v.b); }
inline glm::vec4 _zzww(const glm::vec4& v) { return glm::vec4(v.z, v.z, v.w, v.w); }
inline glm::vec4 _bbaa(const glm::vec4& v) { return glm::vec4(v.b, v.b, v.a, v.a); }
inline glm::vec4 _zwxx(const glm::vec4& v) { return glm::vec4(v.z, v.w, v.x, v.x); }
inline glm::vec4 _barr(const glm::vec4& v) { return glm::vec4(v.b, v.a, v.r, v.r); }
inline glm::vec4 _zwxy(const glm::vec4& v) { return glm::vec4(v.z, v.w, v.x, v.y); }
inline glm::vec4 _barg(const glm::vec4& v) { return glm::vec4(v.b, v.a, v.r, v.g); }
inline glm::vec4 _zwxz(const glm::vec4& v) { return glm::vec4(v.z, v.w, v.x, v.z); }
inline glm::vec4 _barb(const glm::vec4& v) { return glm::vec4(v.b, v.a, v.r, v.b); }
inline glm::vec4 _zwxw(const glm::vec4& v) { return glm::vec4(v.z, v.w, v.x, v.w); }
inline glm::vec4 _bara(const glm::vec4& v) { return glm::vec4(v.b, v.a, v.r, v.a); }
inline glm::vec4 _zwyx(const glm::vec4& v) { return glm::vec4(v.z, v.w, v.y, v.x); }
inline glm::vec4 _bagr(const glm::vec4& v) { return glm::vec4(v.b, v.a, v.g, v.r); }
inline glm::vec4 _zwyy(const glm::vec4& v) { return glm::vec4(v.z, v.w, v.y, v.y); }
inline glm::vec4 _bagg(const glm::vec4& v) { return glm::vec4(v.b, v.a, v.g, v.g); }
inline glm::vec4 _zwyz(const glm::vec4& v) { return glm::vec4(v.z, v.w, v.y, v.z); }
inline glm::vec4 _bagb(const glm::vec4& v) { return glm::vec4(v.b, v.a, v.g, v.b); }
inline glm::vec4 _zwyw(const glm::vec4& v) { return glm::vec4(v.z, v.w, v.y, v.w); }
inline glm::vec4 _baga(const glm::vec4& v) { return glm::vec4(v.b, v.a, v.g, v.a); }
inline glm::vec4 _zwzx(const glm::vec4& v) { return glm::vec4(v.z, v.w, v.z, v.x); }
inline glm::vec4 _babr(const glm::vec4& v) { return glm::vec4(v.b, v.a, v.b, v.r); }
inline glm::vec4 _zwzy(const glm::vec4& v) { return glm::vec4(v.z, v.w, v.z, v.y); }
inline glm::vec4 _babg(const glm::vec4& v) { return glm::vec4(v.b, v.a, v.b, v.g); }
inline glm::vec4 _zwzz(const glm::vec4& v) { return glm::vec4(v.z, v.w, v.z, v.z); }
inline glm::vec4 _babb(const glm::vec4& v) { return glm::vec4(v.b, v.a, v.b, v.b); }
inline glm::vec4 _zwzw(const glm::vec4& v) { return glm::vec4(v.z, v.w, v.z, v.w); }
inline glm::vec4 _baba(const glm::vec4& v) { return glm::vec4(v.b, v.a, v.b, v.a); }
inline glm::vec4 _zwwx(const glm::vec4& v) { return glm::vec4(v.z, v.w, v.w, v.x); }
inline glm::vec4 _baar(const glm::vec4& v) { return glm::vec4(v.b, v.a, v.a, v.r); }
inline glm::vec4 _zwwy(const glm::vec4& v) { return glm::vec4(v.z, v.w, v.w, v.y); }
inline glm::vec4 _baag(const glm::vec4& v) { return glm::vec4(v.b, v.a, v.a, v.g); }
inline glm::vec4 _zwwz(const glm::vec4& v) { return glm::vec4(v.z, v.w, v.w, v.z); }
inline glm::vec4 _baab(const glm::vec4& v) { return glm::vec4(v.b, v.a, v.a, v.b); }
inline glm::vec4 _zwww(const glm::vec4& v) { return glm::vec4(v.z, v.w, v.w, v.w); }
inline glm::vec4 _baaa(const glm::vec4& v) { return glm::vec4(v.b, v.a, v.a, v.a); }
inline glm::vec4 _wxxx(const glm::vec4& v) { return glm::vec4(v.w, v.x, v.x, v.x); }
inline glm::vec4 _arrr(const glm::vec4& v) { return glm::vec4(v.a, v.r, v.r, v.r); }
inline glm::vec4 _wxxy(const glm::vec4& v) { return glm::vec4(v.w, v.x, v.x, v.y); }
inline glm::vec4 _arrg(const glm::vec4& v) { return glm::vec4(v.a, v.r, v.r, v.g); }
inline glm::vec4 _wxxz(const glm::vec4& v) { return glm::vec4(v.w, v.x, v.x, v.z); }
inline glm::vec4 _arrb(const glm::vec4& v) { return glm::vec4(v.a, v.r, v.r, v.b); }
inline glm::vec4 _wxxw(const glm::vec4& v) { return glm::vec4(v.w, v.x, v.x, v.w); }
inline glm::vec4 _arra(const glm::vec4& v) { return glm::vec4(v.a, v.r, v.r, v.a); }
inline glm::vec4 _wxyx(const glm::vec4& v) { return glm::vec4(v.w, v.x, v.y, v.x); }
inline glm::vec4 _argr(const glm::vec4& v) { return glm::vec4(v.a, v.r, v.g, v.r); }
inline glm::vec4 _wxyy(const glm::vec4& v) { return glm::vec4(v.w, v.x, v.y, v.y); }
inline glm::vec4 _argg(const glm::vec4& v) { return glm::vec4(v.a, v.r, v.g, v.g); }
inline glm::vec4 _wxyz(const glm::vec4& v) { return glm::vec4(v.w, v.x, v.y, v.z); }
inline glm::vec4 _argb(const glm::vec4& v) { return glm::vec4(v.a, v.r, v.g, v.b); }
inline glm::vec4 _wxyw(const glm::vec4& v) { return glm::vec4(v.w, v.x, v.y, v.w); }
inline glm::vec4 _arga(const glm::vec4& v) { return glm::vec4(v.a, v.r, v.g, v.a); }
inline glm::vec4 _wxzx(const glm::vec4& v) { return glm::vec4(v.w, v.x, v.z, v.x); }
inline glm::vec4 _arbr(const glm::vec4& v) { return glm::vec4(v.a, v.r, v.b, v.r); }
inline glm::vec4 _wxzy(const glm::vec4& v) { return glm::vec4(v.w, v.x, v.z, v.y); }
inline glm::vec4 _arbg(const glm::vec4& v) { return glm::vec4(v.a, v.r, v.b, v.g); }
inline glm::vec4 _wxzz(const glm::vec4& v) { return glm::vec4(v.w, v.x, v.z, v.z); }
inline glm::vec4 _arbb(const glm::vec4& v) { return glm::vec4(v.a, v.r, v.b, v.b); }
inline glm::vec4 _wxzw(const glm::vec4& v) { return glm::vec4(v.w, v.x, v.z, v.w); }
inline glm::vec4 _arba(const glm::vec4& v) { return glm::vec4(v.a, v.r, v.b, v.a); }
inline glm::vec4 _wxwx(const glm::vec4& v) { return glm::vec4(v.w, v.x, v.w, v.x); }
inline glm::vec4 _arar(const glm::vec4& v) { return glm::vec4(v.a, v.r, v.a, v.r); }
inline glm::vec4 _wxwy(const glm::vec4& v) { return glm::vec4(v.w, v.x, v.w, v.y); }
inline glm::vec4 _arag(const glm::vec4& v) { return glm::vec4(v.a, v.r, v.a, v.g); }
inline glm::vec4 _wxwz(const glm::vec4& v) { return glm::vec4(v.w, v.x, v.w, v.z); }
inline glm::vec4 _arab(const glm::vec4& v) { return glm::vec4(v.a, v.r, v.a, v.b); }
inline glm::vec4 _wxww(const glm::vec4& v) { return glm::vec4(v.w, v.x, v.w, v.w); }
inline glm::vec4 _araa(const glm::vec4& v) { return glm::vec4(v.a, v.r, v.a, v.a); }
inline glm::vec4 _wyxx(const glm::vec4& v) { return glm::vec4(v.w, v.y, v.x, v.x); }
inline glm::vec4 _agrr(const glm::vec4& v) { return glm::vec4(v.a, v.g, v.r, v.r); }
inline glm::vec4 _wyxy(const glm::vec4& v) { return glm::vec4(v.w, v.y, v.x, v.y); }
inline glm::vec4 _agrg(const glm::vec4& v) { return glm::vec4(v.a, v.g, v.r, v.g); }
inline glm::vec4 _wyxz(const glm::vec4& v) { return glm::vec4(v.w, v.y, v.x, v.z); }
inline glm::vec4 _agrb(const glm::vec4& v) { return glm::vec4(v.a, v.g, v.r, v.b); }
inline glm::vec4 _wyxw(const glm::vec4& v) { return glm::vec4(v.w, v.y, v.x, v.w); }
inline glm::vec4 _agra(const glm::vec4& v) { return glm::vec4(v.a, v.g, v.r, v.a); }
inline glm::vec4 _wyyx(const glm::vec4& v) { return glm::vec4(v.w, v.y, v.y, v.x); }
inline glm::vec4 _aggr(const glm::vec4& v) { return glm::vec4(v.a, v.g, v.g, v.r); }
inline glm::vec4 _wyyy(const glm::vec4& v) { return glm::vec4(v.w, v.y, v.y, v.y); }
inline glm::vec4 _aggg(const glm::vec4& v) { return glm::vec4(v.a, v.g, v.g, v.g); }
inline glm::vec4 _wyyz(const glm::vec4& v) { return glm::vec4(v.w, v.y, v.y, v.z); }
inline glm::vec4 _aggb(const glm::vec4& v) { return glm::vec4(v.a, v.g, v.g, v.b); }
inline glm::vec4 _wyyw(const glm::vec4& v) { return glm::vec4(v.w, v.y, v.y, v.w); }
inline glm::vec4 _agga(const glm::vec4& v) { return glm::vec4(v.a, v.g, v.g, v.a); }
inline glm::vec4 _wyzx(const glm::vec4& v) { return glm::vec4(v.w, v.y, v.z, v.x); }
inline glm::vec4 _agbr(const glm::vec4& v) { return glm::vec4(v.a, v.g, v.b, v.r); }
inline glm::vec4 _wyzy(const glm::vec4& v) { return glm::vec4(v.w, v.y, v.z, v.y); }
inline glm::vec4 _agbg(const glm::vec4& v) { return glm::vec4(v.a, v.g, v.b, v.g); }
inline glm::vec4 _wyzz(const glm::vec4& v) { return glm::vec4(v.w, v.y, v.z, v.z); }
inline glm::vec4 _agbb(const glm::vec4& v) { return glm::vec4(v.a, v.g, v.b, v.b); }
inline glm::vec4 _wyzw(const glm::vec4& v) { return glm::vec4(v.w, v.y, v.z, v.w); }
inline glm::vec4 _agba(const glm::vec4& v) { return glm::vec4(v.a, v.g, v.b, v.a); }
inline glm::vec4 _wywx(const glm::vec4& v) { return glm::vec4(v.w, v.y, v.w, v.x); }
inline glm::vec4 _agar(const glm::vec4& v) { return glm::vec4(v.a, v.g, v.a, v.r); }
inline glm::vec4 _wywy(const glm::vec4& v) { return glm::vec4(v.w, v.y, v.w, v.y); }
inline glm::vec4 _agag(const glm::vec4& v) { return glm::vec4(v.a, v.g, v.a, v.g); }
inline glm::vec4 _wywz(const glm::vec4& v) { return glm::vec4(v.w, v.y, v.w, v.z); }
inline glm::vec4 _agab(const glm::vec4& v) { return glm::vec4(v.a, v.g, v.a, v.b); }
inline glm::vec4 _wyww(const glm::vec4& v) { return glm::vec4(v.w, v.y, v.w, v.w); }
inline glm::vec4 _agaa(const glm::vec4& v) { return glm::vec4(v.a, v.g, v.a, v.a); }
inline glm::vec4 _wzxx(const glm::vec4& v) { return glm::vec4(v.w, v.z, v.x, v.x); }
inline glm::vec4 _abrr(const glm::vec4& v) { return glm::vec4(v.a, v.b, v.r, v.r); }
inline glm::vec4 _wzxy(const glm::vec4& v) { return glm::vec4(v.w, v.z, v.x, v.y); }
inline glm::vec4 _abrg(const glm::vec4& v) { return glm::vec4(v.a, v.b, v.r, v.g); }
inline glm::vec4 _wzxz(const glm::vec4& v) { return glm::vec4(v.w, v.z, v.x, v.z); }
inline glm::vec4 _abrb(const glm::vec4& v) { return glm::vec4(v.a, v.b, v.r, v.b); }
inline glm::vec4 _wzxw(const glm::vec4& v) { return glm::vec4(v.w, v.z, v.x, v.w); }
inline glm::vec4 _abra(const glm::vec4& v) { return glm::vec4(v.a, v.b, v.r, v.a); }
inline glm::vec4 _wzyx(const glm::vec4& v) { return glm::vec4(v.w, v.z, v.y, v.x); }
inline glm::vec4 _abgr(const glm::vec4& v) { return glm::vec4(v.a, v.b, v.g, v.r); }
inline glm::vec4 _wzyy(const glm::vec4& v) { return glm::vec4(v.w, v.z, v.y, v.y); }
inline glm::vec4 _abgg(const glm::vec4& v) { return glm::vec4(v.a, v.b, v.g, v.g); }
inline glm::vec4 _wzyz(const glm::vec4& v) { return glm::vec4(v.w, v.z, v.y, v.z); }
inline glm::vec4 _abgb(const glm::vec4& v) { return glm::vec4(v.a, v.b, v.g, v.b); }
inline glm::vec4 _wzyw(const glm::vec4& v) { return glm::vec4(v.w, v.z, v.y, v.w); }
inline glm::vec4 _abga(const glm::vec4& v) { return glm::vec4(v.a, v.b, v.g, v.a); }
inline glm::vec4 _wzzx(const glm::vec4& v) { return glm::vec4(v.w, v.z, v.z, v.x); }
inline glm::vec4 _abbr(const glm::vec4& v) { return glm::vec4(v.a, v.b, v.b, v.r); }
inline glm::vec4 _wzzy(const glm::vec4& v) { return glm::vec4(v.w, v.z, v.z, v.y); }
inline glm::vec4 _abbg(const glm::vec4& v) { return glm::vec4(v.a, v.b, v.b, v.g); }
inline glm::vec4 _wzzz(const glm::vec4& v) { return glm::vec4(v.w, v.z, v.z, v.z); }
inline glm::vec4 _abbb(const glm::vec4& v) { return glm::vec4(v.a, v.b, v.b, v.b); }
inline glm::vec4 _wzzw(const glm::vec4& v) { return glm::vec4(v.w, v.z, v.z, v.w); }
inline glm::vec4 _abba(const glm::vec4& v) { return glm::vec4(v.a, v.b, v.b, v.a); }
inline glm::vec4 _wzwx(const glm::vec4& v) { return glm::vec4(v.w, v.z, v.w, v.x); }
inline glm::vec4 _abar(const glm::vec4& v) { return glm::vec4(v.a, v.b, v.a, v.r); }
inline glm::vec4 _wzwy(const glm::vec4& v) { return glm::vec4(v.w, v.z, v.w, v.y); }
inline glm::vec4 _abag(const glm::vec4& v) { return glm::vec4(v.a, v.b, v.a, v.g); }
inline glm::vec4 _wzwz(const glm::vec4& v) { return glm::vec4(v.w, v.z, v.w, v.z); }
inline glm::vec4 _abab(const glm::vec4& v) { return glm::vec4(v.a, v.b, v.a, v.b); }
inline glm::vec4 _wzww(const glm::vec4& v) { return glm::vec4(v.w, v.z, v.w, v.w); }
inline glm::vec4 _abaa(const glm::vec4& v) { return glm::vec4(v.a, v.b, v.a, v.a); }
inline glm::vec4 _wwxx(const glm::vec4& v) { return glm::vec4(v.w, v.w, v.x, v.x); }
inline glm::vec4 _aarr(const glm::vec4& v) { return glm::vec4(v.a, v.a, v.r, v.r); }
inline glm::vec4 _wwxy(const glm::vec4& v) { return glm::vec4(v.w, v.w, v.x, v.y); }
inline glm::vec4 _aarg(const glm::vec4& v) { return glm::vec4(v.a, v.a, v.r, v.g); }
inline glm::vec4 _wwxz(const glm::vec4& v) { return glm::vec4(v.w, v.w, v.x, v.z); }
inline glm::vec4 _aarb(const glm::vec4& v) { return glm::vec4(v.a, v.a, v.r, v.b); }
inline glm::vec4 _wwxw(const glm::vec4& v) { return glm::vec4(v.w, v.w, v.x, v.w); }
inline glm::vec4 _aara(const glm::vec4& v) { return glm::vec4(v.a, v.a, v.r, v.a); }
inline glm::vec4 _wwyx(const glm::vec4& v) { return glm::vec4(v.w, v.w, v.y, v.x); }
inline glm::vec4 _aagr(const glm::vec4& v) { return glm::vec4(v.a, v.a, v.g, v.r); }
inline glm::vec4 _wwyy(const glm::vec4& v) { return glm::vec4(v.w, v.w, v.y, v.y); }
inline glm::vec4 _aagg(const glm::vec4& v) { return glm::vec4(v.a, v.a, v.g, v.g); }
inline glm::vec4 _wwyz(const glm::vec4& v) { return glm::vec4(v.w, v.w, v.y, v.z); }
inline glm::vec4 _aagb(const glm::vec4& v) { return glm::vec4(v.a, v.a, v.g, v.b); }
inline glm::vec4 _wwyw(const glm::vec4& v) { return glm::vec4(v.w, v.w, v.y, v.w); }
inline glm::vec4 _aaga(const glm::vec4& v) { return glm::vec4(v.a, v.a, v.g, v.a); }
inline glm::vec4 _wwzx(const glm::vec4& v) { return glm::vec4(v.w, v.w, v.z, v.x); }
inline glm::vec4 _aabr(const glm::vec4& v) { return glm::vec4(v.a, v.a, v.b, v.r); }
inline glm::vec4 _wwzy(const glm::vec4& v) { return glm::vec4(v.w, v.w, v.z, v.y); }
inline glm::vec4 _aabg(const glm::vec4& v) { return glm::vec4(v.a, v.a, v.b, v.g); }
inline glm::vec4 _wwzz(const glm::vec4& v) { return glm::vec4(v.w, v.w, v.z, v.z); }
inline glm::vec4 _aabb(const glm::vec4& v) { return glm::vec4(v.a, v.a, v.b, v.b); }
inline glm::vec4 _wwzw(const glm::vec4& v) { return glm::vec4(v.w, v.w, v.z, v.w); }
inline glm::vec4 _aaba(const glm::vec4& v) { return glm::vec4(v.a, v.a, v.b, v.a); }
inline glm::vec4 _wwwx(const glm::vec4& v) { return glm::vec4(v.w, v.w, v.w, v.x); }
inline glm::vec4 _aaar(const glm::vec4& v) { return glm::vec4(v.a, v.a, v.a, v.r); }
inline glm::vec4 _wwwy(const glm::vec4& v) { return glm::vec4(v.w, v.w, v.w, v.y); }
inline glm::vec4 _aaag(const glm::vec4& v) { return glm::vec4(v.a, v.a, v.a, v.g); }
inline glm::vec4 _wwwz(const glm::vec4& v) { return glm::vec4(v.w, v.w, v.w, v.z); }
inline glm::vec4 _aaab(const glm::vec4& v) { return glm::vec4(v.a, v.a, v.a, v.b); }
inline glm::vec4 _wwww(const glm::vec4& v) { return glm::vec4(v.w, v.w, v.w, v.w); }
inline glm::vec4 _aaaa(const glm::vec4& v) { return glm::vec4(v.a, v.a, v.a, v.a); }
inline int _x(const glm::ivec2& v) { return int(v.x); }
inline int _r(const glm::ivec2& v) { return int(v.r); }
inline int _y(const glm::ivec2& v) { return int(v.y); }
inline int _g(const glm::ivec2& v) { return int(v.g); }
inline glm::ivec2 _xx(const glm::ivec2& v) { return glm::ivec2(v.x, v.x); }
inline glm::ivec2 _rr(const glm::ivec2& v) { return glm::ivec2(v.r, v.r); }
inline glm::ivec2 _xy(const glm::ivec2& v) { return glm::ivec2(v.x, v.y); }
inline glm::ivec2 _rg(const glm::ivec2& v) { return glm::ivec2(v.r, v.g); }
inline glm::ivec2 _yx(const glm::ivec2& v) { return glm::ivec2(v.y, v.x); }
inline glm::ivec2 _gr(const glm::ivec2& v) { return glm::ivec2(v.g, v.r); }
inline glm::ivec2 _yy(const glm::ivec2& v) { return glm::ivec2(v.y, v.y); }
inline glm::ivec2 _gg(const glm::ivec2& v) { return glm::ivec2(v.g, v.g); }

inline int _x(const glm::ivec3& v) { return int(v.x); }
inline int _r(const glm::ivec3& v) { return int(v.r); }
inline int _y(const glm::ivec3& v) { return int(v.y); }
inline int _g(const glm::ivec3& v) { return int(v.g); }
inline int _z(const glm::ivec3& v) { return int(v.z); }
inline int _b(const glm::ivec3& v) { return int(v.b); }
inline glm::ivec2 _xx(const glm::ivec3& v) { return glm::ivec2(v.x, v.x); }
inline glm::ivec2 _rr(const glm::ivec3& v) { return glm::ivec2(v.r, v.r); }
inline glm::ivec2 _xy(const glm::ivec3& v) { return glm::ivec2(v.x, v.y); }
inline glm::ivec2 _rg(const glm::ivec3& v) { return glm::ivec2(v.r, v.g); }
inline glm::ivec2 _xz(const glm::ivec3& v) { return glm::ivec2(v.x, v.z); }
inline glm::ivec2 _rb(const glm::ivec3& v) { return glm::ivec2(v.r, v.b); }
inline glm::ivec2 _yx(const glm::ivec3& v) { return glm::ivec2(v.y, v.x); }
inline glm::ivec2 _gr(const glm::ivec3& v) { return glm::ivec2(v.g, v.r); }
inline glm::ivec2 _yy(const glm::ivec3& v) { return glm::ivec2(v.y, v.y); }
inline glm::ivec2 _gg(const glm::ivec3& v) { return glm::ivec2(v.g, v.g); }
inline glm::ivec2 _yz(const glm::ivec3& v) { return glm::ivec2(v.y, v.z); }
inline glm::ivec2 _gb(const glm::ivec3& v) { return glm::ivec2(v.g, v.b); }
inline glm::ivec2 _zx(const glm::ivec3& v) { return glm::ivec2(v.z, v.x); }
inline glm::ivec2 _br(const glm::ivec3& v) { return glm::ivec2(v.b, v.r); }
inline glm::ivec2 _zy(const glm::ivec3& v) { return glm::ivec2(v.z, v.y); }
inline glm::ivec2 _bg(const glm::ivec3& v) { return glm::ivec2(v.b, v.g); }
inline glm::ivec2 _zz(const glm::ivec3& v) { return glm::ivec2(v.z, v.z); }
inline glm::ivec2 _bb(const glm::ivec3& v) { return glm::ivec2(v.b, v.b); }
inline glm::ivec3 _xxx(const glm::ivec3& v) { return glm::ivec3(v.x, v.x, v.x); }
inline glm::ivec3 _rrr(const glm::ivec3& v) { return glm::ivec3(v.r, v.r, v.r); }
inline glm::ivec3 _xxy(const glm::ivec3& v) { return glm::ivec3(v.x, v.x, v.y); }
inline glm::ivec3 _rrg(const glm::ivec3& v) { return glm::ivec3(v.r, v.r, v.g); }
inline glm::ivec3 _xxz(const glm::ivec3& v) { return glm::ivec3(v.x, v.x, v.z); }
inline glm::ivec3 _rrb(const glm::ivec3& v) { return glm::ivec3(v.r, v.r, v.b); }
inline glm::ivec3 _xyx(const glm::ivec3& v) { return glm::ivec3(v.x, v.y, v.x); }
inline glm::ivec3 _rgr(const glm::ivec3& v) { return glm::ivec3(v.r, v.g, v.r); }
inline glm::ivec3 _xyy(const glm::ivec3& v) { return glm::ivec3(v.x, v.y, v.y); }
inline glm::ivec3 _rgg(const glm::ivec3& v) { return glm::ivec3(v.r, v.g, v.g); }
inline glm::ivec3 _xyz(const glm::ivec3& v) { return glm::ivec3(v.x, v.y, v.z); }
inline glm::ivec3 _rgb(const glm::ivec3& v) { return glm::ivec3(v.r, v.g, v.b); }
inline glm::ivec3 _xzx(const glm::ivec3& v) { return glm::ivec3(v.x, v.z, v.x); }
inline glm::ivec3 _rbr(const glm::ivec3& v) { return glm::ivec3(v.r, v.b, v.r); }
inline glm::ivec3 _xzy(const glm::ivec3& v) { return glm::ivec3(v.x, v.z, v.y); }
inline glm::ivec3 _rbg(const glm::ivec3& v) { return glm::ivec3(v.r, v.b, v.g); }
inline glm::ivec3 _xzz(const glm::ivec3& v) { return glm::ivec3(v.x, v.z, v.z); }
inline glm::ivec3 _rbb(const glm::ivec3& v) { return glm::ivec3(v.r, v.b, v.b); }
inline glm::ivec3 _yxx(const glm::ivec3& v) { return glm::ivec3(v.y, v.x, v.x); }
inline glm::ivec3 _grr(const glm::ivec3& v) { return glm::ivec3(v.g, v.r, v.r); }
inline glm::ivec3 _yxy(const glm::ivec3& v) { return glm::ivec3(v.y, v.x, v.y); }
inline glm::ivec3 _grg(const glm::ivec3& v) { return glm::ivec3(v.g, v.r, v.g); }
inline glm::ivec3 _yxz(const glm::ivec3& v) { return glm::ivec3(v.y, v.x, v.z); }
inline glm::ivec3 _grb(const glm::ivec3& v) { return glm::ivec3(v.g, v.r, v.b); }
inline glm::ivec3 _yyx(const glm::ivec3& v) { return glm::ivec3(v.y, v.y, v.x); }
inline glm::ivec3 _ggr(const glm::ivec3& v) { return glm::ivec3(v.g, v.g, v.r); }
inline glm::ivec3 _yyy(const glm::ivec3& v) { return glm::ivec3(v.y, v.y, v.y); }
inline glm::ivec3 _ggg(const glm::ivec3& v) { return glm::ivec3(v.g, v.g, v.g); }
inline glm::ivec3 _yyz(const glm::ivec3& v) { return glm::ivec3(v.y, v.y, v.z); }
inline glm::ivec3 _ggb(const glm::ivec3& v) { return glm::ivec3(v.g, v.g, v.b); }
inline glm::ivec3 _yzx(const glm::ivec3& v) { return glm::ivec3(v.y, v.z, v.x); }
inline glm::ivec3 _gbr(const glm::ivec3& v) { return glm::ivec3(v.g, v.b, v.r); }
inline glm::ivec3 _yzy(const glm::ivec3& v) { return glm::ivec3(v.y, v.z, v.y); }
inline glm::ivec3 _gbg(const glm::ivec3& v) { return glm::ivec3(v.g, v.b, v.g); }
inline glm::ivec3 _yzz(const glm::ivec3& v) { return glm::ivec3(v.y, v.z, v.z); }
inline glm::ivec3 _gbb(const glm::ivec3& v) { return glm::ivec3(v.g, v.b, v.b); }
inline glm::ivec3 _zxx(const glm::ivec3& v) { return glm::ivec3(v.z, v.x, v.x); }
inline glm::ivec3 _brr(const glm::ivec3& v) { return glm::ivec3(v.b, v.r, v.r); }
inline glm::ivec3 _zxy(const glm::ivec3& v) { return glm::ivec3(v.z, v.x, v.y); }
inline glm::ivec3 _brg(const glm::ivec3& v) { return glm::ivec3(v.b, v.r, v.g); }
inline glm::ivec3 _zxz(const glm::ivec3& v) { return glm::ivec3(v.z, v.x, v.z); }
inline glm::ivec3 _brb(const glm::ivec3& v) { return glm::ivec3(v.b, v.r, v.b); }
inline glm::ivec3 _zyx(const glm::ivec3& v) { return glm::ivec3(v.z, v.y, v.x); }
inline glm::ivec3 _bgr(const glm::ivec3& v) { return glm::ivec3(v.b, v.g, v.r); }
inline glm::ivec3 _zyy(const glm::ivec3& v) { return glm::ivec3(v.z, v.y, v.y); }
inline glm::ivec3 _bgg(const glm::ivec3& v) { return glm::ivec3(v.b, v.g, v.g); }
inline glm::ivec3 _zyz(const glm::ivec3& v) { return glm::ivec3(v.z, v.y, v.z); }
inline glm::ivec3 _bgb(const glm::ivec3& v) { return glm::ivec3(v.b, v.g, v.b); }
inline glm::ivec3 _zzx(const glm::ivec3& v) { return glm::ivec3(v.z, v.z, v.x); }
inline glm::ivec3 _bbr(const glm::ivec3& v) { return glm::ivec3(v.b, v.b, v.r); }
inline glm::ivec3 _zzy(const glm::ivec3& v) { return glm::ivec3(v.z, v.z, v.y); }
inline glm::ivec3 _bbg(const glm::ivec3& v) { return glm::ivec3(v.b, v.b, v.g); }
inline glm::ivec3 _zzz(const glm::ivec3& v) { return glm::ivec3(v.z, v.z, v.z); }
inline glm::ivec3 _bbb(const glm::ivec3& v) { return glm::ivec3(v.b, v.b, v.b); }

inline int _x(const glm::ivec4& v) { return int(v.x); }
inline int _r(const glm::ivec4& v) { return int(v.r); }
inline int _y(const glm::ivec4& v) { return int(v.y); }
inline int _g(const glm::ivec4& v) { return int(v.g); }
inline int _z(const glm::ivec4& v) { return int(v.z); }
inline int _b(const glm::ivec4& v) { return int(v.b); }
inline int _w(const glm::ivec4& v) { return int(v.w); }
inline int _a(const glm::ivec4& v) { return int(v.a); }
inline glm::ivec2 _xx(const glm::ivec4& v) { return glm::ivec2(v.x, v.x); }
inline glm::ivec2 _rr(const glm::ivec4& v) { return glm::ivec2(v.r, v.r); }
inline glm::ivec2 _xy(const glm::ivec4& v) { return glm::ivec2(v.x, v.y); }
inline glm::ivec2 _rg(const glm::ivec4& v) { return glm::ivec2(v.r, v.g); }
inline glm::ivec2 _xz(const glm::ivec4& v) { return glm::ivec2(v.x, v.z); }
inline glm::ivec2 _rb(const glm::ivec4& v) { return glm::ivec2(v.r, v.b); }
inline glm::ivec2 _xw(const glm::ivec4& v) { return glm::ivec2(v.x, v.w); }
inline glm::ivec2 _ra(const glm::ivec4& v) { return glm::ivec2(v.r, v.a); }
inline glm::ivec2 _yx(const glm::ivec4& v) { return glm::ivec2(v.y, v.x); }
inline glm::ivec2 _gr(const glm::ivec4& v) { return glm::ivec2(v.g, v.r); }
inline glm::ivec2 _yy(const glm::ivec4& v) { return glm::ivec2(v.y, v.y); }
inline glm::ivec2 _gg(const glm::ivec4& v) { return glm::ivec2(v.g, v.g); }
inline glm::ivec2 _yz(const glm::ivec4& v) { return glm::ivec2(v.y, v.z); }
inline glm::ivec2 _gb(const glm::ivec4& v) { return glm::ivec2(v.g, v.b); }
inline glm::ivec2 _yw(const glm::ivec4& v) { return glm::ivec2(v.y, v.w); }
inline glm::ivec2 _ga(const glm::ivec4& v) { return glm::ivec2(v.g, v.a); }
inline glm::ivec2 _zx(const glm::ivec4& v) { return glm::ivec2(v.z, v.x); }
inline glm::ivec2 _br(const glm::ivec4& v) { return glm::ivec2(v.b, v.r); }
inline glm::ivec2 _zy(const glm::ivec4& v) { return glm::ivec2(v.z, v.y); }
inline glm::ivec2 _bg(const glm::ivec4& v) { return glm::ivec2(v.b, v.g); }
inline glm::ivec2 _zz(const glm::ivec4& v) { return glm::ivec2(v.z, v.z); }
inline glm::ivec2 _bb(const glm::ivec4& v) { return glm::ivec2(v.b, v.b); }
inline glm::ivec2 _zw(const glm::ivec4& v) { return glm::ivec2(v.z, v.w); }
inline glm::ivec2 _ba(const glm::ivec4& v) { return glm::ivec2(v.b, v.a); }
inline glm::ivec2 _wx(const glm::ivec4& v) { return glm::ivec2(v.w, v.x); }
inline glm::ivec2 _ar(const glm::ivec4& v) { return glm::ivec2(v.a, v.r); }
inline glm::ivec2 _wy(const glm::ivec4& v) { return glm::ivec2(v.w, v.y); }
inline glm::ivec2 _ag(const glm::ivec4& v) { return glm::ivec2(v.a, v.g); }
inline glm::ivec2 _wz(const glm::ivec4& v) { return glm::ivec2(v.w, v.z); }
inline glm::ivec2 _ab(const glm::ivec4& v) { return glm::ivec2(v.a, v.b); }
inline glm::ivec2 _ww(const glm::ivec4& v) { return glm::ivec2(v.w, v.w); }
inline glm::ivec2 _aa(const glm::ivec4& v) { return glm::ivec2(v.a, v.a); }
inline glm::ivec3 _xxx(const glm::ivec4& v) { return glm::ivec3(v.x, v.x, v.x); }
inline glm::ivec3 _rrr(const glm::ivec4& v) { return glm::ivec3(v.r, v.r, v.r); }
inline glm::ivec3 _xxy(const glm::ivec4& v) { return glm::ivec3(v.x, v.x, v.y); }
inline glm::ivec3 _rrg(const glm::ivec4& v) { return glm::ivec3(v.r, v.r, v.g); }
inline glm::ivec3 _xxz(const glm::ivec4& v) { return glm::ivec3(v.x, v.x, v.z); }
inline glm::ivec3 _rrb(const glm::ivec4& v) { return glm::ivec3(v.r, v.r, v.b); }
inline glm::ivec3 _xxw(const glm::ivec4& v) { return glm::ivec3(v.x, v.x, v.w); }
inline glm::ivec3 _rra(const glm::ivec4& v) { return glm::ivec3(v.r, v.r, v.a); }
inline glm::ivec3 _xyx(const glm::ivec4& v) { return glm::ivec3(v.x, v.y, v.x); }
inline glm::ivec3 _rgr(const glm::ivec4& v) { return glm::ivec3(v.r, v.g, v.r); }
inline glm::ivec3 _xyy(const glm::ivec4& v) { return glm::ivec3(v.x, v.y, v.y); }
inline glm::ivec3 _rgg(const glm::ivec4& v) { return glm::ivec3(v.r, v.g, v.g); }
inline glm::ivec3 _xyz(const glm::ivec4& v) { return glm::ivec3(v.x, v.y, v.z); }
inline glm::ivec3 _rgb(const glm::ivec4& v) { return glm::ivec3(v.r, v.g, v.b); }
inline glm::ivec3 _xyw(const glm::ivec4& v) { return glm::ivec3(v.x, v.y, v.w); }
inline glm::ivec3 _rga(const glm::ivec4& v) { return glm::ivec3(v.r, v.g, v.a); }
inline glm::ivec3 _xzx(const glm::ivec4& v) { return glm::ivec3(v.x, v.z, v.x); }
inline glm::ivec3 _rbr(const glm::ivec4& v) { return glm::ivec3(v.r, v.b, v.r); }
inline glm::ivec3 _xzy(const glm::ivec4& v) { return glm::ivec3(v.x, v.z, v.y); }
inline glm::ivec3 _rbg(const glm::ivec4& v) { return glm::ivec3(v.r, v.b, v.g); }
inline glm::ivec3 _xzz(const glm::ivec4& v) { return glm::ivec3(v.x, v.z, v.z); }
inline glm::ivec3 _rbb(const glm::ivec4& v) { return glm::ivec3(v.r, v.b, v.b); }
inline glm::ivec3 _xzw(const glm::ivec4& v) { return glm::ivec3(v.x, v.z, v.w); }
inline glm::ivec3 _rba(const glm::ivec4& v) { return glm::ivec3(v.r, v.b, v.a); }
inline glm::ivec3 _xwx(const glm::ivec4& v) { return glm::ivec3(v.x, v.w, v.x); }
inline glm::ivec3 _rar(const glm::ivec4& v) { return glm::ivec3(v.r, v.a, v.r); }
inline glm::ivec3 _xwy(const glm::ivec4& v) { return glm::ivec3(v.x, v.w, v.y); }
inline glm::ivec3 _rag(const glm::ivec4& v) { return glm::ivec3(v.r, v.a, v.g); }
inline glm::ivec3 _xwz(const glm::ivec4& v) { return glm::ivec3(v.x, v.w, v.z); }
inline glm::ivec3 _rab(const glm::ivec4& v) { return glm::ivec3(v.r, v.a, v.b); }
inline glm::ivec3 _xww(const glm::ivec4& v) { return glm::ivec3(v.x, v.w, v.w); }
inline glm::ivec3 _raa(const glm::ivec4& v) { return glm::ivec3(v.r, v.a, v.a); }
inline glm::ivec3 _yxx(const glm::ivec4& v) { return glm::ivec3(v.y, v.x, v.x); }
inline glm::ivec3 _grr(const glm::ivec4& v) { return glm::ivec3(v.g, v.r, v.r); }
inline glm::ivec3 _yxy(const glm::ivec4& v) { return glm::ivec3(v.y, v.x, v.y); }
inline glm::ivec3 _grg(const glm::ivec4& v) { return glm::ivec3(v.g, v.r, v.g); }
inline glm::ivec3 _yxz(const glm::ivec4& v) { return glm::ivec3(v.y, v.x, v.z); }
inline glm::ivec3 _grb(const glm::ivec4& v) { return glm::ivec3(v.g, v.r, v.b); }
inline glm::ivec3 _yxw(const glm::ivec4& v) { return glm::ivec3(v.y, v.x, v.w); }
inline glm::ivec3 _gra(const glm::ivec4& v) { return glm::ivec3(v.g, v.r, v.a); }
inline glm::ivec3 _yyx(const glm::ivec4& v) { return glm::ivec3(v.y, v.y, v.x); }
inline glm::ivec3 _ggr(const glm::ivec4& v) { return glm::ivec3(v.g, v.g, v.r); }
inline glm::ivec3 _yyy(const glm::ivec4& v) { return glm::ivec3(v.y, v.y, v.y); }
inline glm::ivec3 _ggg(const glm::ivec4& v) { return glm::ivec3(v.g, v.g, v.g); }
inline glm::ivec3 _yyz(const glm::ivec4& v) { return glm::ivec3(v.y, v.y, v.z); }
inline glm::ivec3 _ggb(const glm::ivec4& v) { return glm::ivec3(v.g, v.g, v.b); }
inline glm::ivec3 _yyw(const glm::ivec4& v) { return glm::ivec3(v.y, v.y, v.w); }
inline glm::ivec3 _gga(const glm::ivec4& v) { return glm::ivec3(v.g, v.g, v.a); }
inline glm::ivec3 _yzx(const glm::ivec4& v) { return glm::ivec3(v.y, v.z, v.x); }
inline glm::ivec3 _gbr(const glm::ivec4& v) { return glm::ivec3(v.g, v.b, v.r); }
inline glm::ivec3 _yzy(const glm::ivec4& v) { return glm::ivec3(v.y, v.z, v.y); }
inline glm::ivec3 _gbg(const glm::ivec4& v) { return glm::ivec3(v.g, v.b, v.g); }
inline glm::ivec3 _yzz(const glm::ivec4& v) { return glm::ivec3(v.y, v.z, v.z); }
inline glm::ivec3 _gbb(const glm::ivec4& v) { return glm::ivec3(v.g, v.b, v.b); }
inline glm::ivec3 _yzw(const glm::ivec4& v) { return glm::ivec3(v.y, v.z, v.w); }
inline glm::ivec3 _gba(const glm::ivec4& v) { return glm::ivec3(v.g, v.b, v.a); }
inline glm::ivec3 _ywx(const glm::ivec4& v) { return glm::ivec3(v.y, v.w, v.x); }
inline glm::ivec3 _gar(const glm::ivec4& v) { return glm::ivec3(v.g, v.a, v.r); }
inline glm::ivec3 _ywy(const glm::ivec4& v) { return glm::ivec3(v.y, v.w, v.y); }
inline glm::ivec3 _gag(const glm::ivec4& v) { return glm::ivec3(v.g, v.a, v.g); }
inline glm::ivec3 _ywz(const glm::ivec4& v) { return glm::ivec3(v.y, v.w, v.z); }
inline glm::ivec3 _gab(const glm::ivec4& v) { return glm::ivec3(v.g, v.a, v.b); }
inline glm::ivec3 _yww(const glm::ivec4& v) { return glm::ivec3(v.y, v.w, v.w); }
inline glm::ivec3 _gaa(const glm::ivec4& v) { return glm::ivec3(v.g, v.a, v.a); }
inline glm::ivec3 _zxx(const glm::ivec4& v) { return glm::ivec3(v.z, v.x, v.x); }
inline glm::ivec3 _brr(const glm::ivec4& v) { return glm::ivec3(v.b, v.r, v.r); }
inline glm::ivec3 _zxy(const glm::ivec4& v) { return glm::ivec3(v.z, v.x, v.y); }
inline glm::ivec3 _brg(const glm::ivec4& v) { return glm::ivec3(v.b, v.r, v.g); }
inline glm::ivec3 _zxz(const glm::ivec4& v) { return glm::ivec3(v.z, v.x, v.z); }
inline glm::ivec3 _brb(const glm::ivec4& v) { return glm::ivec3(v.b, v.r, v.b); }
inline glm::ivec3 _zxw(const glm::ivec4& v) { return glm::ivec3(v.z, v.x, v.w); }
inline glm::ivec3 _bra(const glm::ivec4& v) { return glm::ivec3(v.b, v.r, v.a); }
inline glm::ivec3 _zyx(const glm::ivec4& v) { return glm::ivec3(v.z, v.y, v.x); }
inline glm::ivec3 _bgr(const glm::ivec4& v) { return glm::ivec3(v.b, v.g, v.r); }
inline glm::ivec3 _zyy(const glm::ivec4& v) { return glm::ivec3(v.z, v.y, v.y); }
inline glm::ivec3 _bgg(const glm::ivec4& v) { return glm::ivec3(v.b, v.g, v.g); }
inline glm::ivec3 _zyz(const glm::ivec4& v) { return glm::ivec3(v.z, v.y, v.z); }
inline glm::ivec3 _bgb(const glm::ivec4& v) { return glm::ivec3(v.b, v.g, v.b); }
inline glm::ivec3 _zyw(const glm::ivec4& v) { return glm::ivec3(v.z, v.y, v.w); }
inline glm::ivec3 _bga(const glm::ivec4& v) { return glm::ivec3(v.b, v.g, v.a); }
inline glm::ivec3 _zzx(const glm::ivec4& v) { return glm::ivec3(v.z, v.z, v.x); }
inline glm::ivec3 _bbr(const glm::ivec4& v) { return glm::ivec3(v.b, v.b, v.r); }
inline glm::ivec3 _zzy(const glm::ivec4& v) { return glm::ivec3(v.z, v.z, v.y); }
inline glm::ivec3 _bbg(const glm::ivec4& v) { return glm::ivec3(v.b, v.b, v.g); }
inline glm::ivec3 _zzz(const glm::ivec4& v) { return glm::ivec3(v.z, v.z, v.z); }
inline glm::ivec3 _bbb(const glm::ivec4& v) { return glm::ivec3(v.b, v.b, v.b); }
inline glm::ivec3 _zzw(const glm::ivec4& v) { return glm::ivec3(v.z, v.z, v.w); }
inline glm::ivec3 _bba(const glm::ivec4& v) { return glm::ivec3(v.b, v.b, v.a); }
inline glm::ivec3 _zwx(const glm::ivec4& v) { return glm::ivec3(v.z, v.w, v.x); }
inline glm::ivec3 _bar(const glm::ivec4& v) { return glm::ivec3(v.b, v.a, v.r); }
inline glm::ivec3 _zwy(const glm::ivec4& v) { return glm::ivec3(v.z, v.w, v.y); }
inline glm::ivec3 _bag(const glm::ivec4& v) { return glm::ivec3(v.b, v.a, v.g); }
inline glm::ivec3 _zwz(const glm::ivec4& v) { return glm::ivec3(v.z, v.w, v.z); }
inline glm::ivec3 _bab(const glm::ivec4& v) { return glm::ivec3(v.b, v.a, v.b); }
inline glm::ivec3 _zww(const glm::ivec4& v) { return glm::ivec3(v.z, v.w, v.w); }
inline glm::ivec3 _baa(const glm::ivec4& v) { return glm::ivec3(v.b, v.a, v.a); }
inline glm::ivec3 _wxx(const glm::ivec4& v) { return glm::ivec3(v.w, v.x, v.x); }
inline glm::ivec3 _arr(const glm::ivec4& v) { return glm::ivec3(v.a, v.r, v.r); }
inline glm::ivec3 _wxy(const glm::ivec4& v) { return glm::ivec3(v.w, v.x, v.y); }
inline glm::ivec3 _arg(const glm::ivec4& v) { return glm::ivec3(v.a, v.r, v.g); }
inline glm::ivec3 _wxz(const glm::ivec4& v) { return glm::ivec3(v.w, v.x, v.z); }
inline glm::ivec3 _arb(const glm::ivec4& v) { return glm::ivec3(v.a, v.r, v.b); }
inline glm::ivec3 _wxw(const glm::ivec4& v) { return glm::ivec3(v.w, v.x, v.w); }
inline glm::ivec3 _ara(const glm::ivec4& v) { return glm::ivec3(v.a, v.r, v.a); }
inline glm::ivec3 _wyx(const glm::ivec4& v) { return glm::ivec3(v.w, v.y, v.x); }
inline glm::ivec3 _agr(const glm::ivec4& v) { return glm::ivec3(v.a, v.g, v.r); }
inline glm::ivec3 _wyy(const glm::ivec4& v) { return glm::ivec3(v.w, v.y, v.y); }
inline glm::ivec3 _agg(const glm::ivec4& v) { return glm::ivec3(v.a, v.g, v.g); }
inline glm::ivec3 _wyz(const glm::ivec4& v) { return glm::ivec3(v.w, v.y, v.z); }
inline glm::ivec3 _agb(const glm::ivec4& v) { return glm::ivec3(v.a, v.g, v.b); }
inline glm::ivec3 _wyw(const glm::ivec4& v) { return glm::ivec3(v.w, v.y, v.w); }
inline glm::ivec3 _aga(const glm::ivec4& v) { return glm::ivec3(v.a, v.g, v.a); }
inline glm::ivec3 _wzx(const glm::ivec4& v) { return glm::ivec3(v.w, v.z, v.x); }
inline glm::ivec3 _abr(const glm::ivec4& v) { return glm::ivec3(v.a, v.b, v.r); }
inline glm::ivec3 _wzy(const glm::ivec4& v) { return glm::ivec3(v.w, v.z, v.y); }
inline glm::ivec3 _abg(const glm::ivec4& v) { return glm::ivec3(v.a, v.b, v.g); }
inline glm::ivec3 _wzz(const glm::ivec4& v) { return glm::ivec3(v.w, v.z, v.z); }
inline glm::ivec3 _abb(const glm::ivec4& v) { return glm::ivec3(v.a, v.b, v.b); }
inline glm::ivec3 _wzw(const glm::ivec4& v) { return glm::ivec3(v.w, v.z, v.w); }
inline glm::ivec3 _aba(const glm::ivec4& v) { return glm::ivec3(v.a, v.b, v.a); }
inline glm::ivec3 _wwx(const glm::ivec4& v) { return glm::ivec3(v.w, v.w, v.x); }
inline glm::ivec3 _aar(const glm::ivec4& v) { return glm::ivec3(v.a, v.a, v.r); }
inline glm::ivec3 _wwy(const glm::ivec4& v) { return glm::ivec3(v.w, v.w, v.y); }
inline glm::ivec3 _aag(const glm::ivec4& v) { return glm::ivec3(v.a, v.a, v.g); }
inline glm::ivec3 _wwz(const glm::ivec4& v) { return glm::ivec3(v.w, v.w, v.z); }
inline glm::ivec3 _aab(const glm::ivec4& v) { return glm::ivec3(v.a, v.a, v.b); }
inline glm::ivec3 _www(const glm::ivec4& v) { return glm::ivec3(v.w, v.w, v.w); }
inline glm::ivec3 _aaa(const glm::ivec4& v) { return glm::ivec3(v.a, v.a, v.a); }
inline glm::ivec4 _xxxx(const glm::ivec4& v) { return glm::ivec4(v.x, v.x, v.x, v.x); }
inline glm::ivec4 _rrrr(const glm::ivec4& v) { return glm::ivec4(v.r, v.r, v.r, v.r); }
inline glm::ivec4 _xxxy(const glm::ivec4& v) { return glm::ivec4(v.x, v.x, v.x, v.y); }
inline glm::ivec4 _rrrg(const glm::ivec4& v) { return glm::ivec4(v.r, v.r, v.r, v.g); }
inline glm::ivec4 _xxxz(const glm::ivec4& v) { return glm::ivec4(v.x, v.x, v.x, v.z); }
inline glm::ivec4 _rrrb(const glm::ivec4& v) { return glm::ivec4(v.r, v.r, v.r, v.b); }
inline glm::ivec4 _xxxw(const glm::ivec4& v) { return glm::ivec4(v.x, v.x, v.x, v.w); }
inline glm::ivec4 _rrra(const glm::ivec4& v) { return glm::ivec4(v.r, v.r, v.r, v.a); }
inline glm::ivec4 _xxyx(const glm::ivec4& v) { return glm::ivec4(v.x, v.x, v.y, v.x); }
inline glm::ivec4 _rrgr(const glm::ivec4& v) { return glm::ivec4(v.r, v.r, v.g, v.r); }
inline glm::ivec4 _xxyy(const glm::ivec4& v) { return glm::ivec4(v.x, v.x, v.y, v.y); }
inline glm::ivec4 _rrgg(const glm::ivec4& v) { return glm::ivec4(v.r, v.r, v.g, v.g); }
inline glm::ivec4 _xxyz(const glm::ivec4& v) { return glm::ivec4(v.x, v.x, v.y, v.z); }
inline glm::ivec4 _rrgb(const glm::ivec4& v) { return glm::ivec4(v.r, v.r, v.g, v.b); }
inline glm::ivec4 _xxyw(const glm::ivec4& v) { return glm::ivec4(v.x, v.x, v.y, v.w); }
inline glm::ivec4 _rrga(const glm::ivec4& v) { return glm::ivec4(v.r, v.r, v.g, v.a); }
inline glm::ivec4 _xxzx(const glm::ivec4& v) { return glm::ivec4(v.x, v.x, v.z, v.x); }
inline glm::ivec4 _rrbr(const glm::ivec4& v) { return glm::ivec4(v.r, v.r, v.b, v.r); }
inline glm::ivec4 _xxzy(const glm::ivec4& v) { return glm::ivec4(v.x, v.x, v.z, v.y); }
inline glm::ivec4 _rrbg(const glm::ivec4& v) { return glm::ivec4(v.r, v.r, v.b, v.g); }
inline glm::ivec4 _xxzz(const glm::ivec4& v) { return glm::ivec4(v.x, v.x, v.z, v.z); }
inline glm::ivec4 _rrbb(const glm::ivec4& v) { return glm::ivec4(v.r, v.r, v.b, v.b); }
inline glm::ivec4 _xxzw(const glm::ivec4& v) { return glm::ivec4(v.x, v.x, v.z, v.w); }
inline glm::ivec4 _rrba(const glm::ivec4& v) { return glm::ivec4(v.r, v.r, v.b, v.a); }
inline glm::ivec4 _xxwx(const glm::ivec4& v) { return glm::ivec4(v.x, v.x, v.w, v.x); }
inline glm::ivec4 _rrar(const glm::ivec4& v) { return glm::ivec4(v.r, v.r, v.a, v.r); }
inline glm::ivec4 _xxwy(const glm::ivec4& v) { return glm::ivec4(v.x, v.x, v.w, v.y); }
inline glm::ivec4 _rrag(const glm::ivec4& v) { return glm::ivec4(v.r, v.r, v.a, v.g); }
inline glm::ivec4 _xxwz(const glm::ivec4& v) { return glm::ivec4(v.x, v.x, v.w, v.z); }
inline glm::ivec4 _rrab(const glm::ivec4& v) { return glm::ivec4(v.r, v.r, v.a, v.b); }
inline glm::ivec4 _xxww(const glm::ivec4& v) { return glm::ivec4(v.x, v.x, v.w, v.w); }
inline glm::ivec4 _rraa(const glm::ivec4& v) { return glm::ivec4(v.r, v.r, v.a, v.a); }
inline glm::ivec4 _xyxx(const glm::ivec4& v) { return glm::ivec4(v.x, v.y, v.x, v.x); }
inline glm::ivec4 _rgrr(const glm::ivec4& v) { return glm::ivec4(v.r, v.g, v.r, v.r); }
inline glm::ivec4 _xyxy(const glm::ivec4& v) { return glm::ivec4(v.x, v.y, v.x, v.y); }
inline glm::ivec4 _rgrg(const glm::ivec4& v) { return glm::ivec4(v.r, v.g, v.r, v.g); }
inline glm::ivec4 _xyxz(const glm::ivec4& v) { return glm::ivec4(v.x, v.y, v.x, v.z); }
inline glm::ivec4 _rgrb(const glm::ivec4& v) { return glm::ivec4(v.r, v.g, v.r, v.b); }
inline glm::ivec4 _xyxw(const glm::ivec4& v) { return glm::ivec4(v.x, v.y, v.x, v.w); }
inline glm::ivec4 _rgra(const glm::ivec4& v) { return glm::ivec4(v.r, v.g, v.r, v.a); }
inline glm::ivec4 _xyyx(const glm::ivec4& v) { return glm::ivec4(v.x, v.y, v.y, v.x); }
inline glm::ivec4 _rggr(const glm::ivec4& v) { return glm::ivec4(v.r, v.g, v.g, v.r); }
inline glm::ivec4 _xyyy(const glm::ivec4& v) { return glm::ivec4(v.x, v.y, v.y, v.y); }
inline glm::ivec4 _rggg(const glm::ivec4& v) { return glm::ivec4(v.r, v.g, v.g, v.g); }
inline glm::ivec4 _xyyz(const glm::ivec4& v) { return glm::ivec4(v.x, v.y, v.y, v.z); }
inline glm::ivec4 _rggb(const glm::ivec4& v) { return glm::ivec4(v.r, v.g, v.g, v.b); }
inline glm::ivec4 _xyyw(const glm::ivec4& v) { return glm::ivec4(v.x, v.y, v.y, v.w); }
inline glm::ivec4 _rgga(const glm::ivec4& v) { return glm::ivec4(v.r, v.g, v.g, v.a); }
inline glm::ivec4 _xyzx(const glm::ivec4& v) { return glm::ivec4(v.x, v.y, v.z, v.x); }
inline glm::ivec4 _rgbr(const glm::ivec4& v) { return glm::ivec4(v.r, v.g, v.b, v.r); }
inline glm::ivec4 _xyzy(const glm::ivec4& v) { return glm::ivec4(v.x, v.y, v.z, v.y); }
inline glm::ivec4 _rgbg(const glm::ivec4& v) { return glm::ivec4(v.r, v.g, v.b, v.g); }
inline glm::ivec4 _xyzz(const glm::ivec4& v) { return glm::ivec4(v.x, v.y, v.z, v.z); }
inline glm::ivec4 _rgbb(const glm::ivec4& v) { return glm::ivec4(v.r, v.g, v.b, v.b); }
inline glm::ivec4 _xyzw(const glm::ivec4& v) { return glm::ivec4(v.x, v.y, v.z, v.w); }
inline glm::ivec4 _rgba(const glm::ivec4& v) { return glm::ivec4(v.r, v.g, v.b, v.a); }
inline glm::ivec4 _xywx(const glm::ivec4& v) { return glm::ivec4(v.x, v.y, v.w, v.x); }
inline glm::ivec4 _rgar(const glm::ivec4& v) { return glm::ivec4(v.r, v.g, v.a, v.r); }
inline glm::ivec4 _xywy(const glm::ivec4& v) { return glm::ivec4(v.x, v.y, v.w, v.y); }
inline glm::ivec4 _rgag(const glm::ivec4& v) { return glm::ivec4(v.r, v.g, v.a, v.g); }
inline glm::ivec4 _xywz(const glm::ivec4& v) { return glm::ivec4(v.x, v.y, v.w, v.z); }
inline glm::ivec4 _rgab(const glm::ivec4& v) { return glm::ivec4(v.r, v.g, v.a, v.b); }
inline glm::ivec4 _xyww(const glm::ivec4& v) { return glm::ivec4(v.x, v.y, v.w, v.w); }
inline glm::ivec4 _rgaa(const glm::ivec4& v) { return glm::ivec4(v.r, v.g, v.a, v.a); }
inline glm::ivec4 _xzxx(const glm::ivec4& v) { return glm::ivec4(v.x, v.z, v.x, v.x); }
inline glm::ivec4 _rbrr(const glm::ivec4& v) { return glm::ivec4(v.r, v.b, v.r, v.r); }
inline glm::ivec4 _xzxy(const glm::ivec4& v) { return glm::ivec4(v.x, v.z, v.x, v.y); }
inline glm::ivec4 _rbrg(const glm::ivec4& v) { return glm::ivec4(v.r, v.b, v.r, v.g); }
inline glm::ivec4 _xzxz(const glm::ivec4& v) { return glm::ivec4(v.x, v.z, v.x, v.z); }
inline glm::ivec4 _rbrb(const glm::ivec4& v) { return glm::ivec4(v.r, v.b, v.r, v.b); }
inline glm::ivec4 _xzxw(const glm::ivec4& v) { return glm::ivec4(v.x, v.z, v.x, v.w); }
inline glm::ivec4 _rbra(const glm::ivec4& v) { return glm::ivec4(v.r, v.b, v.r, v.a); }
inline glm::ivec4 _xzyx(const glm::ivec4& v) { return glm::ivec4(v.x, v.z, v.y, v.x); }
inline glm::ivec4 _rbgr(const glm::ivec4& v) { return glm::ivec4(v.r, v.b, v.g, v.r); }
inline glm::ivec4 _xzyy(const glm::ivec4& v) { return glm::ivec4(v.x, v.z, v.y, v.y); }
inline glm::ivec4 _rbgg(const glm::ivec4& v) { return glm::ivec4(v.r, v.b, v.g, v.g); }
inline glm::ivec4 _xzyz(const glm::ivec4& v) { return glm::ivec4(v.x, v.z, v.y, v.z); }
inline glm::ivec4 _rbgb(const glm::ivec4& v) { return glm::ivec4(v.r, v.b, v.g, v.b); }
inline glm::ivec4 _xzyw(const glm::ivec4& v) { return glm::ivec4(v.x, v.z, v.y, v.w); }
inline glm::ivec4 _rbga(const glm::ivec4& v) { return glm::ivec4(v.r, v.b, v.g, v.a); }
inline glm::ivec4 _xzzx(const glm::ivec4& v) { return glm::ivec4(v.x, v.z, v.z, v.x); }
inline glm::ivec4 _rbbr(const glm::ivec4& v) { return glm::ivec4(v.r, v.b, v.b, v.r); }
inline glm::ivec4 _xzzy(const glm::ivec4& v) { return glm::ivec4(v.x, v.z, v.z, v.y); }
inline glm::ivec4 _rbbg(const glm::ivec4& v) { return glm::ivec4(v.r, v.b, v.b, v.g); }
inline glm::ivec4 _xzzz(const glm::ivec4& v) { return glm::ivec4(v.x, v.z, v.z, v.z); }
inline glm::ivec4 _rbbb(const glm::ivec4& v) { return glm::ivec4(v.r, v.b, v.b, v.b); }
inline glm::ivec4 _xzzw(const glm::ivec4& v) { return glm::ivec4(v.x, v.z, v.z, v.w); }
inline glm::ivec4 _rbba(const glm::ivec4& v) { return glm::ivec4(v.r, v.b, v.b, v.a); }
inline glm::ivec4 _xzwx(const glm::ivec4& v) { return glm::ivec4(v.x, v.z, v.w, v.x); }
inline glm::ivec4 _rbar(const glm::ivec4& v) { return glm::ivec4(v.r, v.b, v.a, v.r); }
inline glm::ivec4 _xzwy(const glm::ivec4& v) { return glm::ivec4(v.x, v.z, v.w, v.y); }
inline glm::ivec4 _rbag(const glm::ivec4& v) { return glm::ivec4(v.r, v.b, v.a, v.g); }
inline glm::ivec4 _xzwz(const glm::ivec4& v) { return glm::ivec4(v.x, v.z, v.w, v.z); }
inline glm::ivec4 _rbab(const glm::ivec4& v) { return glm::ivec4(v.r, v.b, v.a, v.b); }
inline glm::ivec4 _xzww(const glm::ivec4& v) { return glm::ivec4(v.x, v.z, v.w, v.w); }
inline glm::ivec4 _rbaa(const glm::ivec4& v) { return glm::ivec4(v.r, v.b, v.a, v.a); }
inline glm::ivec4 _xwxx(const glm::ivec4& v) { return glm::ivec4(v.x, v.w, v.x, v.x); }
inline glm::ivec4 _rarr(const glm::ivec4& v) { return glm::ivec4(v.r, v.a, v.r, v.r); }
inline glm::ivec4 _xwxy(const glm::ivec4& v) { return glm::ivec4(v.x, v.w, v.x, v.y); }
inline glm::ivec4 _rarg(const glm::ivec4& v) { return glm::ivec4(v.r, v.a, v.r, v.g); }
inline glm::ivec4 _xwxz(const glm::ivec4& v) { return glm::ivec4(v.x, v.w, v.x, v.z); }
inline glm::ivec4 _rarb(const glm::ivec4& v) { return glm::ivec4(v.r, v.a, v.r, v.b); }
inline glm::ivec4 _xwxw(const glm::ivec4& v) { return glm::ivec4(v.x, v.w, v.x, v.w); }
inline glm::ivec4 _rara(const glm::ivec4& v) { return glm::ivec4(v.r, v.a, v.r, v.a); }
inline glm::ivec4 _xwyx(const glm::ivec4& v) { return glm::ivec4(v.x, v.w, v.y, v.x); }
inline glm::ivec4 _ragr(const glm::ivec4& v) { return glm::ivec4(v.r, v.a, v.g, v.r); }
inline glm::ivec4 _xwyy(const glm::ivec4& v) { return glm::ivec4(v.x, v.w, v.y, v.y); }
inline glm::ivec4 _ragg(const glm::ivec4& v) { return glm::ivec4(v.r, v.a, v.g, v.g); }
inline glm::ivec4 _xwyz(const glm::ivec4& v) { return glm::ivec4(v.x, v.w, v.y, v.z); }
inline glm::ivec4 _ragb(const glm::ivec4& v) { return glm::ivec4(v.r, v.a, v.g, v.b); }
inline glm::ivec4 _xwyw(const glm::ivec4& v) { return glm::ivec4(v.x, v.w, v.y, v.w); }
inline glm::ivec4 _raga(const glm::ivec4& v) { return glm::ivec4(v.r, v.a, v.g, v.a); }
inline glm::ivec4 _xwzx(const glm::ivec4& v) { return glm::ivec4(v.x, v.w, v.z, v.x); }
inline glm::ivec4 _rabr(const glm::ivec4& v) { return glm::ivec4(v.r, v.a, v.b, v.r); }
inline glm::ivec4 _xwzy(const glm::ivec4& v) { return glm::ivec4(v.x, v.w, v.z, v.y); }
inline glm::ivec4 _rabg(const glm::ivec4& v) { return glm::ivec4(v.r, v.a, v.b, v.g); }
inline glm::ivec4 _xwzz(const glm::ivec4& v) { return glm::ivec4(v.x, v.w, v.z, v.z); }
inline glm::ivec4 _rabb(const glm::ivec4& v) { return glm::ivec4(v.r, v.a, v.b, v.b); }
inline glm::ivec4 _xwzw(const glm::ivec4& v) { return glm::ivec4(v.x, v.w, v.z, v.w); }
inline glm::ivec4 _raba(const glm::ivec4& v) { return glm::ivec4(v.r, v.a, v.b, v.a); }
inline glm::ivec4 _xwwx(const glm::ivec4& v) { return glm::ivec4(v.x, v.w, v.w, v.x); }
inline glm::ivec4 _raar(const glm::ivec4& v) { return glm::ivec4(v.r, v.a, v.a, v.r); }
inline glm::ivec4 _xwwy(const glm::ivec4& v) { return glm::ivec4(v.x, v.w, v.w, v.y); }
inline glm::ivec4 _raag(const glm::ivec4& v) { return glm::ivec4(v.r, v.a, v.a, v.g); }
inline glm::ivec4 _xwwz(const glm::ivec4& v) { return glm::ivec4(v.x, v.w, v.w, v.z); }
inline glm::ivec4 _raab(const glm::ivec4& v) { return glm::ivec4(v.r, v.a, v.a, v.b); }
inline glm::ivec4 _xwww(const glm::ivec4& v) { return glm::ivec4(v.x, v.w, v.w, v.w); }
inline glm::ivec4 _raaa(const glm::ivec4& v) { return glm::ivec4(v.r, v.a, v.a, v.a); }
inline glm::ivec4 _yxxx(const glm::ivec4& v) { return glm::ivec4(v.y, v.x, v.x, v.x); }
inline glm::ivec4 _grrr(const glm::ivec4& v) { return glm::ivec4(v.g, v.r, v.r, v.r); }
inline glm::ivec4 _yxxy(const glm::ivec4& v) { return glm::ivec4(v.y, v.x, v.x, v.y); }
inline glm::ivec4 _grrg(const glm::ivec4& v) { return glm::ivec4(v.g, v.r, v.r, v.g); }
inline glm::ivec4 _yxxz(const glm::ivec4& v) { return glm::ivec4(v.y, v.x, v.x, v.z); }
inline glm::ivec4 _grrb(const glm::ivec4& v) { return glm::ivec4(v.g, v.r, v.r, v.b); }
inline glm::ivec4 _yxxw(const glm::ivec4& v) { return glm::ivec4(v.y, v.x, v.x, v.w); }
inline glm::ivec4 _grra(const glm::ivec4& v) { return glm::ivec4(v.g, v.r, v.r, v.a); }
inline glm::ivec4 _yxyx(const glm::ivec4& v) { return glm::ivec4(v.y, v.x, v.y, v.x); }
inline glm::ivec4 _grgr(const glm::ivec4& v) { return glm::ivec4(v.g, v.r, v.g, v.r); }
inline glm::ivec4 _yxyy(const glm::ivec4& v) { return glm::ivec4(v.y, v.x, v.y, v.y); }
inline glm::ivec4 _grgg(const glm::ivec4& v) { return glm::ivec4(v.g, v.r, v.g, v.g); }
inline glm::ivec4 _yxyz(const glm::ivec4& v) { return glm::ivec4(v.y, v.x, v.y, v.z); }
inline glm::ivec4 _grgb(const glm::ivec4& v) { return glm::ivec4(v.g, v.r, v.g, v.b); }
inline glm::ivec4 _yxyw(const glm::ivec4& v) { return glm::ivec4(v.y, v.x, v.y, v.w); }
inline glm::ivec4 _grga(const glm::ivec4& v) { return glm::ivec4(v.g, v.r, v.g, v.a); }
inline glm::ivec4 _yxzx(const glm::ivec4& v) { return glm::ivec4(v.y, v.x, v.z, v.x); }
inline glm::ivec4 _grbr(const glm::ivec4& v) { return glm::ivec4(v.g, v.r, v.b, v.r); }
inline glm::ivec4 _yxzy(const glm::ivec4& v) { return glm::ivec4(v.y, v.x, v.z, v.y); }
inline glm::ivec4 _grbg(const glm::ivec4& v) { return glm::ivec4(v.g, v.r, v.b, v.g); }
inline glm::ivec4 _yxzz(const glm::ivec4& v) { return glm::ivec4(v.y, v.x, v.z, v.z); }
inline glm::ivec4 _grbb(const glm::ivec4& v) { return glm::ivec4(v.g, v.r, v.b, v.b); }
inline glm::ivec4 _yxzw(const glm::ivec4& v) { return glm::ivec4(v.y, v.x, v.z, v.w); }
inline glm::ivec4 _grba(const glm::ivec4& v) { return glm::ivec4(v.g, v.r, v.b, v.a); }
inline glm::ivec4 _yxwx(const glm::ivec4& v) { return glm::ivec4(v.y, v.x, v.w, v.x); }
inline glm::ivec4 _grar(const glm::ivec4& v) { return glm::ivec4(v.g, v.r, v.a, v.r); }
inline glm::ivec4 _yxwy(const glm::ivec4& v) { return glm::ivec4(v.y, v.x, v.w, v.y); }
inline glm::ivec4 _grag(const glm::ivec4& v) { return glm::ivec4(v.g, v.r, v.a, v.g); }
inline glm::ivec4 _yxwz(const glm::ivec4& v) { return glm::ivec4(v.y, v.x, v.w, v.z); }
inline glm::ivec4 _grab(const glm::ivec4& v) { return glm::ivec4(v.g, v.r, v.a, v.b); }
inline glm::ivec4 _yxww(const glm::ivec4& v) { return glm::ivec4(v.y, v.x, v.w, v.w); }
inline glm::ivec4 _graa(const glm::ivec4& v) { return glm::ivec4(v.g, v.r, v.a, v.a); }
inline glm::ivec4 _yyxx(const glm::ivec4& v) { return glm::ivec4(v.y, v.y, v.x, v.x); }
inline glm::ivec4 _ggrr(const glm::ivec4& v) { return glm::ivec4(v.g, v.g, v.r, v.r); }
inline glm::ivec4 _yyxy(const glm::ivec4& v) { return glm::ivec4(v.y, v.y, v.x, v.y); }
inline glm::ivec4 _ggrg(const glm::ivec4& v) { return glm::ivec4(v.g, v.g, v.r, v.g); }
inline glm::ivec4 _yyxz(const glm::ivec4& v) { return glm::ivec4(v.y, v.y, v.x, v.z); }
inline glm::ivec4 _ggrb(const glm::ivec4& v) { return glm::ivec4(v.g, v.g, v.r, v.b); }
inline glm::ivec4 _yyxw(const glm::ivec4& v) { return glm::ivec4(v.y, v.y, v.x, v.w); }
inline glm::ivec4 _ggra(const glm::ivec4& v) { return glm::ivec4(v.g, v.g, v.r, v.a); }
inline glm::ivec4 _yyyx(const glm::ivec4& v) { return glm::ivec4(v.y, v.y, v.y, v.x); }
inline glm::ivec4 _gggr(const glm::ivec4& v) { return glm::ivec4(v.g, v.g, v.g, v.r); }
inline glm::ivec4 _yyyy(const glm::ivec4& v) { return glm::ivec4(v.y, v.y, v.y, v.y); }
inline glm::ivec4 _gggg(const glm::ivec4& v) { return glm::ivec4(v.g, v.g, v.g, v.g); }
inline glm::ivec4 _yyyz(const glm::ivec4& v) { return glm::ivec4(v.y, v.y, v.y, v.z); }
inline glm::ivec4 _gggb(const glm::ivec4& v) { return glm::ivec4(v.g, v.g, v.g, v.b); }
inline glm::ivec4 _yyyw(const glm::ivec4& v) { return glm::ivec4(v.y, v.y, v.y, v.w); }
inline glm::ivec4 _ggga(const glm::ivec4& v) { return glm::ivec4(v.g, v.g, v.g, v.a); }
inline glm::ivec4 _yyzx(const glm::ivec4& v) { return glm::ivec4(v.y, v.y, v.z, v.x); }
inline glm::ivec4 _ggbr(const glm::ivec4& v) { return glm::ivec4(v.g, v.g, v.b, v.r); }
inline glm::ivec4 _yyzy(const glm::ivec4& v) { return glm::ivec4(v.y, v.y, v.z, v.y); }
inline glm::ivec4 _ggbg(const glm::ivec4& v) { return glm::ivec4(v.g, v.g, v.b, v.g); }
inline glm::ivec4 _yyzz(const glm::ivec4& v) { return glm::ivec4(v.y, v.y, v.z, v.z); }
inline glm::ivec4 _ggbb(const glm::ivec4& v) { return glm::ivec4(v.g, v.g, v.b, v.b); }
inline glm::ivec4 _yyzw(const glm::ivec4& v) { return glm::ivec4(v.y, v.y, v.z, v.w); }
inline glm::ivec4 _ggba(const glm::ivec4& v) { return glm::ivec4(v.g, v.g, v.b, v.a); }
inline glm::ivec4 _yywx(const glm::ivec4& v) { return glm::ivec4(v.y, v.y, v.w, v.x); }
inline glm::ivec4 _ggar(const glm::ivec4& v) { return glm::ivec4(v.g, v.g, v.a, v.r); }
inline glm::ivec4 _yywy(const glm::ivec4& v) { return glm::ivec4(v.y, v.y, v.w, v.y); }
inline glm::ivec4 _ggag(const glm::ivec4& v) { return glm::ivec4(v.g, v.g, v.a, v.g); }
inline glm::ivec4 _yywz(const glm::ivec4& v) { return glm::ivec4(v.y, v.y, v.w, v.z); }
inline glm::ivec4 _ggab(const glm::ivec4& v) { return glm::ivec4(v.g, v.g, v.a, v.b); }
inline glm::ivec4 _yyww(const glm::ivec4& v) { return glm::ivec4(v.y, v.y, v.w, v.w); }
inline glm::ivec4 _ggaa(const glm::ivec4& v) { return glm::ivec4(v.g, v.g, v.a, v.a); }
inline glm::ivec4 _yzxx(const glm::ivec4& v) { return glm::ivec4(v.y, v.z, v.x, v.x); }
inline glm::ivec4 _gbrr(const glm::ivec4& v) { return glm::ivec4(v.g, v.b, v.r, v.r); }
inline glm::ivec4 _yzxy(const glm::ivec4& v) { return glm::ivec4(v.y, v.z, v.x, v.y); }
inline glm::ivec4 _gbrg(const glm::ivec4& v) { return glm::ivec4(v.g, v.b, v.r, v.g); }
inline glm::ivec4 _yzxz(const glm::ivec4& v) { return glm::ivec4(v.y, v.z, v.x, v.z); }
inline glm::ivec4 _gbrb(const glm::ivec4& v) { return glm::ivec4(v.g, v.b, v.r, v.b); }
inline glm::ivec4 _yzxw(const glm::ivec4& v) { return glm::ivec4(v.y, v.z, v.x, v.w); }
inline glm::ivec4 _gbra(const glm::ivec4& v) { return glm::ivec4(v.g, v.b, v.r, v.a); }
inline glm::ivec4 _yzyx(const glm::ivec4& v) { return glm::ivec4(v.y, v.z, v.y, v.x); }
inline glm::ivec4 _gbgr(const glm::ivec4& v) { return glm::ivec4(v.g, v.b, v.g, v.r); }
inline glm::ivec4 _yzyy(const glm::ivec4& v) { return glm::ivec4(v.y, v.z, v.y, v.y); }
inline glm::ivec4 _gbgg(const glm::ivec4& v) { return glm::ivec4(v.g, v.b, v.g, v.g); }
inline glm::ivec4 _yzyz(const glm::ivec4& v) { return glm::ivec4(v.y, v.z, v.y, v.z); }
inline glm::ivec4 _gbgb(const glm::ivec4& v) { return glm::ivec4(v.g, v.b, v.g, v.b); }
inline glm::ivec4 _yzyw(const glm::ivec4& v) { return glm::ivec4(v.y, v.z, v.y, v.w); }
inline glm::ivec4 _gbga(const glm::ivec4& v) { return glm::ivec4(v.g, v.b, v.g, v.a); }
inline glm::ivec4 _yzzx(const glm::ivec4& v) { return glm::ivec4(v.y, v.z, v.z, v.x); }
inline glm::ivec4 _gbbr(const glm::ivec4& v) { return glm::ivec4(v.g, v.b, v.b, v.r); }
inline glm::ivec4 _yzzy(const glm::ivec4& v) { return glm::ivec4(v.y, v.z, v.z, v.y); }
inline glm::ivec4 _gbbg(const glm::ivec4& v) { return glm::ivec4(v.g, v.b, v.b, v.g); }
inline glm::ivec4 _yzzz(const glm::ivec4& v) { return glm::ivec4(v.y, v.z, v.z, v.z); }
inline glm::ivec4 _gbbb(const glm::ivec4& v) { return glm::ivec4(v.g, v.b, v.b, v.b); }
inline glm::ivec4 _yzzw(const glm::ivec4& v) { return glm::ivec4(v.y, v.z, v.z, v.w); }
inline glm::ivec4 _gbba(const glm::ivec4& v) { return glm::ivec4(v.g, v.b, v.b, v.a); }
inline glm::ivec4 _yzwx(const glm::ivec4& v) { return glm::ivec4(v.y, v.z, v.w, v.x); }
inline glm::ivec4 _gbar(const glm::ivec4& v) { return glm::ivec4(v.g, v.b, v.a, v.r); }
inline glm::ivec4 _yzwy(const glm::ivec4& v) { return glm::ivec4(v.y, v.z, v.w, v.y); }
inline glm::ivec4 _gbag(const glm::ivec4& v) { return glm::ivec4(v.g, v.b, v.a, v.g); }
inline glm::ivec4 _yzwz(const glm::ivec4& v) { return glm::ivec4(v.y, v.z, v.w, v.z); }
inline glm::ivec4 _gbab(const glm::ivec4& v) { return glm::ivec4(v.g, v.b, v.a, v.b); }
inline glm::ivec4 _yzww(const glm::ivec4& v) { return glm::ivec4(v.y, v.z, v.w, v.w); }
inline glm::ivec4 _gbaa(const glm::ivec4& v) { return glm::ivec4(v.g, v.b, v.a, v.a); }
inline glm::ivec4 _ywxx(const glm::ivec4& v) { return glm::ivec4(v.y, v.w, v.x, v.x); }
inline glm::ivec4 _garr(const glm::ivec4& v) { return glm::ivec4(v.g, v.a, v.r, v.r); }
inline glm::ivec4 _ywxy(const glm::ivec4& v) { return glm::ivec4(v.y, v.w, v.x, v.y); }
inline glm::ivec4 _garg(const glm::ivec4& v) { return glm::ivec4(v.g, v.a, v.r, v.g); }
inline glm::ivec4 _ywxz(const glm::ivec4& v) { return glm::ivec4(v.y, v.w, v.x, v.z); }
inline glm::ivec4 _garb(const glm::ivec4& v) { return glm::ivec4(v.g, v.a, v.r, v.b); }
inline glm::ivec4 _ywxw(const glm::ivec4& v) { return glm::ivec4(v.y, v.w, v.x, v.w); }
inline glm::ivec4 _gara(const glm::ivec4& v) { return glm::ivec4(v.g, v.a, v.r, v.a); }
inline glm::ivec4 _ywyx(const glm::ivec4& v) { return glm::ivec4(v.y, v.w, v.y, v.x); }
inline glm::ivec4 _gagr(const glm::ivec4& v) { return glm::ivec4(v.g, v.a, v.g, v.r); }
inline glm::ivec4 _ywyy(const glm::ivec4& v) { return glm::ivec4(v.y, v.w, v.y, v.y); }
inline glm::ivec4 _gagg(const glm::ivec4& v) { return glm::ivec4(v.g, v.a, v.g, v.g); }
inline glm::ivec4 _ywyz(const glm::ivec4& v) { return glm::ivec4(v.y, v.w, v.y, v.z); }
inline glm::ivec4 _gagb(const glm::ivec4& v) { return glm::ivec4(v.g, v.a, v.g, v.b); }
inline glm::ivec4 _ywyw(const glm::ivec4& v) { return glm::ivec4(v.y, v.w, v.y, v.w); }
inline glm::ivec4 _gaga(const glm::ivec4& v) { return glm::ivec4(v.g, v.a, v.g, v.a); }
inline glm::ivec4 _ywzx(const glm::ivec4& v) { return glm::ivec4(v.y, v.w, v.z, v.x); }
inline glm::ivec4 _gabr(const glm::ivec4& v) { return glm::ivec4(v.g, v.a, v.b, v.r); }
inline glm::ivec4 _ywzy(const glm::ivec4& v) { return glm::ivec4(v.y, v.w, v.z, v.y); }
inline glm::ivec4 _gabg(const glm::ivec4& v) { return glm::ivec4(v.g, v.a, v.b, v.g); }
inline glm::ivec4 _ywzz(const glm::ivec4& v) { return glm::ivec4(v.y, v.w, v.z, v.z); }
inline glm::ivec4 _gabb(const glm::ivec4& v) { return glm::ivec4(v.g, v.a, v.b, v.b); }
inline glm::ivec4 _ywzw(const glm::ivec4& v) { return glm::ivec4(v.y, v.w, v.z, v.w); }
inline glm::ivec4 _gaba(const glm::ivec4& v) { return glm::ivec4(v.g, v.a, v.b, v.a); }
inline glm::ivec4 _ywwx(const glm::ivec4& v) { return glm::ivec4(v.y, v.w, v.w, v.x); }
inline glm::ivec4 _gaar(const glm::ivec4& v) { return glm::ivec4(v.g, v.a, v.a, v.r); }
inline glm::ivec4 _ywwy(const glm::ivec4& v) { return glm::ivec4(v.y, v.w, v.w, v.y); }
inline glm::ivec4 _gaag(const glm::ivec4& v) { return glm::ivec4(v.g, v.a, v.a, v.g); }
inline glm::ivec4 _ywwz(const glm::ivec4& v) { return glm::ivec4(v.y, v.w, v.w, v.z); }
inline glm::ivec4 _gaab(const glm::ivec4& v) { return glm::ivec4(v.g, v.a, v.a, v.b); }
inline glm::ivec4 _ywww(const glm::ivec4& v) { return glm::ivec4(v.y, v.w, v.w, v.w); }
inline glm::ivec4 _gaaa(const glm::ivec4& v) { return glm::ivec4(v.g, v.a, v.a, v.a); }
inline glm::ivec4 _zxxx(const glm::ivec4& v) { return glm::ivec4(v.z, v.x, v.x, v.x); }
inline glm::ivec4 _brrr(const glm::ivec4& v) { return glm::ivec4(v.b, v.r, v.r, v.r); }
inline glm::ivec4 _zxxy(const glm::ivec4& v) { return glm::ivec4(v.z, v.x, v.x, v.y); }
inline glm::ivec4 _brrg(const glm::ivec4& v) { return glm::ivec4(v.b, v.r, v.r, v.g); }
inline glm::ivec4 _zxxz(const glm::ivec4& v) { return glm::ivec4(v.z, v.x, v.x, v.z); }
inline glm::ivec4 _brrb(const glm::ivec4& v) { return glm::ivec4(v.b, v.r, v.r, v.b); }
inline glm::ivec4 _zxxw(const glm::ivec4& v) { return glm::ivec4(v.z, v.x, v.x, v.w); }
inline glm::ivec4 _brra(const glm::ivec4& v) { return glm::ivec4(v.b, v.r, v.r, v.a); }
inline glm::ivec4 _zxyx(const glm::ivec4& v) { return glm::ivec4(v.z, v.x, v.y, v.x); }
inline glm::ivec4 _brgr(const glm::ivec4& v) { return glm::ivec4(v.b, v.r, v.g, v.r); }
inline glm::ivec4 _zxyy(const glm::ivec4& v) { return glm::ivec4(v.z, v.x, v.y, v.y); }
inline glm::ivec4 _brgg(const glm::ivec4& v) { return glm::ivec4(v.b, v.r, v.g, v.g); }
inline glm::ivec4 _zxyz(const glm::ivec4& v) { return glm::ivec4(v.z, v.x, v.y, v.z); }
inline glm::ivec4 _brgb(const glm::ivec4& v) { return glm::ivec4(v.b, v.r, v.g, v.b); }
inline glm::ivec4 _zxyw(const glm::ivec4& v) { return glm::ivec4(v.z, v.x, v.y, v.w); }
inline glm::ivec4 _brga(const glm::ivec4& v) { return glm::ivec4(v.b, v.r, v.g, v.a); }
inline glm::ivec4 _zxzx(const glm::ivec4& v) { return glm::ivec4(v.z, v.x, v.z, v.x); }
inline glm::ivec4 _brbr(const glm::ivec4& v) { return glm::ivec4(v.b, v.r, v.b, v.r); }
inline glm::ivec4 _zxzy(const glm::ivec4& v) { return glm::ivec4(v.z, v.x, v.z, v.y); }
inline glm::ivec4 _brbg(const glm::ivec4& v) { return glm::ivec4(v.b, v.r, v.b, v.g); }
inline glm::ivec4 _zxzz(const glm::ivec4& v) { return glm::ivec4(v.z, v.x, v.z, v.z); }
inline glm::ivec4 _brbb(const glm::ivec4& v) { return glm::ivec4(v.b, v.r, v.b, v.b); }
inline glm::ivec4 _zxzw(const glm::ivec4& v) { return glm::ivec4(v.z, v.x, v.z, v.w); }
inline glm::ivec4 _brba(const glm::ivec4& v) { return glm::ivec4(v.b, v.r, v.b, v.a); }
inline glm::ivec4 _zxwx(const glm::ivec4& v) { return glm::ivec4(v.z, v.x, v.w, v.x); }
inline glm::ivec4 _brar(const glm::ivec4& v) { return glm::ivec4(v.b, v.r, v.a, v.r); }
inline glm::ivec4 _zxwy(const glm::ivec4& v) { return glm::ivec4(v.z, v.x, v.w, v.y); }
inline glm::ivec4 _brag(const glm::ivec4& v) { return glm::ivec4(v.b, v.r, v.a, v.g); }
inline glm::ivec4 _zxwz(const glm::ivec4& v) { return glm::ivec4(v.z, v.x, v.w, v.z); }
inline glm::ivec4 _brab(const glm::ivec4& v) { return glm::ivec4(v.b, v.r, v.a, v.b); }
inline glm::ivec4 _zxww(const glm::ivec4& v) { return glm::ivec4(v.z, v.x, v.w, v.w); }
inline glm::ivec4 _braa(const glm::ivec4& v) { return glm::ivec4(v.b, v.r, v.a, v.a); }
inline glm::ivec4 _zyxx(const glm::ivec4& v) { return glm::ivec4(v.z, v.y, v.x, v.x); }
inline glm::ivec4 _bgrr(const glm::ivec4& v) { return glm::ivec4(v.b, v.g, v.r, v.r); }
inline glm::ivec4 _zyxy(const glm::ivec4& v) { return glm::ivec4(v.z, v.y, v.x, v.y); }
inline glm::ivec4 _bgrg(const glm::ivec4& v) { return glm::ivec4(v.b, v.g, v.r, v.g); }
inline glm::ivec4 _zyxz(const glm::ivec4& v) { return glm::ivec4(v.z, v.y, v.x, v.z); }
inline glm::ivec4 _bgrb(const glm::ivec4& v) { return glm::ivec4(v.b, v.g, v.r, v.b); }
inline glm::ivec4 _zyxw(const glm::ivec4& v) { return glm::ivec4(v.z, v.y, v.x, v.w); }
inline glm::ivec4 _bgra(const glm::ivec4& v) { return glm::ivec4(v.b, v.g, v.r, v.a); }
inline glm::ivec4 _zyyx(const glm::ivec4& v) { return glm::ivec4(v.z, v.y, v.y, v.x); }
inline glm::ivec4 _bggr(const glm::ivec4& v) { return glm::ivec4(v.b, v.g, v.g, v.r); }
inline glm::ivec4 _zyyy(const glm::ivec4& v) { return glm::ivec4(v.z, v.y, v.y, v.y); }
inline glm::ivec4 _bggg(const glm::ivec4& v) { return glm::ivec4(v.b, v.g, v.g, v.g); }
inline glm::ivec4 _zyyz(const glm::ivec4& v) { return glm::ivec4(v.z, v.y, v.y, v.z); }
inline glm::ivec4 _bggb(const glm::ivec4& v) { return glm::ivec4(v.b, v.g, v.g, v.b); }
inline glm::ivec4 _zyyw(const glm::ivec4& v) { return glm::ivec4(v.z, v.y, v.y, v.w); }
inline glm::ivec4 _bgga(const glm::ivec4& v) { return glm::ivec4(v.b, v.g, v.g, v.a); }
inline glm::ivec4 _zyzx(const glm::ivec4& v) { return glm::ivec4(v.z, v.y, v.z, v.x); }
inline glm::ivec4 _bgbr(const glm::ivec4& v) { return glm::ivec4(v.b, v.g, v.b, v.r); }
inline glm::ivec4 _zyzy(const glm::ivec4& v) { return glm::ivec4(v.z, v.y, v.z, v.y); }
inline glm::ivec4 _bgbg(const glm::ivec4& v) { return glm::ivec4(v.b, v.g, v.b, v.g); }
inline glm::ivec4 _zyzz(const glm::ivec4& v) { return glm::ivec4(v.z, v.y, v.z, v.z); }
inline glm::ivec4 _bgbb(const glm::ivec4& v) { return glm::ivec4(v.b, v.g, v.b, v.b); }
inline glm::ivec4 _zyzw(const glm::ivec4& v) { return glm::ivec4(v.z, v.y, v.z, v.w); }
inline glm::ivec4 _bgba(const glm::ivec4& v) { return glm::ivec4(v.b, v.g, v.b, v.a); }
inline glm::ivec4 _zywx(const glm::ivec4& v) { return glm::ivec4(v.z, v.y, v.w, v.x); }
inline glm::ivec4 _bgar(const glm::ivec4& v) { return glm::ivec4(v.b, v.g, v.a, v.r); }
inline glm::ivec4 _zywy(const glm::ivec4& v) { return glm::ivec4(v.z, v.y, v.w, v.y); }
inline glm::ivec4 _bgag(const glm::ivec4& v) { return glm::ivec4(v.b, v.g, v.a, v.g); }
inline glm::ivec4 _zywz(const glm::ivec4& v) { return glm::ivec4(v.z, v.y, v.w, v.z); }
inline glm::ivec4 _bgab(const glm::ivec4& v) { return glm::ivec4(v.b, v.g, v.a, v.b); }
inline glm::ivec4 _zyww(const glm::ivec4& v) { return glm::ivec4(v.z, v.y, v.w, v.w); }
inline glm::ivec4 _bgaa(const glm::ivec4& v) { return glm::ivec4(v.b, v.g, v.a, v.a); }
inline glm::ivec4 _zzxx(const glm::ivec4& v) { return glm::ivec4(v.z, v.z, v.x, v.x); }
inline glm::ivec4 _bbrr(const glm::ivec4& v) { return glm::ivec4(v.b, v.b, v.r, v.r); }
inline glm::ivec4 _zzxy(const glm::ivec4& v) { return glm::ivec4(v.z, v.z, v.x, v.y); }
inline glm::ivec4 _bbrg(const glm::ivec4& v) { return glm::ivec4(v.b, v.b, v.r, v.g); }
inline glm::ivec4 _zzxz(const glm::ivec4& v) { return glm::ivec4(v.z, v.z, v.x, v.z); }
inline glm::ivec4 _bbrb(const glm::ivec4& v) { return glm::ivec4(v.b, v.b, v.r, v.b); }
inline glm::ivec4 _zzxw(const glm::ivec4& v) { return glm::ivec4(v.z, v.z, v.x, v.w); }
inline glm::ivec4 _bbra(const glm::ivec4& v) { return glm::ivec4(v.b, v.b, v.r, v.a); }
inline glm::ivec4 _zzyx(const glm::ivec4& v) { return glm::ivec4(v.z, v.z, v.y, v.x); }
inline glm::ivec4 _bbgr(const glm::ivec4& v) { return glm::ivec4(v.b, v.b, v.g, v.r); }
inline glm::ivec4 _zzyy(const glm::ivec4& v) { return glm::ivec4(v.z, v.z, v.y, v.y); }
inline glm::ivec4 _bbgg(const glm::ivec4& v) { return glm::ivec4(v.b, v.b, v.g, v.g); }
inline glm::ivec4 _zzyz(const glm::ivec4& v) { return glm::ivec4(v.z, v.z, v.y, v.z); }
inline glm::ivec4 _bbgb(const glm::ivec4& v) { return glm::ivec4(v.b, v.b, v.g, v.b); }
inline glm::ivec4 _zzyw(const glm::ivec4& v) { return glm::ivec4(v.z, v.z, v.y, v.w); }
inline glm::ivec4 _bbga(const glm::ivec4& v) { return glm::ivec4(v.b, v.b, v.g, v.a); }
inline glm::ivec4 _zzzx(const glm::ivec4& v) { return glm::ivec4(v.z, v.z, v.z, v.x); }
inline glm::ivec4 _bbbr(const glm::ivec4& v) { return glm::ivec4(v.b, v.b, v.b, v.r); }
inline glm::ivec4 _zzzy(const glm::ivec4& v) { return glm::ivec4(v.z, v.z, v.z, v.y); }
inline glm::ivec4 _bbbg(const glm::ivec4& v) { return glm::ivec4(v.b, v.b, v.b, v.g); }
inline glm::ivec4 _zzzz(const glm::ivec4& v) { return glm::ivec4(v.z, v.z, v.z, v.z); }
inline glm::ivec4 _bbbb(const glm::ivec4& v) { return glm::ivec4(v.b, v.b, v.b, v.b); }
inline glm::ivec4 _zzzw(const glm::ivec4& v) { return glm::ivec4(v.z, v.z, v.z, v.w); }
inline glm::ivec4 _bbba(const glm::ivec4& v) { return glm::ivec4(v.b, v.b, v.b, v.a); }
inline glm::ivec4 _zzwx(const glm::ivec4& v) { return glm::ivec4(v.z, v.z, v.w, v.x); }
inline glm::ivec4 _bbar(const glm::ivec4& v) { return glm::ivec4(v.b, v.b, v.a, v.r); }
inline glm::ivec4 _zzwy(const glm::ivec4& v) { return glm::ivec4(v.z, v.z, v.w, v.y); }
inline glm::ivec4 _bbag(const glm::ivec4& v) { return glm::ivec4(v.b, v.b, v.a, v.g); }
inline glm::ivec4 _zzwz(const glm::ivec4& v) { return glm::ivec4(v.z, v.z, v.w, v.z); }
inline glm::ivec4 _bbab(const glm::ivec4& v) { return glm::ivec4(v.b, v.b, v.a, v.b); }
inline glm::ivec4 _zzww(const glm::ivec4& v) { return glm::ivec4(v.z, v.z, v.w, v.w); }
inline glm::ivec4 _bbaa(const glm::ivec4& v) { return glm::ivec4(v.b, v.b, v.a, v.a); }
inline glm::ivec4 _zwxx(const glm::ivec4& v) { return glm::ivec4(v.z, v.w, v.x, v.x); }
inline glm::ivec4 _barr(const glm::ivec4& v) { return glm::ivec4(v.b, v.a, v.r, v.r); }
inline glm::ivec4 _zwxy(const glm::ivec4& v) { return glm::ivec4(v.z, v.w, v.x, v.y); }
inline glm::ivec4 _barg(const glm::ivec4& v) { return glm::ivec4(v.b, v.a, v.r, v.g); }
inline glm::ivec4 _zwxz(const glm::ivec4& v) { return glm::ivec4(v.z, v.w, v.x, v.z); }
inline glm::ivec4 _barb(const glm::ivec4& v) { return glm::ivec4(v.b, v.a, v.r, v.b); }
inline glm::ivec4 _zwxw(const glm::ivec4& v) { return glm::ivec4(v.z, v.w, v.x, v.w); }
inline glm::ivec4 _bara(const glm::ivec4& v) { return glm::ivec4(v.b, v.a, v.r, v.a); }
inline glm::ivec4 _zwyx(const glm::ivec4& v) { return glm::ivec4(v.z, v.w, v.y, v.x); }
inline glm::ivec4 _bagr(const glm::ivec4& v) { return glm::ivec4(v.b, v.a, v.g, v.r); }
inline glm::ivec4 _zwyy(const glm::ivec4& v) { return glm::ivec4(v.z, v.w, v.y, v.y); }
inline glm::ivec4 _bagg(const glm::ivec4& v) { return glm::ivec4(v.b, v.a, v.g, v.g); }
inline glm::ivec4 _zwyz(const glm::ivec4& v) { return glm::ivec4(v.z, v.w, v.y, v.z); }
inline glm::ivec4 _bagb(const glm::ivec4& v) { return glm::ivec4(v.b, v.a, v.g, v.b); }
inline glm::ivec4 _zwyw(const glm::ivec4& v) { return glm::ivec4(v.z, v.w, v.y, v.w); }
inline glm::ivec4 _baga(const glm::ivec4& v) { return glm::ivec4(v.b, v.a, v.g, v.a); }
inline glm::ivec4 _zwzx(const glm::ivec4& v) { return glm::ivec4(v.z, v.w, v.z, v.x); }
inline glm::ivec4 _babr(const glm::ivec4& v) { return glm::ivec4(v.b, v.a, v.b, v.r); }
inline glm::ivec4 _zwzy(const glm::ivec4& v) { return glm::ivec4(v.z, v.w, v.z, v.y); }
inline glm::ivec4 _babg(const glm::ivec4& v) { return glm::ivec4(v.b, v.a, v.b, v.g); }
inline glm::ivec4 _zwzz(const glm::ivec4& v) { return glm::ivec4(v.z, v.w, v.z, v.z); }
inline glm::ivec4 _babb(const glm::ivec4& v) { return glm::ivec4(v.b, v.a, v.b, v.b); }
inline glm::ivec4 _zwzw(const glm::ivec4& v) { return glm::ivec4(v.z, v.w, v.z, v.w); }
inline glm::ivec4 _baba(const glm::ivec4& v) { return glm::ivec4(v.b, v.a, v.b, v.a); }
inline glm::ivec4 _zwwx(const glm::ivec4& v) { return glm::ivec4(v.z, v.w, v.w, v.x); }
inline glm::ivec4 _baar(const glm::ivec4& v) { return glm::ivec4(v.b, v.a, v.a, v.r); }
inline glm::ivec4 _zwwy(const glm::ivec4& v) { return glm::ivec4(v.z, v.w, v.w, v.y); }
inline glm::ivec4 _baag(const glm::ivec4& v) { return glm::ivec4(v.b, v.a, v.a, v.g); }
inline glm::ivec4 _zwwz(const glm::ivec4& v) { return glm::ivec4(v.z, v.w, v.w, v.z); }
inline glm::ivec4 _baab(const glm::ivec4& v) { return glm::ivec4(v.b, v.a, v.a, v.b); }
inline glm::ivec4 _zwww(const glm::ivec4& v) { return glm::ivec4(v.z, v.w, v.w, v.w); }
inline glm::ivec4 _baaa(const glm::ivec4& v) { return glm::ivec4(v.b, v.a, v.a, v.a); }
inline glm::ivec4 _wxxx(const glm::ivec4& v) { return glm::ivec4(v.w, v.x, v.x, v.x); }
inline glm::ivec4 _arrr(const glm::ivec4& v) { return glm::ivec4(v.a, v.r, v.r, v.r); }
inline glm::ivec4 _wxxy(const glm::ivec4& v) { return glm::ivec4(v.w, v.x, v.x, v.y); }
inline glm::ivec4 _arrg(const glm::ivec4& v) { return glm::ivec4(v.a, v.r, v.r, v.g); }
inline glm::ivec4 _wxxz(const glm::ivec4& v) { return glm::ivec4(v.w, v.x, v.x, v.z); }
inline glm::ivec4 _arrb(const glm::ivec4& v) { return glm::ivec4(v.a, v.r, v.r, v.b); }
inline glm::ivec4 _wxxw(const glm::ivec4& v) { return glm::ivec4(v.w, v.x, v.x, v.w); }
inline glm::ivec4 _arra(const glm::ivec4& v) { return glm::ivec4(v.a, v.r, v.r, v.a); }
inline glm::ivec4 _wxyx(const glm::ivec4& v) { return glm::ivec4(v.w, v.x, v.y, v.x); }
inline glm::ivec4 _argr(const glm::ivec4& v) { return glm::ivec4(v.a, v.r, v.g, v.r); }
inline glm::ivec4 _wxyy(const glm::ivec4& v) { return glm::ivec4(v.w, v.x, v.y, v.y); }
inline glm::ivec4 _argg(const glm::ivec4& v) { return glm::ivec4(v.a, v.r, v.g, v.g); }
inline glm::ivec4 _wxyz(const glm::ivec4& v) { return glm::ivec4(v.w, v.x, v.y, v.z); }
inline glm::ivec4 _argb(const glm::ivec4& v) { return glm::ivec4(v.a, v.r, v.g, v.b); }
inline glm::ivec4 _wxyw(const glm::ivec4& v) { return glm::ivec4(v.w, v.x, v.y, v.w); }
inline glm::ivec4 _arga(const glm::ivec4& v) { return glm::ivec4(v.a, v.r, v.g, v.a); }
inline glm::ivec4 _wxzx(const glm::ivec4& v) { return glm::ivec4(v.w, v.x, v.z, v.x); }
inline glm::ivec4 _arbr(const glm::ivec4& v) { return glm::ivec4(v.a, v.r, v.b, v.r); }
inline glm::ivec4 _wxzy(const glm::ivec4& v) { return glm::ivec4(v.w, v.x, v.z, v.y); }
inline glm::ivec4 _arbg(const glm::ivec4& v) { return glm::ivec4(v.a, v.r, v.b, v.g); }
inline glm::ivec4 _wxzz(const glm::ivec4& v) { return glm::ivec4(v.w, v.x, v.z, v.z); }
inline glm::ivec4 _arbb(const glm::ivec4& v) { return glm::ivec4(v.a, v.r, v.b, v.b); }
inline glm::ivec4 _wxzw(const glm::ivec4& v) { return glm::ivec4(v.w, v.x, v.z, v.w); }
inline glm::ivec4 _arba(const glm::ivec4& v) { return glm::ivec4(v.a, v.r, v.b, v.a); }
inline glm::ivec4 _wxwx(const glm::ivec4& v) { return glm::ivec4(v.w, v.x, v.w, v.x); }
inline glm::ivec4 _arar(const glm::ivec4& v) { return glm::ivec4(v.a, v.r, v.a, v.r); }
inline glm::ivec4 _wxwy(const glm::ivec4& v) { return glm::ivec4(v.w, v.x, v.w, v.y); }
inline glm::ivec4 _arag(const glm::ivec4& v) { return glm::ivec4(v.a, v.r, v.a, v.g); }
inline glm::ivec4 _wxwz(const glm::ivec4& v) { return glm::ivec4(v.w, v.x, v.w, v.z); }
inline glm::ivec4 _arab(const glm::ivec4& v) { return glm::ivec4(v.a, v.r, v.a, v.b); }
inline glm::ivec4 _wxww(const glm::ivec4& v) { return glm::ivec4(v.w, v.x, v.w, v.w); }
inline glm::ivec4 _araa(const glm::ivec4& v) { return glm::ivec4(v.a, v.r, v.a, v.a); }
inline glm::ivec4 _wyxx(const glm::ivec4& v) { return glm::ivec4(v.w, v.y, v.x, v.x); }
inline glm::ivec4 _agrr(const glm::ivec4& v) { return glm::ivec4(v.a, v.g, v.r, v.r); }
inline glm::ivec4 _wyxy(const glm::ivec4& v) { return glm::ivec4(v.w, v.y, v.x, v.y); }
inline glm::ivec4 _agrg(const glm::ivec4& v) { return glm::ivec4(v.a, v.g, v.r, v.g); }
inline glm::ivec4 _wyxz(const glm::ivec4& v) { return glm::ivec4(v.w, v.y, v.x, v.z); }
inline glm::ivec4 _agrb(const glm::ivec4& v) { return glm::ivec4(v.a, v.g, v.r, v.b); }
inline glm::ivec4 _wyxw(const glm::ivec4& v) { return glm::ivec4(v.w, v.y, v.x, v.w); }
inline glm::ivec4 _agra(const glm::ivec4& v) { return glm::ivec4(v.a, v.g, v.r, v.a); }
inline glm::ivec4 _wyyx(const glm::ivec4& v) { return glm::ivec4(v.w, v.y, v.y, v.x); }
inline glm::ivec4 _aggr(const glm::ivec4& v) { return glm::ivec4(v.a, v.g, v.g, v.r); }
inline glm::ivec4 _wyyy(const glm::ivec4& v) { return glm::ivec4(v.w, v.y, v.y, v.y); }
inline glm::ivec4 _aggg(const glm::ivec4& v) { return glm::ivec4(v.a, v.g, v.g, v.g); }
inline glm::ivec4 _wyyz(const glm::ivec4& v) { return glm::ivec4(v.w, v.y, v.y, v.z); }
inline glm::ivec4 _aggb(const glm::ivec4& v) { return glm::ivec4(v.a, v.g, v.g, v.b); }
inline glm::ivec4 _wyyw(const glm::ivec4& v) { return glm::ivec4(v.w, v.y, v.y, v.w); }
inline glm::ivec4 _agga(const glm::ivec4& v) { return glm::ivec4(v.a, v.g, v.g, v.a); }
inline glm::ivec4 _wyzx(const glm::ivec4& v) { return glm::ivec4(v.w, v.y, v.z, v.x); }
inline glm::ivec4 _agbr(const glm::ivec4& v) { return glm::ivec4(v.a, v.g, v.b, v.r); }
inline glm::ivec4 _wyzy(const glm::ivec4& v) { return glm::ivec4(v.w, v.y, v.z, v.y); }
inline glm::ivec4 _agbg(const glm::ivec4& v) { return glm::ivec4(v.a, v.g, v.b, v.g); }
inline glm::ivec4 _wyzz(const glm::ivec4& v) { return glm::ivec4(v.w, v.y, v.z, v.z); }
inline glm::ivec4 _agbb(const glm::ivec4& v) { return glm::ivec4(v.a, v.g, v.b, v.b); }
inline glm::ivec4 _wyzw(const glm::ivec4& v) { return glm::ivec4(v.w, v.y, v.z, v.w); }
inline glm::ivec4 _agba(const glm::ivec4& v) { return glm::ivec4(v.a, v.g, v.b, v.a); }
inline glm::ivec4 _wywx(const glm::ivec4& v) { return glm::ivec4(v.w, v.y, v.w, v.x); }
inline glm::ivec4 _agar(const glm::ivec4& v) { return glm::ivec4(v.a, v.g, v.a, v.r); }
inline glm::ivec4 _wywy(const glm::ivec4& v) { return glm::ivec4(v.w, v.y, v.w, v.y); }
inline glm::ivec4 _agag(const glm::ivec4& v) { return glm::ivec4(v.a, v.g, v.a, v.g); }
inline glm::ivec4 _wywz(const glm::ivec4& v) { return glm::ivec4(v.w, v.y, v.w, v.z); }
inline glm::ivec4 _agab(const glm::ivec4& v) { return glm::ivec4(v.a, v.g, v.a, v.b); }
inline glm::ivec4 _wyww(const glm::ivec4& v) { return glm::ivec4(v.w, v.y, v.w, v.w); }
inline glm::ivec4 _agaa(const glm::ivec4& v) { return glm::ivec4(v.a, v.g, v.a, v.a); }
inline glm::ivec4 _wzxx(const glm::ivec4& v) { return glm::ivec4(v.w, v.z, v.x, v.x); }
inline glm::ivec4 _abrr(const glm::ivec4& v) { return glm::ivec4(v.a, v.b, v.r, v.r); }
inline glm::ivec4 _wzxy(const glm::ivec4& v) { return glm::ivec4(v.w, v.z, v.x, v.y); }
inline glm::ivec4 _abrg(const glm::ivec4& v) { return glm::ivec4(v.a, v.b, v.r, v.g); }
inline glm::ivec4 _wzxz(const glm::ivec4& v) { return glm::ivec4(v.w, v.z, v.x, v.z); }
inline glm::ivec4 _abrb(const glm::ivec4& v) { return glm::ivec4(v.a, v.b, v.r, v.b); }
inline glm::ivec4 _wzxw(const glm::ivec4& v) { return glm::ivec4(v.w, v.z, v.x, v.w); }
inline glm::ivec4 _abra(const glm::ivec4& v) { return glm::ivec4(v.a, v.b, v.r, v.a); }
inline glm::ivec4 _wzyx(const glm::ivec4& v) { return glm::ivec4(v.w, v.z, v.y, v.x); }
inline glm::ivec4 _abgr(const glm::ivec4& v) { return glm::ivec4(v.a, v.b, v.g, v.r); }
inline glm::ivec4 _wzyy(const glm::ivec4& v) { return glm::ivec4(v.w, v.z, v.y, v.y); }
inline glm::ivec4 _abgg(const glm::ivec4& v) { return glm::ivec4(v.a, v.b, v.g, v.g); }
inline glm::ivec4 _wzyz(const glm::ivec4& v) { return glm::ivec4(v.w, v.z, v.y, v.z); }
inline glm::ivec4 _abgb(const glm::ivec4& v) { return glm::ivec4(v.a, v.b, v.g, v.b); }
inline glm::ivec4 _wzyw(const glm::ivec4& v) { return glm::ivec4(v.w, v.z, v.y, v.w); }
inline glm::ivec4 _abga(const glm::ivec4& v) { return glm::ivec4(v.a, v.b, v.g, v.a); }
inline glm::ivec4 _wzzx(const glm::ivec4& v) { return glm::ivec4(v.w, v.z, v.z, v.x); }
inline glm::ivec4 _abbr(const glm::ivec4& v) { return glm::ivec4(v.a, v.b, v.b, v.r); }
inline glm::ivec4 _wzzy(const glm::ivec4& v) { return glm::ivec4(v.w, v.z, v.z, v.y); }
inline glm::ivec4 _abbg(const glm::ivec4& v) { return glm::ivec4(v.a, v.b, v.b, v.g); }
inline glm::ivec4 _wzzz(const glm::ivec4& v) { return glm::ivec4(v.w, v.z, v.z, v.z); }
inline glm::ivec4 _abbb(const glm::ivec4& v) { return glm::ivec4(v.a, v.b, v.b, v.b); }
inline glm::ivec4 _wzzw(const glm::ivec4& v) { return glm::ivec4(v.w, v.z, v.z, v.w); }
inline glm::ivec4 _abba(const glm::ivec4& v) { return glm::ivec4(v.a, v.b, v.b, v.a); }
inline glm::ivec4 _wzwx(const glm::ivec4& v) { return glm::ivec4(v.w, v.z, v.w, v.x); }
inline glm::ivec4 _abar(const glm::ivec4& v) { return glm::ivec4(v.a, v.b, v.a, v.r); }
inline glm::ivec4 _wzwy(const glm::ivec4& v) { return glm::ivec4(v.w, v.z, v.w, v.y); }
inline glm::ivec4 _abag(const glm::ivec4& v) { return glm::ivec4(v.a, v.b, v.a, v.g); }
inline glm::ivec4 _wzwz(const glm::ivec4& v) { return glm::ivec4(v.w, v.z, v.w, v.z); }
inline glm::ivec4 _abab(const glm::ivec4& v) { return glm::ivec4(v.a, v.b, v.a, v.b); }
inline glm::ivec4 _wzww(const glm::ivec4& v) { return glm::ivec4(v.w, v.z, v.w, v.w); }
inline glm::ivec4 _abaa(const glm::ivec4& v) { return glm::ivec4(v.a, v.b, v.a, v.a); }
inline glm::ivec4 _wwxx(const glm::ivec4& v) { return glm::ivec4(v.w, v.w, v.x, v.x); }
inline glm::ivec4 _aarr(const glm::ivec4& v) { return glm::ivec4(v.a, v.a, v.r, v.r); }
inline glm::ivec4 _wwxy(const glm::ivec4& v) { return glm::ivec4(v.w, v.w, v.x, v.y); }
inline glm::ivec4 _aarg(const glm::ivec4& v) { return glm::ivec4(v.a, v.a, v.r, v.g); }
inline glm::ivec4 _wwxz(const glm::ivec4& v) { return glm::ivec4(v.w, v.w, v.x, v.z); }
inline glm::ivec4 _aarb(const glm::ivec4& v) { return glm::ivec4(v.a, v.a, v.r, v.b); }
inline glm::ivec4 _wwxw(const glm::ivec4& v) { return glm::ivec4(v.w, v.w, v.x, v.w); }
inline glm::ivec4 _aara(const glm::ivec4& v) { return glm::ivec4(v.a, v.a, v.r, v.a); }
inline glm::ivec4 _wwyx(const glm::ivec4& v) { return glm::ivec4(v.w, v.w, v.y, v.x); }
inline glm::ivec4 _aagr(const glm::ivec4& v) { return glm::ivec4(v.a, v.a, v.g, v.r); }
inline glm::ivec4 _wwyy(const glm::ivec4& v) { return glm::ivec4(v.w, v.w, v.y, v.y); }
inline glm::ivec4 _aagg(const glm::ivec4& v) { return glm::ivec4(v.a, v.a, v.g, v.g); }
inline glm::ivec4 _wwyz(const glm::ivec4& v) { return glm::ivec4(v.w, v.w, v.y, v.z); }
inline glm::ivec4 _aagb(const glm::ivec4& v) { return glm::ivec4(v.a, v.a, v.g, v.b); }
inline glm::ivec4 _wwyw(const glm::ivec4& v) { return glm::ivec4(v.w, v.w, v.y, v.w); }
inline glm::ivec4 _aaga(const glm::ivec4& v) { return glm::ivec4(v.a, v.a, v.g, v.a); }
inline glm::ivec4 _wwzx(const glm::ivec4& v) { return glm::ivec4(v.w, v.w, v.z, v.x); }
inline glm::ivec4 _aabr(const glm::ivec4& v) { return glm::ivec4(v.a, v.a, v.b, v.r); }
inline glm::ivec4 _wwzy(const glm::ivec4& v) { return glm::ivec4(v.w, v.w, v.z, v.y); }
inline glm::ivec4 _aabg(const glm::ivec4& v) { return glm::ivec4(v.a, v.a, v.b, v.g); }
inline glm::ivec4 _wwzz(const glm::ivec4& v) { return glm::ivec4(v.w, v.w, v.z, v.z); }
inline glm::ivec4 _aabb(const glm::ivec4& v) { return glm::ivec4(v.a, v.a, v.b, v.b); }
inline glm::ivec4 _wwzw(const glm::ivec4& v) { return glm::ivec4(v.w, v.w, v.z, v.w); }
inline glm::ivec4 _aaba(const glm::ivec4& v) { return glm::ivec4(v.a, v.a, v.b, v.a); }
inline glm::ivec4 _wwwx(const glm::ivec4& v) { return glm::ivec4(v.w, v.w, v.w, v.x); }
inline glm::ivec4 _aaar(const glm::ivec4& v) { return glm::ivec4(v.a, v.a, v.a, v.r); }
inline glm::ivec4 _wwwy(const glm::ivec4& v) { return glm::ivec4(v.w, v.w, v.w, v.y); }
inline glm::ivec4 _aaag(const glm::ivec4& v) { return glm::ivec4(v.a, v.a, v.a, v.g); }
inline glm::ivec4 _wwwz(const glm::ivec4& v) { return glm::ivec4(v.w, v.w, v.w, v.z); }
inline glm::ivec4 _aaab(const glm::ivec4& v) { return glm::ivec4(v.a, v.a, v.a, v.b); }
inline glm::ivec4 _wwww(const glm::ivec4& v) { return glm::ivec4(v.w, v.w, v.w, v.w); }
inline glm::ivec4 _aaaa(const glm::ivec4& v) { return glm::ivec4(v.a, v.a, v.a, v.a); }

}

#endif