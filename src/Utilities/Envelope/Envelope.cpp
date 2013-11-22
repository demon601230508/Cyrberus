//
//  Envelope.cpp
//  jenMax
//
//  Created by Mitchell Nordine on 2/08/13.
//
//

#include "Envelope.h"

//--------------------------------------------------------------------------------//
// SETUP ENVELOPE
//--------------------------------------------------------------------------------//

void Envelope::setup()
{
    
    return;
    
}

//--------------------------------------------------------------------------------//
// RETURN VALUE @ RATIO
//--------------------------------------------------------------------------------//
// Returns associated value at ratio point.

double Envelope::getValue(double _ratio)
{
    
    ratio = _ratio;
    
    double value = 0.0, interpolation = 0.0, position = 0.0;
    int i=0;
    
    /* Iterate through to correct envelope point */
    for (i=0; i < points.size() && ratio >= points.at(i).time; i++){}
    
    /* Interpolate between points */
    interpolation = interpolate(points.at(i-1), points.at(i));
    
    /* Multiply interpolation by position and add onto previous point value */
    value = interpolation + points.at(i-1).value;
    
    return value;
    
}

//--------------------------------------------------------------------------------//
// INTERPOLATE BETWEEN POINTS
//--------------------------------------------------------------------------------//
// Interpolates via a bezier curve whose depth is defined by the pt.curve value.

double Envelope::interpolate(Pt start, Pt end)
{
    
    double position, duration, result;
    
    /* Find time passed from start of interpolation */
    position = ratio - start.time;
    
    /* Find duration of interpolation */
    duration = end.time - start.time;
    
    /* Set gradient for interpolation */
    algebraic.setup(position);
    algebraic.setGradient(duration, (end.value - start.value));
    
    /* Set bezier depth for interpolation via bezier curve */
    algebraic.setBezierDepth(start.curve);
    
    /* Add gradient and Bezier together */
    result = algebraic.getSignal();
    
    return result;
    
}

//--------------------------------------------------------------------------------//
// ADD POINT TO ENVELOPE
//--------------------------------------------------------------------------------//

void Envelope::addPoint(double time, double value, float curve)
{
    
    Pt pt;
    
    pt.setup(time, value, curve);
    
    points.push_back(pt);
    
    sortByPointTime();
    
    return;
    
}

void Envelope::addPoint(double time, double value)
{
    
    Pt pt;
    
    pt.setup(time, value, 0.0f);
    
    points.push_back(pt);
    
    sortByPointTime();
    
    return;
    
}

//--------------------------------------------------------------------------------//
// SORT POINTS BY TIME
//--------------------------------------------------------------------------------//

void Envelope::sortByPointTime()
{
    
    sort(points.begin(), points.end(), pointCompare);
    
    return;
    
}

//--------------------------------------------------------------------------------//
// COMPARE POINTS FUNCTION (FOR SORTING)
//--------------------------------------------------------------------------------//

bool pointCompare(Pt point1, Pt point2)
{
    
    return point1.time < point2.time;
    
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



