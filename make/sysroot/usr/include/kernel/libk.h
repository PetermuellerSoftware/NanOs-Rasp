#ifndef LIBK_H
#define LIBK_H 1

#include <stddef.h>



/******************************************************
 * abort
 * 
 * beendet die Ausführung auf dem aktuellen Kern und
 * gibt den Kernel-Stack aus. 
 */
 
void abort ();





/******************************************************
 * size2str
 * 
 * wandelt die angegebene Größe in eine entsprechende
 * zeichenfolge als C-String um.
 * Es können die Einheiten Byte, KiB, GiB, TiB und PiB
 * erzeugt werden.
 * 
 * @size    Größe zur Umwandlung
 * @return: char[20], welcher die Zeichenfolge enthält
 */
char* size2str( size_t size);

#endif