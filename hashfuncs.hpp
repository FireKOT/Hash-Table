#ifndef _HASHFUNCS_HPP_
#define _HASHFUNCS_HPP_


unsigned int hashZero      (const char *str);
unsigned int hashFirstChar (const char *str);
unsigned int hashStrLen    (const char *str);
unsigned int hashStrSum    (const char *str);
unsigned int hashRotr      (const char *str);
unsigned int hashRotl      (const char *str);
unsigned int hashCRC32     (const char *str);
unsigned int hashCRC32Fast (const char *str);


#endif