Angles, Directions and Stations {#WBFL_COGO_Angles_Directions_Stations}
================================
The WBFL COGO Library offers a flexible format for specifying angles, directions and stations. These items can be defined with an Angle, Direction, or Station object, a floating point value, or a text string.

Text String Descriptions
----------------------------------------
Angles, directions, and stations can be described with text strings. The symbols in the descriptions that follow have specific meaning.

{} indicates optional elements of the string. For an angle in DD-MM-SS format the string description is dd {mm {ss.s}}. The dd part is required and the mm and ss.s parts 
 are optional, but the mm part is required if the ss.s part is used.

[ ] indicates you must choose one from the list of items separated by 
 |. In [N|S|n|s] you must select one of N, S, n, or s.
 
 {}, [], and | are not part of the text string.

Angle
------

### Floating Point Value

A counter-clockwise angle, measured from the X axis, in radians.

```
    cogoModel.LocateByDistanceAndAngle(idNew,idFrom,idTo,distance,0.785398,offset);
```

### Angle object
An Angle object is used.
```
    Angle angle(0.785398); 
    cogoModel.LocateByDistanceAndAngle(idNew,idFrom,idTo,distance,angle,offset);
```

### Text String
A text string in the one of the following formats:
* {[+|-]}ddd.ddd
* ddd.dd {[L|R|l|r]}
* ddd mm ss.s {[L|R|l|r]}
* {[+|-]}ddd mm ss.s 

```
    cogoModel.LocateByDistanceAndAngle(idNew,idFrom,idTo,distance,_T("45 00 00 R"),offset);
```


Direction
---------
### Floating Point Value
A counter-clockwise angle, measured from the X axis, in radians.

```
    cogoModel.LocateByDistanceAndDirection(idNew,idFrom,idTo,distance,0.785398,offset);
```

### Direction Object
A Direction object is used.

The direction is specified with a Direction object

```
    Direction direction(0.785398);
    cogoModel.LocateByDistanceAndDirection(idNew,idFrom,idTo,distance,direction,offset);
```

### Text String
A text string in the following format:
[N|S|n|s] dd {mm {ss.s}} [E|W|e|w].

```
    cogoModel.LocateByDistanceAndDirection(idNew,idFrom,idTo,distance,_T("N 45 00 00 E"),offset);
```

Station
--------

### Floating Point Value
A value representing a station 
```
    auto bearing = alignment.GetBearing(125.0);
```

### Station Object
A Station object is used
```
    Station station(125.0);
    auto bearing = alignment.GetBearing(station);
```

### Text String
A text string in the one of the following formats: 
* {[+|-]}ddd.ddd{,z}
* {[+|-]}dd+dd{.dd}{,z} for US units
* {[+|-]}dd+ddd{.dd}{,z} for SI units

The optional "z" parameter at the end of the station is the stationing zone index which is used in conjunction with station equations. In string format, stationing zone is a 1-based index because user's don't care to work with 0-based indices. The StationingZoneIndex property of the Station class is 0-based.

```
    Station station(_T("1+25.00"),WBFL::Units::StationFormats::US);
    auto bearing = alignment.GetBearing(station);
```



