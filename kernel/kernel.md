@page Kernel
# Kernel

Struktur
--------

Die Kernel ist als Mikrokernel konzipiert. Um den zwangsläufig entstehenden Overhead in der 
Kommunikation zu begegnen ist ein effizientes Nachrichtensystem unerlässlich. Dieses hat
nach Fertigstellung der Grundlagen (virtueller Speicher, Interrupts) eine besonders hohe
Priorität.

Das Dateisystem soll dem von Linux nachempfunden werden. Dabei werden die Treiber für
FAT16/32 und ext4 im Kernel integriert, um ohne weitere Zwischenschritte alle anderen 
Komponenten nativ laden zu können.

