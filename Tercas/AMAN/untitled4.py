#%matplotlib tk

import urllib.request
import json
import matplotlib.pyplot as plt
from matplotlib import animation
import cartopy.crs as ccrs
#import cartopy.io.img_tiles as cimg

# Define figure
#fig, ax = plt.subplots()
#
## Set axes for plotting area
#ax = plt.axes(projection=ccrs.PlateCarree())
##ax.set_ylim(40.6051, 40.6825)
##ax.set_xlim(-73.8288, -73.7258)
#ax.set_extent([40.6051, 40.6825, -73.8288, -73.7258])
#
## Add OSM basemap
##osm_tiles = OSM()
##osm = cimg.GoogleTiles(style="terrain")
#osm = cimg.StamenTerrain()
#ax.add_image(osm_tiles, 13) # zoom level 13
#
## Plot JFK Intl Airport
#ax.text(-73.778889, 40.639722, 'JFK Intl', horizontalalignment='right', size='large')
#ax.plot([-73.778889], [40.639722], 'bo') # plot a point in blue color
#
#plt.show()