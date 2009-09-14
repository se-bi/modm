
#include <math.h>

#include "angle.h"

// ----------------------------------------------------------------------------
// FIXME in eigne Datei verschieben

#include <stdint.h>

inline bool
is_positive(const float& a) {
	#ifdef __AVR__
	// IEEE 754-1985: the most significant bit is the sign bit
	// sign = 0 => positive
	// sign = 1 => negative
	uint8_t *t = (uint8_t *) &a;
	if (*(t + 3) & 0x80) {
		return false;
	}
	else {
		return true;
	}
	#else
	return (a > 0.0);
	#endif
}

// ----------------------------------------------------------------------------
void
Angle::normalize()
{
	if (is_positive(this->angle)) {
		while (this->angle > M_PI) {
			this->angle -= 2 * M_PI;
		}
	}
	else {
		while (this->angle < -M_PI) {
			this->angle += 2 * M_PI;
		}
	}
}

// ----------------------------------------------------------------------------
void
Angle::reverse() {
	if (is_positive(this->angle)) {
		this->angle -= M_PI;
	}
	else {
		this->angle += M_PI;
	}
}
