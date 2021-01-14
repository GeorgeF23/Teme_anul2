/* I included the AVX header for you */
#include <immintrin.h>
#include <math.h>
#include <stdio.h>

void f_vector_op(float *A, float *B, float *C, float *D, int n)
{
    float sum = 0;

    /* A * B; result stored in sum */
    for (int i = 0; i < n; i++)
        sum += A[i] * B[i];

    /* Computing D */
    for (int i = 0; i < n; i++)
        D[i] = sqrt(C[i]) + sum;
}

/*
    Calculeaza suma elementelor vectorului v
*/
float suma_m256(__m256 v)
{
    __m128 low = _mm256_castps256_ps128(v); // extrag primele 4 elemente
    __m128 high = _mm256_extractf128_ps(v, 1);  // extrag ultimele 4 elemente
    
    // Fac suma primelor 4 elemente
    low = _mm_hadd_ps(low, low);
    low = _mm_hadd_ps(low, low); 

    // Fac suma ultimelor 4 elemente
    high = _mm_hadd_ps(high, high);
    high = _mm_hadd_ps(high, high);

    return _mm_cvtss_f32(_mm_add_ps(low, high));    // Adun cele 2 sume si returnez doar primul element
}


void f_vector_op_avx(float *A, float *B, float *C, float *D, int n)
{
    float a_mul_b = 0;  // Suma finala

    for(int i = 0; i < n; i += 8){
        __m256 avx_A = _mm256_loadu_ps(A); // Incarc A
        __m256 avx_B = _mm256_loadu_ps(B); // Incarc B

        __m256 mul = _mm256_mul_ps(avx_A, avx_B); // A .* B
        float sum = suma_m256(mul); // A * B
        a_mul_b += sum;  // Adaug la suma finala
        A += 8; // Trec la urmatoarele 8 elemente
        B += 8;
    }

    __m256 sum_vector = _mm256_set1_ps(a_mul_b); // Scriu A * B * I(8)

    for(int i = 0; i < n; i += 8){
        __m256 avx_C = _mm256_loadu_ps(C); // Incarc C
        __m256 c_sqrt = _mm256_sqrt_ps(avx_C); // Calculez sqrt(C)
        _mm256_storeu_ps(D, _mm256_add_ps(sum_vector, c_sqrt)); // Salvez in D suma A * B * I(8) + sqrt(C)
        C += 8; // Trec la urmatoarele 8 elemente
        D += 8;
    }
}