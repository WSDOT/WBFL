Angles, Directions and Stations {#WBFL_COGO_Angles_Directions_Stations}
================================

The WBFL COGO Library offers a very flexible format for specifing angles, 
 directions and stations. These items are typically passed into functions using a VARIANT. The VARIANT can have an Angle, Direction, or Station object, a floating point value, or a text string. 
 The tables below describe how to specify angles, directions and stations.

Text String Descriptions
----------------------------------------
Angles, directions, and stations can be described with text strings. The symbols in the descriptions that follow have specific meaning.

{} indicates optional elements of the string. For a bearing in DD-MM-SS format the string description is dd {mm {ss.s}}. The dd part is required and the mm and ss.s parts 
 are optional, but the mm part is required if the ss.s part is used.

[ ] indicates you must choose one from the list of items seperated by 
 |. In [N|S|n|s] you must select one of N, S, n, or s.
 
 {}, [], and | are not part of the text string.

Angle
------
<table>
<tr><th>Method       <th>Description                                                   <th>Example
<tr><td>Floating Point Value <td>A counter-clockwise angle, measured from the X axis, in radians <td>The angle is \f$\pi/4\f$ or 45\f$^\circ\f$ 00' 00" R<br>model.Locate.ByDistAngle(idNew,idFrom,idTo,dblDist,**0.785398**,dblOffset)
<tr><td>Angle Object         <td>An Angle object is used                                         <td>The angle is specified with an Angle object<br>model.Locate.ByDistAngle(idNew,idFrom,idTo,dblDist,**objAngle**,dblOffset)
<tr><td>Text String          <td>A text string in the one of the following formats: 
                                <ul>
								<li>{[+|-]}ddd.ddd
								<li>ddd.dd {[L|R|l|r]}
								<li>ddd mm ss.s {[L|R|l|r]}
								<li>{[+|-]}ddd mm ss.s
                                </ul>                                                            <td>The angle is specified with a text string<br>model.Locate.ByDistAngle(idNew,idFrom,idTo,dblDist, <b>"45 00 00 L"</b>,dblOffset)
</table>

Direction
---------
<table>
<tr><th>Method               <th> Description                                                                  <th> Example
<tr><td>Floating Point Value <td> A counter-clockwise angle, measured from the X axis, in radians              <td> The direction is \f$\pi/4\f$ or 45\f$^\circ\f$ 00' 00" R<br>model.Locate.ByDistDir(idNew,idFrom,idTo,dblDist,**0.785398**,dblOffset)
<tr><td>Direction Object     <td> A Direction object is used                                                   <td> The direction is specified with a Direction object<br>model.Locate.ByDistDir(idNew,idFrom,idTo,dblDist,**objDir**,dblOffset)
<tr><td>Text String          <td> A text string in the following format:<br>[N|S|n|s] dd {mm {ss.s}} [E|W|e|w] <td> The direction is specified with a text string<br>model.Locate.ByDistDir(idNew,idFrom,idTo,dblDist,<b>"N 45 00 00 E"</b>,dblOffset)
</table>

Station
--------
<table>
<tr><th>Method       <th>Description                                                   <th>Example
<tr><td>Floating Point Value <td>A value representing a station <td>point = alignment.LocatePoint(**125.25**,objDir)
<tr><td>Station Object         <td>A Station object is used     <td> point = alignment.LocatePoint(**objStation**,objDir)
<tr><td>Text String          <td>A text string in the one of the following formats: 
                                <ul>
								<li>{[+|-]}ddd.ddd
								<li>dd+dd{.dd} for US units
								<li>dd+ddd{.dd} for SI units
                                </ul>                            <td>point = alignment.LocatePoint(<b>"1+25.25"</b>, objDir)
</table>
