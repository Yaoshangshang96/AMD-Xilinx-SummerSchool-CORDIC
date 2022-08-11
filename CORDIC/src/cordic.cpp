#include "cordic.h"

THETA_TYPE cordic_phase [16] = {
	    45, 26.56505118, 14.03624347, 7.125016349,
	    3.576334375, 1.789910608, 0.8951737102, 0.4476141709,
	    0.2238105004, 0.1119056771, 0.05595289189, 0.02797645262,
	    0.01398822714,0.006994113675, 0.003497056851, 0.001748528427
	};

void cordic(THETA_TYPE theta, COS_SIN_TYPE &s, COS_SIN_TYPE &c)
{
	#pragma HLS INTERFACE s_axilite port=theta
	#pragma HLS INTERFACE s_axilite port=s
	#pragma HLS INTERFACE s_axilite port=c
	#pragma HLS INTERFACE s_axilite port=return

	#pragma HLS ARRAY_PARTITION variable=cordic_phase dim=0
    // Set the initial vector that we will rotate
    // current cos = I; current sin = Q
    COS_SIN_TYPE current_cos = 0.60735;
    COS_SIN_TYPE current_sin = 0.0;

    // This loop iteratively rotates the initial vector to ﬁnd the
    // sine and cosine values corresponding to the input theta angle
    for (int j = 0; j < NUM_ITERATIONS; j++) {
        // Multiply previous iteration by 2ˆ(−j). This is equivalent to
        // a right shift by j on a ﬁxed−point number.
		#pragma HLS unroll
		COS_SIN_TYPE cos_shift = current_cos >> j;
        COS_SIN_TYPE sin_shift = current_sin >> j;

        // Determine if we are rotating by a positive or negative angle
        if(theta >= 0) {
            // Perform the rotation
            current_cos = current_cos - sin_shift;
            current_sin = current_sin + cos_shift;
            theta = theta - cordic_phase[j];

            // Determine the new theta theta = theta − cordic_phase[j];
        } else {
            // Perform the rotation
            current_cos = current_cos + sin_shift;
            current_sin = current_sin - cos_shift;

            // Determine the new theta
            theta = theta + cordic_phase[j];
        }
    }
    // Set the ﬁnal sine and cosine values
    s = current_sin;
    c = current_cos;
}
