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
  #define CASADI_PREFIX(ID) ACADOS_model_cost_ext_cost_fun_jac_ ## ID
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

/* ACADOS_model_cost_ext_cost_fun_jac:(i0[10],i1[4],i2[],i3[22])->(o0,o1[14]) */
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
  a48=12.;
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
  a43=arg[1]? arg[1][0] : 0;
  a13=arg[3]? arg[3][10] : 0;
  a43=(a43-a13);
  a13=casadi_sq(a43);
  a56=arg[1]? arg[1][1] : 0;
  a21=arg[3]? arg[3][11] : 0;
  a56=(a56-a21);
  a21=casadi_sq(a56);
  a13=(a13+a21);
  a21=arg[1]? arg[1][2] : 0;
  a50=arg[3]? arg[3][12] : 0;
  a21=(a21-a50);
  a50=casadi_sq(a21);
  a13=(a13+a50);
  a50=arg[1]? arg[1][3] : 0;
  a57=arg[3]? arg[3][13] : 0;
  a50=(a50-a57);
  a57=casadi_sq(a50);
  a13=(a13+a57);
  a3=(a3+a13);
  if (res[0]!=0) res[0][0]=a3;
  a43=(a43+a43);
  if (res[1]!=0) res[1][0]=a43;
  a56=(a56+a56);
  if (res[1]!=0) res[1][1]=a56;
  a21=(a21+a21);
  if (res[1]!=0) res[1][2]=a21;
  a50=(a50+a50);
  if (res[1]!=0) res[1][3]=a50;
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
  a53=(a53*a42);
  a53=(a20*a53);
  a48=(a24*a53);
  a30=(a30*a42);
  a30=(a20*a30);
  a27=(a31*a30);
  a48=(a48-a27);
  a55=(a55*a42);
  a55=(a20*a55);
  a27=(a31*a55);
  a48=(a48+a27);
  a52=(a52*a42);
  a52=(a20*a52);
  a27=(a26*a52);
  a48=(a48-a27);
  a51=(a51*a42);
  a51=(a20*a51);
  a27=(a24*a51);
  a48=(a48-a27);
  a49=(a49*a42);
  a49=(a20*a49);
  a27=(a26*a49);
  a48=(a48+a27);
  a23=(a23+a45);
  a23=(a20*a23);
  a45=(a31*a23);
  a48=(a48-a45);
  a37=(a37+a38);
  a37=(a20*a37);
  a38=(a24*a37);
  a48=(a48+a38);
  a40=(a40+a41);
  a40=(a20*a40);
  a41=(a31*a40);
  a48=(a48+a41);
  a35=(a35+a36);
  a35=(a20*a35);
  a36=(a26*a35);
  a48=(a48-a36);
  a32=(a32+a34);
  a32=(a20*a32);
  a34=(a24*a32);
  a48=(a48-a34);
  a18=(a18+a29);
  a18=(a20*a18);
  a29=(a26*a18);
  a48=(a48+a29);
  if (res[1]!=0) res[1][10]=a48;
  a48=(a31+a31);
  a44=(a44*a42);
  a44=(a20*a44);
  a48=(a48*a44);
  a29=(a33*a30);
  a48=(a48-a29);
  a29=(a26*a53);
  a48=(a48-a29);
  a29=(a33*a55);
  a48=(a48+a29);
  a29=(a31+a31);
  a54=(a54*a42);
  a54=(a20*a54);
  a29=(a29*a54);
  a48=(a48+a29);
  a29=(a24*a52);
  a48=(a48-a29);
  a29=(a26*a51);
  a48=(a48-a29);
  a29=(a24*a49);
  a48=(a48-a29);
  a29=(a31+a31);
  a28=(a28+a47);
  a28=(a20*a28);
  a29=(a29*a28);
  a48=(a48+a29);
  a29=(a33*a23);
  a48=(a48-a29);
  a29=(a26*a37);
  a48=(a48-a29);
  a29=(a33*a40);
  a48=(a48+a29);
  a29=(a31+a31);
  a15=(a15+a39);
  a15=(a20*a15);
  a29=(a29*a15);
  a48=(a48+a29);
  a29=(a24*a35);
  a48=(a48-a29);
  a29=(a26*a32);
  a48=(a48-a29);
  a29=(a24*a18);
  a48=(a48-a29);
  if (res[1]!=0) res[1][11]=a48;
  a48=(a24+a24);
  a48=(a48*a44);
  a44=(a26*a30);
  a48=(a48-a44);
  a44=(a33*a53);
  a48=(a48+a44);
  a44=(a26*a55);
  a48=(a48-a44);
  a44=(a31*a52);
  a48=(a48-a44);
  a44=(a33*a51);
  a48=(a48-a44);
  a44=(a31*a49);
  a48=(a48-a44);
  a44=(a24+a24);
  a46=(a46*a42);
  a46=(a20*a46);
  a44=(a44*a46);
  a48=(a48+a44);
  a44=(a24+a24);
  a44=(a44*a28);
  a48=(a48+a44);
  a44=(a26*a23);
  a48=(a48-a44);
  a44=(a33*a37);
  a48=(a48+a44);
  a44=(a26*a40);
  a48=(a48-a44);
  a44=(a31*a35);
  a48=(a48-a44);
  a44=(a33*a32);
  a48=(a48-a44);
  a44=(a31*a18);
  a48=(a48-a44);
  a44=(a24+a24);
  a11=(a11+a22);
  a20=(a20*a11);
  a44=(a44*a20);
  a48=(a48+a44);
  if (res[1]!=0) res[1][12]=a48;
  a48=(a26+a26);
  a48=(a48*a54);
  a30=(a24*a30);
  a53=(a31*a53);
  a30=(a30+a53);
  a55=(a24*a55);
  a30=(a30+a55);
  a48=(a48-a30);
  a52=(a33*a52);
  a48=(a48-a52);
  a51=(a31*a51);
  a48=(a48-a51);
  a49=(a33*a49);
  a48=(a48+a49);
  a49=(a26+a26);
  a49=(a49*a46);
  a48=(a48+a49);
  a23=(a24*a23);
  a48=(a48-a23);
  a37=(a31*a37);
  a48=(a48-a37);
  a24=(a24*a40);
  a48=(a48-a24);
  a24=(a26+a26);
  a24=(a24*a15);
  a48=(a48+a24);
  a35=(a33*a35);
  a48=(a48-a35);
  a31=(a31*a32);
  a48=(a48-a31);
  a33=(a33*a18);
  a48=(a48+a33);
  a26=(a26+a26);
  a26=(a26*a20);
  a48=(a48+a26);
  if (res[1]!=0) res[1][13]=a48;
  return 0;
}

