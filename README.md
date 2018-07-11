# cvutil
### Example
<img src="res/window1.jpg" alt="Example" height="300" width="500"/>

## Algorithm briefly
<img src="res/imshows.jpg" alt="Example"/>
1. Get peaks on histogram
<br/> 2. Get binary threshold with darkest peak
<br/> 3. Get convex hull from threshold
<br/> 4. Distance transform on that hull and get location of brightest pixel (assume this is center)
<br/> 5. Rotate image 3 times around center and get average image (sum & divide it by 3 and threshold with ~.6 (where 2 of 3 rotations are white)
<br/> 6. convex hull on that and fit ellipse
<br/> 7. finding core is trivial to explain
