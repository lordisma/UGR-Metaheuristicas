#include <generador.h>

unsigned long Seed = 50627728;

#define MASK 2147483647
#define PRIME 65539
#define SCALE 0.4656612875e-9

unsigned long Get_random (void){
	return Seed;
}

float Rand(void){
    return ((Seed = ((Seed * PRIME) & MASK)) * SCALE );
}

float Randfloat(float low, float high){
	return (low + (high-(low))*Rand());
}

int Randint(int low, int high){
    return (int) (low + (high-(low)+1) * Rand());
}

void Set_random(unsigned long x){
	Seed = (unsigned long) x;
}