CASADI_SYMBOL_EXPORT int ACADOS_model_cost_ext_cost_fun_jac(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem){
  return casadi_f0(arg, res, iw, w, mem);
}

CASADI_SYMBOL_EXPORT int ACADOS_model_cost_ext_cost_fun_jac_alloc_mem(void) {
  return 0;
}

CASADI_SYMBOL_EXPORT int ACADOS_model_cost_ext_cost_fun_jac_init_mem(int mem) {
  return 0;
}

CASADI_SYMBOL_EXPORT void ACADOS_model_cost_ext_cost_fun_jac_free_mem(int mem) {
}

CASADI_SYMBOL_EXPORT int ACADOS_model_cost_ext_cost_fun_jac_checkout(void) {
  return 0;
}

CASADI_SYMBOL_EXPORT void ACADOS_model_cost_ext_cost_fun_jac_release(int mem) {
}

CASADI_SYMBOL_EXPORT void ACADOS_model_cost_ext_cost_fun_jac_incref(void) {
}

CASADI_SYMBOL_EXPORT void ACADOS_model_cost_ext_cost_fun_jac_decref(void) {
}

CASADI_SYMBOL_EXPORT casadi_int ACADOS_model_cost_ext_cost_fun_jac_n_in(void) { return 4;}

CASADI_SYMBOL_EXPORT casadi_int ACADOS_model_cost_ext_cost_fun_jac_n_out(void) { return 2;}

CASADI_SYMBOL_EXPORT casadi_real ACADOS_model_cost_ext_cost_fun_jac_default_in(casadi_int i){
  switch (i) {
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const char* ACADOS_model_cost_ext_cost_fun_jac_name_in(casadi_int i){
  switch (i) {
    case 0: return "i0";
    case 1: return "i1";
    case 2: return "i2";
    case 3: return "i3";
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const char* ACADOS_model_cost_ext_cost_fun_jac_name_out(casadi_int i){
  switch (i) {
    case 0: return "o0";
    case 1: return "o1";
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const casadi_int* ACADOS_model_cost_ext_cost_fun_jac_sparsity_in(casadi_int i) {
  switch (i) {
    case 0: return casadi_s0;
    case 1: return casadi_s1;
    case 2: return casadi_s2;
    case 3: return casadi_s3;
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT const casadi_int* ACADOS_model_cost_ext_cost_fun_jac_sparsity_out(casadi_int i) {
  switch (i) {
    case 0: return casadi_s4;
    case 1: return casadi_s5;
    default: return 0;
  }
}

CASADI_SYMBOL_EXPORT int ACADOS_model_cost_ext_cost_fun_jac_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w) {
  if (sz_arg) *sz_arg = 4;
  if (sz_res) *sz_res = 2;
  if (sz_iw) *sz_iw = 0;
  if (sz_w) *sz_w = 0;
  return 0;
}


#ifdef __cplusplus
} /* extern "C" */
#endif
