#ifndef INCLUDED_DRAWSUPPORTS_H_
#define INCLUDED_DRAWSUPPORTS_H_

// support size in twips
static const long SUPSIZE = 1440 *1/4;

void DrawGround(CDC* pDC, long cx, long cy, long wid, long hgt);
void DrawRollerSupport(CDC* pDC, long cx, long cy, long wid, long hgt);
void DrawFixedSupport(CDC* pDC, long cx, long cy, long wid, long hgt);
void DrawPinnedSupport(CDC* pDC, long cx, long cy, long wid, long hgt);
void DrawZeroLengthSupport(CDC* pDC, BoundaryConditionType ct, long cx, long cy, long wid, long hgt);



#endif