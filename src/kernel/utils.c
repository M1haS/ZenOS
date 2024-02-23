#include "kernel/utils.h"

void *memcpy(void *dest, const void *src, uint32_t count)
{
	const uint8_t *sp = (const uint8_t *) src;
	uint8_t	*dp	= (uint8_t *) dest;

	for (; count != 0; --count)
		*dp++ = *sp++;
	return dest;
}

void *memset(void *dest, uint8_t val, uint32_t count)
{
	uint8_t *temp = (uint8_t *) dest;

	for (; count != 0; --count)
		*temp++ = val;
	return dest;
}

uint16_t *memsetw(uint16_t *dest, uint16_t val, uint32_t count)
{
	uint16_t *temp = (uint16_t *) dest;

	for (; count != 0; --count)
		*temp++ = val;
	return dest;
}

int strlen(const char *str)
{
	int len;

	for (len = 0; *str; ++str)
		++len;
	return len;
}

int strcmp( const char *str1, const char *str2 )
{
	while (*str1 || *str2) {
		if (*str1 == *str2) {
			++str1;
			++str2;
		} else return(*str1 - *str2);
	}
	return 0;
}

char *strcpy(char *dest, const char *src)
{
	char *addr = dest;

	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return addr;
}

char *strcat(char *dest, const char *src)
{
	char *addr = dest;

	while (*dest)
		++dest;
	do
		*dest++ = *src++;
	while (*src);
	                  /* end by zero */
	return addr;
}

/* this function is case sensitive
 * return the substring, not index*/
char *strstr(const char *str, const char *search)
{
	char *p = (char *) search;

	while (*str) {
		while ((!*p) || *str == *p) {
			if (!*p)
				return (char *) str;
			++str;
			++p;
		}
		p = (char *) search;
		++str;
	}
	return NULL;
}

int strncmp(const char *str1, const char *str2, uint32_t n)
{
	while ((*str1 || *str2) && n > 0) {
		if ( *str1 == *str2 ) {
			++str1;
			++str2;
			--n;
		} else return(*str1 - *str2);
	}
	return 0;
}

char *strncpy(char *dest, const char *src, uint32_t n)
{
	char *addr = dest;

	while (*src && n > 0) {
		*dest++ = *src++;
		--n;
	}
	*dest = '\0';
	return addr;
}

void itoa(char *buf, int base, int d)
{
    char *p = buf;
    char *p1, *p2;
    uint32_t ud = d;
    int divisor = 10;

    /* If %d is specified and D is minus, put ‘-’ in the head. */
    if (base == 'd' && d < 0) {
        *p++ = '-';
        buf++;
        ud = -d;
    }
	else if (base == 'x')
        divisor = 16;

    /* Divide UD by DIVISOR until UD == 0. */
    do {
        int remainder = ud % divisor;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    } while (ud /= divisor);

    /* Terminate BUF. */
    *p = 0;

    /* Reverse BUF. */
    p1 = buf;
    p2 = p - 1;
    while (p1 < p2) {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        ++p1;
        --p2;
    }
}