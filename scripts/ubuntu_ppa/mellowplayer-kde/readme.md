1) Update changelog
2) Open package.sh and update version variable
3) Run package.sh, this will create source packages for all the supported
   version of ubuntu
   
If you need to add support for a new ubuntu release, just add the new release
name to the list of supported release (at the bottom of the file, look for 
the **for** loop).
