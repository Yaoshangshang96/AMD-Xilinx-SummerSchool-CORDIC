#include <ap_fixed.h>

//NUM_ITERATIONS
#define NUM_ITERATIONS 16

typedef ap_fixed<28,8,AP_RND> THETA_TYPE;
//typedef float THETA_TYPE;

typedef ap_fixed<28,8,AP_RND> COS_SIN_TYPE;
//typedef double COS_SIN_TYPE;

void cordic(THETA_TYPE theta, COS_SIN_TYPE &s, COS_SIN_TYPE &c);
