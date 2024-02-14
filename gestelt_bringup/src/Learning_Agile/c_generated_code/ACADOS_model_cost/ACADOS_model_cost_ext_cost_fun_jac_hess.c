/* This file was automatically generated by CasADi.
   The CasADi copyright holders make no ownership claim of its contents. */
#ifdef __cplusplus
extern "C" {
#endif

/* How to prefix internal symbols */
#ifdef CASADI_CODEGEN_PREFIX
  #define CASADI_NAMESPACE_CONCAT(NS, ID) _CASADI_NAMESPACE_CONCAT(NS, ID)
  #define _CASADI_NAMESPACE_CONCAT(NS, ID) NS ## ID
  #define CASADI_PREFIX(ID) CASADI_NAMESPACE_CONCAT(CODEGEN_PREFIX, ID)
#else
  #define CASADI_PREFIX(ID) ACADOS_model_cost_ext_cost_fun_jac_hess_ ## ID
#endif

#include <math.h>

#ifndef casadi_real
#define casadi_real double
#endif

#ifndef casadi_int
#define casadi_int int
#endif

/* Add prefix to internal symbols */
#define casadi_f0 CASADI_PREFIX(f0)
#define casadi_s0 CASADI_PREFIX(s0)
#define casadi_s1 CASADI_PREFIX(s1)
#define casadi_s2 CASADI_PREFIX(s2)
#define casadi_s3 CASADI_PREFIX(s3)
#define casadi_s4 CASADI_PREFIX(s4)
#define casadi_s5 CASADI_PREFIX(s5)
#define casadi_s6 CASADI_PREFIX(s6)
#define casadi_s7 CASADI_PREFIX(s7)
#define casadi_sq CASADI_PREFIX(sq)

/* Symbol visibility in DLLs */
#ifndef CASADI_SYMBOL_EXPORT
  #if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
    #if defined(STATIC_LINKED)
      #define CASADI_SYMBOL_EXPORT
    #else
      #define CASADI_SYMBOL_EXPORT __declspec(dllexport)
    #endif
  #elif defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
    #define CASADI_SYMBOL_EXPORT __attribute__ ((visibility ("default")))
  #else
    #define CASADI_SYMBOL_EXPORT
  #endif
#endif

casadi_real casadi_sq(casadi_real x) { return x*x;}

static const casadi_int casadi_s0[14] = {10, 1, 0, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
static const casadi_int casadi_s1[8] = {4, 1, 0, 4, 0, 1, 2, 3};
static const casadi_int casadi_s2[3] = {0, 0, 0};
static const casadi_int casadi_s3[26] = {22, 1, 0, 22, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21};
static const casadi_int casadi_s4[5] = {1, 1, 0, 1, 0};
static const casadi_int casadi_s5[18] = {14, 1, 0, 14, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
static const casadi_int casadi_s6[39] = {14, 14, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 10, 14, 18, 22, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13, 10, 11, 12, 13};
static const casadi_int casadi_s7[17] = {0, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/* ACADOS_model_cost_ext_cost_fun_jac_hess:(i0[10],i1[4],i2[],i3[22])->(o0,o1[14],o2[14x14,22nz],o3[],o4[0x14]) */
static int casadi_f0(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem) {
  casadi_real a0, a1, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a2, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a3, a30, a31, a32, a33, a34, a35, a36, a37, a38, a39, a4, a40, a41, a42, a43, a44, a45, a46, a47, a48, a49, a5, a50, a51, a52, a53, a54, a55, a56, a57, a6, a7, a8, a9;
  a0=arg[0]? arg[0][0] : 0;
  a1=arg[3]? arg[3][0] : 0;
  a2=(a0-a1);
  a3=casadi_sq(a2);
  a4=arg[0]? arg[0][1] : 0;
  a5=arg[3]? arg[3][1] : 0;
  a6=(a4-a5);
  a7=casadi_sq(a6);
  a3=(a3+a7);
  a7=arg[0]? arg[0][2] : 0;
  a8=arg[3]? arg[3][2] : 0;
  a9=(a7-a8);
  a10=casadi_sq(a9);
  a3=(a3+a10);
  a10=arg[0]? arg[0][3] : 0;
  a11=arg[3]? arg[3][3] : 0;
  a12=(a10-a11);
  a13=casadi_sq(a12);
  a14=arg[0]? arg[0][4] : 0;
  a15=arg[3]? arg[3][4] : 0;
  a16=(a14-a15);
  a17=casadi_sq(a16);
  a13=(a13+a17);
  a17=arg[0]? arg[0][5] : 0;
  a18=arg[3]? arg[3][5] : 0;
  a19=(a17-a18);
  a20=casadi_sq(a19);
  a13=(a13+a20);
  a3=(a3+a13);
  a13=1.;
  a20=2.;
  a21=arg[3]? arg[3][8] : 0;
  a22=casadi_sq(a21);
  a23=arg[3]? arg[3][9] : 0;
  a24=casadi_sq(a23);
  a22=(a22+a24);
  a22=(a20*a22);
  a22=(a13-a22);
  a24=arg[0]? arg[0][8] : 0;
  a25=casadi_sq(a24);
  a26=arg[0]? arg[0][9] : 0;
  a27=casadi_sq(a26);
  a25=(a25+a27);
  a25=(a20*a25);
  a25=(a13-a25);
  a27=(a22*a25);
  a28=arg[3]? arg[3][7] : 0;
  a29=(a28*a21);
  a30=arg[3]? arg[3][6] : 0;
  a31=(a30*a23);
  a29=(a29-a31);
  a29=(a20*a29);
  a31=arg[0]? arg[0][7] : 0;
  a32=(a31*a24);
  a33=arg[0]? arg[0][6] : 0;
  a34=(a33*a26);
  a32=(a32-a34);
  a32=(a20*a32);
  a34=(a29*a32);
  a27=(a27+a34);
  a34=(a28*a23);
  a35=(a30*a21);
  a34=(a34+a35);
  a34=(a20*a34);
  a35=(a31*a26);
  a36=(a33*a24);
  a35=(a35+a36);
  a35=(a20*a35);
  a36=(a34*a35);
  a27=(a27+a36);
  a27=(a13-a27);
  a36=(a28*a21);
  a37=(a30*a23);
  a36=(a36+a37);
  a36=(a20*a36);
  a37=(a31*a24);
  a38=(a33*a26);
  a37=(a37+a38);
  a37=(a20*a37);
  a38=(a36*a37);
  a39=casadi_sq(a28);
  a40=casadi_sq(a23);
  a39=(a39+a40);
  a39=(a20*a39);
  a39=(a13-a39);
  a40=casadi_sq(a31);
  a41=casadi_sq(a26);
  a40=(a40+a41);
  a40=(a20*a40);
  a40=(a13-a40);
  a41=(a39*a40);
  a38=(a38+a41);
  a41=(a21*a23);
  a42=(a30*a28);
  a41=(a41-a42);
  a41=(a20*a41);
  a42=(a24*a26);
  a43=(a33*a31);
  a42=(a42-a43);
  a42=(a20*a42);
  a43=(a41*a42);
  a38=(a38+a43);
  a38=(a13-a38);
  a27=(a27+a38);
  a38=(a28*a23);
  a43=(a30*a21);
  a38=(a38-a43);
  a38=(a20*a38);
  a43=(a31*a26);
  a44=(a33*a24);
  a43=(a43-a44);
  a43=(a20*a43);
  a44=(a38*a43);
  a45=(a21*a23);
  a46=(a30*a28);
  a45=(a45+a46);
  a45=(a20*a45);
  a46=(a24*a26);
  a47=(a33*a31);
  a46=(a46+a47);
  a46=(a20*a46);
  a47=(a45*a46);
  a44=(a44+a47);
  a47=casadi_sq(a28);
  a48=casadi_sq(a21);
  a47=(a47+a48);
  a47=(a20*a47);
  a47=(a13-a47);
  a48=casadi_sq(a31);
  a49=casadi_sq(a24);
  a48=(a48+a49);
  a48=(a20*a48);
  a48=(a13-a48);
  a49=(a47*a48);
  a44=(a44+a49);
  a44=(a13-a44);
  a27=(a27+a44);
  a3=(a3+a27);
  a1=(a0-a1);
  a27=casadi_sq(a1);
  a5=(a4-a5);
  a44=casadi_sq(a5);
  a27=(a27+a44);
  a8=(a7-a8);
  a44=casadi_sq(a8);
  a27=(a27+a44);
  a10=(a10-a11);
  a11=casadi_sq(a10);
  a14=(a14-a15);
  a15=casadi_sq(a14);
  a11=(a11+a15);
  a17=(a17-a18);
  a18=casadi_sq(a17);
  a11=(a11+a18);
  a27=(a27+a11);
  a11=casadi_sq(a21);
  a18=casadi_sq(a23);
  a11=(a11+a18);
  a11=(a20*a11);
  a11=(a13-a11);
  a25=(a11*a25);
  a18=(a28*a21);
  a15=(a30*a23);
  a18=(a18-a15);
  a18=(a20*a18);
  a32=(a18*a32);
  a25=(a25+a32);
  a32=(a28*a23);
  a15=(a30*a21);
  a32=(a32+a15);
  a32=(a20*a32);
  a35=(a32*a35);
  a25=(a25+a35);
  a25=(a13-a25);
  a35=(a28*a21);
  a15=(a30*a23);
  a35=(a35+a15);
  a35=(a20*a35);
  a37=(a35*a37);
  a15=casadi_sq(a28);
  a44=casadi_sq(a23);
  a15=(a15+a44);
  a15=(a20*a15);
  a15=(a13-a15);
  a40=(a15*a40);
  a37=(a37+a40);
  a40=(a21*a23);
  a44=(a30*a28);
  a40=(a40-a44);
  a40=(a20*a40);
  a42=(a40*a42);
  a37=(a37+a42);
  a37=(a13-a37);
  a25=(a25+a37);
  a37=(a28*a23);
  a42=(a30*a21);
  a37=(a37-a42);
  a37=(a20*a37);
  a43=(a37*a43);
  a23=(a21*a23);
  a30=(a30*a28);
  a23=(a23+a30);
  a23=(a20*a23);
  a46=(a23*a46);
  a43=(a43+a46);
  a28=casadi_sq(a28);
  a21=casadi_sq(a21);
  a28=(a28+a21);
  a28=(a20*a28);
  a28=(a13-a28);
  a48=(a28*a48);
  a43=(a43+a48);
  a43=(a13-a43);
  a25=(a25+a43);
  a27=(a27+a25);
  a3=(a3+a27);
  a27=arg[3]? arg[3][21] : 0;
  a25=5.;
  a43=arg[3]? arg[3][14] : 0;
  a0=(a0-a43);
  a43=casadi_sq(a0);
  a48=arg[3]? arg[3][15] : 0;
  a4=(a4-a48);
  a48=casadi_sq(a4);
  a43=(a43+a48);
  a48=arg[3]? arg[3][16] : 0;
  a7=(a7-a48);
  a48=casadi_sq(a7);
  a43=(a43+a48);
  a43=(a25*a43);
  a48=8.;
  a21=arg[3]? arg[3][19] : 0;
  a46=casadi_sq(a21);
  a30=arg[3]? arg[3][20] : 0;
  a42=casadi_sq(a30);
  a46=(a46+a42);
  a46=(a20*a46);
  a46=(a13-a46);
  a42=casadi_sq(a24);
  a44=casadi_sq(a26);
  a42=(a42+a44);
  a42=(a20*a42);
  a42=(a13-a42);
  a42=(a46*a42);
  a44=arg[3]? arg[3][18] : 0;
  a49=(a44*a21);
  a50=arg[3]? arg[3][17] : 0;
  a51=(a50*a30);
  a49=(a49-a51);
  a49=(a20*a49);
  a51=(a31*a24);
  a52=(a33*a26);
  a51=(a51-a52);
  a51=(a20*a51);
  a51=(a49*a51);
  a42=(a42+a51);
  a51=(a44*a30);
  a52=(a50*a21);
  a51=(a51+a52);
  a51=(a20*a51);
  a52=(a31*a26);
  a53=(a33*a24);
  a52=(a52+a53);
  a52=(a20*a52);
  a52=(a51*a52);
  a42=(a42+a52);
  a42=(a13-a42);
  a52=(a44*a21);
  a53=(a50*a30);
  a52=(a52+a53);
  a52=(a20*a52);
  a53=(a31*a24);
  a54=(a33*a26);
  a53=(a53+a54);
  a53=(a20*a53);
  a53=(a52*a53);
  a54=casadi_sq(a44);
  a55=casadi_sq(a30);
  a54=(a54+a55);
  a54=(a20*a54);
  a54=(a13-a54);
  a55=casadi_sq(a31);
  a56=casadi_sq(a26);
  a55=(a55+a56);
  a55=(a20*a55);
  a55=(a13-a55);
  a55=(a54*a55);
  a53=(a53+a55);
  a55=(a21*a30);
  a56=(a50*a44);
  a55=(a55-a56);
  a55=(a20*a55);
  a56=(a24*a26);
  a57=(a33*a31);
  a56=(a56-a57);
  a56=(a20*a56);
  a56=(a55*a56);
  a53=(a53+a56);
  a53=(a13-a53);
  a42=(a42+a53);
  a53=(a44*a30);
  a56=(a50*a21);
  a53=(a53-a56);
  a53=(a20*a53);
  a56=(a31*a26);
  a57=(a33*a24);
  a56=(a56-a57);
  a56=(a20*a56);
  a56=(a53*a56);
  a30=(a21*a30);
  a50=(a50*a44);
  a30=(a30+a50);
  a30=(a20*a30);
  a50=(a24*a26);
  a57=(a33*a31);
  a50=(a50+a57);
  a50=(a20*a50);
  a50=(a30*a50);
  a56=(a56+a50);
  a44=casadi_sq(a44);
  a21=casadi_sq(a21);
  a44=(a44+a21);
  a44=(a20*a44);
  a44=(a13-a44);
  a21=casadi_sq(a31);
  a50=casadi_sq(a24);
  a21=(a21+a50);
  a21=(a20*a21);
  a21=(a13-a21);
  a21=(a44*a21);
  a56=(a56+a21);
  a13=(a13-a56);
  a42=(a42+a13);
  a13=casadi_sq(a42);
  a13=(a48*a13);
  a43=(a43+a13);
  a43=(a27*a43);
  a3=(a3+a43);
  if (res[0]!=0) res[0][0]=a3;
  a3=0.;
  if (res[1]!=0) res[1][0]=a3;
  if (res[1]!=0) res[1][1]=a3;
  if (res[1]!=0) res[1][2]=a3;
  if (res[1]!=0) res[1][3]=a3;
  a0=(a0+a0);
  a25=(a25*a27);
  a0=(a0*a25);
  a1=(a1+a1);
  a0=(a0+a1);
  a2=(a2+a2);
  a0=(a0+a2);
  if (res[1]!=0) res[1][4]=a0;
  a4=(a4+a4);
  a4=(a4*a25);
  a5=(a5+a5);
  a4=(a4+a5);
  a6=(a6+a6);
  a4=(a4+a6);
  if (res[1]!=0) res[1][5]=a4;
  a7=(a7+a7);
  a7=(a7*a25);
  a8=(a8+a8);
  a7=(a7+a8);
  a9=(a9+a9);
  a7=(a7+a9);
  if (res[1]!=0) res[1][6]=a7;
  a10=(a10+a10);
  a12=(a12+a12);
  a10=(a10+a12);
  if (res[1]!=0) res[1][7]=a10;
  a14=(a14+a14);
  a16=(a16+a16);
  a14=(a14+a16);
  if (res[1]!=0) res[1][8]=a14;
  a17=(a17+a17);
  a19=(a19+a19);
  a17=(a17+a19);
  if (res[1]!=0) res[1][9]=a17;
  a42=(a42+a42);
  a48=(a48*a27);
  a42=(a42*a48);
  a27=(a53*a42);
  a27=(a20*a27);
  a17=(a24*a27);
  a19=(a30*a42);
  a19=(a20*a19);
  a14=(a31*a19);
  a17=(a17-a14);
  a14=(a55*a42);
  a14=(a20*a14);
  a16=(a31*a14);
  a17=(a17+a16);
  a16=(a52*a42);
  a16=(a20*a16);
  a10=(a26*a16);
  a17=(a17-a10);
  a10=(a51*a42);
  a10=(a20*a10);
  a12=(a24*a10);
  a17=(a17-a12);
  a12=(a49*a42);
  a12=(a20*a12);
  a7=(a26*a12);
  a17=(a17+a7);
  a23=(a23+a45);
  a23=(a20*a23);
  a45=(a31*a23);
  a17=(a17-a45);
  a37=(a37+a38);
  a37=(a20*a37);
  a38=(a24*a37);
  a17=(a17+a38);
  a40=(a40+a41);
  a40=(a20*a40);
  a41=(a31*a40);
  a17=(a17+a41);
  a35=(a35+a36);
  a35=(a20*a35);
  a36=(a26*a35);
  a17=(a17-a36);
  a32=(a32+a34);
  a32=(a20*a32);
  a34=(a24*a32);
  a17=(a17-a34);
  a18=(a18+a29);
  a18=(a20*a18);
  a29=(a26*a18);
  a17=(a17+a29);
  if (res[1]!=0) res[1][10]=a17;
  a17=(a31+a31);
  a29=(a44*a42);
  a29=(a20*a29);
  a34=(a17*a29);
  a36=(a33*a19);
  a34=(a34-a36);
  a36=(a26*a27);
  a34=(a34-a36);
  a36=(a33*a14);
  a34=(a34+a36);
  a36=(a31+a31);
  a41=(a54*a42);
  a41=(a20*a41);
  a38=(a36*a41);
  a34=(a34+a38);
  a38=(a24*a16);
  a34=(a34-a38);
  a38=(a26*a10);
  a34=(a34-a38);
  a38=(a24*a12);
  a34=(a34-a38);
  a38=(a31+a31);
  a28=(a28+a47);
  a28=(a20*a28);
  a38=(a38*a28);
  a34=(a34+a38);
  a38=(a33*a23);
  a34=(a34-a38);
  a38=(a26*a37);
  a34=(a34-a38);
  a38=(a33*a40);
  a34=(a34+a38);
  a38=(a31+a31);
  a15=(a15+a39);
  a15=(a20*a15);
  a38=(a38*a15);
  a34=(a34+a38);
  a38=(a24*a35);
  a34=(a34-a38);
  a38=(a26*a32);
  a34=(a34-a38);
  a38=(a24*a18);
  a34=(a34-a38);
  if (res[1]!=0) res[1][11]=a34;
  a34=(a24+a24);
  a38=(a34*a29);
  a39=(a26*a19);
  a38=(a38-a39);
  a39=(a33*a27);
  a38=(a38+a39);
  a39=(a26*a14);
  a38=(a38-a39);
  a39=(a31*a16);
  a38=(a38-a39);
  a39=(a33*a10);
  a38=(a38-a39);
  a39=(a31*a12);
  a38=(a38-a39);
  a39=(a24+a24);
  a42=(a46*a42);
  a42=(a20*a42);
  a47=(a39*a42);
  a38=(a38+a47);
  a47=(a24+a24);
  a47=(a47*a28);
  a38=(a38+a47);
  a47=(a26*a23);
  a38=(a38-a47);
  a47=(a33*a37);
  a38=(a38+a47);
  a47=(a26*a40);
  a38=(a38-a47);
  a47=(a31*a35);
  a38=(a38-a47);
  a47=(a33*a32);
  a38=(a38-a47);
  a47=(a31*a18);
  a38=(a38-a47);
  a47=(a24+a24);
  a11=(a11+a22);
  a11=(a20*a11);
  a47=(a47*a11);
  a38=(a38+a47);
  if (res[1]!=0) res[1][12]=a38;
  a38=(a26+a26);
  a47=(a38*a41);
  a22=(a24*a19);
  a45=(a31*a27);
  a22=(a22+a45);
  a45=(a24*a14);
  a22=(a22+a45);
  a47=(a47-a22);
  a22=(a33*a16);
  a47=(a47-a22);
  a22=(a31*a10);
  a47=(a47-a22);
  a22=(a33*a12);
  a47=(a47+a22);
  a22=(a26+a26);
  a45=(a22*a42);
  a47=(a47+a45);
  a45=(a24*a23);
  a47=(a47-a45);
  a45=(a31*a37);
  a47=(a47-a45);
  a45=(a24*a40);
  a47=(a47-a45);
  a45=(a26+a26);
  a45=(a45*a15);
  a47=(a47+a45);
  a45=(a33*a35);
  a47=(a47-a45);
  a45=(a31*a32);
  a47=(a47-a45);
  a45=(a33*a18);
  a47=(a47+a45);
  a45=(a26+a26);
  a45=(a45*a11);
  a47=(a47+a45);
  if (res[1]!=0) res[1][13]=a47;
  a47=(a20*a25);
  a47=(a47+a20);
  a47=(a47+a20);
  if (res[2]!=0) res[2][0]=a47;
  a47=(a20*a25);
  a47=(a47+a20);
  a47=(a47+a20);
  if (res[2]!=0) res[2][1]=a47;
  a25=(a20*a25);
  a25=(a25+a20);
  a25=(a25+a20);
  if (res[2]!=0) res[2][2]=a25;
  a25=4.;
  if (res[2]!=0) res[2][3]=a25;
  if (res[2]!=0) res[2][4]=a25;
  if (res[2]!=0) res[2][5]=a25;
  a25=(a20*a24);
  a25=(a51*a25);
  a47=(a20*a26);
  a47=(a49*a47);
  a25=(a25-a47);
  a47=(a20*a26);
  a47=(a52*a47);
  a45=(a20*a31);
  a45=(a55*a45);
  a47=(a47-a45);
  a25=(a25+a47);
  a47=(a20*a31);
  a47=(a30*a47);
  a45=(a20*a24);
  a45=(a53*a45);
  a47=(a47-a45);
  a25=(a25+a47);
  a25=(a25+a25);
  a25=(a48*a25);
  a47=(a30*a25);
  a47=(a20*a47);
  a47=(a31*a47);
  a45=(a53*a25);
  a45=(a20*a45);
  a45=(a24*a45);
  a47=(a47-a45);
  a45=(a55*a25);
  a45=(a20*a45);
  a45=(a31*a45);
  a47=(a47-a45);
  a45=(a52*a25);
  a45=(a20*a45);
  a45=(a26*a45);
  a47=(a47+a45);
  a45=(a51*a25);
  a45=(a20*a45);
  a45=(a24*a45);
  a47=(a47+a45);
  a25=(a49*a25);
  a25=(a20*a25);
  a25=(a26*a25);
  a47=(a47-a25);
  if (res[2]!=0) res[2][6]=a47;
  a47=(a20*a24);
  a47=(a49*a47);
  a25=(a20*a26);
  a25=(a51*a25);
  a47=(a47+a25);
  a25=(a20*a24);
  a25=(a52*a25);
  a45=(a31+a31);
  a45=(a20*a45);
  a45=(a54*a45);
  a25=(a25-a45);
  a45=(a20*a33);
  a45=(a55*a45);
  a25=(a25-a45);
  a47=(a47+a25);
  a25=(a20*a26);
  a25=(a53*a25);
  a45=(a20*a33);
  a45=(a30*a45);
  a25=(a25+a45);
  a45=(a31+a31);
  a45=(a20*a45);
  a45=(a44*a45);
  a25=(a25-a45);
  a47=(a47+a25);
  a47=(a47+a47);
  a47=(a48*a47);
  a25=(a55*a47);
  a25=(a20*a25);
  a45=(a31*a25);
  a45=(a14-a45);
  a7=(a53*a47);
  a7=(a20*a7);
  a9=(a24*a7);
  a8=(a30*a47);
  a8=(a20*a8);
  a4=(a31*a8);
  a4=(a19-a4);
  a9=(a9+a4);
  a45=(a45-a9);
  a9=(a52*a47);
  a9=(a20*a9);
  a4=(a26*a9);
  a45=(a45+a4);
  a4=(a51*a47);
  a4=(a20*a4);
  a6=(a24*a4);
  a45=(a45+a6);
  a6=(a49*a47);
  a6=(a20*a6);
  a5=(a26*a6);
  a45=(a45-a5);
  a45=(a45-a23);
  a45=(a45+a40);
  if (res[2]!=0) res[2][7]=a45;
  a5=(a20*a31);
  a5=(a49*a5);
  a0=(a24+a24);
  a0=(a20*a0);
  a0=(a46*a0);
  a5=(a5-a0);
  a0=(a20*a33);
  a0=(a51*a0);
  a5=(a5+a0);
  a0=(a20*a31);
  a0=(a52*a0);
  a2=(a20*a26);
  a2=(a55*a2);
  a0=(a0+a2);
  a5=(a5+a0);
  a0=(a20*a26);
  a0=(a30*a0);
  a2=(a20*a33);
  a2=(a53*a2);
  a0=(a0-a2);
  a2=(a24+a24);
  a2=(a20*a2);
  a2=(a44*a2);
  a0=(a0-a2);
  a5=(a5+a0);
  a5=(a5+a5);
  a5=(a48*a5);
  a0=(a53*a5);
  a0=(a20*a0);
  a2=(a24*a0);
  a2=(a27-a2);
  a1=(a30*a5);
  a1=(a20*a1);
  a3=(a31*a1);
  a2=(a2+a3);
  a3=(a55*a5);
  a3=(a20*a3);
  a43=(a31*a3);
  a2=(a2-a43);
  a43=(a52*a5);
  a43=(a20*a43);
  a13=(a26*a43);
  a2=(a2+a13);
  a13=(a51*a5);
  a13=(a20*a13);
  a56=(a24*a13);
  a56=(a10-a56);
  a2=(a2-a56);
  a56=(a49*a5);
  a56=(a20*a56);
  a21=(a26*a56);
  a2=(a2-a21);
  a2=(a2+a37);
  a2=(a2-a32);
  if (res[2]!=0) res[2][8]=a2;
  a21=(a20*a31);
  a21=(a51*a21);
  a50=(a26+a26);
  a50=(a20*a50);
  a50=(a46*a50);
  a57=(a20*a33);
  a57=(a49*a57);
  a50=(a50+a57);
  a21=(a21-a50);
  a50=(a20*a33);
  a50=(a52*a50);
  a57=(a26+a26);
  a57=(a20*a57);
  a57=(a54*a57);
  a50=(a50-a57);
  a57=(a20*a24);
  a57=(a55*a57);
  a50=(a50+a57);
  a21=(a21+a50);
  a50=(a20*a31);
  a50=(a53*a50);
  a57=(a20*a24);
  a57=(a30*a57);
  a50=(a50+a57);
  a21=(a21+a50);
  a21=(a21+a21);
  a48=(a48*a21);
  a30=(a30*a48);
  a30=(a20*a30);
  a21=(a31*a30);
  a53=(a53*a48);
  a53=(a20*a53);
  a50=(a24*a53);
  a21=(a21-a50);
  a55=(a55*a48);
  a55=(a20*a55);
  a50=(a31*a55);
  a21=(a21-a50);
  a52=(a52*a48);
  a52=(a20*a52);
  a50=(a26*a52);
  a50=(a16-a50);
  a21=(a21-a50);
  a51=(a51*a48);
  a51=(a20*a51);
  a50=(a24*a51);
  a21=(a21+a50);
  a49=(a49*a48);
  a49=(a20*a49);
  a50=(a26*a49);
  a50=(a12-a50);
  a21=(a21+a50);
  a21=(a21-a35);
  a21=(a21+a18);
  if (res[2]!=0) res[2][9]=a21;
  if (res[2]!=0) res[2][10]=a45;
  a45=(a20*a29);
  a50=(a44*a47);
  a50=(a20*a50);
  a50=(a17*a50);
  a45=(a45-a50);
  a8=(a33*a8);
  a45=(a45+a8);
  a7=(a26*a7);
  a45=(a45+a7);
  a25=(a33*a25);
  a45=(a45-a25);
  a25=(a20*a41);
  a47=(a54*a47);
  a47=(a20*a47);
  a47=(a36*a47);
  a25=(a25-a47);
  a45=(a45+a25);
  a9=(a24*a9);
  a45=(a45+a9);
  a4=(a26*a4);
  a45=(a45+a4);
  a6=(a24*a6);
  a45=(a45+a6);
  a6=(a20*a28);
  a45=(a45+a6);
  a6=(a20*a15);
  a45=(a45+a6);
  if (res[2]!=0) res[2][11]=a45;
  a45=(a33*a1);
  a6=(a44*a5);
  a6=(a20*a6);
  a4=(a17*a6);
  a45=(a45-a4);
  a4=(a26*a0);
  a45=(a45+a4);
  a4=(a33*a3);
  a45=(a45-a4);
  a4=(a54*a5);
  a4=(a20*a4);
  a4=(a36*a4);
  a45=(a45-a4);
  a4=(a24*a43);
  a16=(a16-a4);
  a45=(a45-a16);
  a16=(a26*a13);
  a45=(a45+a16);
  a16=(a24*a56);
  a12=(a12-a16);
  a45=(a45-a12);
  a45=(a45-a35);
  a45=(a45-a18);
  if (res[2]!=0) res[2][12]=a45;
  a18=(a33*a30);
  a44=(a44*a48);
  a44=(a20*a44);
  a17=(a17*a44);
  a18=(a18-a17);
  a17=(a26*a53);
  a27=(a27-a17);
  a18=(a18-a27);
  a27=(a33*a55);
  a18=(a18-a27);
  a54=(a54*a48);
  a54=(a20*a54);
  a36=(a36*a54);
  a18=(a18-a36);
  a36=(a24*a52);
  a18=(a18+a36);
  a36=(a26*a51);
  a10=(a10-a36);
  a18=(a18-a10);
  a10=(a24*a49);
  a18=(a18+a10);
  a18=(a18-a37);
  a18=(a18-a32);
  if (res[2]!=0) res[2][13]=a18;
  if (res[2]!=0) res[2][14]=a2;
  if (res[2]!=0) res[2][15]=a45;
  a29=(a20*a29);
  a6=(a34*a6);
  a29=(a29-a6);
  a1=(a26*a1);
  a29=(a29+a1);
  a0=(a33*a0);
  a29=(a29-a0);
  a3=(a26*a3);
  a29=(a29+a3);
  a43=(a31*a43);
  a29=(a29+a43);
  a13=(a33*a13);
  a29=(a29+a13);
  a56=(a31*a56);
  a29=(a29+a56);
  a56=(a20*a42);
  a5=(a46*a5);
  a5=(a20*a5);
  a5=(a39*a5);
  a56=(a56-a5);
  a29=(a29+a56);
  a28=(a20*a28);
  a29=(a29+a28);
  a28=(a20*a11);
  a29=(a29+a28);
  if (res[2]!=0) res[2][16]=a29;
  a29=(a31*a52);
  a34=(a34*a44);
  a44=(a26*a30);
  a19=(a19-a44);
  a34=(a34+a19);
  a19=(a33*a53);
  a34=(a34+a19);
  a26=(a26*a55);
  a14=(a14-a26);
  a34=(a34+a14);
  a29=(a29-a34);
  a34=(a33*a51);
  a29=(a29+a34);
  a34=(a31*a49);
  a29=(a29+a34);
  a46=(a46*a48);
  a46=(a20*a46);
  a39=(a39*a46);
  a29=(a29-a39);
  a29=(a29-a23);
  a29=(a29-a40);
  if (res[2]!=0) res[2][17]=a29;
  if (res[2]!=0) res[2][18]=a21;
  if (res[2]!=0) res[2][19]=a18;
  if (res[2]!=0) res[2][20]=a29;
  a41=(a20*a41);
  a38=(a38*a54);
  a41=(a41-a38);
  a30=(a24*a30);
  a53=(a31*a53);
  a30=(a30+a53);
  a24=(a24*a55);
  a30=(a30+a24);
  a41=(a41+a30);
  a52=(a33*a52);
  a41=(a41+a52);
  a31=(a31*a51);
  a41=(a41+a31);
  a33=(a33*a49);
  a41=(a41-a33);
  a42=(a20*a42);
  a22=(a22*a46);
  a42=(a42-a22);
  a41=(a41+a42);
  a15=(a20*a15);
  a41=(a41+a15);
  a20=(a20*a11);
  a41=(a41+a20);
  if (res[2]!=0) res[2][21]=a41;
  return 0;
}

CASADI_SYMBOL_EXPORT int ACADOS_model_cost_ext_cost_fun_jac_hess(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem){
  return casadi_f0(arg, res, iw, w, mem);
}

CASADI_SYMBOL_EXPORT int ACADOS_model_cost_ext_cost_fun_jac_hess_alloc_mem(void) {
  return 0;
}

CASADI_SYMBOL_EXPORT int ACADOS_model_cost_ext_cost_fun_jac_hess_init_mem(int mem) {
  return 0;
}

CASADI_SYMBOL_EXPORT void ACADOS_model_cost_ext_cost_fun_jac_hess_free_mem(int mem) {
}

CASADI_SYMBOL_EXPORT int ACADOS_model_cost_ext_cost_fun_jac_hess_checkout(void) {
  return 0;
}

CASADI_SYMBOL_EXPORT void ACADOS_model_cost_ext_cost_fun_jac_hess_release(int mem) {
}

CASADI_SYMBOL_EXPORT void ACADOS_model_cost_ext_cost_fun_jac_hess_incref(void) {
}

CASADI_SYMBOL_EXPORT void ACADOS_model_cost_ext_cost_fun_jac_hess_decref(void) {
}

CASADI_SYMBOL_EXPORT casadi_int ACADOS_model_cost_ext_cost_fun_jac_hess_n_in(void) { return 4;}

CASADI_SYMBOL_EXPORT casadi_int ACADOS_model_cost_ext_cost_fun_jac_hess_n_out(void) { return 5;}

CASADI_SYMBOL_EXPORT casadi_real ACADOS_model_cost_ext_cost_fun_jac_hess_default_in(casadi_int i){
  switch (i) {
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const char* ACADOS_model_cost_ext_cost_fun_jac_hess_name_in(casadi_int i){
  switch (i) {
    case 0: return "i0";
    case 1: return "i1";
    case 2: return "i2";
    case 3: return "i3";
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const char* ACADOS_model_cost_ext_cost_fun_jac_hess_name_out(casadi_int i){
  switch (i) {
    case 0: return "o0";
    case 1: return "o1";
    case 2: return "o2";
    case 3: return "o3";
    case 4: return "o4";
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const casadi_int* ACADOS_model_cost_ext_cost_fun_jac_hess_sparsity_in(casadi_int i) {
  switch (i) {
    case 0: return casadi_s0;
    case 1: return casadi_s1;
    case 2: return casadi_s2;
    case 3: return casadi_s3;
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const casadi_int* ACADOS_model_cost_ext_cost_fun_jac_hess_sparsity_out(casadi_int i) {
  switch (i) {
    case 0: return casadi_s4;
    case 1: return casadi_s5;
    case 2: return casadi_s6;
    case 3: return casadi_s2;
    case 4: return casadi_s7;
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT int ACADOS_model_cost_ext_cost_fun_jac_hess_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w) {
  if (sz_arg) *sz_arg = 4;
  if (sz_res) *sz_res = 5;
  if (sz_iw) *sz_iw = 0;
  if (sz_w) *sz_w = 0;
  return 0;
}


#ifdef __cplusplus
} /* extern "C" */
#endif
