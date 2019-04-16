
./build.sh


mkdir -p ../isodir
mkdir -p ../isodir/boot



latestfile=$(find sysroot -type f | xargs ls -tr | tail -n 1)
echo $latestfile
# nur kopieren, wenn auch notwendig
if [ nanos.iso -ot $latestfile ]
then

    cp -u -r src/* ../isodir/boot
    cp -u ../kernel/build/kernel8.img ../isodir/boot/kernel8.img
    
    rm nanos.iso
    xorriso -x -outdev nanos.iso -blank as_needed -map ../isodir /
fi